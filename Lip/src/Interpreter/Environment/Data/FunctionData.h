#pragma once

#include <memory>

class Function;

struct FunctionData {
	std::unique_ptr<const Function> function;
	bool hasArgCount;
	uint8_t argCount;
	bool isEmbedded;
};