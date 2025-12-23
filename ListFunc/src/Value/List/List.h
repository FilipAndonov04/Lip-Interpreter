#pragma once
#include "Value/Value.h"

class List : public Value {
public:
	virtual size_t length() const = 0;

	virtual std::unique_ptr<Value> at(size_t index) const = 0;
	virtual std::unique_ptr<Value> back() const;

	virtual void insert(size_t index, std::unique_ptr<Value>&& element) = 0;
	virtual void pushBack(std::unique_ptr<Value>&& element);
	virtual void erase(size_t index) = 0;
	virtual void popBack();
	virtual std::unique_ptr<Value> eraseAndGet(size_t index) = 0;
	virtual std::unique_ptr<Value> popBackAndGet();

	std::unique_ptr<Value> cloneValue() const override;
	virtual std::unique_ptr<List> cloneList() const = 0;

	std::string toString() const override;

	bool isEmpty() const;

	std::unique_ptr<Value> operator[](size_t index) const;
	std::unique_ptr<Value> front() const;
	
	void pushFront(std::unique_ptr<Value>&& element);
	void popFront();
	std::unique_ptr<Value> popFrontAndGet();

protected:
	void assertNotEmpty() const;
	void assertAccessIndex(size_t index) const;
	void assertInsertIndex(size_t index) const;
};