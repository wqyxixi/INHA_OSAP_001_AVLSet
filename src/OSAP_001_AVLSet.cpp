#include "OSAP_001_AVLSet.h"
#include <algorithm>
#include <iostream>
#include<sstream>

using namespace std;

// Node 클래스 생성자 및 소멸자
Node::Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}

Node::~Node() {
    // 필요하면 메모리를 수동으로 관리하여 좌우 자식 노드를 해제
}

// Node 클래스의 getter 및 setter 메소드들
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

// AVLTree 클래스 생성자 및 소멸자
AVLTree::AVLTree() : root(nullptr), tree_size(0) {}

AVLTree::~AVLTree() {
    clear(root);
}

// AVLTree 클래스의 private 보조 메소드들
int AVLTree::getHeight(Node* N) const {
    if (N == nullptr)
        return 0;
    return N->getHeight();
}

int AVLTree::max(int a, int b) const {
    return (a > b) ? a : b;
}

// rightRotate 메서드는 오른쪽 회전을 수행하여 트리의 균형을 맞추다.
Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->getLeft();
    Node* T2 = x->getRight();

    // 회전 과정
    x->setRight(y);
    y->setLeft(T2);

    // 높이 업데이트
    y->setHeight(max(getHeight(y->getLeft()), getHeight(y->getRight())) + 1);
    x->setHeight(max(getHeight(x->getLeft()), getHeight(x->getRight())) + 1);

    return x;
}

// leftRotate 메서드는 오른쪽 회전을 수행하여 트리의 균형을 맞추다
Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->getRight();
    Node* T2 = y->getLeft();

    y->setLeft(x);
    x->setRight(T2);

    x->setHeight(max(getHeight(x->getLeft()), getHeight(x->getRight())) + 1);
    y->setHeight(max(getHeight(y->getLeft()), getHeight(y->getRight())) + 1);

    return y;
}

// getBalance 메서드는 노드의 균형 인수를 반환하여 균형 상태를 평가하다
int AVLTree::getBalance(Node* N) const {
    if (N == nullptr)
        return 0;
    return getHeight(N->getLeft()) - getHeight(N->getRight());
}

// insert 메서드는 주어진 키 값을 삽입하고 트리를 균형 잡힌 상태로 유지하다.
Node* AVLTree::insert(Node* node, int key, int& depth) {
    if (node == nullptr) {
        return new Node(key);
    }

    if (key < node->getKey()) {
        depth++;
        node->setLeft(insert(node->getLeft(), key, depth));
    }
    else if (key > node->getKey()) {
        depth++;
        node->setRight(insert(node->getRight(), key, depth));
    }
    else { // Duplicate keys not allowed
        return node;
    }

    node->setHeight(1 + max(getHeight(node->getLeft()), getHeight(node->getRight())));

    int balance = getBalance(node);

    // LL
    if (balance > 1 && key < node->getLeft()->getKey())
        return rightRotate(node);

    // RR
    if (balance < -1 && key > node->getRight()->getKey())
        return leftRotate(node);

    // LR
    if (balance > 1 && key > node->getLeft()->getKey()) {
        node->setLeft(leftRotate(node->getLeft()));
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && key < node->getRight()->getKey()) {
        node->setRight(rightRotate(node->getRight()));
        return leftRotate(node);
    }

    return node;
}

//find 메서드는 트리에서 주어진 키 값을 찾다.
Node* AVLTree::find(Node* node, int key, int& depth) const {
    if (node == nullptr || node->getKey() == key) {
        return node;
    }

    if (key < node->getKey()) {
        depth++;
        return find(node->getLeft(), key, depth);
    }
    else {
        depth++;
        return find(node->getRight(), key, depth);
    }
}

// clear 메서드는 재귀적으로 모든 노드를 해제하여 트리를 정리하다.
void AVLTree::clear(Node* node) {
    if (node != nullptr) {
        clear(node->getLeft());
        clear(node->getRight());
        delete node;
        node = nullptr;
    }
}


// countNodes 메서드는 트리의 총 노드 수를 계산하다
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

// AVLTree 클래스의 public 메소드들
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

string AVLTree::intToString(int value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

string AVLTree::ancestor(int key) {
    Node* node = root;
    int depth = 0;
    int sum = 0;
    std::ostringstream result;

    while (node != nullptr) {
        sum += node->getKey(); 
        result << node->getKey() << " "; 

        if (key == node->getKey()) {
            return intToString(depth + getHeight(node)) + " " + result.str();
        }

        depth++;
        if (key < node->getKey()) {
            node = node->getLeft(); 
        }
        else {
            node = node->getRight(); 
        }
    }
    return "0"; 
}

int AVLTree::rank(int key) {
    Node* node = root;
    int rank = 0;

    while (node != nullptr) {
        if (key < node->getKey()) {
            node = node->getLeft(); 
        }
        else {
            rank += (node->getLeft() ? countNodes(node->getLeft()) : 0) + 1;
            if (key == node->getKey()) {
                return rank; 
            }
            node = node->getRight(); 
        }
    }

    return 0; 
}

int AVLTree::countNodes(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + countNodes(node->getLeft()) + countNodes(node->getRight());
}

