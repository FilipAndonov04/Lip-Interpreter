#pragma once

#include <string>

class VariableSet;
class Variable;

class VariableRef {
public:
	VariableRef(std::string name, const VariableSet& variableSet);

	const Variable& deref() const;
	const Variable* ptr() const;
	const Variable& operator*() const;
	const Variable* operator->() const;

	bool isValid() const;
	operator bool() const;

	const std::string& getName() const;
	const VariableSet& getVariableSet() const;

private:
	std::string name;
	const VariableSet* variableSet;
};