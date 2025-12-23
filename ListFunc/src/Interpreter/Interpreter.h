#pragma once
#include "Interpreter/VariableSet.h"
#include "Interpreter/LineParser.h"
#include "ObjectFactory.h"

#include <string_view>

class Interpreter {
public:
	Interpreter() = default;
	explicit Interpreter(VariableSet&& variableSet);

	void interpret(std::string_view line);

	const VariableSet& getVariableSet() const;
	VariableSet& getVariableSet();

private:
	VariableSet variableSet;
};