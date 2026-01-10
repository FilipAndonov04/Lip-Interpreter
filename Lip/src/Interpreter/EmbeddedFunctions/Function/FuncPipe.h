#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncPipe {
	static inline const std::string NAME{"pipe"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};