#pragma once
#include "Interpreter/Interpreter.h"

void initInterpreter(Interpreter& interpreter);

void initMathModule(Interpreter& interpreter);
void initLogicModule(Interpreter& interpreter);
void initComparisonModule(Interpreter& interpreter);
void initConversionModule(Interpreter& interpreter);
void initFunctionModule(Interpreter& interpreter);
void initInputOutputModule(Interpreter& interpreter);