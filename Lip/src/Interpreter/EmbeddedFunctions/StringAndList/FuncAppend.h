#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncAppend {
	static inline const std::string NAME{"append"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};