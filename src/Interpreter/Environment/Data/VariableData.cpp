#include "VariableData.h"
#include "Value/Value.h"

VariableData::VariableData(std::unique_ptr<Value>&& value, bool isConst) 
    : value(std::move(value)), isConst(isConst) {}

const Value* VariableData::getValue() const {
    return value.get();
}

bool VariableData::getIsConst() const {
    return isConst;
}

void VariableData::setValue(std::unique_ptr<Value>&& value) {
    this->value = std::move(value);
}

void VariableData::setIsConst(bool isConst) {
    this->isConst = isConst;
}