#include "Interpreter/Interpreter.h"
#include "Function/Wrapper/WrapperFunction.hpp"

#include "Value/Number/RealNumber.h"
#include "Value/List/Concrete/ConcreteList.h"
#include "Expression/FunctionCall/FunctionCall.h"
#include "Function/Graph/GraphFunction.h"
#include "Function/Graph/Node/Leaf/Argument/ArgumentNode.h"
#include "Function/Graph/Node/Leaf/Expression/ExpressionNode.h"
#include "Function/Graph/Node/Composite/CompositeNode.h"

#include "Interpreter/EmbeddedFunctions/Math/FuncAdd.h"
#include "Interpreter/EmbeddedFunctions/Math/FuncSubtract.h"
#include "Interpreter/EmbeddedFunctions/Math/FuncMultiply.h"
#include "Interpreter/EmbeddedFunctions/Math/FuncDivide.h"
#include "Interpreter/EmbeddedFunctions/Math/FuncMod.h"
#include "Interpreter/EmbeddedFunctions/Math/FuncSqrt.h"

#include "Interpreter/EmbeddedFunctions/Logical/FuncNot.h"
#include "Interpreter/EmbeddedFunctions/Logical/FuncAnd.h"
#include "Interpreter/EmbeddedFunctions/Logical/FuncOr.h"

#include "Interpreter/EmbeddedFunctions/Comparison/FuncEqual.h"
#include "Interpreter/EmbeddedFunctions/Comparison/FuncLessThan.h"
#include "Interpreter/EmbeddedFunctions/Comparison/FuncNotEqual.h"
#include "Interpreter/EmbeddedFunctions/Comparison/FuncLessOrEqual.h"
#include "Interpreter/EmbeddedFunctions/Comparison/FuncGreaterThan.h"
#include "Interpreter/EmbeddedFunctions/Comparison/FuncGreaterOrEqual.h"

#include "Interpreter/EmbeddedFunctions/ControlFlow/FuncIf.h"

#include "Interpreter/EmbeddedFunctions/Conversion/FuncInt.h"
#include "Interpreter/EmbeddedFunctions/Conversion/FuncBool.h"

#include "Interpreter/EmbeddedFunctions/InputOutput/FuncInput.h"
#include "Interpreter/EmbeddedFunctions/InputOutput/FuncPrint.h"

#include "Interpreter/EmbeddedFunctions/List/FuncHead.h"
#include "Interpreter/EmbeddedFunctions/List/FuncTail.h"
#include "Interpreter/EmbeddedFunctions/List/FuncList.h"

#include "Interpreter/EmbeddedFunctions/StringAndList/FuncLength.h"
#include "Interpreter/EmbeddedFunctions/StringAndList/FuncConcat.h"
#include "Interpreter/EmbeddedFunctions/StringAndList/FuncReverse.h"

#include "Utils/StringUtils.h"

#include <iostream>
#include <string>
#include <fstream>

struct Worker {
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const {
		std::cout << "\tDoing work\n";

		return RealNumber::of(1);
	}
};

static Interpreter setUpFunctions();

int main() {
	Interpreter inter = setUpFunctions();
	
	{
		std::ifstream ifs("functions.txt");
		std::string line;
		while (std::getline(ifs, line)) {
			inter.interpret(line);
		}
	}

	while (true) {
		std::cout << "input command: " << Utils::GREEN;
		std::string line;
		std::getline(std::cin, line);
		std::cout << Utils::DEFAULT;

		if (line == "quit") {
			break;
		}

		inter.interpret(line);
	}
}

Interpreter setUpFunctions() {
	Interpreter inter;
	Environment& env = inter.getCurrentEnvironment();

	env.addFunction(FuncAdd::NAME, std::make_unique<WrapperFunction<FuncAdd>>(2));
	env.addFunction(FuncSubtract::NAME, std::make_unique<WrapperFunction<FuncSubtract>>(2));
	env.addFunction(FuncMultiply::NAME, std::make_unique<WrapperFunction<FuncMultiply>>(2));
	env.addFunction(FuncDivide::NAME, std::make_unique<WrapperFunction<FuncDivide>>(2));
	env.addFunction(FuncMod::NAME, std::make_unique<WrapperFunction<FuncMod>>(2));
	env.addFunction(FuncSqrt::NAME, std::make_unique<WrapperFunction<FuncSqrt>>(1));

	env.addFunction(FuncNot::NAME, std::make_unique<WrapperFunction<FuncNot>>(1));
	env.addFunction(FuncAnd::NAME, std::make_unique<WrapperFunction<FuncAnd>>(2));
	env.addFunction(FuncOr::NAME, std::make_unique<WrapperFunction<FuncOr>>(2));

	env.addFunction(FuncEqual::NAME, std::make_unique<WrapperFunction<FuncEqual>>(2));
	env.addFunction(FuncLessThan::NAME, std::make_unique<WrapperFunction<FuncLessThan>>(2));
	env.addFunction(FuncNotEqual::NAME, std::make_unique<WrapperFunction<FuncNotEqual>>(2));
	env.addFunction(FuncLessOrEqual::NAME, std::make_unique<WrapperFunction<FuncLessOrEqual>>(2));
	env.addFunction(FuncGreaterThan::NAME, std::make_unique<WrapperFunction<FuncGreaterThan>>(2));
	env.addFunction(FuncGreaterOrEqual::NAME, std::make_unique<WrapperFunction<FuncGreaterOrEqual>>(2));

	env.addFunction(FuncIf::NAME, std::make_unique<WrapperFunction<FuncIf>>(3));

	env.addFunction(FuncInt::NAME, std::make_unique<WrapperFunction<FuncInt>>(1));
	env.addFunction(FuncInt::NAME, std::make_unique<WrapperFunction<FuncBool>>(1));

	env.addFunction(FuncInput::NAME, std::make_unique<WrapperFunction<FuncInput>>(0, FuncInput{inter}));
	env.addFunction(FuncPrint::NAME, std::make_unique<WrapperFunction<FuncPrint>>(0));
	env.addFunction(FuncPrint::NAME, std::make_unique<WrapperFunction<FuncPrint>>(1));
	env.addFunction(FuncPrint::NAME, std::make_unique<WrapperFunction<FuncPrint>>(2));
	env.addFunction(FuncPrint::NAME, std::make_unique<WrapperFunction<FuncPrint>>(3));
	env.addFunction(FuncPrint::NAME, std::make_unique<WrapperFunction<FuncPrint>>(4));
	env.addFunction(FuncPrint::NAME, std::make_unique<WrapperFunction<FuncPrint>>(5));

	env.addFunction(FuncHead::NAME, std::make_unique<WrapperFunction<FuncHead>>(1));
	env.addFunction(FuncTail::NAME, std::make_unique<WrapperFunction<FuncTail>>(1));
	env.addFunction(FuncList::NAME, std::make_unique<WrapperFunction<FuncList>>(3));
	env.addFunction(FuncList::NAME, std::make_unique<WrapperFunction<FuncList>>(2));
	env.addFunction(FuncList::NAME, std::make_unique<WrapperFunction<FuncList>>(1));

	env.addFunction(FuncLength::NAME, std::make_unique<WrapperFunction<FuncLength>>(1));
	env.addFunction(FuncConcat::NAME, std::make_unique<WrapperFunction<FuncConcat>>(2));
	env.addFunction(FuncReverse::NAME, std::make_unique<WrapperFunction<FuncReverse>>(1));

	// extra
	env.addFunction("work", std::make_unique<WrapperFunction<Worker>>(0));

	return inter;
}