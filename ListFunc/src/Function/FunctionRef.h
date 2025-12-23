#pragma once
#include "Function/Function.h"

#include <string>

class VariableSet;

class FunctionRef {
public:
	FunctionRef(std::string name, size_t argCount, const VariableSet& variableSet);

	Function& function() const;
	Function& operator*() const;
	Function* operator->() const;
	
	bool isValid() const;
	operator bool() const;

private:
	std::string name;
	size_t argCount;
	const VariableSet* variableSet;
};