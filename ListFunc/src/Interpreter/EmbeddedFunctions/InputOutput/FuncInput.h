#pragma once
#include "Expression/Expression.h"

#include <vector>

class Interpreter;

struct FuncInput {
	explicit FuncInput(Interpreter& interpreter);

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;

private:
	mutable Interpreter* interpreter;
};