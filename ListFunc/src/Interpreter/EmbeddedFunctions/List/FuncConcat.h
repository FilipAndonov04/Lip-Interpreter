#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncConcat {
	static inline const std::string NAME{"concat"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};