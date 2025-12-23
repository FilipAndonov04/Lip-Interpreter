#pragma once
#include "Expression/Variable/Variable.h"

class List : public Variable {
public:
	virtual size_t length() const = 0;

	virtual std::unique_ptr<Expression> at(size_t index) const = 0;
	virtual std::unique_ptr<Expression> back() const;

	virtual void insert(size_t index, std::unique_ptr<Expression>&& element) = 0;
	virtual void pushBack(std::unique_ptr<Expression>&& element);
	virtual void erase(size_t index) = 0;
	virtual void popBack();
	virtual std::unique_ptr<Expression> eraseAndGet(size_t index) = 0;
	virtual std::unique_ptr<Expression> popBackAndGet();

	std::unique_ptr<Variable> cloneVariable() const override;
	virtual std::unique_ptr<List> cloneList() const = 0;

	std::string toString() const override;

	bool isEmpty() const;

	std::unique_ptr<Expression> operator[](size_t index) const;
	std::unique_ptr<Expression> front() const;
	
	void pushFront(std::unique_ptr<Expression>&& element);
	void popFront();
	std::unique_ptr<Expression> popFrontAndGet();

protected:
	void assertNotEmpty() const;
	void assertAccessIndex(size_t index) const;
	void assertInsertIndex(size_t index) const;
};