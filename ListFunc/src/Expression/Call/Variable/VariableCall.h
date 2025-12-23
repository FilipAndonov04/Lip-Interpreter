#pragma once
#include "Expression/Call/Call.h"
#include "Interpreter/VariableSet/VariableRef.h"

class VariableCall final : public Call {
public:
	explicit VariableCall(VariableRef variableRef);

	std::unique_ptr<Variable> evaluate() const override;

	ExpressionType type() const override;

	std::unique_ptr<Expression> cloneExpression() const override;

	std::string toString() const override;

private:
	VariableRef variableRef;
};