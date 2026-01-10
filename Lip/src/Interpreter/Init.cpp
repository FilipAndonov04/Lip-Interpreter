#include "Init.h"

#include "Interpreter/Environment/Data/FunctionData.h"
#include "Function/Wrapper/WrapperFunction.hpp"
#include "Value/Number/RealNumber.h"

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
#include "Interpreter/EmbeddedFunctions/InputOutput/FuncRead.h"

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
#include "Interpreter/EmbeddedFunctions/Function/FuncCurry.h"

#include <numbers>

template <typename EmbFunc>
static std::shared_ptr<FunctionData> makeEmbeddedFunction(bool hasArgCount, size_t argCount);
template <typename EmbFunc>
static std::shared_ptr<FunctionData> makeEmbeddedFunction(EmbFunc&& embFunc, bool hasArgCount, size_t argCount);

void initInterpreter(Interpreter& interpreter) {
	initMathModule(interpreter);
	initLogicModule(interpreter);
	initComparisonModule(interpreter);
	initConversionModule(interpreter);
	initFunctionModule(interpreter);
	initInputOutputModule(interpreter);

	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncIf::NAME, makeEmbeddedFunction<FuncIf>(true, 3));

	env.addFunction(FuncHead::NAME, makeEmbeddedFunction<FuncHead>(true, 1));
	env.addFunction(FuncTail::NAME, makeEmbeddedFunction<FuncTail>(true, 1));
	env.addFunction(FuncList::NAME, makeEmbeddedFunction<FuncList>(true, 3));
	env.addFunction(FuncList::NAME, makeEmbeddedFunction<FuncList>(true, 2));
	env.addFunction(FuncList::NAME, makeEmbeddedFunction<FuncList>(true, 1));
	env.addFunction(FuncGenerate::NAME, makeEmbeddedFunction<FuncGenerate>(true, 2));
	env.addFunction(FuncGenerate::NAME, makeEmbeddedFunction<FuncGenerate>(true, 3));

	env.addFunction(FuncLength::NAME, makeEmbeddedFunction<FuncLength>(true, 1));
	env.addFunction(FuncConcat::NAME, makeEmbeddedFunction<FuncConcat>(true, 2));
	env.addFunction(FuncReverse::NAME, makeEmbeddedFunction<FuncReverse>(true, 1));
	env.addFunction(FuncAppend::NAME, makeEmbeddedFunction<FuncAppend>(true, 2));
}

void initMathModule(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncAdd::NAME, makeEmbeddedFunction<FuncAdd>(true, 2));
	env.addFunction(FuncSubtract::NAME, makeEmbeddedFunction<FuncSubtract>(true, 2));
	env.addFunction(FuncMultiply::NAME, makeEmbeddedFunction<FuncMultiply>(true, 2));
	env.addFunction(FuncDivide::NAME, makeEmbeddedFunction<FuncDivide>(true, 2));
	env.addFunction(FuncMod::NAME, makeEmbeddedFunction<FuncMod>(true, 2));
	env.addFunction(FuncSqrt::NAME, makeEmbeddedFunction<FuncSqrt>(true, 1));

	env.addVariable("PI", std::make_unique<VariableData>(RealNumber::of(std::numbers::pi), true));
	env.addVariable("E", std::make_unique<VariableData>(RealNumber::of(std::numbers::e), true));
}

void initLogicModule(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncNot::NAME, makeEmbeddedFunction<FuncNot>(true, 1));
	env.addFunction(FuncAnd::NAME, makeEmbeddedFunction<FuncAnd>(true, 2));
	env.addFunction(FuncOr::NAME, makeEmbeddedFunction<FuncOr>(true, 2));

	env.addVariable("true", std::make_unique<VariableData>(RealNumber::of(1.0), true));
	env.addVariable("false", std::make_unique<VariableData>(RealNumber::of(0.0), true));
}

void initComparisonModule(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncEqual::NAME, makeEmbeddedFunction<FuncEqual>(true, 2));
	env.addFunction(FuncLessThan::NAME, makeEmbeddedFunction<FuncLessThan>(true, 2));
	env.addFunction(FuncNotEqual::NAME, makeEmbeddedFunction<FuncNotEqual>(true, 2));
	env.addFunction(FuncLessOrEqual::NAME, makeEmbeddedFunction<FuncLessOrEqual>(true, 2));
	env.addFunction(FuncGreaterThan::NAME, makeEmbeddedFunction<FuncGreaterThan>(true, 2));
	env.addFunction(FuncGreaterOrEqual::NAME, makeEmbeddedFunction<FuncGreaterOrEqual>(true, 2));
}

void initConversionModule(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncInt::NAME, makeEmbeddedFunction<FuncInt>(true, 1));
	env.addFunction(FuncBool::NAME, makeEmbeddedFunction<FuncBool>(true, 1));
}

void initFunctionModule(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncCompose::NAME, makeEmbeddedFunction<FuncCompose>(false, 0));
	env.addFunction(FuncPipe::NAME, makeEmbeddedFunction<FuncPipe>(false, 0));
	env.addFunction(FuncCurry::NAME, makeEmbeddedFunction<FuncCurry>(false, 0));
}

void initInputOutputModule(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncInput::NAME, makeEmbeddedFunction<FuncInput>(FuncInput{interpreter}, true, 0));
	env.addFunction(FuncPrint::NAME, makeEmbeddedFunction<FuncPrint>(false, 0));
	env.addFunction(FuncRead::NAME, makeEmbeddedFunction<FuncRead>(true, 1));
}

template<typename EmbFunc>
std::shared_ptr<FunctionData> makeEmbeddedFunction(bool hasArgCount, size_t argCount) {
	return std::make_shared<FunctionData>(std::make_unique<WrapperFunction<EmbFunc>>(), 
										  hasArgCount, argCount, true);
}

template<typename EmbFunc>
std::shared_ptr<FunctionData> makeEmbeddedFunction(EmbFunc&& embFunc, bool hasArgCount, size_t argCount) {
	return std::make_shared<FunctionData>(std::make_unique<WrapperFunction<EmbFunc>>(std::move(embFunc)), 
										  hasArgCount, argCount, true);
}