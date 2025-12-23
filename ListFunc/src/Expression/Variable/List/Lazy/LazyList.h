#pragma once
#include "Expression/Variable/List/List.h"

class Function;

class LazyList : public List {
public:
	LazyList(std::unique_ptr<Expression>&& initialElement, std::unique_ptr<Function>&& step);
	LazyList(std::unique_ptr<List>&& cachedElements, std::unique_ptr<Function>&& step);

	ExpressionType type() const override;

protected:
	void cacheElement(size_t index) const;

	std::unique_ptr<List> cachedElements;
	std::unique_ptr<Function> step;
};