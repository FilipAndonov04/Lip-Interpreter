#pragma once

#include <memory>
#include <string>

class Value;

class Expression {
public:
	Expression() = default;
	Expression(const Expression&) = delete;
	Expression& operator=(const Expression&) = delete;
	virtual ~Expression() = default;

	virtual std::unique_ptr<Value> evaluate() const = 0;

	virtual std::unique_ptr<Expression> cloneExpression() const = 0;

	virtual std::string toString() const { return "expr"; }
};