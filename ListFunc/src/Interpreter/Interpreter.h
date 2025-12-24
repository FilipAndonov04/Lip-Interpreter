#pragma once
#include "Interpreter/Environment/Environment.h"

#include <string_view>

class Interpreter {
public:
	void interpret(std::string_view line);

	const Environment& getCurrentEnvironment() const;
	Environment& getCurrentEnvironment();
	void setCurrentEnvironment(std::unique_ptr<Environment>&& environment);

private:
	void handleFunctionDefinition(std::vector<std::string>&& tokens);
	void handleExpressionEvaluation(std::vector<std::string>&& tokens) const;

	std::unique_ptr<Environment> currentEnvironment = std::make_unique<Environment>();
};