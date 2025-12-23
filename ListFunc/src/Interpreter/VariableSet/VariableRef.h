#pragma once
#include "Value/Value.h"

#include <string>

class VariableSet;

class VariableRef {
public:
	VariableRef(std::string name, const VariableSet& variableSet);

	const Value& deref() const;
	const Value* ptr() const;
	const Value& operator*() const;
	const Value* operator->() const;

	bool isValid() const;
	operator bool() const;

	const std::string& getName() const;
	const VariableSet& getVariableSet() const;

private:
	std::string name;
	const VariableSet* variableSet;
};