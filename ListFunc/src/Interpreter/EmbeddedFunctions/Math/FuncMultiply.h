#pragma once
#include "Expression/Expression.h"

#include <vector>

struct FuncMultiply {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const;
};