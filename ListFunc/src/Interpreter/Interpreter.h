#pragma once
#include "Interpreter/Environment/Environment.h"

#include <string_view>

struct Token;

class Interpreter {
public:
	void interpret(std::string_view line);

	const Environment& getCurrentEnvironment() const;
	Environment& getCurrentEnvironment();
	void setCurrentEnvironment(std::unique_ptr<Environment>&& environment);

private:
	void handleFunctionDefinition(std::vector<Token>&& tokens);
	void handleExpressionEvaluation(std::vector<Token>&& tokens) const;

	std::unique_ptr<Environment> currentEnvironment = std::make_unique<Environment>();
};