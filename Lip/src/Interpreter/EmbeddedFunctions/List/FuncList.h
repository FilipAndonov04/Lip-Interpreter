#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncList {
	static inline const std::string NAME{"list"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};