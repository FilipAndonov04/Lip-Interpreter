#pragma once

#include <memory>

class Function;

struct FunctionData {
	std::shared_ptr<const Function> function;
	bool isEmbedded;
};