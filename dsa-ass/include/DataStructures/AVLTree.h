/*
* NAME: ASHTON CHONG
* ID: S10257765
* GROUP: glorp
* FEATURES:
* - an AVLTree that allows for insertion of data like Actor and Movie objects into the tree
* - auto balances the tree after every insertion via rotations
* - allows custom comparisons with flexible comparison functions
*/



#pragma once
#include <iostream>

template <typename T>
using CompareFunction = bool(*)(T*, T*);


template <typename T>
class AVLTree 
{
private:
	struct AVLNode {
		T* data;
		AVLNode* left;
		AVLNode* right;
		int height;
		AVLNode(T* value) : data(value), left(nullptr), right(nullptr), height(1) {}
	};
	AVLNode* root;
	CompareFunction<T> compare;

	int height(AVLNode* node);

	int isBalanced(AVLNode* node);

	AVLNode* rotateRight(AVLNode* y);

	AVLNode* rotateLeft(AVLNode* x);

	AVLNode* insert(AVLNode* y, T* data);

	void displayInOrder(AVLNode* root);
public:
	AVLTree(CompareFunction<T> compare);
	void push(T* data);
	void displayInOrder();
};

#include "../../src/DataStructures/AVLTree.cpp"