#pragma once
#include "Function/Graph/Node/FunctionNode.h"

class Literal;

class LiteralNode final : public FunctionNode {
public:
	explicit LiteralNode(std::unique_ptr<Literal>&& literal);

	std::unique_ptr<Expression> call(const std::vector<const Expression*>& args) const override;

	std::unique_ptr<FunctionNode> clone() const override;

	const Literal& getLiteral() const;

public:
	static std::unique_ptr<LiteralNode> of(std::unique_ptr<Literal>&& literal);

private:
	std::unique_ptr<const Literal> literal;
};