#include "VariableSet.h"

#include <stdexcept>
#include <algorithm>

bool VariableSet::containsVariable(const std::string& name) const {
	return variables.find(name) != variables.end();
}

bool VariableSet::containsFunction(const std::string& name) const {
	return functions.find(name) != functions.end();
}

bool VariableSet::containsFunction(const std::string& name, size_t argCount) const {
	auto sameNamed = functions.find(name);
	if (sameNamed == functions.end()) {
		return false;
	}
	
	auto& funcs = sameNamed->second;
	auto sameArgs = std::find_if(funcs.begin(), funcs.end(), [argCount](const std::unique_ptr<Function>& f) {
		return f->getArgCount() == argCount;
	});
	return sameArgs != funcs.end();
}

void VariableSet::add(const std::string& name, std::unique_ptr<Variable>&& variable) {
	if (containsVariable(name)) {
		throw std::runtime_error("there is already a variable named " + name);
	} else if (containsFunction(name)) {
		throw std::runtime_error("there is already a function named " + name);
	}

	variables.insert({name, std::move(variable)});
}

void VariableSet::add(const std::string& name, std::unique_ptr<Function>&& function) {
	if (containsVariable(name)) {
		throw std::runtime_error("there is already a variable named " + name);
	} else if (containsFunction(name, function->getArgCount())) {
		throw std::runtime_error("there is already a function named " + name + " that takes " + 
								 std::to_string(function->getArgCount()) + " arguments");
	}

	functions[name].push_back(std::move(function));
}

void VariableSet::removeVariable(const std::string& name) {
	auto var = variables.find(name);
	if (var != variables.end()) {
		variables.erase(var);
	}
}

void VariableSet::removeFunctions(const std::string& name) {
	auto funcs = functions.find(name);
	if (funcs != functions.end()) {
		functions.erase(funcs);
	}
}

void VariableSet::removeFunction(const std::string& name, size_t argCount) {
	auto sameNamed = functions.find(name);
	if (sameNamed == functions.end()) {
		return;
	}

	auto& funcs = sameNamed->second;
	auto sameArgs = std::find_if(funcs.begin(), funcs.end(), [argCount](const std::unique_ptr<Function>& f) {
		return f->getArgCount() == argCount;
	});
	if (sameArgs == funcs.end()) {
		return;
	}

	funcs.erase(sameArgs);
	if (funcs.empty()) {
		functions.erase(sameNamed);
	}
}

Variable& VariableSet::getVariable(const std::string& name) const {
	auto var = variables.find(name);
	if (var == variables.end()) {
		throw std::runtime_error("there is not a variable with named " + name);
	}

	return *(var->second);
}

Function& VariableSet::getFunction(const std::string& name, size_t argCount) const {
	auto sameNamed = functions.find(name);
	if (sameNamed == functions.end()) {
		throw std::runtime_error("there is not a function named " + name);
	}

	auto& funcs = sameNamed->second;
	auto sameArgs = std::find_if(funcs.begin(), funcs.end(), [argCount](const std::unique_ptr<Function>& f) {
		return f->getArgCount() == argCount;
	});
	if (sameArgs == funcs.end()) {
		throw std::runtime_error("function " + name + " does not take " + std::to_string(argCount) + " arguments");
	}

	return **sameArgs;
}