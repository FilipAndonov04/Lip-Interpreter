#include "FuncLength.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/List/List.h"
#include "Value/String/String.h"
#include "Value/Number/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Value> FuncLength::operator()(const std::vector<const Expression*>& args) const {
    assertArgCount(1, args.size(), NAME);
    
    auto arg1 = args[0]->evaluate();

    auto l = getList(*arg1);
    if (l) {
        return RealNumber::of(static_cast<double>(l->length()));
    }
    
    auto s = getString(*arg1);
    if (s) {
        return RealNumber::of(static_cast<double>(s->getString().length()));
    }

    throw std::invalid_argument(NAME + " takes a string or a list as an argument");
}
