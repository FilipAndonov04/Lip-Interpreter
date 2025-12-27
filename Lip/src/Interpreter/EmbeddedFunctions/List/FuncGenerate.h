#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncGenerate {
	static inline const std::string NAME{"gen"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};