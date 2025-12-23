#include "FuncTail.h"
#include "Expression/Variable/List/List.h"

#include <stdexcept>

std::unique_ptr<Expression> FuncTail::operator()(const std::vector<const Expression*>& args) const {
    auto arg1 = args[0]->evaluate();
    
    if (!isList(arg1->type())) {
        throw std::invalid_argument("tail argument must be a list");
    }

    auto l1 = static_cast<List*>(arg1.get());
    l1->popFront();
    return arg1;
}
