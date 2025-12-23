#pragma once
#include "Expression/Call/Call.h"
#include "Interpreter/VariableSet/FunctionRef.h"

#include <vector>

class FunctionCall final : public Call {
public:
	explicit FunctionCall(FunctionRef functionRef);
	FunctionCall(FunctionRef functionRef, std::vector<std::unique_ptr<Expression>>&& args);

	std::unique_ptr<Variable> evaluate() const override;

	ExpressionType type() const override;

	std::unique_ptr<Expression> cloneExpression() const override;

	std::string toString() const override;

private:
	FunctionRef functionRef;
	std::vector<std::unique_ptr<Expression>> args;
};