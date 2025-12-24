#pragma once

#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncSubtract {
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};