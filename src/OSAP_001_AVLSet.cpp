#include "OSAP_001_AVLSet.h"
#include <iostream>

// 노드의 높이를 가져옵니다. 노드가 nullptr인 경우 높이는 0입니다.
int AVLTree::height(AVLNode *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}


// 노드의 균형 계수를 계산하여 AVL 트리가 회전을 필요로 하는지 확인합니다.
int AVLTree::balanceFactor(AVLNode *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

// 노드의 높이를 업데이트하여 높이 정보가 올바르게 유지되도록 합니다.
void AVLTree::updateHeight(AVLNode *node)
{
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

// 오른쪽 회전: AVL 트리의 불균형을 수정 (LL 상황에서 사용).
AVLTree::AVLNode *AVLTree::rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;
    // 회전 수행

    updateHeight(y);
    updateHeight(x);
    // 노드 높이 업데이트

    return x;
}

// 왼쪽 회전: AVL 트리의 불균형을 수정 (RR 상황에서 사용)
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

// 노드를 삽입하고 AVL 트리의 균형을 유지하는 재귀 함수.
AVLTree::AVLNode *AVLTree::insertNode(AVLNode *node, int key)
{
    if (node == nullptr)
        return new AVLNode(key);
    // 비어 있는 위치에 새 노드 생성.

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;//중복이 허용되지 않습니다.

    updateHeight(node);

    int balance = balanceFactor(node);

    //LL의 상황
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    //RR의 상황
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR의 상황
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL의상황
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
}// AVL 트리의 노드 개수를 계산합니다.

bool AVLTree::empty()
{
    return emptyNode(root);
}// AVL 트리가 비어 있는지 확인합니다. 루트 노드가 비어 있으면 true 반환.

bool AVLTree::emptyNode(AVLNode *node)
{
    return node == nullptr;
}// 보조 함수: 특정 노드가 비어 있는지 확인.
