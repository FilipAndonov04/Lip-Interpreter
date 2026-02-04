#include "FunctionData.h"
#include "Function/Function.h"

FunctionData::FunctionData(std::unique_ptr<Function>&& function, bool isVarArgs, 
                           uint8_t argCount, bool isEmbedded)
    : function(std::move(function)), isVarArgs(isVarArgs), argCount(argCount),
      isEmbedded(isEmbedded) {}

const Function* FunctionData::getFunction() const {
    return function.get();
}

uint8_t FunctionData::getArgCount() const {
    return argCount;
}

bool FunctionData::getIsVarArgs() const {
    return isVarArgs;
}

bool FunctionData::getIsEmbedded() const {
    return isEmbedded;
}

void FunctionData::setFunction(std::unique_ptr<Function>&& function) {
    this->function = std::move(function);
}

void FunctionData::setIsVarArgs(bool isVarArgs) {
    this->isVarArgs = isVarArgs;
}

void FunctionData::setArgCount(uint8_t argCount) {
    this->argCount = argCount;
}

void FunctionData::setIsEmbedded(bool isEmbedded) {
    this->isEmbedded = isEmbedded;
}