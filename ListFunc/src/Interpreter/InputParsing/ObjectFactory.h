#pragma once

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

class VariableSet;

#include <memory>
#include <string>
#include <unordered_set>

class ObjectFactory {
public:
	ObjectFactory(std::vector<std::string> tokens, const VariableSet& variableSet, size_t index = 0);

	std::unique_ptr<Expression> createExpression();
	std::unique_ptr<Function> createFunction(size_t argCount);

private:
	std::unique_ptr<Literal> createLiteral();
	std::unique_ptr<NumberLiteral> createNumberLiteral();
	std::unique_ptr<ListLiteral> createListLiteral();
	std::unique_ptr<FunctionCall> createFunctionCall();

	std::unique_ptr<GraphFunction> createGraphFunction(size_t argCount);

	std::unique_ptr<FunctionNode> createFunctionNode();
	std::unique_ptr<ArgumentNode> createArgumentNode();
	std::unique_ptr<LiteralNode> createLiteralNode();
	std::unique_ptr<CompositeNode> createCompositeNode();

	void assertIndex() const;

	std::vector<std::string> tokens;
	size_t index;
	const VariableSet* variableSet;

	std::unordered_set<size_t> argIds;
};