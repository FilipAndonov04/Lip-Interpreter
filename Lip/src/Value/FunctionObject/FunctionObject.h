#pragma once
#include "Value/Value.h"

#include <vector>

class Function;
class Expression;

class FunctionObject final : public Value {
public:
	explicit FunctionObject(const Function* function);
	explicit FunctionObject(std::vector<const Function*> functions);

	ValueType type() const override;

	std::unique_ptr<Value> cloneValue() const override;
	std::unique_ptr<FunctionObject> cloneFunctionObject() const;

	std::string toString() const override;

	std::unique_ptr<Value> call(const std::vector<const Expression*>& args) const;
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;

	const std::vector<const Function*>& getFunctions() const;
	void addFunction(size_t index, const Function* function);
	void pushBackFunction(const Function* function);
	void pushFrontFunction(const Function* function);

public:
	static std::unique_ptr<FunctionObject> of(const Function* function);

private:
	std::vector<const Function*> functions;
};