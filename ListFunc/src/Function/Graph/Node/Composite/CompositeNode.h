#pragma once
#include "Function/Graph/Node/FunctionNode.h"
#include "Interpreter/VariableSet/FunctionRef.h"

class CompositeNode final : public FunctionNode {
public:
	explicit CompositeNode(FunctionRef functionRef);
	CompositeNode(FunctionRef functionRef, std::vector<std::unique_ptr<FunctionNode>>&& argNodes);

	std::unique_ptr<Expression> call(const std::vector<const Expression*>& args) const override;

	std::unique_ptr<FunctionNode> clone() const override;

	const FunctionRef& getFunctionRef() const;
	std::vector<const FunctionNode*> getArgNodes() const;

private:
	std::vector<std::unique_ptr<FunctionNode>> argNodes;
	FunctionRef functionRef;
};