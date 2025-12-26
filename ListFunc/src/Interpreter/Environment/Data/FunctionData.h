#pragma once

#include <memory>
#include <string>

class Function;

struct FunctionData {
	std::unique_ptr<const Function> function;
	bool isEmbedded;
	std::string description;
};