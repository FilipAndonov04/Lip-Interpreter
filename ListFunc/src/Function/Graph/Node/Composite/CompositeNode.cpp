#include "CompositeNode.h"
#include "Expression/Variable/Variable.h"
#include "Expression/Call/Function/FunctionCall.h"

CompositeNode::CompositeNode(FunctionRef functionRef) 
    : functionRef(std::move(functionRef)) {}

CompositeNode::CompositeNode(FunctionRef functionRef,
                             std::vector<std::unique_ptr<FunctionNode>>&& argNodes) 
    : functionRef(std::move(functionRef)), argNodes(std::move(argNodes)) {}

std::unique_ptr<Expression> CompositeNode::call(const std::vector<const Expression*>& args) const {
    std::vector<std::unique_ptr<Expression>> refArgs;
    refArgs.reserve(argNodes.size());

    for (const auto& argNode : argNodes) {
        refArgs.push_back(argNode->call(args));
    }

    return std::make_unique<FunctionCall>(functionRef, std::move(refArgs));
}

std::unique_ptr<FunctionNode> CompositeNode::clone() const {
    std::vector<std::unique_ptr<FunctionNode>> clonedNodes;
    clonedNodes.reserve(argNodes.size());

    for (const auto& childNode : argNodes) {
        clonedNodes.push_back(childNode->clone());
    }

    return std::make_unique<CompositeNode>(functionRef, std::move(clonedNodes));
}

const FunctionRef& CompositeNode::getFunctionRef() const {
    return functionRef;
}

std::vector<const FunctionNode*> CompositeNode::getArgNodes() const {
    return std::vector<const FunctionNode*>();
}
