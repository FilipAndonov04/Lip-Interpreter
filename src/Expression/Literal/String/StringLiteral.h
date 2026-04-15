#pragma once
#include "Expression/Literal/Literal.h"

#include <string>

class StringLiteral final : public Literal {
public:
	explicit StringLiteral(std::string string);

	std::unique_ptr<Value> evaluate() const override;

	std::unique_ptr<Expression> clone() const override;

	std::string toString() const override;

	const std::string& getString() const;

public:
	static std::unique_ptr<StringLiteral> of(std::string string);

private:
	std::string string;
};