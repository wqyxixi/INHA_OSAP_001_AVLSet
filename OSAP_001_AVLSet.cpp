#include "OSAP_001_AVLSet.h"
#include <algorithm>
#include <iostream>

// Node 类的构造函数和析构函数
Node::Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}

Node::~Node() {
    // 如果需要手动管理内存，这里应该释放左右子节点
}

// Node 类的 getter 和 setter 方法
int Node::getKey() const {
    return key;
}

void Node::setKey(int val) {
    key = val;
}

Node* Node::getLeft() const {
    return left;
}

void Node::setLeft(Node* leftChild) {
    left = leftChild;
}

Node* Node::getRight() const {
    return right;
}

void Node::setRight(Node* rightChild) {
    right = rightChild;
}

int Node::getHeight() const {
    return height;
}

void Node::setHeight(int h) {
    height = h;
}

// AVLTree 类的构造函数和析构函数
AVLTree::AVLTree() : root(nullptr), tree_size(0) {}

AVLTree::~AVLTree() {
    clear(root);
}

// AVLTree 类的私有辅助方法
int AVLTree::getHeight(Node* N) const {
    if (N == nullptr)
        return 0;
    return N->getHeight();
}

int AVLTree::max(int a, int b) const {
    return (a > b) ? a : b;
}

Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->getLeft();
    Node* T2 = x->getRight();

    x->setRight(y);
    y->setLeft(T2);

    y->setHeight(max(getHeight(y->getLeft()), getHeight(y->getRight())) + 1);
    x->setHeight(max(getHeight(x->getLeft()), getHeight(x->getRight())) + 1);

    return x;
}

Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->getRight();
    Node* T2 = y->getLeft();

    y->setLeft(x);
    x->setRight(T2);

    x->setHeight(max(getHeight(x->getLeft()), getHeight(x->getRight())) + 1);
    y->setHeight(max(getHeight(y->getLeft()), getHeight(y->getRight())) + 1);

    return y;
}

int AVLTree::getBalance(Node* N) const {
    if (N == nullptr)
        return 0;
    return getHeight(N->getLeft()) - getHeight(N->getRight());
}

Node* AVLTree::insert(Node* node, int key, int& depth) {
    if (node == nullptr) {
        return new Node(key);
    }

    if (key < node->getKey()) {
        depth++;
        node->setLeft(insert(node->getLeft(), key, depth));
    } else if (key > node->getKey()) {
        depth++;
        node->setRight(insert(node->getRight(), key, depth));
    } else { // Duplicate keys not allowed
        return node;
    }

    node->setHeight(1 + max(getHeight(node->getLeft()), getHeight(node->getRight())));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->getLeft()->getKey())
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->getRight()->getKey())
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->getLeft()->getKey()) {
        node->setLeft(leftRotate(node->getLeft()));
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->getRight()->getKey()) {
        node->setRight(rightRotate(node->getRight()));
        return leftRotate(node);
    }

    return node;
}

Node* AVLTree::find(Node* node, int key, int& depth) const {
    if (node == nullptr || node->getKey() == key) {
        return node;
    }

    if (key < node->getKey()) {
        depth++;
        return find(node->getLeft(), key, depth);
    } else {
        depth++;
        return find(node->getRight(), key, depth);
    }
}

void AVLTree::clear(Node* node) {
    if (node != nullptr) {
        clear(node->getLeft());
        clear(node->getRight());
        delete node;
        node = nullptr;
    }
}

int AVLTree::countNodes(Node* node) const {
    if (node == nullptr)
        return 0;
    return 1 + countNodes(node->getLeft()) + countNodes(node->getRight());
}

int AVLTree::treeHeight(Node* node) const {
    if (node == nullptr)
        return 0;
    return 1 + max(treeHeight(node->getLeft()), treeHeight(node->getRight()));
}

// AVLTree 类的公有方法
int AVLTree::insert(int key) {
    int depth = 0;
    root = insert(root, key, depth);
    tree_size++;
    return depth + getHeight(root);
}

int AVLTree::find(int key) {
    int depth = 0;
    Node* foundNode = find(root, key, depth);
    if (foundNode == nullptr) {
        return 0; // Not found
    }
    return depth + getHeight(foundNode);
}

bool AVLTree::empty() const {
    return (root == nullptr);
}

int AVLTree::size() const {
    return tree_size;
}

int AVLTree::height() const {
    return (root == nullptr) ? -1 : treeHeight(root);
}
