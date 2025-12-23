#pragma once
#include "Expression/Variable/List/List.h"

#include <vector>

class ConcreteList final : public List {
public:
	ConcreteList() = default;
	explicit ConcreteList(std::vector<std::unique_ptr<Expression>>&& elements);

	size_t length() const override;

	std::unique_ptr<Expression> at(size_t index) const override;

	void insert(size_t index, std::unique_ptr<Expression>&& element) override;
	void erase(size_t index) override;
	std::unique_ptr<Expression> eraseAndGet(size_t index) override;

	std::unique_ptr<List> cloneList() const override;

private:
	std::vector<std::unique_ptr<Expression>> elements;
};