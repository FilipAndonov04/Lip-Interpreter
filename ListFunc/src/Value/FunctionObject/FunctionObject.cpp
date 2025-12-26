#include "FunctionObject.h"
#include "Function/Function.h"
#include "Expression/Expression.h"

FunctionObject::FunctionObject(const Function* function) 
    : function(function) {}

ValueType FunctionObject::type() const {
    return ValueType::FunctionObject;
}

std::unique_ptr<Value> FunctionObject::cloneValue() const {
    return cloneFunctionObject();
}

std::unique_ptr<FunctionObject> FunctionObject::cloneFunctionObject() const {
    return of(function);
}

std::string FunctionObject::toString() const {
    return "funcObj()";
}

std::unique_ptr<Value> FunctionObject::call(const std::vector<const Expression*>& args) const {
    return function->call(args);
}

std::unique_ptr<Value> FunctionObject::operator()(const std::vector<const Expression*>& args) const {
    return call(args);
}

const Function* FunctionObject::getFunction() const {
    return function;
}

void FunctionObject::setFunction(const Function* function) {
    this->function = function;
}

std::unique_ptr<FunctionObject> FunctionObject::of(const Function* function) {
    return std::make_unique<FunctionObject>(function);
}
