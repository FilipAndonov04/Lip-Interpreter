#include "Number.h"

ExpressionType Number::type() const {
	return ExpressionType::Number;
}

std::unique_ptr<Variable> Number::cloneVariable() const {
	return cloneNumber();
}
