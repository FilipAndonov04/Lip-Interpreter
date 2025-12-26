#include "Environment.h"
#include "Function/Function.h"
#include "Value/FunctionObject/FunctionObject.h"

#include <stdexcept>
#include <algorithm>

Environment::Environment(const Environment& other) 
	: functions(other.functions), variables(other.variables) {}

Environment& Environment::operator=(const Environment& other) {
	if (this != &other) {
		functions = other.functions;
		variables = other.variables;
		previous.reset();
	}
	return *this;
}

bool Environment::containsFunction(const std::string& name) const {
	return functions.find(name) != functions.end();
}

bool Environment::containsFunction(const std::string& name, size_t argCount) const {
	return getFunction(name, argCount);
}

bool Environment::containsVariable(const std::string& name) const {
	return getVariable(name);
}

const Function* Environment::getFunction(const std::string& name, size_t argCount) const {
	auto funcData = getFunctionData(name, argCount);
	return funcData ? funcData->function.get() : nullptr;
}

const FunctionData* Environment::getFunctionData(const std::string& name, size_t argCount) const {
	auto funcDatasByName = functions.find(name);
	if (funcDatasByName == functions.end()) {
		return nullptr;
	}

	const auto& container = funcDatasByName->second;
	auto hasSameArgCount = [argCount](const std::shared_ptr<const FunctionData>& fd) {
		return fd->function->getArgCount() == argCount;
	};

	auto funcData = std::find_if(container.cbegin(), container.cend(), hasSameArgCount);
	return funcData != container.end() ? funcData->get() : nullptr;
}

const Value* Environment::getVariable(const std::string& name) const {
	auto varData = getVariableData(name);
	return varData ? varData->value.get() : nullptr;
}

const VariableData* Environment::getVariableData(const std::string& name) const {
	auto varData = variables.find(name);
	return varData != variables.end() ? varData->second.get() : nullptr;
}

std::unique_ptr<Value> Environment::getVariableOrFunctionObject(const std::string& name) const {
	if (auto var = getVariable(name)) {
		return var->cloneValue();
	}

	return getFunctionObject(name);
}

std::unique_ptr<Value> Environment::getFunctionObject(const std::string& name) const {
	auto funcs = functions.find(name);
	if (funcs != functions.end() && funcs->second.size() == 1) {
		return FunctionObject::of(funcs->second[0]->function.get());
	}

	auto var = getVariable(name);
	if (var && var->type() == ValueType::FunctionObject) {
		auto funcObj = static_cast<const FunctionObject*>(var);
		return funcObj->cloneFunctionObject();
	}

	return nullptr;
}

std::unique_ptr<Value> Environment::getFunctionObject(const std::string& name, 
															   size_t argCount) const {
	auto func = getFunction(name, argCount);
	if (func) {
		return FunctionObject::of(func);
	}

	auto var = getVariable(name);
	if (var && var->type() == ValueType::FunctionObject) {
		auto funcObj = static_cast<const FunctionObject*>(var);
		return funcObj->cloneFunctionObject();
	}

	return nullptr;
}

bool Environment::addFunction(const std::string& name, 
							  const std::shared_ptr<Function>& function, bool isEmbedded) {
	if (containsVariable(name)) {
		return false;
	}

	auto& container = functions[name];

	auto hasSameArgCount = [argCount = function->getArgCount()](const std::shared_ptr<const FunctionData>& fd) {
		return fd->function->getArgCount() == argCount;
	};

	auto funcData = std::find_if(container.begin(), container.end(), hasSameArgCount);
	if (funcData != container.end()) {
		return false;
	}

	container.push_back(std::make_shared<FunctionData>(function, isEmbedded));
	return true;
}

bool Environment::addFunction(const std::string& name, 
							  std::shared_ptr<Function>&& function, bool isEmbedded) {
	if (containsVariable(name)) {
		return false;
	}

	auto& container = functions[name];

	auto hasSameArgCount = [argCount = function->getArgCount()](const std::shared_ptr<const FunctionData>& fd) {
		return fd->function->getArgCount() == argCount;
	};

	auto funcData = std::find_if(container.begin(), container.end(), hasSameArgCount);
	if (funcData != container.end()) {
		return false;
	}

	container.push_back(std::make_shared<FunctionData>(std::move(function), isEmbedded));
	return true;
}

bool Environment::addVariable(const std::string& name, std::unique_ptr<Value>&& value, 
							  bool isConst) {
	if (containsVariable(name) || containsFunction(name)) {
		return false;
	}

	variables[name] = std::make_shared<VariableData>(std::move(value), isConst);
	return true;
}

bool Environment::removeFunctions(const std::string& name) {
	auto funcs = functions.find(name);
	if (funcs == functions.end()) {
		return false;
	}

	functions.erase(funcs);
	return true;
}

bool Environment::removeFunction(const std::string& name, size_t argCount) {
	auto funcsByName = functions.find(name);
	if (funcsByName == functions.end()) {
		return false;
	}

	auto& container = funcsByName->second;
	auto hasSameArgCount = [argCount](const std::shared_ptr<const FunctionData>& fd) {
		return fd->function->getArgCount() == argCount;
	};

	auto funcData = std::find_if(container.begin(), container.end(), hasSameArgCount);
	if (funcData == container.end()) {
		return false;
	}

	container.erase(funcData);
	if (container.empty()) {
		functions.erase(funcsByName);
	}
	return true;
}

bool Environment::removeVariable(const std::string& name) {
	auto varData = variables.find(name);
	if (varData == variables.end()) {
		return false;
	}

	if (varData->second->isConst) {
		return false;
	}

	variables.erase(varData);
	return true;
}

bool Environment::replaceFunction(const std::string& name, 
								  const std::shared_ptr<Function>& newFunction, bool isEmbedded) {
	auto funcDatasByName = functions.find(name);
	if (funcDatasByName == functions.end()) {
		return false;
	}

	auto& container = funcDatasByName->second;
	auto hasSameArgCount = [argCount = newFunction->getArgCount()](const std::shared_ptr<const FunctionData>& fd) {
		return fd->function->getArgCount() == argCount;
	};

	auto funcData = std::find_if(container.begin(), container.end(), hasSameArgCount);
	if (funcData == container.end()) {
		return false;
	}

	container.erase(funcData);
	container.push_back(std::make_shared<FunctionData>(newFunction, isEmbedded));
	return true;
}

bool Environment::replaceFunction(const std::string& name, 
								  std::shared_ptr<Function>&& newFunction, bool isEmbedded) {
	auto funcDatasByName = functions.find(name);
	if (funcDatasByName == functions.end()) {
		return false;
	}

	auto& container = funcDatasByName->second;
	auto hasSameArgCount = [argCount = newFunction->getArgCount()](const std::shared_ptr<const FunctionData>& fd) {
		return fd->function->getArgCount() == argCount;
	};

	auto funcData = std::find_if(container.begin(), container.end(), hasSameArgCount);
	if (funcData == container.end()) {
		return false;
	}

	container.erase(funcData);
	container.push_back(std::make_shared<FunctionData>(std::move(newFunction), isEmbedded));
	return true;
}

bool Environment::replaceVariable(const std::string& name, std::unique_ptr<Value>&& newValue,
								  bool isConst) {
	auto varDataByName = variables.find(name);
	if (varDataByName == variables.end()) {
		return false;
	}

	auto& varData = varDataByName->second;
	if (varData->isConst) {
		return false;
	}

	varData = std::make_shared<VariableData>(std::move(newValue), isConst);
	return true;
}

const Environment* Environment::getPreviousEnvironment() const {
	return previous.get();
}

Environment* Environment::getPreviousEnvironment() {
	return previous.get();
}

void Environment::setPreviousEnvironment(std::unique_ptr<Environment>&& environment) {
	previous = std::move(environment);
}
