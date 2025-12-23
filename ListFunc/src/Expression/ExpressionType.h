#pragma once

enum class ExpressionType {
	Variable,
	Number,
	List,
	ConcreteList,
	LazyList,
	FiniteList,
	InfiniteList,
	FunctionCall
};

bool isVariable(ExpressionType type);
bool isList(ExpressionType type);