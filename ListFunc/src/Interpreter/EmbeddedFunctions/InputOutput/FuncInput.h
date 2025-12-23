#pragma once
#include "Expression/Expression.h"
#include "Interpreter/VariableSet/VariableSet.h"

#include <vector>

struct FuncInput {
	explicit FuncInput(const VariableSet& variableSet);

	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const;

private:
	const VariableSet* variableSet;
};