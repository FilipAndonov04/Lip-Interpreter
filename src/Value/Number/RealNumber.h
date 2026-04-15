#pragma once
#include "Value/Value.h"

class RealNumber final : public Value {
public:
	explicit RealNumber(double value);

	ValueType type() const override;

	std::unique_ptr<Value> cloneValue() const override;

	std::string toString() const override;

	double getValue() const;
	void setValue(double value);

public:
	static std::unique_ptr<RealNumber> of(double value);

private:
	double value;
};