#include "FuncDivide.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Value> FuncDivide::operator()(const std::vector<const Expression*>& args) const {
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

	if (num2->getValue() == 0.0) {
		throw std::invalid_argument("cannot divide by zero");
	}

	return RealNumber::of(num1->getValue() / num2->getValue());
}