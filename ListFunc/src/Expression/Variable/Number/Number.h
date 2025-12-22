#pragma once
#include "Expression/Variable/Variable.h"

class Number : public Variable {
public:
	std::unique_ptr<Variable> cloneVariable() const override;
	virtual std::unique_ptr<Number> cloneNumber() const = 0;
};