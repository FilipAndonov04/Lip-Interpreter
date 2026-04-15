#include "FuncCurry.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/FunctionObject/FunctionObject.h"

#include <stdexcept>

std::unique_ptr<Value> FuncCurry::operator()(const std::vector<const Expression*>& args) const {
    auto arg1 = args[0]->evaluate();
    auto f1 = getFunctionObject(*arg1);
    if (!f1) {
        throw std::invalid_argument(NAME + " takes a function as a first argument");
    }

    for (size_t i = 1; i < args.size(); i++) {
        f1->pushBackArg(args[i]->clone());
    }

    return arg1;
}
