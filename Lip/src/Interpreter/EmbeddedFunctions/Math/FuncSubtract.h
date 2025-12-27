#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncSubtract {
	static inline const std::string NAME{"sub"};
	
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};