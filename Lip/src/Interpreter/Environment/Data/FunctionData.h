#pragma once

#include <memory>

class Function;

struct FunctionData {
	std::unique_ptr<const Function> function;
	bool anyArgCount;
	uint8_t argCount;
	bool isEmbedded;
};