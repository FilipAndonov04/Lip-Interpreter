#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncLessThan {
	static inline const std::string NAME{"lt"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};