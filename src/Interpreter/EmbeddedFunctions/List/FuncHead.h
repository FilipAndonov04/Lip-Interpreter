#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncHead {
	static inline const std::string NAME{"head"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};