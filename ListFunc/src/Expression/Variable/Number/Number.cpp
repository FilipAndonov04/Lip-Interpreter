#include "Number.h"

std::unique_ptr<Variable> Number::cloneVariable() const {
	return cloneNumber();
}
