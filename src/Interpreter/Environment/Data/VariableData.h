#pragma once

#include <memory>

class Value;

class VariableData {
public:
	VariableData() = default;
	VariableData(std::unique_ptr<Value>&& value, bool isConst);

	const Value* getValue() const;
	bool getIsConst() const;

	void setValue(std::unique_ptr<Value>&& value);
	void setIsConst(bool isConst);

private:
	std::unique_ptr<const Value> value;
	bool isConst;
};