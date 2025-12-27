#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;
class Interpreter;

struct FuncInput {
	static inline const std::string NAME{"input"};

	explicit FuncInput(Interpreter& interpreter);

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;

private:
	mutable Interpreter* interpreter;
};