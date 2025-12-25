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
	void defineFunction(std::vector<Token>&& tokens);
	void undefineFunction(std::vector<Token>&& tokens);

	void evaluateExpression(std::vector<Token>&& tokens) const;

	bool isValidFunctionDefinition(const std::vector<Token>& tokens) const;
	bool isValidFunctionUndefinition(const std::vector<Token>& tokens) const;

	static constexpr const char KEYWORD_DEFINE_FUNCTION[] = "def";
	static constexpr const char KEYWORD_UNDEFINE_FUNCTION[] = "undef";

	std::unique_ptr<Environment> currentEnvironment = std::make_unique<Environment>();
};