#pragma once
#include "Expression/Expression.h"

#include <vector>

struct FuncList {
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};