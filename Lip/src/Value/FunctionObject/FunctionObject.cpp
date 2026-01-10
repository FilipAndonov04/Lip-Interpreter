#include "FunctionObject.h"
#include "Interpreter/Environment/Data/FunctionData.h"
#include "Function/Function.h"
#include "Expression/Value/ValueExpression.h"

#include <stdexcept>

FunctionObject::FunctionObject(const FunctionData* function) 
    : functions{function} {}

FunctionObject::FunctionObject(std::vector<const FunctionData*> functions) 
    : functions(std::move(functions)) {}

ValueType FunctionObject::type() const {
    return ValueType::FunctionObject;
}

std::unique_ptr<Value> FunctionObject::cloneValue() const {
    return cloneFunctionObject();
}

std::unique_ptr<FunctionObject> FunctionObject::cloneFunctionObject() const {
    return std::make_unique<FunctionObject>(functions);
}

std::string FunctionObject::toString() const {
    return "funcObj()";
}

std::unique_ptr<Value> FunctionObject::call(const std::vector<const Expression*>& args) const {
    auto res = functions[0]->function->call(args);
    if (functions.size() == 1) {
        return res;
    }

    std::vector<const Expression*> valArgs(1);
    for (size_t i = 1; i < functions.size(); i++) {
        auto expr = ValueExpression::of(std::move(res));

        valArgs[0] = expr.get();
        res = std::move(functions[i]->function->call(valArgs));
    }
    return res;
}

std::unique_ptr<Value> FunctionObject::operator()(const std::vector<const Expression*>& args) const {
    return call(args);
}

const std::vector<const FunctionData*>& FunctionObject::getFunctions() const {
    return functions;
}

void FunctionObject::insertFunction(size_t index, const FunctionData* function) {
    if (index > functions.size()) {
        throw std::out_of_range("index out of bound");
    }

    functions.insert(functions.begin() + index, function);
}

void FunctionObject::pushBackFunction(const FunctionData* function) {
    insertFunction(functions.size(), function);
}

void FunctionObject::pushFrontFunction(const FunctionData* function) {
    insertFunction(0, function);
}

std::unique_ptr<FunctionObject> FunctionObject::of(const FunctionData* function) {
    return std::make_unique<FunctionObject>(function);
}
