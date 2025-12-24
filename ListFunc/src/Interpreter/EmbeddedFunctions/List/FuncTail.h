#pragma once
#include "Expression/Expression.h"

#include <vector>

struct FuncTail {
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};