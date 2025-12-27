#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncOr {
	static inline const std::string NAME{"or"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};