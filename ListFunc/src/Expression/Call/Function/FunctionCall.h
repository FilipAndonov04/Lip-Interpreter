#pragma once
#include "Expression/Call/Call.h"

#include <vector>

class Function;

class FunctionCall final : public Call {
public:
	explicit FunctionCall(const Function* function);
	FunctionCall(const Function* function, std::vector<std::unique_ptr<Expression>>&& args);

	std::unique_ptr<Value> evaluate() const override;

	ExpressionType type() const override;

	std::unique_ptr<Expression> cloneExpression() const override;

	std::string toString() const override;

	const Function* getFunction() const;
	std::vector<const Expression*> getArgs() const;

private:
	const Function* function;
	std::vector<std::unique_ptr<Expression>> args;
};