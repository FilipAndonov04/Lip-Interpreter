#pragma once
#include "Function/Graph/Node/FunctionNode.h"

class Variable;

class LiteralNode final : public FunctionNode {
public:
	explicit LiteralNode(std::unique_ptr<Variable>&& variable);

	std::unique_ptr<Expression> call(const std::vector<const Expression*>& args) const override;

	std::unique_ptr<FunctionNode> clone() const override;

	const Variable& getVariable() const;

public:
	static std::unique_ptr<LiteralNode> of(std::unique_ptr<Variable>&& variable);

private:
	std::unique_ptr<const Variable> variable;
};