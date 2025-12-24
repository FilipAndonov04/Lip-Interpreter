#pragma once
#include "Function/Graph/Node/FunctionNode.h"

class Function;

class CompositeNode final : public FunctionNode {
public:
	explicit CompositeNode(const Function* function);
	CompositeNode(const Function* function, std::vector<std::unique_ptr<FunctionNode>>&& argNodes);

	std::unique_ptr<Expression> call(const std::vector<const Expression*>& args) const override;

	std::unique_ptr<FunctionNode> clone() const override;

private:
	const Function* function;
	std::vector<std::unique_ptr<FunctionNode>> argNodes;
};