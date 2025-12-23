#pragma once
#include "Interpreter/VariableSet/VariableSet.h"

#include <string_view>

class Interpreter {
public:
	Interpreter() = default;
	explicit Interpreter(VariableSet&& variableSet);

	void interpret(std::string_view line);

	const VariableSet& getVariableSet() const;
	VariableSet& getVariableSet();

private:
	void handleFunctionDefinition(std::vector<std::string>&& tokens);
	void handleExpressionEvaluation(std::vector<std::string>&& tokens) const;

	VariableSet variableSet;
};