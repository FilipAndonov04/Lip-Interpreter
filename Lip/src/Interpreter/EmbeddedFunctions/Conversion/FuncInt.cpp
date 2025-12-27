#include "FuncInt.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Value> FuncInt::operator()(const std::vector<const Expression*>& args) const {
	assertArgCount(1, args.size(), NAME);

	auto arg1 = args[0]->evaluate();
	auto num1 = getNumber(*arg1);
	if (!num1) {
		throw std::invalid_argument(NAME + " takes a number as an argument");
	}

	return RealNumber::of(static_cast<int>(num1->getValue()));
}
