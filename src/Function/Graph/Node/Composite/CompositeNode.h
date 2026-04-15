#pragma once
#include "Function/Graph/Node/FunctionNode.h"

class CompositeNode final : public FunctionNode {
public:
	explicit CompositeNode(std::unique_ptr<FunctionNode>&& functionNode);
	CompositeNode(std::unique_ptr<FunctionNode>&& funcNode, 
				  std::vector<std::unique_ptr<FunctionNode>>&& functionNode);

	std::unique_ptr<Expression> call(const std::vector<const Expression*>& args) const override;

	std::unique_ptr<FunctionNode> clone() const override;

private:
	std::unique_ptr<FunctionNode> functionNode;
	std::vector<std::unique_ptr<FunctionNode>> argNodes;
};