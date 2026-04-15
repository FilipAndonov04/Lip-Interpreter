#include "FuncIf.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

std::unique_ptr<Value> FuncIf::operator()(const std::vector<const Expression*>& args) const {
	assertArgCount(3, args.size(), NAME);

	auto arg1 = args[0]->evaluate();
	return toBool(*arg1) ? args[1]->evaluate() : args[2]->evaluate();
}
