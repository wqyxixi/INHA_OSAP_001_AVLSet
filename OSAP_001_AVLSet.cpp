// author: CHEN XUYAN
// date: 2024-11-19

#include "OSAP_001_AVLSet.h"
#include <iostream>
using namespace std;

// 생성자
// AVLTree 초기화 (루트 노드는 nullptr, 노드 수는 0)
AVLTree::AVLTree() : root(nullptr), nodeCount(0) {}

// 삽입 함수
// 값을 삽입하고, 삽입된 노드의 깊이를 반환
int AVLTree::insert(int x)
{
    root = insert(root, x);
    int depth = 0;
    Node *temp = root;
    Node *target = findNode(root, x);
    while (temp && temp != target)
    {
        if (x < temp->key)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
        depth++;
    }
    int sum = depth + target->height;
    return sum;
}

// 삽입을 수행하는 재귀 함수
// 반환값: 삽입 후의 루트 노드
AVLTree::Node *AVLTree::insert(Node *node, int x)
{
    if (x < 1 || x > 300000)
    {
        return nullptr; // 값이 범위를 벗어나면 무시
    }

    if (!node)
    {
        nodeCount++;
        return new Node(x); // 새로운 노드 생성
    }

    if (x < node->key)
    {
     
        node->left = insert(node->left, x);
    }
    else if (x > node->key)
    {
     
        node->right = insert(node->right, x);
    }
    else
    {
        return node; // 값이 이미 존재함
    }

    updateHeightAndSize(node); // 높이와 크기 갱신
    return balance(node);      // 균형 유지
}

// 트리를 균형 상태로 유지하는 함수
AVLTree::Node *AVLTree::balance(Node *node)
{
    int balanceFactor = getBalanceFactor(node);

    // 좌측 균형이 무너짐
    if (balanceFactor > 1)
    {
        if (getBalanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left); // 좌-우 회전
        }
        return rotateRight(node); // 우회전
    }
    // 우측 균형이 무너짐
    else if (balanceFactor < -1)
    {
        if (getBalanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right); // 우-좌 회전
        }
        return rotateLeft(node); // 좌회전
    }
    return node; // 균형 상태
}

// 좌회전
AVLTree::Node *AVLTree::rotateLeft(Node *node)
{
    Node *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    updateHeightAndSize(node);    // 원래 노드 업데이트
    updateHeightAndSize(newRoot); // 새로운 루트 업데이트
    return newRoot;
}

// 우회전
AVLTree::Node *AVLTree::rotateRight(Node *node)
{
    Node *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    updateHeightAndSize(node);    // 원래 노드 업데이트
    updateHeightAndSize(newRoot); // 새로운 루트 업데이트
    return newRoot;
}

// 노드의 높이와 크기를 업데이트하는 함수
void AVLTree::updateHeightAndSize(Node *node)
{
    node->height = (height(node->left) > height(node->right) ? height(node->left) : height(node->right)) + 1;
    node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);
}

// 노드의 높이를 반환
int AVLTree::height(Node *node) const
{
    return node ? node->height : -1; // 노드가 없으면 -1 반환
}

// 균형 계수를 반환
int AVLTree::getBalanceFactor(Node *node) const
{
    return height(node->left) - height(node->right);
}

// AVLTree 크기 반환
int AVLTree::size() const
{
    return nodeCount;
}

// AVLTree가 비어 있는지 확인
int AVLTree::empty() const
{
    return nodeCount == 0 ? 1 : 0;
}

// AVLTree의 높이를 반환
int AVLTree::height() const
{
    return height(root);
}

// 노드 x의 깊이와 높이의 합을 반환
int AVLTree::find(int x) const
{
    if (x < 1 || x > 300000)
    {
        return -1; // 범위를 벗어난 값 무시
    }

    Node *target = findNode(root, x);
    if (!target)
        return 0; // 노드가 존재하지 않음

    int depth = 0;
    Node *temp = root;
    while (temp)
    {
        if (x < temp->key)
        {
            temp = temp->left;
            depth++;
        }
        else if (x > temp->key)
        {
            temp = temp->right;
            depth++;
        }
        else
        {
            break; // 노드 발견
        }
    }
    return depth + target->height;
}

// 특정 노드를 찾는 함수
AVLTree::Node *AVLTree::findNode(Node *node, int x) const
{
    if (!node || node->key == x)
        return node;
    if (x < node->key)
        return findNode(node->left, x);
    return findNode(node->right, x);
}

// Ancestor 함수: 노드 x의 정보 출력
void AVLTree::ancestor(int x) const
{
    if (!root)
    {
        cout << "-1 0" << endl; // 트리가 비어 있음
        return;
    }

    Node *target = findNode(root, x);
    if (!target)
    {
        cout << "-1 0" << endl; // 노드가 존재하지 않음
        return;
    }

    int depth = 0;
    Node *temp = root;
    while (temp && temp != target)
    {
        if (x < temp->key)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
        depth++;
    }
    int sum = depth + target->height;

    int pathSum = 0;
    Node *current = root;
    while (current && current != target)
    {
        pathSum += current->key;
        if (x < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (target == root)
    {
        pathSum = 0; // 루트 노드일 경우 경로 합은 0
    }

    cout << sum << " " << pathSum << endl;
}

// Average 함수: 서브트리의 최소값과 최대값 평균 반환
int AVLTree::average(int x) const
{
    Node *target = findNode(root, x);
    if (!target)
        return 0;

    int minVal = target->key;
    int maxVal = target->key;
    findMinMax(target, minVal, maxVal);

    return (minVal + maxVal) / 2;
}

// 서브트리의 최소값과 최대값을 찾는 함수
void AVLTree::findMinMax(Node *node, int &minVal, int &maxVal) const
{
    if (!node)
        return;
    if (node->key < minVal)
        minVal = node->key;
    if (node->key > maxVal)
        maxVal = node->key;
    findMinMax(node->left, minVal, maxVal);
    findMinMax(node->right, minVal, maxVal);
}
