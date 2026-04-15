#include "FuncList.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Expression/Literal/Number/NumberLiteral.h"
#include "Value/List/Lazy/Finite/FiniteList.h"
#include "Value/List/Lazy/Infinite/InfiniteList.h"
#include "Value/Number/RealNumber.h"
#include "Function/Wrapper/WrapperFunction.hpp"
#include "Interpreter/Environment/Data/FunctionData.h"

#include <stdexcept>

struct StepAdd {
    std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const {
        auto arg1 = args[0]->evaluate();
        auto n1 = getNumber(*arg1);
        
        auto arg2 = args[1]->evaluate();
        auto n2 = getNumber(*arg2);

        return RealNumber::of(n1->getValue() + n2->getValue());
    }
};

std::unique_ptr<FunctionData> FuncList::step = std::make_unique<FunctionData>(std::make_unique<WrapperFunction<StepAdd>>(), true, 2, false);

std::unique_ptr<Value> FuncList::operator()(const std::vector<const Expression*>& args) const {
    if (args.size() == 1) {
        auto arg1 = args[0]->evaluate();
        if (!isNumber(*arg1)) {
            throw std::invalid_argument(NAME + " takes a number as a first argument");
        }
        
        auto func = FunctionObject::of(step.get());
        func->pushBackArg(NumberLiteral::of(1.0));
        return std::make_unique<InfiniteList>(args[0]->clone(), std::move(func));
    } else if (args.size() == 2) {
        auto arg1 = args[0]->evaluate();
        if (!isNumber(*arg1)) {
            throw std::invalid_argument(NAME + " takes a number as a first argument");
        }

        auto arg2 = args[1]->evaluate();
        auto n2 = getNumber(*arg2);
        if (!n2) {
            throw std::invalid_argument(NAME + " takes a number as a second argument");
        }

        auto func = FunctionObject::of(step.get());
        func->pushBackArg(NumberLiteral::of(n2->getValue()));
        return std::make_unique<InfiniteList>(args[0]->clone(), std::move(func));
    } else if (args.size() == 3) {
        auto arg1 = args[0]->evaluate();
        if (!isNumber(*arg1)) {
            throw std::invalid_argument(NAME + " takes a number as a first argument");
        }

        auto arg2 = args[1]->evaluate();
        auto n2 = getNumber(*arg2);
        if (!n2) {
            throw std::invalid_argument(NAME + " takes a number as a second argument");
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

        auto func = FunctionObject::of(step.get());
        func->pushBackArg(NumberLiteral::of(n2->getValue()));
        return std::make_unique<FiniteList>(args[0]->clone(), std::move(func), i3);
    }

    throw std::invalid_argument(NAME + " expects 1,2 or 3 arguments, but was called with " + 
                                std::to_string(args.size()));
}
