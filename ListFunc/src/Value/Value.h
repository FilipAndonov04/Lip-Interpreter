#pragma once
#include "Value/ValueType.h"

#include <memory>
#include <string>

class Value {
public:
	Value() = default;
	Value(const Value&) = delete;
	Value& operator=(const Value&) = delete;
	virtual ~Value() = default;

	virtual ValueType type() const = 0;
	
	virtual std::unique_ptr<Value> cloneValue() const = 0;

	virtual std::string toString() const = 0;
};