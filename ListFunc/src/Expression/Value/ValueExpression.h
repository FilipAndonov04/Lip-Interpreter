#pragma once
#include "Expression/Expression.h"

class ValueExpression : public Expression {
public:
	ValueExpression(std::unique_ptr<Value>&& value);

	std::unique_ptr<Value> evaluate() const override;

	std::unique_ptr<Expression> clone() const override;

	std::string toString() const override;

public:
	static std::unique_ptr<ValueExpression> of(std::unique_ptr<Value>&& value);

private:
	std::unique_ptr<Value> value;
};