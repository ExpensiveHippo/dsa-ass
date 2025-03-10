#pragma once

#include "../../include/DataStructures/Vector.h"

#include <stdexcept>

template<class T> 
Vector<T>::Vector()
	: arr(new T[1])
	, maxCapacity(1)
	, currentCapacity(0) { }

template<class T>
Vector<T>::~Vector() {
	arr = nullptr;
}

template<class T> 
Vector<T>::Vector(Vector&& other) noexcept 
	: arr(std::move(other.arr))
	, maxCapacity(other.maxCapacity)
	, currentCapacity(other.currentCapacity) 
{
	other.maxCapacity = 0;
	other.currentCapacity = 0;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept 
{
	if (this != &other) {
		arr = std::move(other.arr);
		maxCapacity = other.maxCapacity;
		currentCapacity = other.currentCapacity;

		other.maxCapacity = 0;
		other.currentCapacity = 0;
	}
	return *this;
}

template<class T> 
Vector<T>::Vector(const Vector& other) noexcept
	: arr(std::make_unique<T[]>(other.maxCapacity)),
	currentCapacity(other.currentCapacity),
	maxCapacity(other.maxCapacity)
{
	for (size_t i = 0; i < other.currentCapacity; i++) {
		arr[i] = other.arr[i];
	}
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector& other) noexcept {
	if (this != &other) {
		arr = std::make_unique<T[]>(other.maxCapacity);
		currentCapacity = other.currentCapacity;
		maxCapacity = other.maxCapacity;

		for (size_t i = 0; i < other.currentCapacity; i++) {
			arr[i] = other.arr[i];
		}
	}
	return *this;
}

template<class T> 
void Vector<T>::push(T item) {
	// if current array is full, double the size of the array
	if (currentCapacity == maxCapacity) {
		T* temp = new T[2 * maxCapacity];
		for (int i = 0; i < maxCapacity; i++) {
			temp[i] = arr[i];
		}
		maxCapacity *= 2;
		arr.reset(temp);
	}
	arr[currentCapacity++] = item;
}

template<class T>
T& Vector<T>::get(size_t pos) {
	if (pos >= currentCapacity) 
	{
		throw std::out_of_range("Index out of bounds");
	}
	
	return arr[pos];
}

template<class T> 
bool Vector<T>::contains(T item) {
	for (int i = 0; i < currentCapacity; i++) {
		if (arr[i] == item) {
			return true;
		}
	}
	return false;
}

template<class T> 
size_t Vector<T>::length() {
	return currentCapacity;
}

