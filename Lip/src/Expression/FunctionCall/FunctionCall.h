#pragma once
#include "Expression/Expression.h"

#include <vector>

class FunctionCall final : public Expression {
public:
	explicit FunctionCall(std::unique_ptr<Expression>&& function);
	FunctionCall(std::unique_ptr<Expression>&& function, 
				 std::vector<std::unique_ptr<Expression>>&& args);

	std::unique_ptr<Value> evaluate() const override;

	std::unique_ptr<Expression> clone() const override;

	std::string toString() const override;

	std::vector<const Expression*> getArgs() const;

private:
	std::unique_ptr<Expression> function;
	std::vector<std::unique_ptr<Expression>> args;
};