#include "ObjectFactory.h"
#include "Expression/Literal/Number/NumberLiteral.h"
#include "Expression/Literal/List/ListLiteral.h"
#include "Expression/Literal/String/StringLiteral.h"
#include "Expression/FunctionCall/FunctionCall.h"
#include "Expression/Variable/VariableExpression.h"
#include "Expression/Value/ValueExpression.h"

#include "Function/Graph/GraphFunction.h"
#include "Function/Graph/Node/Leaf/Argument/ArgumentNode.h"
#include "Function/Graph/Node/Leaf/Expression/ExpressionNode.h"
#include "Function/Graph/Node/Composite/CompositeNode.h"

#include "Interpreter/Environment/Environment.h"
#include "Interpreter/InputParsing/Tokenizer/Token.h"

#include "Value/FunctionObject/FunctionObject.h"

#include "Utils/StringUtils.h"

#include <stdexcept>

ObjectFactory::ObjectFactory(std::vector<Token> tokens, Environment& environment, size_t index)
    : tokens(std::move(tokens)), environment(&environment), index(index) {}

std::unique_ptr<Expression> ObjectFactory::createExpression() {
    assertIndex(index);

    if (tokens[index].type == TokenType::Word && index != tokens.size() - 1 && 
        tokens[index + 1].type == TokenType::OpenCircleBracket) {
        return createFunctionCall();
    } else if (tokens[index].type == TokenType::Word) {
        return createVariableExpression();
    }

    return createLiteral();
}

std::shared_ptr<Function> ObjectFactory::createFunction(const std::string& name, size_t argCount) {
    return createGraphFunction(name, argCount);
}

size_t ObjectFactory::getCurrentIndex() const {
    return index;
}

std::unique_ptr<Literal> ObjectFactory::createLiteral() {
    assertIndex(index);

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
    int sign = 1;
    if (tokens[index].type == TokenType::Dash) {
        sign = -1;
        index++;
    }

    assertIndex(index);
    double value = Utils::toDouble(tokens[index++].payload);
    return NumberLiteral::of(value * sign);
}

std::unique_ptr<ListLiteral> ObjectFactory::createListLiteral() {
    index++;

    assertIndex(index);
    if (tokens[index].type == TokenType::CloseSquareBracket) {
        index++;
        return std::make_unique<ListLiteral>();
    }

    std::vector<std::unique_ptr<Expression>> elements;
    elements.push_back(createExpression());

    while (true) {
        assertIndex(index);

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

    assertIndex(index);
    if (tokens[index].type != TokenType::Text) {
        throw std::invalid_argument("invalid string token");
    }

    std::string string = std::move(tokens[index++].payload);

    assertIndex(index);
    if (tokens[index++].type != quoteType) {
        throw std::invalid_argument("string start quote must be the same as its end quote");
    }

    return StringLiteral::of(std::move(string));
}

std::unique_ptr<Expression> ObjectFactory::createVariableExpression() {
    auto var = environment->getVariableOrFunctionObject(tokens[index++].payload);
    if (!var) {
        throw std::invalid_argument("undefined variable");
    }

    return ValueExpression::of(std::move(var));
}

std::unique_ptr<FunctionCall> ObjectFactory::createFunctionCall() {
    std::string funcName = std::move(tokens[index++].payload);
    auto args = createFunctionCallArgs();
    auto func = createFunctionCallFunction(funcName, args.size());
    auto funcCall = std::make_unique<FunctionCall>(std::move(func), std::move(args));

    while (index < tokens.size() && 
           tokens[index].type == TokenType::OpenCircleBracket) {
        args = createFunctionCallArgs();
        funcCall = std::make_unique<FunctionCall>(std::move(funcCall), std::move(args));
    }

    return funcCall;
}

std::unique_ptr<Expression> ObjectFactory::createFunctionCallFunction(const std::string& funcName, 
                                                                      size_t argCount) {
    auto func = environment->getFunctionObject(funcName, argCount);
    if (!func) {
        throw std::invalid_argument("cannot make a call with a non function");
    }

    return ValueExpression::of(std::move(func));
}

std::vector<std::unique_ptr<Expression>> ObjectFactory::createFunctionCallArgs() {
    assertCurrentIndex();
    assertCurrentTokenType(TokenType::OpenCircleBracket, 
                           "function args are not surounded by circle brackets");
    
    std::vector<std::unique_ptr<Expression>> args;

    index++;
    assertCurrentIndex();
    if (tokens[index].type == TokenType::CloseCircleBracket) {
        index++;
        return args;
    }

    args.push_back(createExpression());

    while (true) {
        assertCurrentIndex();
        if (tokens[index].type == TokenType::CloseCircleBracket) {
            index++;
            return args;
        }

        assertCurrentTokenType(TokenType::Comma, "function args are not separated by commas");
        index++;

        args.push_back(createExpression());
    }
}

std::shared_ptr<GraphFunction> ObjectFactory::createGraphFunction(const std::string& name, size_t argCount) {
    argIds.clear();

    auto func = std::make_shared<GraphFunction>(argCount);
    if (!environment->addFunction(name, func)) {
        throw std::invalid_argument("adding function failed");
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
    assertIndex(index);

    if (tokens[index].type == TokenType::Word && index != tokens.size() - 1 && 
        tokens[index + 1].type == TokenType::OpenCircleBracket || 
        tokens[index].type == TokenType::Dolar && index < tokens.size() - 2 &&
        tokens[index + 2].type == TokenType::OpenCircleBracket) {
        return createCompositeNode();
    }

    return createLeafNode();
}

std::unique_ptr<LeafNode> ObjectFactory::createLeafNode() {
    assertIndex(index);

    if (tokens[index].type == TokenType::Dolar) {
        return createArgumentNode();
    } else if (tokens[index].type == TokenType::Number ||
               tokens[index].type == TokenType::Dash ||
               tokens[index].type == TokenType::SingleQuote ||
               tokens[index].type == TokenType::DoubleQuote ||
               tokens[index].type == TokenType::OpenSquareBracket ||
               tokens[index].type == TokenType::Word) {
        return createExpressionNode();
    }

    throw std::invalid_argument("invalid function body token");
}

std::unique_ptr<ArgumentNode> ObjectFactory::createArgumentNode() {
    index++;
    assertIndex(index);

    size_t id = Utils::toSizeType(tokens[index++].payload);
    argIds.insert(id);
    return ArgumentNode::of(id);
}

std::unique_ptr<ExpressionNode> ObjectFactory::createExpressionNode() {
    return ExpressionNode::of(createExpressionNoFuncCall());
}

std::unique_ptr<CompositeNode> ObjectFactory::createCompositeNode() {
    auto functionNode = createLeafNode();

    assertIndex(index);
    if (tokens[index++].type != TokenType::OpenCircleBracket) {
        throw std::invalid_argument("function name must be followed by a circle bracket");
    }

    assertIndex(index);
    if (tokens[index].type == TokenType::CloseCircleBracket) {
        index++;
        return std::make_unique<CompositeNode>(std::move(functionNode));
    }

    std::vector<std::unique_ptr<FunctionNode>> argNodes;
    argNodes.push_back(createFunctionNode());

    while (true) {
        assertIndex(index);
        if (tokens[index].type == TokenType::CloseCircleBracket) {
            index++;
            return std::make_unique<CompositeNode>(std::move(functionNode), std::move(argNodes));
        }

        if (tokens[index++].type != TokenType::Comma) {
            throw std::invalid_argument("function arguments must be separated by comma");
        }
        argNodes.push_back(createFunctionNode());
    }
}

std::unique_ptr<Expression> ObjectFactory::createExpressionNoFuncCall() {
    assertIndex(index);

    if (tokens[index].type == TokenType::Word) {
        return createVariableExpression();
    }

    return createLiteral();
}

size_t ObjectFactory::getCloseCircleBracketIndex(size_t index) {
    size_t openBrackets = 1;
    while (index < tokens.size() && openBrackets != 0) {
        if (tokens[index].type == TokenType::OpenCircleBracket) {
            openBrackets++;
        } else if (tokens[index].type == TokenType::CloseCircleBracket) {
            openBrackets--;
        }

        index++;
    }

    if (openBrackets == 0) {
        return index - 1;
    }
    return index;
}

void ObjectFactory::assertIndex(size_t index) const {
    if (index >= tokens.size()) {
        throw std::invalid_argument("there are no more tokens");
    }
}

void ObjectFactory::assertCurrentIndex() const {
    assertIndex(index);
}

void ObjectFactory::assertTokenType(size_t index, TokenType type) {
    assertTokenType(index, type, "invalid token type at index" + std::to_string(index));
}

void ObjectFactory::assertTokenType(size_t index, TokenType type, const std::string& errorMessage) {
    assertTokenType(index, type, errorMessage.c_str());
}

void ObjectFactory::assertTokenType(size_t index, TokenType type, const char* errorMessage) {
    if (tokens[index].type != type) {
        throw std::invalid_argument(errorMessage);
    }
}

void ObjectFactory::assertCurrentTokenType(TokenType type) {
    assertTokenType(index, type);
}

void ObjectFactory::assertCurrentTokenType(TokenType type, const std::string& errorMessage) {
    assertTokenType(index, type, errorMessage);
}

void ObjectFactory::assertCurrentTokenType(TokenType type, const char* errorMessage) {
    assertTokenType(index, type, errorMessage);
}
