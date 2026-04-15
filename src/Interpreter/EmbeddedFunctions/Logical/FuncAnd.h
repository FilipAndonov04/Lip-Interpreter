#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncAnd {
	static inline const std::string NAME{"and"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};