#include "FuncMod.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Value> FuncMod::operator()(const std::vector<const Expression*>& args) const {
	assertArgCount(2, args.size(), NAME);
	
	auto arg1 = args[0]->evaluate();
	auto num1 = getNumber(*arg1);
	if (!num1) {
		throw std::invalid_argument(NAME + " takes a number as a first argument");
	}

	auto arg2 = args[1]->evaluate();
	auto num2 = getNumber(*arg2);
	if (!num2) {
		throw std::invalid_argument(NAME + " takes a number as a second argument");
	}

	auto i1 = static_cast<int>(num1->getValue());
	auto i2 = static_cast<int>(num2->getValue());
	if (i1 != num1->getValue()) {
		throw std::invalid_argument(NAME + " takes an integer as a first argument");
	} else if (i2 != num2->getValue()) {
		throw std::invalid_argument(NAME + " takes an integer as a second argument");
	}

	return RealNumber::of(i1 % i2);
}