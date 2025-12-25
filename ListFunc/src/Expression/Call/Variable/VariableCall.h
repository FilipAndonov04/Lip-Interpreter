#pragma once
#include "Expression/Call/Call.h"

class Value;

class VariableCall final : public Call {
public:
	explicit VariableCall(const Value* variable); 
	
	std::unique_ptr<Value> evaluate() const override;

	std::unique_ptr<Expression> clone() const override;

	std::string toString() const override;

	const Value* getVariable() const;

public:
	static std::unique_ptr<VariableCall> of(const Value* variable);

private:
	const Value* variable;
};