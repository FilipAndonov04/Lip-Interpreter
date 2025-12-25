#pragma once

#include <memory>
#include <vector>

class Expression;
class Value;

struct FuncIf {
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const;
};