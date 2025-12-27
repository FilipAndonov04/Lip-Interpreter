#pragma once

#include <memory>

class Value;

struct VariableData {
	std::unique_ptr<const Value> value;
	bool isConst;
};