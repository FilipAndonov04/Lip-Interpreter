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
	
	void createVariable(std::vector<Token>&& tokens);
	void assignVariable(std::vector<Token>&& tokens);
	void deleteVariable(std::vector<Token>&& tokens);

	void evaluateExpression(std::vector<Token>&& tokens) const;

	bool isValidFunctionDefinition(const std::vector<Token>& tokens) const;
	bool isValidFunctionRedefinition(const std::vector<Token>& tokens) const;
	bool isValidFunctionUndefinition(const std::vector<Token>& tokens) const;

	bool isValidVariableCreation(const std::vector<Token>& tokens) const;
	bool isValidVariableAssignment(const std::vector<Token>& tokens) const;
	bool isValidVariableDeletion(const std::vector<Token>& tokens) const;

	bool isKeyword(std::string_view word);

	static constexpr const char KEYWORD_DEFINE_FUNCTION[] = "def";
	static constexpr const char KEYWORD_REDEFINE_FUNCTION[] = "redef";
	static constexpr const char KEYWORD_UNDEFINE_FUNCTION[] = "undef";
	
	static constexpr const char KEYWORD_CREATE_VARIABLE[] = "var";
	static constexpr const char KEYWORD_DELETE_VARIABLE[] = "delete";

	std::unique_ptr<Environment> currentEnvironment = std::make_unique<Environment>();
};