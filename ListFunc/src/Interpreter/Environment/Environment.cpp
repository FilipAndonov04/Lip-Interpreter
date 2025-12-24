#include "Environment.h"
#include "Function/Function.h"

#include <stdexcept>
#include <algorithm>

Environment::Environment(const Environment& other) 
	: functions(other.functions) {}

Environment& Environment::operator=(const Environment& other) {
	if (this != &other) {
		functions = other.functions;
		previous.reset();
	}
	return *this;
}

bool Environment::containsFunction(const std::string& name) const {
	return functions.find(name) != functions.end();
}

bool Environment::containsFunction(const std::string& name, size_t argCount) const {
	return getFunction(name, argCount) != nullptr;
}

const Function* Environment::getFunction(const std::string& name, size_t argCount) const {
	auto funcsByName = functions.find(name);
	if (funcsByName == functions.end()) {
		return nullptr;
	}

	const auto& container = funcsByName->second;
	auto hasSameArgCount = [argCount](const std::shared_ptr<Function>& f) {
		return f->getArgCount() == argCount;
	};
	
	auto func = std::find_if(container.cbegin(), container.cend(), hasSameArgCount);
	return func != container.end() ? func->get() : nullptr;
}

bool Environment::addFunction(const std::string& name, const std::shared_ptr<Function>& function) {
	auto& container = functions[name];

	auto hasSameArgCount = [argCount = function->getArgCount()](const std::shared_ptr<Function>& f) {
		return f->getArgCount() == argCount;
	};

	auto func = std::find_if(container.begin(), container.end(), hasSameArgCount);
	if (func != container.end()) {
		return false;
	}

	container.push_back(function);
	return true;
}

bool Environment::addFunction(const std::string& name, std::shared_ptr<Function>&& function) {
	auto& container = functions[name];

	auto hasSameArgCount = [argCount = function->getArgCount()](const std::shared_ptr<Function>& f) {
		return f->getArgCount() == argCount;
	};

	auto func = std::find_if(container.begin(), container.end(), hasSameArgCount);
	if (func != container.end()) {
		return false;
	}

	container.push_back(std::move(function));
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
	auto hasSameArgCount = [argCount](const std::shared_ptr<Function>& f) {
		return f->getArgCount() == argCount;
	};

	auto func = std::find_if(container.begin(), container.end(), hasSameArgCount);
	if (func == container.end()) {
		return false;
	}

	container.erase(func);
	if (container.empty()) {
		functions.erase(funcsByName);
	}
	return true;
}

bool Environment::replaceFunction(const std::string& name, const std::shared_ptr<Function>& newFunction) {
	auto funcsByName = functions.find(name);
	if (funcsByName == functions.end()) {
		return false;
	}

	auto& container = funcsByName->second;
	auto hasSameArgCount = [argCount = newFunction->getArgCount()](const std::shared_ptr<Function>& f) {
		return f->getArgCount() == argCount;
	};

	auto func = std::find_if(container.begin(), container.end(), hasSameArgCount);
	if (func == container.end()) {
		return false;
	}

	container.erase(func);
	container.push_back(newFunction);
	return true;
}

bool Environment::replaceFunction(const std::string& name, std::shared_ptr<Function>&& newFunction) {
	auto funcsByName = functions.find(name);
	if (funcsByName == functions.end()) {
		return false;
	}

	auto& container = funcsByName->second;
	auto hasSameArgCount = [argCount = newFunction->getArgCount()](const std::shared_ptr<Function>& f) {
		return f->getArgCount() == argCount;
	};

	auto func = std::find_if(container.begin(), container.end(), hasSameArgCount);
	if (func == container.end()) {
		return false;
	}

	container.erase(func);
	container.push_back(std::move(newFunction));
	return true;
}

const Environment* Environment::getPreviousEnvironment() const {
	return previous.get();
}

void Environment::setPreviousEnvironment(std::unique_ptr<Environment>&& environment) {
	previous = std::move(environment);
}
