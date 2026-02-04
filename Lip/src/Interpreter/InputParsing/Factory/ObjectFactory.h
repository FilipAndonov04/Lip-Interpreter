#pragma once
#include "Interpreter/InputParsing/Tokenizer/Token.h"

#include <memory>
#include <vector>
#include <unordered_set>

class Expression;
class Literal;
class NumberLiteral;
class ListLiteral;
class StringLiteral;
class FunctionCall;
class VariableExpression;

class FunctionData;
class Function;
class GraphFunction;

class FunctionNode;
class LeafNode;
class ExpressionNode;
class ArgumentNode;
class CompositeNode;

class Environment;

class ObjectFactory {
public:
	ObjectFactory(std::vector<Token> tokens, Environment& environment, size_t index = 0);

	std::unique_ptr<Expression> createExpression();
	std::shared_ptr<FunctionData> createFunction(const std::string& name, uint8_t argCount);

	size_t getCurrentIndex() const;

private:
	std::unique_ptr<Literal> createLiteral();
	std::unique_ptr<NumberLiteral> createNumberLiteral();
	std::unique_ptr<ListLiteral> createListLiteral();
	std::unique_ptr<StringLiteral> createStringLiteral();
	std::unique_ptr<Expression> createVariableExpression();
	std::unique_ptr<FunctionCall> createFunctionCall();

	std::unique_ptr<Expression> createFunctionCallFunction(const std::string& funcName, size_t argCount);
	std::vector<std::unique_ptr<Expression>> createFunctionCallArgs();

	std::unique_ptr<GraphFunction> createGraphFunction(const std::string& name, size_t argCount);

	std::unique_ptr<FunctionNode> createFunctionNode();
	std::unique_ptr<LeafNode> createLeafNode();
	std::unique_ptr<ArgumentNode> createArgumentNode();
	std::unique_ptr<ExpressionNode> createExpressionNode();
	std::unique_ptr<CompositeNode> createCompositeNode();

	std::unique_ptr<Expression> createExpressionNoFuncCall();
	std::unique_ptr<FunctionNode> createCompositeNodeFunc(const std::string& payload,
														  TokenType type,
														  uint8_t argCount);
	std::vector<std::unique_ptr<FunctionNode>> createCompositeNodeArgs();

	size_t getCloseCircleBracketIndex(size_t index);

	void assertIndex(size_t index) const;
	void assertCurrentIndex() const;

	void assertTokenType(size_t index, TokenType type);
	void assertTokenType(size_t index, TokenType type, const std::string& errorMessage);
	void assertTokenType(size_t index, TokenType type, const char* errorMessage);
	void assertCurrentTokenType(TokenType type);
	void assertCurrentTokenType(TokenType type, const std::string& errorMessage);
	void assertCurrentTokenType(TokenType type, const char* errorMessage);

	std::vector<Token> tokens;
	size_t index;
	Environment* environment;

	std::unordered_set<uint8_t> argIds;
};