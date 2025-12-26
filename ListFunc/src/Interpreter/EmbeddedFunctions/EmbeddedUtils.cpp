#include "EmbeddedUtils.h"
#include "Value/Number/RealNumber.h"
#include "Value/String/String.h"
#include "Value/List/List.h"
#include "Value/FunctionObject/FunctionObject.h"

#include <stdexcept>

void assertArgCount(size_t expected, size_t actual, const std::string& name) {
    if (expected != actual) {
        throw std::invalid_argument(name + " expected " + std::to_string(expected) +
                                    "arguments, but was called with " + std::to_string(actual));
    }
}

bool isNumber(const Value& value) {
    return value.type() == ValueType::Number;
}

bool isString(const Value& value) {
    return value.type() == ValueType::String;
}

bool isList(const Value& value) {
    return value.type() == ValueType::List;
}

bool isFunctionObject(const Value& value) {
    return value.type() == ValueType::FunctionObject;
}

const RealNumber* getNumber(const Value& value) {
    return isNumber(value) ? static_cast<const RealNumber*>(&value) : nullptr;
}

const String* getString(const Value& value) {
    return isString(value) ? static_cast<const String*>(&value) : nullptr;
}

const List* getList(const Value& value) {
    return isList(value) ? static_cast<const List*>(&value) : nullptr;
}

const FunctionObject* getFunctionObject(const Value& value) {
    return isFunctionObject(value) ? static_cast<const FunctionObject*>(&value) : nullptr;
}

RealNumber* getNumber(Value& value) {
    return isNumber(value) ? static_cast<RealNumber*>(&value) : nullptr;
}

String* getString(Value& value) {
    return isString(value) ? static_cast<String*>(&value) : nullptr;
}

List* getList(Value& value) {
    return isList(value) ? static_cast<List*>(&value) : nullptr;
}

FunctionObject* getFunctionObject(Value& value) {
    return isFunctionObject(value) ? static_cast<FunctionObject*>(&value) : nullptr;
}

bool toBool(const Value& value) {
    if (auto num = getNumber(value)) {
        return num->getValue();
    } else if (auto str = getString(value)) {
        return !str->getString().empty();
    } else if (auto list = getList(value)) {
        return !list->isEmpty();
    } else if (auto func = getFunctionObject(value)) {
        return false;
    }

    return false;
}

std::string toString(const Value& value) {
    return value.toString();
}
