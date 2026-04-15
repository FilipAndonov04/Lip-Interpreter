#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncTail {
	static inline const std::string NAME{"tail"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};