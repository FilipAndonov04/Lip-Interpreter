#pragma once
#include "Expression/Literal/Literal.h"

#include <vector>

class ListLiteral final : public Literal {
public:
	explicit ListLiteral(std::vector<std::unique_ptr<Expression>>&& elements);

	std::unique_ptr<Value> evaluate() const override;

	ExpressionType type() const override;

	std::unique_ptr<Expression> clone() const override;

	std::string toString() const override;

	size_t length() const;
	bool isEmpty() const;

	const Expression& at(size_t index) const;
	const Expression& operator[](size_t index) const;
	const Expression& front() const;
	const Expression& back() const;

private:
	std::vector<std::unique_ptr<Expression>> elements;
};