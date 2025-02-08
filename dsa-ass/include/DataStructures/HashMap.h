/*
* NAME: RYAN HO
* ID: S10261024
* GROUP: glorp
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

	/*
	@brief Check if key exists in hashmap

	@param key - key to check

	@returns bool - true if key exists
	*/
	bool hasKey(K key);

	/*
	@brief Add new kvp

	@param key - key
	@param value - value

	@returns void
	*/
	void add(K key, V value);
	
	/*
	@brief Update value given key

	@param key - key
	@param value - value

	@returns void
	*/
	void update(K key, V value);

	/*
	@brief Retrieve value given key

	@param key - key

	@returns V& - value
	*/
	V& get(K key);

	/*
	@brief Remove kvp given key

	@param key - key

	@returns V - value
	*/
	V pop(K key);

	/*
	@brief Print the hashmap

	@returns void
	*/
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