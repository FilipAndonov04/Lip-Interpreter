#pragma once
#include "Value/List/List.h"

#include <vector>

class ConcreteList final : public List {
public:
	ConcreteList() = default;
	explicit ConcreteList(std::vector<std::unique_ptr<Value>>&& elements);

	size_t length() const override;

	std::unique_ptr<Value> at(size_t index) const override;

	void set(size_t index, std::unique_ptr<Value>&& element) override;

	void insert(size_t index, std::unique_ptr<Value>&& element) override;
	void erase(size_t index) override;
	std::unique_ptr<Value> eraseAndGet(size_t index) override;

	std::unique_ptr<List> cloneList() const override;

private:
	std::vector<std::unique_ptr<Value>> elements;
};