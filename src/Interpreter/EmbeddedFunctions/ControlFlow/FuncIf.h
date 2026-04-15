#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncIf {
	static inline const std::string NAME{"if"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};