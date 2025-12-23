#pragma once
#include "Expression/Variable/List/Lazy/LazyList.h"

class FiniteList final : public LazyList {
public:
	FiniteList(std::unique_ptr<Expression>&& initialElement,
			   std::unique_ptr<Function>&& step, size_t elementCount);
	FiniteList(std::unique_ptr<List>&& cachedElements, 
			   std::unique_ptr<Function>&& step, size_t elementCount);

	size_t length() const override;

	std::unique_ptr<Expression> at(size_t index) const override;

	void insert(size_t index, std::unique_ptr<Expression>&& element) override;
	void erase(size_t index) override;
	std::unique_ptr<Expression> eraseAndGet(size_t index) override;

	ExpressionType type() const override;

	std::unique_ptr<List> cloneList() const override;

private:
	size_t elementCount;
};