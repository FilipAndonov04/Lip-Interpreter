#include "FuncLength.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/List/List.h"
#include "Value/Number/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Value> FuncLength::operator()(const std::vector<const Expression*>& args) const {
    assertArgCount(1, args.size(), NAME);
    
    auto arg1 = args[0]->evaluate();
    if (!isList(*arg1)) {
        throw std::invalid_argument(NAME + " takes a list as an argument");
    }

    auto l = getList(*arg1);
    return RealNumber::of(static_cast<double>(l->length()));
}
