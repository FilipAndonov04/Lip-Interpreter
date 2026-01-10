#pragma once
#include "Value/List/Lazy/LazyList.h"
#include "Value/FunctionObject/FunctionObject.h"

class InfiniteList final : public LazyList {
public:
	InfiniteList(std::unique_ptr<Expression>&& initialElement, std::unique_ptr<FunctionObject>&& step);
	InfiniteList(std::vector<std::unique_ptr<Value>>&& cachedElements, std::unique_ptr<FunctionObject>&& step);

	size_t length() const override;

	std::unique_ptr<Value> at(size_t index) const override;
	std::unique_ptr<Value> back() const override;

	void set(size_t index, std::unique_ptr<Value>&& element) override;
	
	void insert(size_t index, std::unique_ptr<Value>&& element) override;
	void pushBack(std::unique_ptr<Value>&& element) override;
	void erase(size_t index) override;
	void popBack()override;
	std::unique_ptr<Value> eraseAndGet(size_t index) override;
	std::unique_ptr<Value> popBackAndGet() override;

	std::unique_ptr<List> cloneList() const override;
};