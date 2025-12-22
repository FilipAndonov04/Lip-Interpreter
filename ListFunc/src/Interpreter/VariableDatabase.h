#pragma once
#include "Expression/Variable/Variable.h"
#include "Function/Function.h"

#include <string>
#include <unordered_map>

class VariableDatabase {
public:
	bool containsVariable(const std::string& name) const;
	bool containsFunction(const std::string& name) const;
	bool containsFunction(const std::string& name, size_t argCount) const;

	void add(const std::string& name, std::unique_ptr<Variable>&& variable);
	void add(const std::string& name, std::unique_ptr<Function>&& function);
	
	void removeVariable(const std::string& name);
	void removeFunctions(const std::string& name);
	void removeFunction(const std::string& name, size_t argCount);

	Variable& getVariable(const std::string& name) const;
	Function& getFunction(const std::string& name, size_t argCount) const;

private:
	std::unordered_map<std::string, std::unique_ptr<Variable>> variables;
	std::unordered_map<std::string, std::vector<std::unique_ptr<Function>>> functions;
};