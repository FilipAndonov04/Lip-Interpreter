#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FunctionData;

struct FuncList {
	static inline const std::string NAME{"list"};
	static std::unique_ptr<FunctionData> step;

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};