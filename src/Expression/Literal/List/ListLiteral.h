#pragma once
#include "Expression/Literal/Literal.h"

#include <vector>

class ListLiteral final : public Literal {
public:
	ListLiteral() = default;
	explicit ListLiteral(std::vector<std::unique_ptr<Expression>>&& elements);

	std::unique_ptr<Value> evaluate() const override;

	std::unique_ptr<Expression> clone() const override;

	std::string toString() const override;

private:
	std::vector<std::unique_ptr<Expression>> elements;
};