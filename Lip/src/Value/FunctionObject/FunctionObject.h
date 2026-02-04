#pragma once
#include "Value/Value.h"
#include "Expression/Expression.h"

#include <vector>

class FunctionData;

class FunctionObject final : public Value {
public:
	explicit FunctionObject(const FunctionData* function);
	explicit FunctionObject(std::vector<const FunctionData*> functions);
	FunctionObject(std::vector<const FunctionData*> functions,
				   std::vector<std::unique_ptr<Expression>> curryArgs);

	ValueType type() const override;

	std::unique_ptr<Value> cloneValue() const override;
	std::unique_ptr<FunctionObject> cloneFunctionObject() const;

	std::string toString() const override;

	std::unique_ptr<Value> call(const std::vector<const Expression*>& args) const;
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;

	const std::vector<const FunctionData*>& getFunctions() const;

	void insertFunction(size_t index, const FunctionData* function);
	void pushBackFunction(const FunctionData* function);
	void pushFrontFunction(const FunctionData* function);

	void pushBackArg(std::unique_ptr<Expression>&& arg);

public:
	static std::unique_ptr<FunctionObject> of(const FunctionData* function);

private:
	std::vector<const FunctionData*> functions;
	std::vector<std::unique_ptr<Expression>> curryArgs;
};