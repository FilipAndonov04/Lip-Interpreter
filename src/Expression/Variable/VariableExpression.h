#pragma once
#include "Expression/Expression.h"

class Value;

class VariableExpression final : public Expression {
public:
	explicit VariableExpression(const Value* variable); 
	
	std::unique_ptr<Value> evaluate() const override;

	std::unique_ptr<Expression> clone() const override;

	std::string toString() const override;

	const Value* getVariable() const;

public:
	static std::unique_ptr<VariableExpression> of(const Value* variable);

private:
	const Value* variable;
};