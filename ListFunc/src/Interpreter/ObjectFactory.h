#pragma once
#include "Expression/Variable/Number/Real/RealNumber.h"
#include "Expression/Variable/List/Concrete/ConcreteList.h"
#include "Expression/FunctionCall/FunctionCall.h"
#include "Function/Graph/GraphFunction.h"
#include "Function/Graph/Node/Argument/ArgumentNode.h"
#include "Function/Graph/Node/Literal/LiteralNode.h"
#include "Function/Graph/Node/Composite/CompositeNode.h"

#include <memory>
#include <string>

class ObjectFactory {
public:
	ObjectFactory(const std::vector<std::string>& tokens);
	ObjectFactory(std::vector<std::string>&& tokens);

	std::unique_ptr<Expression> createExpression();
	std::unique_ptr<Variable> createVariable();
	std::unique_ptr<Function> createFunction();

private:
	std::unique_ptr<RealNumber> createRealNumber();
	std::unique_ptr<ConcreteList> createConcreteList();
	std::unique_ptr<FunctionCall> createFunctionCall();

	std::unique_ptr<GraphFunction> createGraphFunction();
	std::unique_ptr<FunctionNode> createFunctionNode();
	std::unique_ptr<ArgumentNode> createArgumentNode();
	std::unique_ptr<LiteralNode> createLiteralNode();
	std::unique_ptr<CompositeNode> createCompositeNode();

	std::vector<std::string> tokens;
};