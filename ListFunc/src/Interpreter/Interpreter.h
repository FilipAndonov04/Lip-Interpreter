#pragma once
#include "Interpreter/VariableDatabase.h"
#include "Interpreter/LineParser.h"

#include <string_view>

class Interpreter {
public:
	Interpreter() = default;
	explicit Interpreter(const VariableDatabase& variableDatabase);
	explicit Interpreter(VariableDatabase&& variableDatabase);

	void interpret(std::string_view line);

	const VariableDatabase& getVariableDatabase() const;
	VariableDatabase& getVariableDatabase();

private:
	VariableDatabase variableDatabase;
};