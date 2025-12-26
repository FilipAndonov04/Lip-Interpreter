#include "FunctionObject.h"
#include "Function/Function.h"
#include "Expression/Value/ValueExpression.h"

#include <stdexcept>

FunctionObject::FunctionObject(const Function* function) 
    : functions{function} {}

FunctionObject::FunctionObject(std::vector<const Function*> functions) 
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
    auto res = functions[0]->call(args);
    if (functions.size() == 1) {
        return res;
    }

    std::vector<const Expression*> valArgs(1);
    for (size_t i = 1; i < functions.size(); i++) {
        auto expr = ValueExpression::of(std::move(res));

        valArgs[0] = expr.get();
        res = std::move(functions[i]->call(valArgs));
    }
    return res;
}

std::unique_ptr<Value> FunctionObject::operator()(const std::vector<const Expression*>& args) const {
    return call(args);
}

const std::vector<const Function*>& FunctionObject::getFunctions() const {
    return functions;
}

void FunctionObject::addFunction(size_t index, const Function* function) {
    if (index > functions.size()) {
        throw std::out_of_range("index out of bound");
    }

    functions.insert(functions.begin() + index, function);
}

void FunctionObject::pushBackFunction(const Function* function) {
    addFunction(functions.size(), function);
}

void FunctionObject::pushFrontFunction(const Function* function) {
    addFunction(0, function);
}

std::unique_ptr<FunctionObject> FunctionObject::of(const Function* function) {
    return std::make_unique<FunctionObject>(function);
}
