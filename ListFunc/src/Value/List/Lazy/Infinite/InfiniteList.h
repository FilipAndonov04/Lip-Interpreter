#pragma once
#include "Value/List/Lazy/LazyList.h"

class InfiniteList final : public LazyList {
public:
	InfiniteList(std::unique_ptr<Value>&& initialElement, std::unique_ptr<Function>&& step);
	InfiniteList(std::unique_ptr<List>&& cachedElements, std::unique_ptr<Function>&& step);

	size_t length() const override;

	std::unique_ptr<Value> at(size_t index) const override;

	void insert(size_t index, std::unique_ptr<Value>&& element) override;
	void pushBack(std::unique_ptr<Value>&& element) override;
	void erase(size_t index) override;
	void popBack()override;
	std::unique_ptr<Value> eraseAndGet(size_t index) override;
	std::unique_ptr<Value> popBackAndGet() override;

	std::unique_ptr<List> cloneList() const override;
};