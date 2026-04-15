#include "FunctionCall.h"
#include "Value/FunctionObject/FunctionObject.h"

#include <stdexcept>

FunctionCall::FunctionCall(std::unique_ptr<Expression>&& function)
    : function(std::move(function)) {}

FunctionCall::FunctionCall(std::unique_ptr<Expression>&& function,
                           std::vector<std::unique_ptr<Expression>>&& args)
    : function(std::move(function)), args(std::move(args)) {}


std::unique_ptr<Value> FunctionCall::evaluate() const {
    auto val = function->evaluate();
    if (val->type() != ValueType::FunctionObject) {
        throw std::invalid_argument("function in function call is not a function");
    }

    auto func = static_cast<const FunctionObject*>(val.get());
    return func->call(getArgs());
}

std::unique_ptr<Expression> FunctionCall::clone() const {
    std::vector<std::unique_ptr<Expression>> clonedArgs;
    clonedArgs.reserve(args.size());

    for (const auto& arg : args) {
        clonedArgs.push_back(arg->clone());
    }

    return std::make_unique<FunctionCall>(function->clone(), std::move(clonedArgs));
}

std::string FunctionCall::toString() const {
    std::string s = "(" + function->toString() + ", " + "(";

    for (size_t i = 0; i < args.size(); i++) {
        s.append(args[i]->toString()).append(i != args.size() - 1 ? ", " : "");
    }

    s.append("))");
    return s;
}

std::vector<const Expression*> FunctionCall::getArgs() const {
    std::vector<const Expression*> argRefs;
    argRefs.reserve(args.size());

    for (const auto& arg : args) {
        argRefs.push_back(arg.get());
    }

    return argRefs;
}
