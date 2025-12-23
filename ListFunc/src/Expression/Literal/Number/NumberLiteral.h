#pragma once
#include "Expression/Literal/Literal.h"

class NumberLiteral final : public Literal {
public:
	explicit NumberLiteral(double value);

	std::unique_ptr<Value> evaluate() const override;

	ExpressionType type() const override;

	std::unique_ptr<Expression> clone() const override;

	std::string toString() const override;

	double getValue() const;

public:
	static std::unique_ptr<NumberLiteral> of(double value);

private:
	double value;
};