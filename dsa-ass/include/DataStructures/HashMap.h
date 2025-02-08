/*
* NAME: RYAN HO
* ID: S10261024
* GROUP: 
* FEATURES:
* - unique_ptr for node and buckets which automatically manages the deletion of it when it goes out of bounds (e.g. assigned a new pointer) 
* - hashmap automatically resizes when it hits a threshold, reducing the chances of collisions
* - uses djb2 hash 
*/
#pragma once

#include <string>
#include <memory>

template <class V>
class HashMap {
public:
	typedef std::string K;

	// constructor
	HashMap();

	// check if key exists
	bool hasKey(K key);

	// add new kvp
	void add(K key, V value);
	
	// update existing kvp
	void update(K key, V value);

	// get value given key
	V& get(K key);

	// print
	void print();

private:
	const float LOAD_FACTOR = 0.75;
	const size_t INITIAL_CAPACITY = 16;
	const size_t MAX_CAPACITY = 65'535;

	struct Node {
		K key;
		V value;
		std::unique_ptr<Node> next;

		Node(K key, V value) 
			: key(key),
			value(value),
			next(nullptr) {}
	};
	
	// number of buckets
	int capacity;

	// number of nodes
	int entries;

	// array of buckets
	std::unique_ptr<std::unique_ptr<Node>[]> buckets;

	// hash
	size_t hash(K key);

	// increase hashmap size
	void resize();
};

#include "../../src/DataStructures/HashMap.cpp"