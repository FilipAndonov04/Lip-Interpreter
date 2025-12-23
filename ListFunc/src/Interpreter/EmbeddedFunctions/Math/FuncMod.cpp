#include "FuncMod.h"
#include "Expression/Variable/Number/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Expression> FuncMod::operator()(const std::vector<const Expression*>& args) const {
	auto arg1 = args[0]->evaluate();
	auto arg2 = args[1]->evaluate();

	if (arg1->type() != ExpressionType::Number ||
		arg2->type() != ExpressionType::Number) {
		throw std::invalid_argument("modulo takes 2 integers as arguments");
	}

	auto n1 = static_cast<const RealNumber*>(arg1.get());
	auto n2 = static_cast<const RealNumber*>(arg2.get());
	int i1 = n1->getValue();
	int i2 = n2->getValue();
	if (i1 != n1->getValue() || i2 != n2->getValue()) {
		throw std::invalid_argument("modulo takes 2 integers as arguments");
	}

	return RealNumber::of(i1 % i2);
}