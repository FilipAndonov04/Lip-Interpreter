#pragma once

#include <string>

class Expression;

class Value;
class RealNumber;
class String;
class List;
class FunctionObject;

void assertArgCount(size_t expected, size_t actual, const std::string& name);

bool isNumber(const Value& value);
bool isString(const Value& value);
bool isList(const Value& value);
bool isFunctionObject(const Value& value);

const RealNumber* getNumber(const Value& value);
const String* getString(const Value& value);
const List* getList(const Value& value);
const FunctionObject* getFunctionObject(const Value& value);

RealNumber* getNumber(Value& value);
String* getString(Value& value);
List* getList(Value& value);
FunctionObject* getFunctionObject(Value& value);

bool toBool(const Value& value);
std::string toString(const Value& value);