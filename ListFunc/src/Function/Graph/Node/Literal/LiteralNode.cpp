#include "LiteralNode.h"
#include "Expression/Variable/Variable.h"

LiteralNode::LiteralNode(std::unique_ptr<Variable>&& variable) 
    : variable(std::move(variable)) {}

std::unique_ptr<Expression> LiteralNode::call(const std::vector<const Expression*>& args) const {
    return variable->cloneVariable();
}

std::unique_ptr<FunctionNode> LiteralNode::clone() const {
    return of(variable->cloneVariable());
}

const Variable& LiteralNode::getVariable() const {
    return *variable;
}

std::unique_ptr<LiteralNode> LiteralNode::of(std::unique_ptr<Variable>&& variable) {
    return std::make_unique<LiteralNode>(std::move(variable));
}
