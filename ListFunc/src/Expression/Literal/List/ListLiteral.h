#pragma once
#include "Expression/Literal/Literal.h"

#include <vector>

class ListLiteral final : public Literal {
public:
	ListLiteral() = default;
	explicit ListLiteral(std::vector<std::unique_ptr<Expression>>&& elements);

	std::unique_ptr<Value> evaluate() const override;

	ExpressionType type() const override;

	std::unique_ptr<Literal> cloneLiteral() const override;

	std::string toString() const override;

	size_t length() const;
	bool isEmpty() const;

	const Expression& at(size_t index) const;
	const Expression& operator[](size_t index) const;
	const Expression& front() const;
	const Expression& back() const;

	void insert(size_t index, std::unique_ptr<Expression>&& element);
	void pushFront(std::unique_ptr<Expression>&& element);
	void pushBack(std::unique_ptr<Expression>&& element);

	void erase(size_t index);
	void popFront();
	void popBack();

	std::unique_ptr<Expression> eraseAndGet(size_t index);
	std::unique_ptr<Expression> popFrontAndGet();
	std::unique_ptr<Expression> popBackAndGet();

private:
	void assertNotEmpty() const;
	void assertAccessIndex(size_t index) const;
	void assertInsertIndex(size_t index) const;

	std::vector<std::unique_ptr<Expression>> elements;
};