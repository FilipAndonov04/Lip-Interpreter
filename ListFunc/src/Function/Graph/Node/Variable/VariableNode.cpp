#include "VariableNode.h"

VariableNode::VariableNode(VariableRef variableRef) 
    : variableRef(std::move(variableRef)) {}

std::unique_ptr<Expression> VariableNode::call(const std::vector<const Expression*>& args) const {
    return variableRef->cloneVariable();
}

std::unique_ptr<FunctionNode> VariableNode::clone() const {
    return of(variableRef);
}

const VariableRef& VariableNode::getVariableRef() const {
    return variableRef;
}

std::unique_ptr<VariableNode> VariableNode::of(VariableRef variableRef) {
    return std::make_unique<VariableNode>(std::move(variableRef));
}
