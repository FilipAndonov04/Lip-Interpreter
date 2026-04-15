#include "FunctionObject.h"
#include "Interpreter/Environment/Data/FunctionData.h"
#include "Function/Function.h"
#include "Expression/Value/ValueExpression.h"

#include <stdexcept>
#include <algorithm>
#include <iterator>

FunctionObject::FunctionObject(const FunctionData* function) 
    : functions{function} {}

FunctionObject::FunctionObject(std::vector<const FunctionData*> functions) 
    : functions(std::move(functions)) {}

FunctionObject::FunctionObject(std::vector<const FunctionData*> functions, 
                               std::vector<std::unique_ptr<Expression>> curryArgs)
    : functions(std::move(functions)), curryArgs(std::move(curryArgs)) {}

ValueType FunctionObject::type() const {
    return ValueType::FunctionObject;
}

std::unique_ptr<Value> FunctionObject::cloneValue() const {
    return cloneFunctionObject();
}

std::unique_ptr<FunctionObject> FunctionObject::cloneFunctionObject() const {
    std::vector<std::unique_ptr<Expression>> curryArgsClones;
    curryArgsClones.reserve(curryArgs.size());

    for (const auto& arg : curryArgs) {
        curryArgsClones.push_back(arg->clone());
    }

    return std::make_unique<FunctionObject>(functions, std::move(curryArgsClones));
}

std::string FunctionObject::toString() const {
    return "funcObj()";
}

std::unique_ptr<Value> FunctionObject::call(const std::vector<const Expression*>& args) const {
    std::vector<const Expression*> allArgs;
    allArgs.reserve(curryArgs.size() + args.size());

    std::transform(curryArgs.begin(), curryArgs.end(), std::back_inserter(allArgs),
                   [](const std::unique_ptr<Expression>& expr) { return expr.get(); });
    std::copy(args.begin(), args.end(), std::back_inserter(allArgs));

    auto res = functions[0]->getFunction()->call(allArgs);
    if (functions.size() == 1) {
        return res;
    }

    std::vector<const Expression*> valArgs(1);
    for (size_t i = 1; i < functions.size(); i++) {
        auto expr = ValueExpression::of(std::move(res));

        valArgs[0] = expr.get();
        res = std::move(functions[i]->getFunction()->call(valArgs));
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

void FunctionObject::pushBackArg(std::unique_ptr<Expression>&& arg) {
    curryArgs.push_back(std::move(arg));
}

std::unique_ptr<FunctionObject> FunctionObject::of(const FunctionData* function) {
    return std::make_unique<FunctionObject>(function);
}
