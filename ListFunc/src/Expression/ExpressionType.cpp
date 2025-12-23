#include "ExpressionType.h"

bool isVariable(ExpressionType type) {
	switch (type) {
	case ExpressionType::Variable:
	case ExpressionType::Number:
	case ExpressionType::RealNumber:
	case ExpressionType::List:
	case ExpressionType::ConcreteList:
	case ExpressionType::LazyList:
	case ExpressionType::FiniteList:
	case ExpressionType::InfiniteList:
		return true;
	case ExpressionType::FunctionCall:
		return false;
	}

	throw 0;
}

bool isNumber(ExpressionType type) {
	switch (type) {
	case ExpressionType::Variable:
		return false;
	case ExpressionType::Number:
	case ExpressionType::RealNumber:
		return true;
	case ExpressionType::List:
	case ExpressionType::ConcreteList:
	case ExpressionType::LazyList:
	case ExpressionType::FiniteList:
	case ExpressionType::InfiniteList:
	case ExpressionType::FunctionCall:
		return false;
	}

	throw 0;
}

bool isList(ExpressionType type) {
	switch (type) {
	case ExpressionType::Variable:
	case ExpressionType::Number:
	case ExpressionType::RealNumber:
		return false;
	case ExpressionType::List:
	case ExpressionType::ConcreteList:
	case ExpressionType::LazyList:
	case ExpressionType::FiniteList:
	case ExpressionType::InfiniteList:
		return true;
	case ExpressionType::FunctionCall:
		return false;
	}

	throw 0;
}
