#include "FuncAppend.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/List/List.h"

#include <stdexcept>

std::unique_ptr<Value> FuncAppend::operator()(const std::vector<const Expression*>& args) const {
    assertArgCount(2, args.size(), NAME);

    auto arg1 = args[0]->evaluate();
    auto l1 = getList(*arg1);
    if (!l1) {
        throw std::invalid_argument(NAME + " takes a list as a first argument");
    }

    auto arg2 = args[1]->evaluate();
    l1->pushBack(std::move(arg2));

    return arg1;
}
