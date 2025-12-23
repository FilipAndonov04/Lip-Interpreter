#pragma once
#include "Expression/Expression.h"

class Variable : public Expression {
public:
	std::unique_ptr<Variable> evaluate() const override;

	ExpressionType type() const override;

	std::unique_ptr<Expression> cloneExpression() const override;
	virtual std::unique_ptr<Variable> cloneVariable() const = 0;
};