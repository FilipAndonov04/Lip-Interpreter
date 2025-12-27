#pragma once

#include <string>
#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncGreaterThan {
	static inline const std::string NAME{"gt"};

	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};