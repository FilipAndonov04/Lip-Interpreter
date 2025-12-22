#pragma once
#include "Expression/Variable/List/List.h"

#include <vector>

class ConcreteList final : public List {
public:
	ConcreteList() = default;
	explicit ConcreteList(std::vector<std::unique_ptr<Variable>>&& elements);

	size_t length() const override;

	const Variable& at(size_t index) const override;
	Variable& at(size_t index) override;

	void insert(size_t index, std::unique_ptr<Variable>&& element) override;
	void erase(size_t index) override;
	std::unique_ptr<Variable> eraseAndGet(size_t index) override;

	std::unique_ptr<List> cloneList() const override;

private:
	std::vector<std::unique_ptr<Variable>> elements;
};