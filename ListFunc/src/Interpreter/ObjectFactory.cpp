#include "ObjectFactory.h"
#include "Expression/Variable/Number/Real/RealNumber.h"
#include "Expression/Variable/List/Concrete/ConcreteList.h"
#include "Function/Graph/GraphFunction.h"
#include "Function/Graph/Node/FunctionNode.h"

#include <stdexcept>

ObjectFactory::ObjectFactory(const std::vector<std::string>& tokens) 
    : tokens(tokens) {}

ObjectFactory::ObjectFactory(std::vector<std::string>&& tokens) 
    : tokens(tokens) {}

std::unique_ptr<Expression> ObjectFactory::createExpression() {
    return std::unique_ptr<Expression>();
}

std::unique_ptr<Variable> ObjectFactory::createVariable() {
    throw std::runtime_error("invalid line");
}

std::unique_ptr<Function> ObjectFactory::createFunction() {
    return std::unique_ptr<Function>();
}

std::unique_ptr<FunctionNode> ObjectFactory::createFunctionNode() {
    throw std::runtime_error("invalid line");
}

std::unique_ptr<RealNumber> ObjectFactory::createRealNumber() {
    return RealNumber::of(-1);
}

std::unique_ptr<ConcreteList> ObjectFactory::createConcreteList() {
    return std::unique_ptr<ConcreteList>();
}

std::unique_ptr<FunctionCall> ObjectFactory::createFunctionCall() {
    return std::unique_ptr<FunctionCall>();
}

std::unique_ptr<GraphFunction> ObjectFactory::createGraphFunction() {
    return std::unique_ptr<GraphFunction>();
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