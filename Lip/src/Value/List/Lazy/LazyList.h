#pragma once
#include "Value/List/List.h"

class Expression;
class FunctionObject;

class LazyList : public List {
public:
	LazyList(std::unique_ptr<Expression>&& initialElement, std::unique_ptr<FunctionObject>&& step);
	LazyList(std::unique_ptr<List>&& cachedElements, std::unique_ptr<FunctionObject>&& step);

protected:
	void cacheElement(size_t index) const;

	mutable std::unique_ptr<Expression> initialElement;
	std::unique_ptr<FunctionObject> step;
	mutable std::unique_ptr<List> cachedElements;
};