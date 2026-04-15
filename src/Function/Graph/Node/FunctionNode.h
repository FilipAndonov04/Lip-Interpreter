#pragma once

#include <memory>
#include <vector>

class Expression;

class FunctionNode {
public:
	FunctionNode() = default;
	FunctionNode(const FunctionNode&) = delete;
	FunctionNode& operator=(const FunctionNode&) = delete;
	virtual ~FunctionNode() = default;

	virtual std::unique_ptr<Expression> call(const std::vector<const Expression*>& args) const = 0;

	virtual std::unique_ptr<FunctionNode> clone() const = 0;
};