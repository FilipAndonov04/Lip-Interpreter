#pragma once
#include "Expression/Expression.h"
#include "Interpreter/Environment/Environment.h"

#include <vector>

struct FuncInput {
	explicit FuncInput(Environment& environment);

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;

private:
	Environment* environment;
};