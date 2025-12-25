#include "Interpreter/Interpreter.h"
#include "Function/Wrapper/WrapperFunction.hpp"

#include "Value/Number/RealNumber.h"
#include "Value/List/Concrete/ConcreteList.h"
#include "Expression/Call/Function/FunctionCall.h"
#include "Function/Graph/GraphFunction.h"
#include "Function/Graph/Node/Argument/ArgumentNode.h"
#include "Function/Graph/Node/Literal/LiteralNode.h"
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
#include "Interpreter/EmbeddedFunctions/List/FuncLength.h"
#include "Interpreter/EmbeddedFunctions/List/FuncConcat.h"
#include "Interpreter/EmbeddedFunctions/List/FuncList.h"

#include "StringUtils/StringUtils.h"

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
		std::cout << "input command: " << StringUtils::GREEN;
		std::string line;
		std::getline(std::cin, line);
		std::cout << StringUtils::DEFAULT;

		if (line == "quit") {
			break;
		}

		inter.interpret(line);
	}
}

Interpreter setUpFunctions() {
	Interpreter inter;
	Environment& env = inter.getCurrentEnvironment();

	env.addFunction("add", std::make_unique<WrapperFunction<FuncAdd>>(2));
	env.addFunction("sub", std::make_unique<WrapperFunction<FuncSubtract>>(2));
	env.addFunction("mul", std::make_unique<WrapperFunction<FuncMultiply>>(2));
	env.addFunction("div", std::make_unique<WrapperFunction<FuncDivide>>(2));
	env.addFunction("mod", std::make_unique<WrapperFunction<FuncMod>>(2));
	env.addFunction("sqrt", std::make_unique<WrapperFunction<FuncSqrt>>(1));

	env.addFunction("not", std::make_unique<WrapperFunction<FuncNot>>(1));
	env.addFunction("and", std::make_unique<WrapperFunction<FuncAnd>>(2));
	env.addFunction("or", std::make_unique<WrapperFunction<FuncOr>>(2));

	env.addFunction("eq", std::make_unique<WrapperFunction<FuncEqual>>(2));
	env.addFunction("lt", std::make_unique<WrapperFunction<FuncLessThan>>(2));
	env.addFunction("ne", std::make_unique<WrapperFunction<FuncNotEqual>>(2));
	env.addFunction("le", std::make_unique<WrapperFunction<FuncLessOrEqual>>(2));
	env.addFunction("gt", std::make_unique<WrapperFunction<FuncGreaterThan>>(2));
	env.addFunction("ge", std::make_unique<WrapperFunction<FuncGreaterOrEqual>>(2));

	env.addFunction("if", std::make_unique<WrapperFunction<FuncIf>>(3));

	env.addFunction("int", std::make_unique<WrapperFunction<FuncInt>>(1));
	env.addFunction("bool", std::make_unique<WrapperFunction<FuncBool>>(1));

	env.addFunction("input", std::make_unique<WrapperFunction<FuncInput>>(0, FuncInput{inter}));
	env.addFunction("print", std::make_unique<WrapperFunction<FuncPrint>>(1));

	env.addFunction("head", std::make_unique<WrapperFunction<FuncHead>>(1));
	env.addFunction("tail", std::make_unique<WrapperFunction<FuncTail>>(1));
	env.addFunction("len", std::make_unique<WrapperFunction<FuncLength>>(1));
	env.addFunction("concat", std::make_unique<WrapperFunction<FuncConcat>>(2));
	env.addFunction("list", std::make_unique<WrapperFunction<FuncList>>(3));
	env.addFunction("list", std::make_unique<WrapperFunction<FuncList>>(2));
	env.addFunction("list", std::make_unique<WrapperFunction<FuncList>>(1));

	// extra
	env.addFunction("work", std::make_unique<WrapperFunction<Worker>>(0));

	return inter;
}