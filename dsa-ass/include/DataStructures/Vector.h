#pragma once

#include <memory>

template <class T>
class Vector
{
private:
	// pointer to start of array
    std::unique_ptr<T[]> arr;

	// maximum number of elements the vector can hold
	size_t maxCapacity;

	// the current number of elements in the vector
	size_t currentCapacity;
public:

	// empty constructor
	Vector();

	// desctructor
	~Vector();

	// move constructor
	Vector(Vector&& other) noexcept;

	// move operator
	Vector& operator=(Vector&& other) noexcept;

	// appends an item to the back of the vector
	void push(T item);

	// gets item at index specified
	T get(size_t pos);

	// checks if an item exists
	bool contains(T item);

	// returns the number of elements in the vector
	size_t length();
};

#include "../../src/DataStructures/Vector.cpp"

