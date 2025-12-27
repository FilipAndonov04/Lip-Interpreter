#include "ExpressionNode.h"
#include "Expression/Expression.h"

ExpressionNode::ExpressionNode(std::unique_ptr<Expression>&& expression) 
    : expression(std::move(expression)) {}

std::unique_ptr<Expression> ExpressionNode::call(const std::vector<const Expression*>& args) const {
    return expression->clone();
}

std::unique_ptr<FunctionNode> ExpressionNode::clone() const {
    return of(expression->clone());
}

const Expression& ExpressionNode::getExpression() const {
    return *expression;
}

std::unique_ptr<ExpressionNode> ExpressionNode::of(std::unique_ptr<Expression>&& expression) {
    return std::make_unique<ExpressionNode>(std::move(expression));
}
