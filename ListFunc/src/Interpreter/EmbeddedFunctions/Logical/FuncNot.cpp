#include "FuncNot.h"
#include "Expression/Variable/Number/Real/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Expression> FuncNot::operator()(const std::vector<const Expression*>& args) const {
	auto arg1 = args[0]->evaluate();

	if (arg1->type() != ExpressionType::RealNumber) {
		throw std::invalid_argument("not takes 1 real numbers as arguments");
	}

	auto n1 = static_cast<const RealNumber*>(arg1.get());
	return RealNumber::of(!n1->getValue());
}