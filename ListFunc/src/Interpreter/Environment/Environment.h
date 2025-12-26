#pragma once
#include "Data/FunctionData.h"
#include "Data/VariableData.h"

#include <string>
#include <memory>
#include <unordered_map>

class Environment {
public:
	Environment() = default;
	Environment(const Environment& other);
	Environment(Environment&&) noexcept = default;
	Environment& operator=(const Environment& other);
	Environment& operator=(Environment&&) noexcept = default;
	~Environment() = default;

	bool containsFunction(const std::string& name) const;
	bool containsFunction(const std::string& name, size_t argCount) const;
	bool containsVariable(const std::string& name) const;
	
	const Function* getFunction(const std::string& name, size_t argCount) const;
	const FunctionData* getFunctionData(const std::string& name, size_t argCount) const;
	const Value* getVariable(const std::string& name) const;
	const VariableData* getVariableData(const std::string& name) const;
	
	bool addFunction(const std::string& name, const std::shared_ptr<Function>& function, 
					 bool isEmbedded = false);
	bool addFunction(const std::string& name, std::shared_ptr<Function>&& function, 
					 bool isEmbedded = false);
	bool addVariable(const std::string& name, std::unique_ptr<Value>&& value, bool isConst);

	bool removeFunctions(const std::string& name);
	bool removeFunction(const std::string& name, size_t argCount);
	bool removeVariable(const std::string& name);

	bool replaceFunction(const std::string& name, const std::shared_ptr<Function>& newFunction, 
						 bool isEmbedded = false);
	bool replaceFunction(const std::string& name, std::shared_ptr<Function>&& newFunction, 
						 bool isEmbedded = false);
	bool replaceVariable(const std::string& name, std::unique_ptr<Value>&& newValue, bool isConst);

	const Environment* getPreviousEnvironment() const;
	Environment* getPreviousEnvironment();
	void setPreviousEnvironment(std::unique_ptr<Environment>&& environment);

private:
	std::unordered_map<std::string, std::vector<std::shared_ptr<const FunctionData>>> functions;
	std::unordered_map<std::string, std::shared_ptr<const VariableData>> variables;

	std::unique_ptr<Environment> previous;
};