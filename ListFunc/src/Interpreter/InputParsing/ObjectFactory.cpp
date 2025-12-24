#include "ObjectFactory.h"
#include "Expression/Literal/Number/NumberLiteral.h"
#include "Expression/Literal/List/ListLiteral.h"
#include "Expression/Call/Function/FunctionCall.h"

#include "Function/Graph/GraphFunction.h"
#include "Function/Graph/Node/Argument/ArgumentNode.h"
#include "Function/Graph/Node/Literal/LiteralNode.h"
#include "Function/Graph/Node/Composite/CompositeNode.h"

#include "Interpreter/Environment/Environment.h"

#include "StringUtils/StringUtils.h"
#include "StringUtils/CharUtils.h"

#include <stdexcept>

ObjectFactory::ObjectFactory(std::vector<std::string> tokens, Environment& environment, size_t index)
    : tokens(std::move(tokens)), environment(&environment), index(index) {}

std::unique_ptr<Expression> ObjectFactory::createExpression() {
    assertIndex();

    if (StringUtils::isLetter(tokens[index].front())) {
        return createFunctionCall();
    }

    return createLiteral();
}

std::shared_ptr<Function> ObjectFactory::createFunction(const std::string& name, size_t argCount) {
    return createGraphFunction(name, argCount);
}

std::unique_ptr<Literal> ObjectFactory::createLiteral() {
    assertIndex();

    if (tokens[index] == "[") {
        return createListLiteral();
    } else if (StringUtils::isDigit(tokens[index].front()) || 
               StringUtils::isDash(tokens[index].front())) {
        return createNumberLiteral();
    }

    throw std::invalid_argument("invalid token for literal");
}

std::unique_ptr<NumberLiteral> ObjectFactory::createNumberLiteral() {
    double value = StringUtils::toDouble(tokens[index++]);
    return NumberLiteral::of(value);
}

std::unique_ptr<ListLiteral> ObjectFactory::createListLiteral() {
    index++;

    assertIndex();
    if (tokens[index] == "]") {
        index++;
        return std::make_unique<ListLiteral>();
    }

    auto list = std::make_unique<ListLiteral>();
    list->pushBack(createExpression());

    while (true) {
        assertIndex();

        if (tokens[index] == "]") {
            index++;
            return list;
        }

        if (tokens[index++] != ",") {
            throw std::invalid_argument("invalid token for list");
        }
        list->pushBack(createExpression());
    }
}

std::unique_ptr<FunctionCall> ObjectFactory::createFunctionCall() {
    std::string funcName = std::move(tokens[index++]);

    assertIndex();
    if (tokens[index++] != "(") {
        throw std::invalid_argument("function name must be followed by a circle bracket");
    }

    assertIndex();
    if (tokens[index] == ")") {
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

        if (tokens[index] == ")") {
            index++;
            auto func = environment->getFunction(funcName, args.size());
            if (!func) {
                throw std::invalid_argument("function <" + funcName + "(" +
                                            std::to_string(args.size()) + ")> is not defined");
            }

            return std::make_unique<FunctionCall>(func, std::move(args));
        }

        if (tokens[index++] != ",") {
            throw std::invalid_argument("function arguments must be separated by commas");
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

    if (tokens[index] == "$") {
        return createArgumentNode();
    } else if (StringUtils::isDigit(tokens[index].front()) || 
               StringUtils::isDash(tokens[index].front()) || 
               StringUtils::isOpenSquareBracket(tokens[index].front())) {
        return createLiteralNode();
    } else if (StringUtils::isLetter(tokens[index].front())) {
        return createCompositeNode();
    }

    throw std::invalid_argument("invalid token for function node");
}

std::unique_ptr<ArgumentNode> ObjectFactory::createArgumentNode() {
    index++;
    assertIndex();

    size_t id = StringUtils::toSizeType(tokens[index++]);
    argIds.insert(id);
    return ArgumentNode::of(id);
}

std::unique_ptr<LiteralNode> ObjectFactory::createLiteralNode() {
    return LiteralNode::of(createLiteral());
}

std::unique_ptr<CompositeNode> ObjectFactory::createCompositeNode() {
    std::string funcName = std::move(tokens[index++]);

    assertIndex();
    if (tokens[index++] != "(") {
        throw std::invalid_argument("function name must be followed by a circle bracket");
    }

    assertIndex();
    if (tokens[index] == ")") {
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

        if (tokens[index] == ")") {
            index++;
            auto func = environment->getFunction(funcName, argNodes.size());
            if (!func) {
                throw std::invalid_argument("function <" + funcName + "(" + 
                                            std::to_string(argNodes.size()) + ")> is not defined");
            }

            return std::make_unique<CompositeNode>(func, std::move(argNodes));
        }

        if (tokens[index++] != ",") {
            throw std::invalid_argument("function arguments must be separated by commas");
        }
        argNodes.push_back(createFunctionNode());
    }
}

void ObjectFactory::assertIndex() const {
    if (index >= tokens.size()) {
        throw std::invalid_argument("there are no more tokens");
    }
}
