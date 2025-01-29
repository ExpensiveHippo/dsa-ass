#pragma once
#include <iostream>
	
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
	int height(AVLNode* node);
	int isBalanced(AVLNode* node);
	AVLNode* rotateRight(AVLNode* y);
	AVLNode* rotateLeft(AVLNode* x);
	AVLNode* insert(AVLNode* y, T* data);
	void displayInOrder(AVLNode* root);
public:
	AVLTree();
	void push(T* data);
	void displayInOrder();
};

#include "../../src/DataStructures/AVLTree.cpp"