#pragma once
#include "Expression/Expression.h"

class Literal : public Expression {
public:
	std::unique_ptr<Expression> cloneExpression() const override;
	virtual std::unique_ptr<Literal> cloneLiteral() const = 0;
};