#pragma once
#include "Expression/Expression.h"

#include <vector>

struct FuncInt {
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};