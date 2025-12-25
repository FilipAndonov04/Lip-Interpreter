#pragma once

#include <string>
#include <memory>
#include <unordered_map>

class Function;
class Value;

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
	const Value* getVariable(const std::string& name) const;
	
	bool addFunction(const std::string& name, const std::shared_ptr<Function>& function);
	bool addFunction(const std::string& name, std::shared_ptr<Function>&& function);
	bool addVariable(const std::string& name, const std::shared_ptr<Value>& value);
	bool addVariable(const std::string& name, std::shared_ptr<Value>&& value);

	bool removeFunctions(const std::string& name);
	bool removeFunction(const std::string& name, size_t argCount);
	bool removeVariable(const std::string& name);

	bool replaceFunction(const std::string& name, const std::shared_ptr<Function>& newFunction);
	bool replaceFunction(const std::string& name, std::shared_ptr<Function>&& newFunction);
	bool replaceVariable(const std::string& name, const std::shared_ptr<Value>& newValue);
	bool replaceVariable(const std::string& name, std::shared_ptr<Value>&& newValue);

	const Environment* getPreviousEnvironment() const;
	void setPreviousEnvironment(std::unique_ptr<Environment>&& environment);

private:
	std::unordered_map<std::string, std::vector<std::shared_ptr<Function>>> functions;
	std::unordered_map<std::string, std::shared_ptr<Value>> variables;

	std::unique_ptr<Environment> previous;
};