#pragma once

#include <memory>

class Function;

class FunctionData {
public:
	FunctionData() = default;
	FunctionData(std::unique_ptr<Function>&& function, bool isVarArgs, 
				 uint8_t argCount, bool isEmbedded);

	const Function* getFunction() const;
	bool getIsVarArgs() const;
	uint8_t getArgCount() const;
	bool getIsEmbedded() const;
	
	void setFunction(std::unique_ptr<Function>&& function);
	void setIsVarArgs(bool isVarArgs);
	void setArgCount(uint8_t argCount);
	void setIsEmbedded(bool isEmbedded);

private:
	std::unique_ptr<const Function> function;
	bool isVarArgs;
	uint8_t argCount;
	bool isEmbedded;
};