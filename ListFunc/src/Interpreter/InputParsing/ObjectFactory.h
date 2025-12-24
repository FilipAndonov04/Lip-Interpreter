#pragma once

#include <memory>
#include <string>
#include <unordered_set>

class Expression;
class Literal;
class NumberLiteral;
class ListLiteral;
class FunctionCall;

class Function;
class GraphFunction;

class FunctionNode;
class LiteralNode;
class ArgumentNode;
class CompositeNode;

class Environment;

class ObjectFactory {
public:
	ObjectFactory(std::vector<std::string> tokens, Environment& environment, size_t index = 0);

	std::unique_ptr<Expression> createExpression();
	std::shared_ptr<Function> createFunction(const std::string& name, size_t argCount);

private:
	std::unique_ptr<Literal> createLiteral();
	std::unique_ptr<NumberLiteral> createNumberLiteral();
	std::unique_ptr<ListLiteral> createListLiteral();
	std::unique_ptr<FunctionCall> createFunctionCall();

	std::shared_ptr<GraphFunction> createGraphFunction(const std::string& name, size_t argCount);

	std::unique_ptr<FunctionNode> createFunctionNode();
	std::unique_ptr<ArgumentNode> createArgumentNode();
	std::unique_ptr<LiteralNode> createLiteralNode();
	std::unique_ptr<CompositeNode> createCompositeNode();

	void assertIndex() const;

	std::vector<std::string> tokens;
	size_t index;
	Environment* environment;

	std::unordered_set<size_t> argIds;
};