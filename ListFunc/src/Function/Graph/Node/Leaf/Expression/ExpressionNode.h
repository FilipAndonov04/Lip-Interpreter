#pragma once
#include "Function/Graph/Node/Leaf/LeafNode.h"

class ExpressionNode final : public LeafNode {
public:
	explicit ExpressionNode(std::unique_ptr<Expression>&& expression);

	std::unique_ptr<Expression> call(const std::vector<const Expression*>& args) const override;

	std::unique_ptr<FunctionNode> clone() const override;

	const Expression& getExpression() const;

public:
	static std::unique_ptr<ExpressionNode> of(std::unique_ptr<Expression>&& expression);

private:
	std::unique_ptr<const Expression> expression;
};