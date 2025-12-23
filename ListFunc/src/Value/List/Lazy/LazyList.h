#pragma once
#include "Value/List/List.h"

class Function;

class LazyList : public List {
public:
	LazyList(std::unique_ptr<Value>&& initialElement, std::unique_ptr<Function>&& step);
	LazyList(std::unique_ptr<List>&& cachedElements, std::unique_ptr<Function>&& step);

protected:
	void cacheElement(size_t index) const;

	std::unique_ptr<List> cachedElements;
	std::unique_ptr<Function> step;
};