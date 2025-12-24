#pragma once
#include "Function/Function.h"
#include "Interpreter/Environment/Environment.h"

class FunctionNode;

class GraphFunction final : public Function {
public:
	explicit GraphFunction(size_t argCount);
	GraphFunction(size_t argCount, std::unique_ptr<FunctionNode>&& graphRoot);

	std::unique_ptr<Function> clone() const override;

	void setGraphRoot(std::unique_ptr<FunctionNode>&& graphRoot);

protected:
	std::unique_ptr<Value> callImpl(const std::vector<const Expression*>& args) const override;

private:
	std::unique_ptr<FunctionNode> graphRoot;
};