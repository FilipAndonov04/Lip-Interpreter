#pragma once

#include <memory>
#include <string>

class Function;

struct FunctionData {
	std::unique_ptr<const Function> function;
	std::string name;
	std::string description;
	bool isEmbedded;
};