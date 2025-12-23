#include "FuncIf.h"

#include <stdexcept>

std::unique_ptr<Expression> FuncIf::operator()(const std::vector<const Expression*>& args) const {
	auto arg1 = args[0]->evaluate();

	if (arg1->type() != ExpressionType::RealNumber) {
		throw std::invalid_argument("if's first argument is real number");
	}

	auto n1 = static_cast<const RealNumber*>(arg1.get());

	return static_cast<bool>(n1->getValue()) ? args[1]->cloneExpression() : args[2]->cloneExpression();
}
