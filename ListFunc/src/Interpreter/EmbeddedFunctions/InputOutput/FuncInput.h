#pragma once

#include <memory>
#include <vector>

class Expression;
class Value;
class Interpreter;

struct FuncInput {
	explicit FuncInput(Interpreter& interpreter);

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;

private:
	mutable Interpreter* interpreter;
};