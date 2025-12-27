#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncLength {
	static inline const std::string NAME{"len"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};