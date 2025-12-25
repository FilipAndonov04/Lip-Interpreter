#include "ObjectFactory.h"
#include "Expression/Literal/Number/NumberLiteral.h"
#include "Expression/Literal/List/ListLiteral.h"
#include "Expression/Literal/String/StringLiteral.h"
#include "Expression/Call/Function/FunctionCall.h"
#include "Function/Graph/GraphFunction.h"
#include "Function/Graph/Node/Argument/ArgumentNode.h"
#include "Function/Graph/Node/Literal/LiteralNode.h"
#include "Function/Graph/Node/Composite/CompositeNode.h"

#include "Interpreter/Environment/Environment.h"
#include "Interpreter/InputParsing/Tokenizer/Token.h"

#include "Utils/StringUtils.h"

#include <stdexcept>

ObjectFactory::ObjectFactory(std::vector<Token> tokens, Environment& environment, size_t index)
    : tokens(std::move(tokens)), environment(&environment), index(index) {}

std::unique_ptr<Expression> ObjectFactory::createExpression() {
    assertIndex();
    if (tokens[index].type == TokenType::Word) {
        return createFunctionCall();
    }

    return createLiteral();
}

std::shared_ptr<Function> ObjectFactory::createFunction(const std::string& name, size_t argCount) {
    return createGraphFunction(name, argCount);
}

std::unique_ptr<Literal> ObjectFactory::createLiteral() {
    assertIndex();

    if (tokens[index].type == TokenType::OpenSquareBracket) {
        return createListLiteral();
    } else if (tokens[index].type == TokenType::SingleQuote || 
               tokens[index].type == TokenType::DoubleQuote) {
        return createStringLiteral();
    } else if (tokens[index].type == TokenType::Number ||
               tokens[index].type == TokenType::Dash) {
        return createNumberLiteral();
    }

    throw std::invalid_argument("invalid token for literal");
}

std::unique_ptr<NumberLiteral> ObjectFactory::createNumberLiteral() {
    double value = Utils::toDouble(tokens[index++].payload);
    return NumberLiteral::of(value);
}

std::unique_ptr<ListLiteral> ObjectFactory::createListLiteral() {
    index++;

    assertIndex();
    if (tokens[index].type == TokenType::CloseSquareBracket) {
        index++;
        return std::make_unique<ListLiteral>();
    }

    std::vector<std::unique_ptr<Expression>> elements;
    elements.push_back(createExpression());

    while (true) {
        assertIndex();

        if (tokens[index].type == TokenType::CloseSquareBracket) {
            index++;
            return std::make_unique<ListLiteral>(std::move(elements));
        }

        if (tokens[index++].type != TokenType::Comma) {
            throw std::invalid_argument("list arguments must be separated by comma");
        }
        elements.push_back(createExpression());
    }
}

std::unique_ptr<StringLiteral> ObjectFactory::createStringLiteral() {
    TokenType quoteType = tokens[index].type;
    index++;

    assertIndex();
    if (tokens[index].type != TokenType::Text) {
        throw std::invalid_argument("invalid string token");
    }

    std::string string = std::move(tokens[index++].payload);

    assertIndex();
    if (tokens[index++].type != quoteType) {
        throw std::invalid_argument("string start quote must be the same as its end quote");
    }

    return StringLiteral::of(std::move(string));
}

std::unique_ptr<FunctionCall> ObjectFactory::createFunctionCall() {
    std::string funcName = std::move(tokens[index++].payload);

    assertIndex();
    if (tokens[index++].type != TokenType::OpenCircleBracket) {
        throw std::invalid_argument("function name must be followed by an open circle bracket");
    }

    assertIndex();
    if (tokens[index].type == TokenType::CloseCircleBracket) {
        index++;
        auto func = environment->getFunction(funcName, 0);
        if (!func) {
            throw std::invalid_argument("function <" + funcName + "(0)> is not defined");
        }

        return std::make_unique<FunctionCall>(func);
    }

    std::vector<std::unique_ptr<Expression>> args;
    args.push_back(createExpression());

    while (true) {
        assertIndex();

        if (tokens[index].type == TokenType::CloseCircleBracket) {
            index++;
            auto func = environment->getFunction(funcName, args.size());
            if (!func) {
                throw std::invalid_argument("function <" + funcName + "(" +
                                            std::to_string(args.size()) + ")> is not defined");
            }

            return std::make_unique<FunctionCall>(func, std::move(args));
        }

        if (tokens[index++].type != TokenType::Comma) {
            throw std::invalid_argument("function arguments must be separated by comma");
        }
        args.push_back(createExpression());
    }
}

std::shared_ptr<GraphFunction> ObjectFactory::createGraphFunction(const std::string& name, size_t argCount) {
    argIds.clear();

    auto func = std::make_shared<GraphFunction>(argCount);
    if (!environment->addFunction(name, func)) {
        throw std::invalid_argument("there is already a function <" + name + 
                                    "(" + std::to_string(argCount) + ")>");
    }

    auto root = createFunctionNode();
    if (argIds.size() != argCount || !argIds.empty() && 
        *std::max_element(argIds.begin(), argIds.end()) != argCount) {
        throw std::invalid_argument("invalid argument count in function definition");
    }

    func->setGraphRoot(std::move(root));
    return func;
}

std::unique_ptr<FunctionNode> ObjectFactory::createFunctionNode() {
    assertIndex();

    if (tokens[index].type == TokenType::Dolar) {
        return createArgumentNode();
    } else if (tokens[index].type == TokenType::Word) {
        return createCompositeNode();
    } else if (tokens[index].type == TokenType::Number ||
               tokens[index].type == TokenType::Dash ||
               tokens[index].type == TokenType::OpenSquareBracket) {
        return createLiteralNode();
    }

    throw std::invalid_argument("invalid function body token");
}

std::unique_ptr<ArgumentNode> ObjectFactory::createArgumentNode() {
    index++;
    assertIndex();

    size_t id = Utils::toSizeType(tokens[index++].payload);
    argIds.insert(id);
    return ArgumentNode::of(id);
}

std::unique_ptr<LiteralNode> ObjectFactory::createLiteralNode() {
    return LiteralNode::of(createLiteral());
}

std::unique_ptr<CompositeNode> ObjectFactory::createCompositeNode() {
    std::string funcName = std::move(tokens[index++].payload);

    assertIndex();
    if (tokens[index++].type != TokenType::OpenCircleBracket) {
        throw std::invalid_argument("function name must be followed by a circle bracket");
    }

    assertIndex();
    if (tokens[index].type == TokenType::CloseCircleBracket) {
        index++;
        auto func = environment->getFunction(funcName, 0);
        if (!func) {
            throw std::invalid_argument("function <" + funcName + "(0)> is not defined");
        }

        return std::make_unique<CompositeNode>(func);
    }

    std::vector<std::unique_ptr<FunctionNode>> argNodes;
    argNodes.push_back(createFunctionNode());

    while (true) {
        assertIndex();
        if (tokens[index].type == TokenType::CloseCircleBracket) {
            index++;
            auto func = environment->getFunction(funcName, argNodes.size());
            if (!func) {
                throw std::invalid_argument("function <" + funcName + "(" + 
                                            std::to_string(argNodes.size()) + ")> is not defined");
            }

            return std::make_unique<CompositeNode>(func, std::move(argNodes));
        }

        if (tokens[index++].type != TokenType::Comma) {
            throw std::invalid_argument("function arguments must be separated by comma");
        }
        argNodes.push_back(createFunctionNode());
    }
}

void ObjectFactory::assertIndex() const {
    if (index >= tokens.size()) {
        throw std::invalid_argument("there are no more tokens");
    }
}
