#include "Init.h"
#include "Value/Number/RealNumber.h"

#include "Interpreter/Environment/Data/FunctionData.h"

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
#include "Interpreter/EmbeddedFunctions/List/FuncGenerate.h"

#include "Interpreter/EmbeddedFunctions/StringAndList/FuncLength.h"
#include "Interpreter/EmbeddedFunctions/StringAndList/FuncConcat.h"
#include "Interpreter/EmbeddedFunctions/StringAndList/FuncReverse.h"
#include "Interpreter/EmbeddedFunctions/StringAndList/FuncAppend.h"

#include "Interpreter/EmbeddedFunctions/Function/FuncCompose.h"
#include "Interpreter/EmbeddedFunctions/Function/FuncPipe.h"

#include "Function/Wrapper/WrapperFunction.hpp"

#include <iostream>

static struct Worker {
	std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const {
		std::cout << "\tDoing work\n";

		return RealNumber::of(1);
	}
};

void initInterpreter(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncAdd::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncAdd>>(), false, 2, true));
	env.addFunction(FuncSubtract::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncSubtract>>(), false, 2, true));
	env.addFunction(FuncMultiply::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncMultiply>>(), false, 2, true));
	env.addFunction(FuncDivide::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncDivide>>(), false, 2, true));
	env.addFunction(FuncMod::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncMod>>(), false, 2, true));
	env.addFunction(FuncSqrt::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncSqrt>>(), false, 1, true));

	env.addFunction(FuncNot::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncNot>>(), false, 1, true));
	env.addFunction(FuncAnd::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncAnd>>(), false, 2, true));
	env.addFunction(FuncOr::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncOr>>(), false, 2, true));

	env.addFunction(FuncEqual::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncEqual>>(), false, 2, true));
	env.addFunction(FuncLessThan::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncLessThan>>(), false, 2, true));
	env.addFunction(FuncNotEqual::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncNotEqual>>(), false, 2, true));
	env.addFunction(FuncLessOrEqual::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncLessOrEqual>>(), false, 2, true));
	env.addFunction(FuncGreaterThan::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncGreaterThan>>(), false, 2, true));
	env.addFunction(FuncGreaterOrEqual::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncGreaterOrEqual>>(), false, 2, true));

	env.addFunction(FuncIf::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncIf>>(), false, 3, true));

	env.addFunction(FuncInt::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncInt>>(), false, 1, true));
	env.addFunction(FuncBool::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncBool>>(), false, 1, true));

	env.addFunction(FuncInput::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncInput>>(FuncInput{interpreter}), false, 0, true));
	env.addFunction(FuncPrint::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncPrint>>(), true, 0, true));

	env.addFunction(FuncHead::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncHead>>(), false, 1, true));
	env.addFunction(FuncTail::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncTail>>(), false, 1, true));
	env.addFunction(FuncList::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncList>>(), false, 3, true));
	env.addFunction(FuncList::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncList>>(), false, 2, true));
	env.addFunction(FuncList::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncList>>(), false, 1, true));
	env.addFunction(FuncGenerate::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncGenerate>>(), false, 2, true));
	env.addFunction(FuncGenerate::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncGenerate>>(), false, 3, true));

	env.addFunction(FuncLength::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncLength>>(), false, 1, true));
	env.addFunction(FuncConcat::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncConcat>>(), false, 2, true));
	env.addFunction(FuncReverse::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncReverse>>(), false, 1, true));
	env.addFunction(FuncAppend::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncAppend>>(), false, 2, true));

	env.addFunction(FuncCompose::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncCompose>>(), true, 0, true));
	env.addFunction(FuncPipe::NAME, std::make_shared<FunctionData>(std::make_unique<WrapperFunction<FuncPipe>>(), true, 0, true));

	// extra work
	env.addFunction("work", std::make_shared<FunctionData>(std::make_unique<WrapperFunction<Worker>>(), false, 0, true));
}