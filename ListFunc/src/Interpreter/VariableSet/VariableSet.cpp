#include "VariableSet.h"

#include <stdexcept>
#include <algorithm>

VariableSet::VariableSet(const VariableSet& other) {
	variables.reserve(other.variables.size());
	for (const auto& var : other.variables) {
		variables.insert({var.first, var.second->cloneValue()});
	}

	functions.reserve(other.functions.size());
	for (const auto& funcs : other.functions) {
		std::vector<std::unique_ptr<Function>> clonedFuncs;
		clonedFuncs.reserve(funcs.second.size());

		for (const auto& f : funcs.second) {
			clonedFuncs.push_back(f->clone());
		}

		functions.insert({funcs.first, std::move(clonedFuncs)});
	}
}

VariableSet& VariableSet::operator=(const VariableSet& other) {
	if (this != &other) {
		VariableSet temp(other);
		*this = std::move(temp);
	}
	return *this;
}

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

void VariableSet::add(const std::string& name, std::unique_ptr<Value>&& variable) {
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

const Value* VariableSet::getVariable(const std::string& name) const {
	auto var = variables.find(name);
	if (var == variables.end()) {
		return nullptr;
	}

	return var->second.get();
}

Value* VariableSet::getVariable(const std::string& name) {
	auto var = variables.find(name);
	if (var == variables.end()) {
		return nullptr;
	}

	return var->second.get();
}

const Function* VariableSet::getFunction(const std::string& name, size_t argCount) const {
	auto sameNamed = functions.find(name);
	if (sameNamed == functions.end()) {
		return nullptr;
	}

	auto& funcs = sameNamed->second;
	auto sameArgs = std::find_if(funcs.begin(), funcs.end(), [argCount](const std::unique_ptr<Function>& f) {
		return f->getArgCount() == argCount;
	});
	if (sameArgs == funcs.end()) {
		return nullptr;
	}

	return sameArgs->get();
}

Function* VariableSet::getFunction(const std::string& name, size_t argCount) {
	auto sameNamed = functions.find(name);
	if (sameNamed == functions.end()) {
		return nullptr;
	}

	auto& funcs = sameNamed->second;
	auto sameArgs = std::find_if(funcs.begin(), funcs.end(), [argCount](const std::unique_ptr<Function>& f) {
		return f->getArgCount() == argCount;
	});
	if (sameArgs == funcs.end()) {
		return nullptr;
	}

	return sameArgs->get();
}