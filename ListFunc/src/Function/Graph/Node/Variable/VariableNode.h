#pragma once
#include "Function/Graph/Node/FunctionNode.h"
#include "Interpreter/VariableSet/VariableRef.h"

class VariableNode : public FunctionNode {
public:
	explicit VariableNode(VariableRef variableRef);

	std::unique_ptr<Expression> call(const std::vector<const Expression*>& args) const override;

	std::unique_ptr<FunctionNode> clone() const override;

	const VariableRef& getVariableRef() const;

public:
	static std::unique_ptr<VariableNode> of(VariableRef variableRef);

private:
	VariableRef variableRef;
};