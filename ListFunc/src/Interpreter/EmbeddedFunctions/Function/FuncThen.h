#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncThen {
	static inline const std::string NAME{"then"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};