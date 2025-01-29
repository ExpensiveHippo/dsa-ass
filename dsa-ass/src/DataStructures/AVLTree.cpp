#pragma once
#include "../../include/DataStructures/AVLTree.h"
#include "../../include/Models/Actor.h"
#include "../../include/Models/Movie.h"
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T>
int AVLTree<T>::height(AVLNode* node) {
    return node ? node->height : 0;
}

template <typename T>
int AVLTree<T>::isBalanced(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}
template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}
template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}
template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::insert(AVLNode* node, T* data) {
    if (!node)
        return new AVLNode(data);   //root

    if (*data < *(node->data))
        node->left = insert(node->left, data);
    else if (*data > *(node->data))
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = isBalanced(node);

    // Single Rotation (Right Rotation)
    if (balance > 1 && *data < *(node->left->data))
        return rotateRight(node);

    // Single Rotation (Left Rotation)
    if (balance < -1 && *data > *(node->right->data))
        return rotateLeft(node);

    // Double Rotation(Left Right)
    if (balance > 1 && *data > *(node->left->data)) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Double Rotation (Right Left)
    if (balance < -1 && *data < *(node->right->data)) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}
template <typename T>
void AVLTree<T>::displayInOrder(AVLNode* root) {
    if (root != nullptr) {
        displayInOrder(root->left);
        root->data->print();
        displayInOrder(root->right);
    }
}
template <typename T>
void AVLTree<T>::push(T* data) {
    root = insert(root, data);
}
template <typename T>
void AVLTree<T>::displayInOrder() {
    displayInOrder(root);
}
