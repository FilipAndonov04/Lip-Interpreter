#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncMultiply {
	static inline const std::string NAME{"mul"};
	
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};