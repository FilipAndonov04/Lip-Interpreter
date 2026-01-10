#pragma once
#include "Value/List/Lazy/LazyList.h"

class FiniteList final : public LazyList {
public:
	FiniteList(std::unique_ptr<Expression>&& initialElement,
			   std::unique_ptr<FunctionObject>&& step, size_t elementCount);
	FiniteList(std::vector<std::unique_ptr<Value>>&& cachedElements, 
			   std::unique_ptr<FunctionObject>&& step, size_t elementCount);

	size_t length() const override;

	std::unique_ptr<Value> at(size_t index) const override;

	void set(size_t index, std::unique_ptr<Value>&& element) override;

	void insert(size_t index, std::unique_ptr<Value>&& element) override;
	void erase(size_t index) override;
	std::unique_ptr<Value> eraseAndGet(size_t index) override;

	std::unique_ptr<List> cloneList() const override;

private:
	size_t elementCount;
};