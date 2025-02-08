/*
* NAME: RYAN HO
* ID: S10261024
* GROUP: 
* FEATURES:
* - unique_ptr for arr which automatically manages the deletion of it when it goes out of bounds (e.g. assigned a new pointer) 
* - vector automatically resizes (by creating a new raw array) when it hits a threshold
*/

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

	// copy constructor
	Vector(const Vector& other) noexcept;

	// copy operator
	Vector& operator=(const Vector& other) noexcept;

	/*
	@brief appends an item to the back of the vector

	@param item - the item to append

	@returns void
	*/
	void push(T item);

	/*
	@brief gets item at index specified

	@param pos - the index of the item

	@returns T& - reference to the item
	*/
	T& get(size_t pos);

	/*
	@brief checks if an item is in the vector

	@param item - the item to check for

	@returns bool - true if the item is in the vector, else false
	*/
	bool contains(T item);

	/*
	@brief Returns the current length of the vector

	@returns size_t - the current length of the vector
	*/
	size_t length();
};

#include "../../src/DataStructures/Vector.cpp"

