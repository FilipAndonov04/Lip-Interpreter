#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncNot {
	static inline const std::string NAME{"not"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};