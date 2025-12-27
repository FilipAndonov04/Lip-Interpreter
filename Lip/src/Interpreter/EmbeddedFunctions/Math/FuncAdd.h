#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncAdd {
	static inline const std::string NAME{"add"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};