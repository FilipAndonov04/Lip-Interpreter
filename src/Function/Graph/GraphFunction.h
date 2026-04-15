#pragma once
#include "Function/Function.h"

class FunctionNode;

class GraphFunction final : public Function {
public:
	GraphFunction() = default;
	explicit GraphFunction(std::unique_ptr<FunctionNode>&& graphRoot);

	std::unique_ptr<Function> clone() const override;

	void setGraphRoot(std::unique_ptr<FunctionNode>&& graphRoot);

protected:
	std::unique_ptr<Value> callImpl(const std::vector<const Expression*>& args) const override;

private:
	std::unique_ptr<FunctionNode> graphRoot;
};