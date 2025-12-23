#include "FuncSqrt.h"
#include "Expression/Variable/Number/Real/RealNumber.h"

#include <stdexcept>
#include <cmath>

std::unique_ptr<Expression> FuncSqrt::operator()(const std::vector<const Expression*>& args) const {
	auto arg1 = args[0]->evaluate();

	if (arg1->type() != ExpressionType::RealNumber) {
		throw std::invalid_argument("sqrt takes 1 real number as argument");
	}

	auto n1 = static_cast<const RealNumber*>(arg1.get());
	return RealNumber::of(sqrt(n1->getValue()));
}