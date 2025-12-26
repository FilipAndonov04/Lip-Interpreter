#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncLength {
	static inline const std::string NAME{"length"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};