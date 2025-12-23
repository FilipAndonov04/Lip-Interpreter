#pragma once
#include "Expression/Variable/Variable.h"

class RealNumber final : public Variable {
public:
	explicit RealNumber(double value);

	ExpressionType type() const override;

	std::unique_ptr<Variable> cloneVariable() const override;

	std::string toString() const override;

	double getValue() const;
	void setValue(double value);

public:
	static std::unique_ptr<RealNumber> of(double value);

private:
	double value;
};