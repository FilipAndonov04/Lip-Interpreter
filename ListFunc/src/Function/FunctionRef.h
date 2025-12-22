#pragma once
#include "Function/Function.h"

#include <string>

class VariableDatabase;

class FunctionRef {
public:
	FunctionRef(std::string name, size_t argCount, const VariableDatabase& database);

	Function& function() const;
	Function& operator*() const;
	Function* operator->() const;
	
	bool isValid() const;
	operator bool() const;

private:
	std::string name;
	size_t argCount;
	const VariableDatabase* database;
};