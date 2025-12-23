#pragma once

enum class ExpressionType {
	Variable,
	Number,
	RealNumber,
	List,
	ConcreteList,
	LazyList,
	FiniteList,
	InfiniteList,
	FunctionCall
};

bool isVariable(ExpressionType type);
bool isNumber(ExpressionType type);
bool isList(ExpressionType type);