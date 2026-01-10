#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncWrite {
	static inline const std::string NAME{"write"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};