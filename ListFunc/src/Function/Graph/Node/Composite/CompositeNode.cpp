#include "CompositeNode.h"
#include "Function/Function.h"
#include "Expression/Call/Function/FunctionCall.h"

CompositeNode::CompositeNode(const Function* function)
    : function(function) {}

CompositeNode::CompositeNode(const Function* function,
                             std::vector<std::unique_ptr<FunctionNode>>&& argNodes) 
    : function(function), argNodes(std::move(argNodes)) {}

std::unique_ptr<Expression> CompositeNode::call(const std::vector<const Expression*>& args) const {
    std::vector<std::unique_ptr<Expression>> refArgs;
    refArgs.reserve(argNodes.size());

    for (const auto& argNode : argNodes) {
        refArgs.push_back(argNode->call(args));
    }

    return std::make_unique<FunctionCall>(function, std::move(refArgs));
}

std::unique_ptr<FunctionNode> CompositeNode::clone() const {
    std::vector<std::unique_ptr<FunctionNode>> clonedNodes;
    clonedNodes.reserve(argNodes.size());

    for (const auto& childNode : argNodes) {
        clonedNodes.push_back(childNode->clone());
    }

    return std::make_unique<CompositeNode>(function, std::move(clonedNodes));
}