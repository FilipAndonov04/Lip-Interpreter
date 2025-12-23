#pragma once
#include "Expression/Variable/List/Lazy/LazyList.h"

class InfiniteList final : public LazyList {
public:
	InfiniteList(std::unique_ptr<Expression>&& initialElement, std::unique_ptr<Function>&& step);
	InfiniteList(std::unique_ptr<List>&& cachedElements, std::unique_ptr<Function>&& step);

	size_t length() const override;

	std::unique_ptr<Expression> at(size_t index) const override;

	void insert(size_t index, std::unique_ptr<Expression>&& element) override;
	void pushBack(std::unique_ptr<Expression>&& element) override;
	void erase(size_t index) override;
	void popBack()override;
	std::unique_ptr<Expression> eraseAndGet(size_t index) override;
	std::unique_ptr<Expression> popBackAndGet() override;

	ExpressionType type() const override;

	std::unique_ptr<List> cloneList() const override;
};