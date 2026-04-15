#pragma once
#include "Value/List/List.h"

#include <vector>

class Expression;
class FunctionObject;

class LazyList : public List {
public:
	LazyList(std::unique_ptr<Expression>&& initialElement, std::unique_ptr<FunctionObject>&& step);
	LazyList(std::vector<std::unique_ptr<Value>>&& cachedElements, std::unique_ptr<FunctionObject>&& step);

protected:
	void cacheElement(size_t index) const;
	std::vector<std::unique_ptr<Value>> cloneCachedElements() const;

	mutable std::unique_ptr<Expression> initialElement;
	std::unique_ptr<FunctionObject> step;
	mutable std::vector<std::unique_ptr<Value>> cachedElements;
};