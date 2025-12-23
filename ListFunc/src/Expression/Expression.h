#pragma once
#include "Expression/ExpressionType.h"

#include <memory>
#include <string>

class Variable;

class Expression {
public:
	Expression() = default;
	Expression(const Expression&) = delete;
	Expression& operator=(const Expression&) = delete;
	virtual ~Expression() = default;

	virtual std::unique_ptr<Variable> evaluate() const = 0;

	virtual ExpressionType type() const = 0;

	virtual std::unique_ptr<Expression> cloneExpression() const = 0;

	virtual std::string toString() const { return "expr"; }

public:
	static std::unique_ptr<Variable> evaluate(std::unique_ptr<Expression>&& expression);
};