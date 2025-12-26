#pragma once
#include "Value/Value.h"

#include <vector>

class Function;
class Expression;

class FunctionObject final : public Value {
public:
	explicit FunctionObject(const Function* function);

	ValueType type() const override;

	std::unique_ptr<Value> cloneValue() const override;

	std::string toString() const override;

	std::unique_ptr<Value> call(const std::vector<const Expression*>& args) const;
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;

	const Function* getFunction() const;
	void setFunction(const Function* function);

public:
	static std::unique_ptr<FunctionObject> of(const Function* function);

private:
	const Function* function;
};