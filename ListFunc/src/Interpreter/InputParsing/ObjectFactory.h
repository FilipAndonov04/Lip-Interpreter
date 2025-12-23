#pragma once
#include "Expression/Variable/Number/RealNumber.h"
#include "Expression/Variable/List/Concrete/ConcreteList.h"
#include "Expression/Call/Function/FunctionCall.h"
#include "Function/Graph/GraphFunction.h"
#include "Function/Graph/Node/Argument/ArgumentNode.h"
#include "Function/Graph/Node/Literal/LiteralNode.h"
#include "Function/Graph/Node/Composite/CompositeNode.h"

#include <memory>
#include <string>
#include <unordered_set>

class ObjectFactory {
public:
	ObjectFactory(std::vector<std::string> tokens, const VariableSet& variableSet, size_t index = 0);

	std::unique_ptr<Expression> createExpression();
	std::unique_ptr<Variable> createVariable();
	std::unique_ptr<Function> createFunction(size_t argCount);

private:
	std::unique_ptr<RealNumber> createRealNumber();
	std::unique_ptr<ConcreteList> createConcreteList();
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