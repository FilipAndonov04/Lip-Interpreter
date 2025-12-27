#pragma once

#include <memory>
#include <vector>

class Expression;
class Value;

class Function {
public:
	Function(size_t argCount);
	Function(const Function&) = delete;
	Function& operator=(const Function&) = delete;
	virtual ~Function() = default;

	virtual std::unique_ptr<Function> clone() const = 0;

	std::unique_ptr<Value> call(const std::vector<const Expression*>& args) const;
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;

	size_t getArgCount() const;

protected:
	virtual std::unique_ptr<Value> callImpl(const std::vector<const Expression*>& args) const = 0;

private:
	size_t argCount;
};