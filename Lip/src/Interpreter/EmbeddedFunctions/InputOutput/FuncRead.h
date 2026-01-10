#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncRead {
	static inline const std::string NAME{"read"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};