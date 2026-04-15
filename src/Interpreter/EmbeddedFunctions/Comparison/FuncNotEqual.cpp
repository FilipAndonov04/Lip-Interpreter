#include "FuncNotEqual.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

std::unique_ptr<Value> FuncNotEqual::operator()(const std::vector<const Expression*>& args) const {
	assertArgCount(2, args.size(), NAME);

	auto arg1 = args[0]->evaluate();
	auto arg2 = args[1]->evaluate();

	return RealNumber::of(compare(*arg1, *arg2) != 0);
}