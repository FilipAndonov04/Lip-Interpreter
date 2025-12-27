#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncNotEqual {
	static inline const std::string NAME{"ne"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};