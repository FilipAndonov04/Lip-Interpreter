#include "ArgumentNode.h"
#include "Expression/Expression.h"

ArgumentNode::ArgumentNode(size_t argId)
    : argId(argId) {}

std::unique_ptr<Expression> ArgumentNode::call(const std::vector<const Expression*>& args) const {
    return args[argId - 1]->cloneExpression();
}

std::unique_ptr<FunctionNode> ArgumentNode::clone() const {
    return of(argId);
}

size_t ArgumentNode::getArgId() const {
    return argId;
}

std::unique_ptr<ArgumentNode> ArgumentNode::of(size_t argId) {
    return std::make_unique<ArgumentNode>(argId);
}
