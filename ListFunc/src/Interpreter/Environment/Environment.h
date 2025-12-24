#pragma once

#include <string>
#include <memory>
#include <unordered_map>

class Function;

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
	
	const Function* getFunction(const std::string& name, size_t argCount) const;
	
	bool addFunction(const std::string& name, const std::shared_ptr<Function>& function);
	bool addFunction(const std::string& name, std::shared_ptr<Function>&& function);

	bool removeFunctions(const std::string& name);
	bool removeFunction(const std::string& name, size_t argCount);

	bool replaceFunction(const std::string& name, const std::shared_ptr<Function>& newFunction);
	bool replaceFunction(const std::string& name, std::shared_ptr<Function>&& newFunction);

	const Environment* getPreviousEnvironment() const;
	void setPreviousEnvironment(std::unique_ptr<Environment>&& environment);

private:
	std::unordered_map<std::string, std::vector<std::shared_ptr<Function>>> functions;
	std::unique_ptr<Environment> previous;
};