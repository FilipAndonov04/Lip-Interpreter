#include "Interpreter/Interpreter.h"
#include "Function/Wrapper/WrapperFunction.hpp"

#include "Expression/Variable/Number/RealNumber.h"
#include "Expression/Variable/List/Concrete/ConcreteList.h"
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

#include <iostream>
#include <string>
#include <fstream>

struct Worker {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const {
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
		std::cout << "input command: ";
		std::string line;
		std::getline(std::cin, line);

		if (line == "quit") {
			break;
		}

		inter.interpret(line);
	}
}

Interpreter setUpFunctions() {
	Interpreter inter;
	VariableSet& varSet = inter.getVariableSet();

	varSet.add("add", std::make_unique<WrapperFunction<FuncAdd>>(2));
	varSet.add("sub", std::make_unique<WrapperFunction<FuncSubtract>>(2));
	varSet.add("mul", std::make_unique<WrapperFunction<FuncMultiply>>(2));
	varSet.add("div", std::make_unique<WrapperFunction<FuncDivide>>(2));
	varSet.add("mod", std::make_unique<WrapperFunction<FuncMod>>(2));
	varSet.add("sqrt", std::make_unique<WrapperFunction<FuncSqrt>>(1));

	varSet.add("not", std::make_unique<WrapperFunction<FuncNot>>(1));
	varSet.add("and", std::make_unique<WrapperFunction<FuncAnd>>(2));
	varSet.add("or", std::make_unique<WrapperFunction<FuncOr>>(2));

	varSet.add("eq", std::make_unique<WrapperFunction<FuncEqual>>(2));
	varSet.add("lt", std::make_unique<WrapperFunction<FuncLessThan>>(2));
	varSet.add("ne", std::make_unique<WrapperFunction<FuncNotEqual>>(2));
	varSet.add("le", std::make_unique<WrapperFunction<FuncLessOrEqual>>(2));
	varSet.add("gt", std::make_unique<WrapperFunction<FuncGreaterThan>>(2));
	varSet.add("ge", std::make_unique<WrapperFunction<FuncGreaterOrEqual>>(2));

	varSet.add("if", std::make_unique<WrapperFunction<FuncIf>>(3));

	varSet.add("int", std::make_unique<WrapperFunction<FuncInt>>(1));
	varSet.add("bool", std::make_unique<WrapperFunction<FuncBool>>(1));

	varSet.add("input", std::make_unique<WrapperFunction<FuncInput>>(0, FuncInput{varSet}));
	varSet.add("print", std::make_unique<WrapperFunction<FuncPrint>>(1));

	varSet.add("head", std::make_unique<WrapperFunction<FuncHead>>(1));
	varSet.add("tail", std::make_unique<WrapperFunction<FuncTail>>(1));
	varSet.add("len", std::make_unique<WrapperFunction<FuncLength>>(1));
	varSet.add("concat", std::make_unique<WrapperFunction<FuncConcat>>(2));
	varSet.add("list", std::make_unique<WrapperFunction<FuncList>>(3));
	varSet.add("list", std::make_unique<WrapperFunction<FuncList>>(2));
	varSet.add("list", std::make_unique<WrapperFunction<FuncList>>(1));

	// extra
	varSet.add("work", std::make_unique<WrapperFunction<Worker>>(0));

	// variables
	varSet.add("pi", RealNumber::of(3.14));
	varSet.add("e", RealNumber::of(2.71828));
	varSet.add("a", RealNumber::of(1));
	varSet.add("b", RealNumber::of(-5.5));

	return inter;
}