#pragma once
#include "Function/Function.h"

#include <string>

class VariableSet;

class FunctionRef {
public:
	FunctionRef(std::string name, size_t argCount, const VariableSet& variableSet);

	const Function& deref() const;
	const Function* ptr() const;
	const Function& operator*() const;
	const Function* operator->() const;
	
	bool isValid() const;
	operator bool() const;

	const std::string& getName() const;
	size_t getArgCount() const;
	const VariableSet& getVariableSet() const;

private:
	std::string name;
	size_t argCount;
	const VariableSet* variableSet;
};