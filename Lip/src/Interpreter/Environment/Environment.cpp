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

bool Environment::containsFunction(const std::string& name, uint8_t argCount) const {
	return getFunction(name, argCount);
}

bool Environment::containsVariable(const std::string& name) const {
	return getVariable(name);
}

const Function* Environment::getFunction(const std::string& name, uint8_t argCount) const {
	auto funcData = getFunctionData(name, argCount);
	return funcData ? funcData->function.get() : nullptr;
}

struct isFunctionContained {
	uint8_t argCount;

	isFunctionContained(uint8_t argCount)
		: argCount(argCount) {}

	bool operator()(const std::shared_ptr<const FunctionData>& fd) const {
		return !fd->hasArgCount || fd->argCount == argCount;
	}
};

const FunctionData* Environment::getFunctionData(const std::string& name, uint8_t argCount) const {
	auto funcDatasByName = functions.find(name);
	if (funcDatasByName == functions.end()) {
		return nullptr;
	}

	const auto& container = funcDatasByName->second;

	auto funcData = std::find_if(container.cbegin(), container.cend(), isFunctionContained{argCount});
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
		return FunctionObject::of(funcs->second[0].get());
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
	auto func = getFunctionData(name, argCount);
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

bool Environment::addFunction(const std::string& name, const std::shared_ptr<FunctionData>& functionData) {
	if (containsVariable(name)) {
		return false;
	}

	auto& funcDatas = functions[name];

	auto funcData = std::find_if(funcDatas.begin(), funcDatas.end(), 
								 isFunctionContained{functionData->argCount});
	if (funcData != funcDatas.end()) {
		return false;
	}

	funcDatas.push_back(functionData);
	return true;
}

bool Environment::addFunction(const std::string& name, std::shared_ptr<FunctionData>&& functionData) {
	if (containsVariable(name)) {
		return false;
	}

	auto& funcDatas = functions[name];

	auto funcData = std::find_if(funcDatas.begin(), funcDatas.end(), 
								 isFunctionContained{functionData->argCount});
	if (funcData != funcDatas.end()) {
		return false;
	}

	funcDatas.push_back(std::move(functionData));
	return true;
}

bool Environment::addVariable(const std::string& name, std::unique_ptr<VariableData>&& variableData) {
	if (containsVariable(name) || containsFunction(name)) {
		return false;
	}

	variables.insert({name, std::move(variableData)});
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
		return fd->argCount == argCount;
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

bool Environment::replaceVariable(const std::string& name, std::unique_ptr<VariableData>&& variableData) {
	auto varDataByName = variables.find(name);
	if (varDataByName == variables.end()) {
		return false;
	}

	auto& varData = varDataByName->second;
	if (varData->isConst) {
		return false;
	}

	varData = std::move(variableData);
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