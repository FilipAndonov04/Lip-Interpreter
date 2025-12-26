#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncLessOrEqual {
	static inline const std::string NAME{"le"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};