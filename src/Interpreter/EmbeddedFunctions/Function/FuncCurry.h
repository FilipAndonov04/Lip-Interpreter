#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncCurry {
	static inline const std::string NAME{"curry"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};