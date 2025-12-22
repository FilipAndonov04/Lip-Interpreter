#pragma once
#include "Expression/Variable/Variable.h"

class List : public Variable {
public:
	virtual size_t length() const = 0;

	virtual const Variable& at(size_t index) const = 0;
	virtual Variable& at(size_t index) = 0;
	virtual const Variable& back() const;
	virtual Variable& back();

	virtual void insert(size_t index, std::unique_ptr<Variable>&& element) = 0;
	virtual void pushBack(std::unique_ptr<Variable>&& element);
	virtual void erase(size_t index) = 0;
	virtual void popBack();
	virtual std::unique_ptr<Variable> eraseAndGet(size_t index) = 0;
	virtual std::unique_ptr<Variable> popBackAndGet();

	std::unique_ptr<Variable> cloneVariable() const override;
	virtual std::unique_ptr<List> cloneList() const = 0;

	std::string toString() const override;

	bool isEmpty() const;

	const Variable& operator[](size_t index) const;
	Variable& operator[](size_t index);
	const Variable& front() const;
	Variable& front();
	
	void pushFront(std::unique_ptr<Variable>&& element);
	void popFront();
	std::unique_ptr<Variable> popFrontAndGet();

protected:
	void assertNotEmpty() const;
	void assertAccessIndex(size_t index) const;
	void assertInsertIndex(size_t index) const;
};