#pragma once

#include <initializer_list>
#include <vector>

class Stack {

	std::vector<int> data;

public:

	Stack() = default;
	Stack(std::initializer_list<int> l) : data(l) {}

	bool empty() const;
	std::size_t size() const;

	void push(int value);
	int pop();
	int peek();

};
