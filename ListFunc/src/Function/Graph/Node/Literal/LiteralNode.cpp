#include "LiteralNode.h"
#include "Expression/Literal/Literal.h"

LiteralNode::LiteralNode(std::unique_ptr<Literal>&& literal) 
    : literal(std::move(literal)) {}

std::unique_ptr<Expression> LiteralNode::call(const std::vector<const Expression*>& args) const {
    return literal->cloneLiteral();
}

std::unique_ptr<FunctionNode> LiteralNode::clone() const {
    return of(literal->cloneLiteral());
}

const Literal& LiteralNode::getLiteral() const {
    return *literal;
}

std::unique_ptr<LiteralNode> LiteralNode::of(std::unique_ptr<Literal>&& literal) {
    return std::make_unique<LiteralNode>(std::move(literal));
}
