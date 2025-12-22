#pragma once
#include "Expression/Variable/List/Lazy/LazyList.h"

class FiniteList final : public LazyList {
public:
	FiniteList(std::unique_ptr<Variable>&& initialElement, 
			   std::unique_ptr<Function>&& step, size_t elementCount);
	FiniteList(std::unique_ptr<List>&& cachedElements, 
			   std::unique_ptr<Function>&& step, size_t elementCount);

	size_t length() const override;

	const Variable& at(size_t index) const override;
	Variable& at(size_t index) override;

	void insert(size_t index, std::unique_ptr<Variable>&& element) override;
	void erase(size_t index) override;
	std::unique_ptr<Variable> eraseAndGet(size_t index) override;

	std::unique_ptr<List> cloneList() const override;

private:
	size_t elementCount;
};