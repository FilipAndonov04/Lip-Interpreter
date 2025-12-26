#include "FuncSqrt.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

#include <stdexcept>
#include <cmath>

std::unique_ptr<Value> FuncSqrt::operator()(const std::vector<const Expression*>& args) const {
	assertArgCount(1, args.size(), NAME);

	auto arg1 = args[0]->evaluate();
	auto num1 = getNumber(*arg1);
	if (!num1) {
		throw std::invalid_argument(NAME + " takes a non-negative number as an argument");
	}

	if (num1->getValue() < 0.0) {
		throw std::invalid_argument(NAME + " takes a non-negative number as an argument");
	}

	return RealNumber::of(sqrt(num1->getValue()));
}