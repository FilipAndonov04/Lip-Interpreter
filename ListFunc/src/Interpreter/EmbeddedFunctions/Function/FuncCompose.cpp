#include "FuncCompose.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/FunctionObject/FunctionObject.h"

#include <stdexcept>

std::unique_ptr<Value> FuncCompose::operator()(const std::vector<const Expression*>& args) const {
    assertArgCount(2, args.size(), NAME);

    auto arg1 = args[0]->evaluate();
    auto f1 = getFunctionObject(*arg1);
    if (!f1) {
        throw std::invalid_argument(NAME + " takes a function as a first argument");
    }
    
    auto arg2 = args[1]->evaluate();
    auto f2 = getFunctionObject(*arg2);
    if (!f2) {
        throw std::invalid_argument(NAME + " takes a function as a second argument");
    }

    const auto& f1funcs = f1->getFunctions();
    for (const auto& func : f1funcs) {
        f2->pushBackFunction(func);
    }

    return arg2;
}
