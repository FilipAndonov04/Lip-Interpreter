#pragma once
#include "Data/FunctionData.h"
#include "Data/VariableData.h"

#include <string>
#include <memory>
#include <unordered_map>

class Environment {
public:
	bool containsFunction(const std::string& name) const;
	bool containsFunction(const std::string& name, uint8_t argCount) const;
	bool containsVariable(const std::string& name) const;
	
	const Function* getFunction(const std::string& name, uint8_t argCount) const;
	const FunctionData* getFunctionData(const std::string& name, uint8_t argCount) const;
	const Value* getVariable(const std::string& name) const;
	const VariableData* getVariableData(const std::string& name) const;

	std::unique_ptr<Value> getVariableOrFunctionObject(const std::string& name) const;
	std::unique_ptr<Value> getFunctionObject(const std::string& name) const;
	std::unique_ptr<Value> getFunctionObject(const std::string& name, size_t argCount) const;
	
	bool addFunction(const std::string& name, const std::shared_ptr<FunctionData>& functionData);
	bool addFunction(const std::string& name, std::shared_ptr<FunctionData>&& functionData);
	bool addVariable(const std::string& name, std::unique_ptr<VariableData>&& variableData);

	bool removeFunctions(const std::string& name);
	bool removeFunction(const std::string& name, size_t argCount);
	bool removeVariable(const std::string& name);

	bool replaceVariable(const std::string& name, std::unique_ptr<VariableData>&& variableData);

private:
	std::unordered_map<std::string, std::vector<std::shared_ptr<const FunctionData>>> functions;
	std::unordered_map<std::string, std::shared_ptr<const VariableData>> variables;
};