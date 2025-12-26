#pragma once

#include <memory>
#include <string>

class Function;

struct FunctionData {
	std::shared_ptr<const Function> function;
	bool isEmbedded;
};