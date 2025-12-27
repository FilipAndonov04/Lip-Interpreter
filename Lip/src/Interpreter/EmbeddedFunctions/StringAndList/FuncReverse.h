#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncReverse {
	static inline const std::string NAME{"rev"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};