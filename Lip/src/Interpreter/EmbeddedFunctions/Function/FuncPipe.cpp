#include "FuncPipe.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/FunctionObject/FunctionObject.h"

#include <stdexcept>

std::unique_ptr<Value> FuncPipe::operator()(const std::vector<const Expression*>& args) const {
    auto arg1 = args[0]->evaluate();
    auto f1 = getFunctionObject(*arg1);
    if (!f1) {
        throw std::invalid_argument(NAME + " takes a function as a first argument");
    }

    for (size_t i = 1; i < args.size(); i++) {
        auto arg2 = args[i]->evaluate();
        auto f2 = getFunctionObject(*arg2);
        if (!f2) {
            throw std::invalid_argument(NAME + " takes a function as a second argument");
        }

        const auto& f2funcs = f2->getFunctions();
        for (const auto& func : f2funcs) {
            f1->pushBackFunction(func);
        }
    }

    return arg1;
}