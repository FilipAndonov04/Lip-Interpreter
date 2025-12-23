#include "ObjectFactory.h"
#include "Expression/Variable/Number/Real/RealNumber.h"
#include "Expression/Variable/List/Concrete/ConcreteList.h"
#include "Function/Graph/GraphFunction.h"
#include "Function/Graph/Node/FunctionNode.h"

#include "StringUtils/StringUtils.h"
#include "StringUtils/CharUtils.h"

#include <stdexcept>

ObjectFactory::ObjectFactory(std::vector<std::string> tokens, const VariableSet& variableSet)
    : tokens(std::move(tokens)), variableSet(&variableSet) {}

std::unique_ptr<Expression> ObjectFactory::createExpression() {
    assertIndex();

    if (StringUtils::isLetter(tokens[index].front())) {
        return createFunctionCall();
    }

    return createVariable();
}

std::unique_ptr<Variable> ObjectFactory::createVariable() {
    assertIndex();

    if (StringUtils::isDigit(tokens[index].front()) || StringUtils::isDash(tokens[index].front())) {
        return createRealNumber();
    } else if (tokens[index] == "[") {
        return createConcreteList();
    }

    throw std::runtime_error("invalid token for variable");
}

std::unique_ptr<Function> ObjectFactory::createFunction() {
    return std::unique_ptr<Function>();
}

std::unique_ptr<RealNumber> ObjectFactory::createRealNumber() {
    double value = StringUtils::toDouble(tokens[index++]);
    return RealNumber::of(value);
}

std::unique_ptr<ConcreteList> ObjectFactory::createConcreteList() {
    index++;

    assertIndex();
    if (tokens[index] == "]") {
        index++;
        return std::make_unique<ConcreteList>();
    }

    auto list = std::make_unique<ConcreteList>();
    list->pushBack(Expression::evaluate(createExpression()));

    while (true) {
        assertIndex();

        if (tokens[index] == "]") {
            index++;
            return list;
        }

        if (tokens[index++] != ",") {
            throw std::runtime_error("invalid token for list");
        }
        list->pushBack(Expression::evaluate(createExpression()));
    }
}

std::unique_ptr<FunctionCall> ObjectFactory::createFunctionCall() {
    std::string functionName = std::move(tokens[index++]);

    assertIndex();
    if (tokens[index++] != "(") {
        throw std::runtime_error("invalid token for function call");
    }

    assertIndex();
    if (tokens[index] == ")") {
        index++;
        return std::make_unique<FunctionCall>(FunctionRef{std::move(functionName), 0, *variableSet});
    }

    std::vector<std::unique_ptr<Expression>> args;
    args.push_back(createExpression());

    while (true) {
        assertIndex();

        if (tokens[index] == ")") {
            index++;
            return std::make_unique<FunctionCall>(FunctionRef{std::move(functionName), 
                                                  args.size(), *variableSet}, std::move(args));
        }

        if (tokens[index++] != ",") {
            throw std::runtime_error("invalid token for function call");
        }
        args.push_back(createExpression());
    }
}

std::unique_ptr<GraphFunction> ObjectFactory::createGraphFunction() {
    return std::unique_ptr<GraphFunction>();
}

std::unique_ptr<FunctionNode> ObjectFactory::createFunctionNode() {
    throw std::runtime_error("invalid line");
}

std::unique_ptr<ArgumentNode> ObjectFactory::createArgumentNode() {
    return ArgumentNode::of(0);
}

std::unique_ptr<LiteralNode> ObjectFactory::createLiteralNode() {
    return LiteralNode::of(createVariable());
}

std::unique_ptr<CompositeNode> ObjectFactory::createCompositeNode() {
    return std::unique_ptr<CompositeNode>();
}

void ObjectFactory::assertIndex() const {
    if (index >= tokens.size()) {
        throw std::runtime_error("there are no more tokens");
    }
}
