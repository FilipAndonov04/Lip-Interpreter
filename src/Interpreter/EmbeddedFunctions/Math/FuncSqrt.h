#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncSqrt {
	static inline const std::string NAME{"sqrt"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};