#pragma once
#include "Interpreter/Environment/EnvironmentStack.h"

#include <string_view>

struct Token;

class Interpreter {
public:
	Interpreter();

	void interpret(std::string_view line);

	const Environment& getCurrentEnvironment() const;
	Environment& getCurrentEnvironment();

private:
	void defineFunction(std::vector<Token>&& tokens);
	void redefineFunction(std::vector<Token>&& tokens);
	void undefineFunction(std::vector<Token>&& tokens);
	
	void createVariable(std::vector<Token>&& tokens);
	void createConstVariable(std::vector<Token>&& tokens);
	void removeVariable(std::vector<Token>&& tokens);

	void evaluateExpression(std::vector<Token>&& tokens);

	bool isValidFunctionDefinition(const std::vector<Token>& tokens) const;
	bool isValidFunctionRedefinition(const std::vector<Token>& tokens) const;
	bool isValidFunctionUndefinition(const std::vector<Token>& tokens) const;

	bool isValidVariableCreation(const std::vector<Token>& tokens) const;
	bool isValidConstVariableCreation(const std::vector<Token>& tokens) const;
	bool isValidVariableRemoval(const std::vector<Token>& tokens) const;

	void pushEnvironment(const Environment& environment);
	void pushEnvironment(Environment&& environment);

	EnvironmentStack environmentStack;
};