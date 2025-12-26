#include "CompositeNode.h"
#include "Function/Function.h"
#include "Expression/FunctionCall/FunctionCall.h"

CompositeNode::CompositeNode(std::unique_ptr<FunctionNode>&& functionNode)
    : functionNode(std::move(functionNode)) {}

CompositeNode::CompositeNode(std::unique_ptr<FunctionNode>&& functionNode,
                             std::vector<std::unique_ptr<FunctionNode>>&& argNodes) 
    : functionNode(std::move(functionNode)), argNodes(std::move(argNodes)) {}

std::unique_ptr<Expression> CompositeNode::call(const std::vector<const Expression*>& args) const {
    std::vector<std::unique_ptr<Expression>> argNodeRes;
    argNodeRes.reserve(argNodes.size());

    for (const auto& argNode : argNodes) {
        argNodeRes.push_back(argNode->call(args));
    }

    auto functionNodeRes = functionNode->call(args);
    return std::make_unique<FunctionCall>(std::move(functionNodeRes), std::move(argNodeRes));
}

std::unique_ptr<FunctionNode> CompositeNode::clone() const {
    std::vector<std::unique_ptr<FunctionNode>> clonedNodes;
    clonedNodes.reserve(argNodes.size());

    for (const auto& childNode : argNodes) {
        clonedNodes.push_back(childNode->clone());
    }

    return std::make_unique<CompositeNode>(functionNode->clone(), std::move(clonedNodes));
}