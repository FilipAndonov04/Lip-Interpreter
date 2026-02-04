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
#include "Interpreter/EmbeddedFunctions/InputOutput/FuncWrite.h"

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

	env.addFunction(FuncIf::NAME, makeEmbeddedFunction<FuncIf>(false, 3));

	env.addFunction(FuncHead::NAME, makeEmbeddedFunction<FuncHead>(false, 1));
	env.addFunction(FuncTail::NAME, makeEmbeddedFunction<FuncTail>(false, 1));
	env.addFunction(FuncList::NAME, makeEmbeddedFunction<FuncList>(false, 3));
	env.addFunction(FuncList::NAME, makeEmbeddedFunction<FuncList>(false, 2));
	env.addFunction(FuncList::NAME, makeEmbeddedFunction<FuncList>(false, 1));
	env.addFunction(FuncGenerate::NAME, makeEmbeddedFunction<FuncGenerate>(false, 2));
	env.addFunction(FuncGenerate::NAME, makeEmbeddedFunction<FuncGenerate>(false, 3));

	env.addFunction(FuncLength::NAME, makeEmbeddedFunction<FuncLength>(false, 1));
	env.addFunction(FuncConcat::NAME, makeEmbeddedFunction<FuncConcat>(false, 2));
	env.addFunction(FuncReverse::NAME, makeEmbeddedFunction<FuncReverse>(false, 1));
	env.addFunction(FuncAppend::NAME, makeEmbeddedFunction<FuncAppend>(false, 2));
}

void initMathModule(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncAdd::NAME, makeEmbeddedFunction<FuncAdd>(false, 2));
	env.addFunction(FuncSubtract::NAME, makeEmbeddedFunction<FuncSubtract>(false, 2));
	env.addFunction(FuncMultiply::NAME, makeEmbeddedFunction<FuncMultiply>(false, 2));
	env.addFunction(FuncDivide::NAME, makeEmbeddedFunction<FuncDivide>(false, 2));
	env.addFunction(FuncMod::NAME, makeEmbeddedFunction<FuncMod>(false, 2));
	env.addFunction(FuncSqrt::NAME, makeEmbeddedFunction<FuncSqrt>(false, 1));

	env.addVariable("PI", std::make_unique<VariableData>(RealNumber::of(std::numbers::pi), true));
	env.addVariable("E", std::make_unique<VariableData>(RealNumber::of(std::numbers::e), true));
}

void initLogicModule(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncNot::NAME, makeEmbeddedFunction<FuncNot>(false, 1));
	env.addFunction(FuncAnd::NAME, makeEmbeddedFunction<FuncAnd>(false, 2));
	env.addFunction(FuncOr::NAME, makeEmbeddedFunction<FuncOr>(false, 2));

	env.addVariable("TRUE", std::make_unique<VariableData>(RealNumber::of(1.0), true));
	env.addVariable("FALSE", std::make_unique<VariableData>(RealNumber::of(0.0), true));
}

void initComparisonModule(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncEqual::NAME, makeEmbeddedFunction<FuncEqual>(false, 2));
	env.addFunction(FuncLessThan::NAME, makeEmbeddedFunction<FuncLessThan>(false, 2));
	env.addFunction(FuncNotEqual::NAME, makeEmbeddedFunction<FuncNotEqual>(false, 2));
	env.addFunction(FuncLessOrEqual::NAME, makeEmbeddedFunction<FuncLessOrEqual>(false, 2));
	env.addFunction(FuncGreaterThan::NAME, makeEmbeddedFunction<FuncGreaterThan>(false, 2));
	env.addFunction(FuncGreaterOrEqual::NAME, makeEmbeddedFunction<FuncGreaterOrEqual>(false, 2));
}

void initConversionModule(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncInt::NAME, makeEmbeddedFunction<FuncInt>(false, 1));
	env.addFunction(FuncBool::NAME, makeEmbeddedFunction<FuncBool>(false, 1));
}

void initFunctionModule(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncCompose::NAME, makeEmbeddedFunction<FuncCompose>(true, 0));
	env.addFunction(FuncPipe::NAME, makeEmbeddedFunction<FuncPipe>(true, 0));
	env.addFunction(FuncCurry::NAME, makeEmbeddedFunction<FuncCurry>(true, 0));
}

void initInputOutputModule(Interpreter& interpreter) {
	Environment& env = interpreter.getCurrentEnvironment();

	env.addFunction(FuncInput::NAME, makeEmbeddedFunction<FuncInput>(FuncInput{interpreter}, false, 0));
	env.addFunction(FuncPrint::NAME, makeEmbeddedFunction<FuncPrint>(true, 0));
	env.addFunction(FuncRead::NAME, makeEmbeddedFunction<FuncRead>(false, 1));
	env.addFunction(FuncWrite::NAME, makeEmbeddedFunction<FuncWrite>(false, 3));
}

template<typename EmbFunc>
std::shared_ptr<FunctionData> makeEmbeddedFunction(bool isVarArgs, size_t argCount) {
	return std::make_shared<FunctionData>(std::make_unique<WrapperFunction<EmbFunc>>(), 
										  isVarArgs, argCount, true);
}

template<typename EmbFunc>
std::shared_ptr<FunctionData> makeEmbeddedFunction(EmbFunc&& embFunc, bool isVarArgs, size_t argCount) {
	return std::make_shared<FunctionData>(std::make_unique<WrapperFunction<EmbFunc>>(std::move(embFunc)), 
										  isVarArgs, argCount, true);
}