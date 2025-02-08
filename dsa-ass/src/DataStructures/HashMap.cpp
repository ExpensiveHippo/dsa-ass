#pragma once

#include "../../include/DataStructures/HashMap.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

template<class V>
HashMap<V>::HashMap()
	: capacity(INITIAL_CAPACITY),
	entries(0),
	buckets(std::make_unique<std::unique_ptr<Node>[]>(capacity)) {}

template<class V>
size_t HashMap<V>::hash(K key) {
	// djb2 algorithm
	size_t hash = 5381;

	for (char c : key) {
		hash = ((hash << 5) + hash) + c; 
	}
	return hash % capacity;
}

template<class V>
void HashMap<V>::resize() {
	capacity *= 2;
	auto newBuckets = std::make_unique<std::unique_ptr<Node>[]>(capacity);
	
	for (int i = 0, j = capacity / 2; i < j; i++) {
		while (buckets[i] != nullptr) {
			std::unique_ptr<Node> n = std::move(buckets[i]);
			buckets[i] = std::move(n->next);

			size_t index = hash(n->key);
			// std::cout << "[RESIZING]: " << index << std::endl;

			n->next = std::move(newBuckets[index]);
			newBuckets[index] = std::move(n);
		}
	}
	
	buckets = std::move(newBuckets);
}


template<class V>
bool HashMap<V>::hasKey(K key) {
	size_t index = hash(key);

	if (buckets[index] == nullptr) {
		return false;
	}

	const Node* current = buckets[index].get();
	
	while (current != nullptr) {
		if (current->key == key) {
			return true;
		}
		current = current->next.get();
	}
	return false;
}

template<class V>
void HashMap<V>::add(K key, V value) {
	if (hasKey(key)) {
		std::cout << "[DUPLICATE KEY] " << key << std::endl;
		throw std::invalid_argument("Key already exists");
	}

	if (entries >= capacity * LOAD_FACTOR) {
		resize();
	}

	size_t index = hash(key);
	// std::cout << "[ADDING]: " << index << std::endl;
	std::unique_ptr<Node> temp = std::make_unique<Node>(key, value);

	temp->next = std::move(buckets[index]);
	buckets[index] = std::move(temp);

	entries++;
}

template<class V>
void HashMap<V>::update(K key, V value) {
	if (!hasKey(key)) {
		throw std::invalid_argument("Key does not exist");
	}

	size_t index = hash(key);
	Node* current = buckets[index].get();

	while (current != nullptr) {
		if (current->key == key) {
			current->value = value;
			return;
		}
	}
}

template<class V>
V& HashMap<V>::get(K key) {
	size_t index = hash(key);
	Node* current = buckets[index].get();

	while (current != nullptr) {
		if (current->key == key) {
			return current->value;
		}
		current = current->next.get();
	}

	throw std::out_of_range("Key not found");
}

template<class V>
V HashMap<V>::pop(K key) {
	size_t index = hash(key);
	auto& head = buckets[index];
	Node* current = buckets[index].get();
	Node* prev = nullptr;

	while (current != nullptr) {
		if (current->key == key) {

			V value = std::move(current->value);

			if (prev != nullptr) {
				prev->next = std::move(current->next);
			}
			else {
				head = std::move(current->next);
			}
			return value;
		}
		else {
			prev = current;
			current = current->next.get();
		}
	}

	throw std::out_of_range("Key not found");
}

template<class V>
void HashMap<V>::print() {
	std::cout << "[HASHMAP]" << std::endl;
	for (int i = 0; i < capacity; i++) {
		std::cout << "[" << i << "]: ";
		Node* n = buckets[i].get();
		while (n != nullptr) {
			std::cout << n->key << " -> ";
			n = n->next.get();
		}
		std::cout << "END" << std::endl;
	}
}
