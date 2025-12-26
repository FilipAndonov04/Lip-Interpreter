#include "FuncConcat.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/List/List.h"

#include <stdexcept>

std::unique_ptr<Value> FuncConcat::operator()(const std::vector<const Expression*>& args) const {
    assertArgCount(1, args.size(), NAME);
    
    auto arg1 = args[0]->evaluate();
    auto l1 = getList(*arg1);
    if (!l1) {
        throw std::invalid_argument(NAME + " takes a list as a first argument");
    }
    
    auto arg2 = args[1]->evaluate();
    auto l2 = getList(*arg2);
    if (!l2) {
        throw std::invalid_argument(NAME + " takes a list as a second argument");
    }

    for (size_t i = 0; i < l2->length(); i++) {
        l1->pushBack(l2->at(i));
    }

    return arg1;
}
