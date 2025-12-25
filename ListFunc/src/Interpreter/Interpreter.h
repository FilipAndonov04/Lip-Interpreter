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
	void redefineFunction(std::vector<Token>&& tokens);
	void undefineFunction(std::vector<Token>&& tokens);
	
	void defineVariable(std::vector<Token>&& tokens);
	void redefineVariable(std::vector<Token>&& tokens);
	void undefineVariable(std::vector<Token>&& tokens);

	void evaluateExpression(std::vector<Token>&& tokens) const;

	bool isValidFunctionDefinition(const std::vector<Token>& tokens) const;
	bool isValidFunctionRedefinition(const std::vector<Token>& tokens) const;
	bool isValidFunctionUndefinition(const std::vector<Token>& tokens) const;

	bool isValidVariableDefinition(const std::vector<Token>& tokens) const;
	bool isValidVariableRedefinition(const std::vector<Token>& tokens) const;
	bool isValidVariableUndefinition(const std::vector<Token>& tokens) const;

	static constexpr const char KEYWORD_DEFINE_FUNCTION[] = "def";
	static constexpr const char KEYWORD_REDEFINE_FUNCTION[] = "redef";
	static constexpr const char KEYWORD_UNDEFINE_FUNCTION[] = "undef";
	
	static constexpr const char KEYWORD_DEFINE_VARIABLE[] = "var";
	static constexpr const char KEYWORD_UNDEFINE_VARIABLE[] = "delete";

	std::unique_ptr<Environment> currentEnvironment = std::make_unique<Environment>();
};