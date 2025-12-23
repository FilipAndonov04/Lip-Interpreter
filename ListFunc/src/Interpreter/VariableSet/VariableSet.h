#pragma once
#include "Value/Value.h"
#include "Function/Function.h"

#include <string>
#include <unordered_map>

class VariableSet {
public:
	VariableSet() = default;
	VariableSet(const VariableSet& other);
	VariableSet(VariableSet&&) noexcept = default;
	VariableSet& operator=(const VariableSet& other);
	VariableSet& operator=(VariableSet&&) noexcept = default;
	~VariableSet() = default;

	bool containsVariable(const std::string& name) const;
	bool containsFunction(const std::string& name) const;
	bool containsFunction(const std::string& name, size_t argCount) const;

	void add(const std::string& name, std::unique_ptr<Value>&& variable);
	void add(const std::string& name, std::unique_ptr<Function>&& function);
	
	void removeVariable(const std::string& name);
	void removeFunctions(const std::string& name);
	void removeFunction(const std::string& name, size_t argCount);

	const Variable* getVariable(const std::string& name) const;
	Value* getVariable(const std::string& name);
	const Function* getFunction(const std::string& name, size_t argCount) const;
	Function* getFunction(const std::string& name, size_t argCount);

private:
	std::unordered_map<std::string, std::unique_ptr<Variable>> variables;
	std::unordered_map<std::string, std::vector<std::unique_ptr<Function>>> functions;
};