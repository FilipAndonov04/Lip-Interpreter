#pragma once

#include <memory>
#include <vector>

class Expression;

class Function {
public:
	Function(size_t argCount);
	Function(const Function& other) = delete;
	Function& operator=(const Function& other) = delete;
	virtual ~Function() = default;

	virtual std::unique_ptr<Function> clone() const = 0;

	std::unique_ptr<Expression> call(const std::vector<const Expression*>& args) const;
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const;

	size_t getArgCount() const;

protected:
	virtual std::unique_ptr<Expression> callImpl(const std::vector<const Expression*>& args) const = 0;

private:
	size_t argCount;
};