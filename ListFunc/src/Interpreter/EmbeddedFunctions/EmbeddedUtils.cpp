#include "EmbeddedUtils.h"
#include "Value/Number/RealNumber.h"
#include "Value/String/String.h"
#include "Value/List/List.h"
#include "Value/FunctionObject/FunctionObject.h"

#include <stdexcept>

static constexpr double EPSILON = 1e-3;
static constexpr size_t MAX_LIST_COMPARISON_LENGTH = 10000;

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

int compare(const Value& value1, const Value& value2) {
    if (value1.type() != value2.type()) {
        throw std::invalid_argument("not comparable types");
    }

    auto n1 = getNumber(value1);
    if (n1) {
        auto n2 = getNumber(value2);
        if (std::abs(n1->getValue() - n2->getValue()) < EPSILON) {
            return 0;
        }
        return static_cast<int>(n1->getValue() - n2->getValue());
    }

    auto s1 = getString(value1);
    if (s1) {
        auto s2 = getString(value2);
        return strcmp(s1->getString().c_str(), s2->getString().c_str());
    }

    auto l1 = getList(value1);
    if (l1) {
        auto l2 = getList(value2);
        if (l1->length() != l2->length()) {
            return static_cast<int>(l1->length() - l2->length());
        }

        const auto length = std::min(l1->length(), MAX_LIST_COMPARISON_LENGTH);
        for (size_t i = 0; i < length; i++) {
            int cmp = compare(*l1->at(i), *l2->at(i));
            if (cmp != 0) {
                return cmp;
            }
        }
        return 0;
    }

    throw std::invalid_argument("not comparable types");
}
