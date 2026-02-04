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

	bool isKeyword(std::string_view word);

	void pushEnvironment(const Environment& environment);
	void pushEnvironment(Environment&& environment);

	static constexpr const char KEYWORD_DEFINE_FUNCTION[] = "def";
	static constexpr const char KEYWORD_REDEFINE_FUNCTION[] = "redef";
	static constexpr const char KEYWORD_UNDEFINE_FUNCTION[] = "undef";
	
	static constexpr const char KEYWORD_CREATE_VARIABLE[] = "let";
	static constexpr const char KEYWORD_CREATE_CONST_VARIABLE[] = "const";
	static constexpr const char KEYWORD_REMOVE_VARIABLE[] = "rm";

	EnvironmentStack environmentStack;
};