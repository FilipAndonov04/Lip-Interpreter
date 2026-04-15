#include "FuncGenerate.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Interpreter/Environment/Data/FunctionData.h"
#include "Expression/Expression.h"
#include "Value/List/Lazy/Finite/FiniteList.h"
#include "Value/List/Lazy/Infinite/InfiniteList.h"
#include "Value/Number/RealNumber.h"
#include "Value/FunctionObject/FunctionObject.h"
#include "Function/Wrapper/WrapperFunction.hpp"

#include <stdexcept>

std::unique_ptr<Value> FuncGenerate::operator()(const std::vector<const Expression*>& args) const {
   if (args.size() == 2) {
        auto arg2 = args[1]->evaluate();
        auto f2 = getFunctionObject(*arg2);
        if (!f2) {
            throw std::invalid_argument(NAME + " takes a function as a second argument");
        }

        arg2.release();
        return std::make_unique<InfiniteList>(args[0]->clone(), std::unique_ptr<FunctionObject>(f2));
    } else if (args.size() == 3) {
        auto arg2 = args[1]->evaluate();
        auto f2 = getFunctionObject(*arg2);
        if (!f2) {
            throw std::invalid_argument(NAME + " takes a function as a second argument");
        }

        auto arg3 = args[2]->evaluate();
        auto n3 = getNumber(*arg3);
        if (!n3) {
            throw std::invalid_argument(NAME + " takes a non-negative integer as a third argument");
        }

        auto i3 = static_cast<int>(n3->getValue());
        if (i3 < 0 || i3 != n3->getValue()) {
            throw std::invalid_argument(NAME + " takes a non-negative integer as a third argument");
        }

        arg2.release();
        return std::make_unique<FiniteList>(args[0]->clone(), std::unique_ptr<FunctionObject>(f2), i3);
    }

    throw std::invalid_argument(NAME + " expects 2 or 3 arguments, but was called with " +
                                std::to_string(args.size()));
}