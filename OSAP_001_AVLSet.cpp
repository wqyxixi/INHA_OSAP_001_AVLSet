#include "OSAP_001_AVLSet.h"
#include <iostream>

int AVLTree::height(AVLNode *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLTree::balanceFactor(AVLNode *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

void AVLTree::updateHeight(AVLNode *node)
{
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

AVLTree::AVLNode *AVLTree::rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLTree::AVLNode *AVLTree::leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

AVLTree::AVLNode *AVLTree::insertNode(AVLNode *node, int key)
{
    if (node == nullptr)
        return new AVLNode(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node; // 不允许重复键

    updateHeight(node);

    int balance = balanceFactor(node);

    // 左左情况
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // 右右情况
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // 左右情况
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // 右左情况
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

bool AVLTree::findNode(AVLNode *node, int key)
{
    if (node == nullptr)
        return false;

    if (key == node->key)
        return true;
    else if (key < node->key)
        return findNode(node->left, key);
    else
        return findNode(node->right, key);
}

int AVLTree::sizeNode(AVLNode *node)
{
    if (node == nullptr)
        return 0;
    return 1 + sizeNode(node->left) + sizeNode(node->right);
}

AVLTree::AVLTree() : root(nullptr) {}

void AVLTree::clear()
{
    clearTree(root);
    root = nullptr;
}

void AVLTree::clearTree(AVLNode *node)
{
    if (node == nullptr)
        return;

    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

AVLTree::~AVLTree()
{
    clear();
}

void AVLTree::insert(int key)
{
    root = insertNode(root, key);
}

bool AVLTree::find(int key)
{
    return findNode(root, key);
}

int AVLTree::size()
{
    return sizeNode(root);
}

bool AVLTree::empty()
{
    return emptyNode(root);
}

bool AVLTree::emptyNode(AVLNode *node)
{
    return node == nullptr;
}
