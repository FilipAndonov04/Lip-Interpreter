#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncAndThen {
	static inline const std::string NAME{"and_then"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};