// author: CHEN XUYAN
// date: 2024-11-19

#ifndef OSAP_001_AVLSet_H
#define OSAP_001_AVLSet_H

// AVLTree 클래스는 균형 이진 검색 트리 구조를 구현합니다.
class AVLTree {
public:
    // AVLTree 생성자
    AVLTree();

    // 노드에 값을 삽입합니다.
    // 반환값: 삽입된 노드의 깊이
    int insert(int x);

    // 트리의 총 노드 개수를 반환합니다.
    int size() const;

    // 트리가 비어 있는지 확인합니다.
    // 반환값: 비어 있으면 1, 그렇지 않으면 0
    int empty() const;

    // 트리의 높이를 반환합니다.
    // 트리가 비어 있으면 -1을 반환합니다.
    int height() const;

    // 노드 x의 깊이와 높이의 합을 반환합니다.
    // 노드 x가 존재하지 않으면 0을 반환합니다.
    int find(int x) const;

    // 노드 x의 깊이와 높이의 합(K)과 x의 부모에서 루트로 가는 경로의 노드 key 값 합을 공백으로 구분하여 출력합니다.
    // x가 루트라면 'K 0'을 출력합니다.
    void ancestor(int x) const;

    // 노드 x가 루트인 서브트리에서 노드 key 값의 최소값과 최대값의 산술평균을 반환합니다.
    int average(int x) const;

private:
    // AVLTree의 노드를 표현하는 구조체
    struct Node {
        int key;        // 노드의 키 값
        int height;     // 노드의 높이
        int size;       // 서브트리의 총 노드 개수
        Node* left;     // 왼쪽 자식 노드
        Node* right;    // 오른쪽 자식 노드

        // Node 생성자
        Node(int k)
            : key(k), height(0), size(1), left(nullptr), right(nullptr) {}
    };

    Node* root;       // AVLTree의 루트 노드
    int nodeCount;    // AVLTree의 총 노드 개수

    // 삽입 연산을 수행하는 재귀 함수
    Node* insert(Node* node, int x);

    // AVLTree를 균형 상태로 유지하는 함수
    Node* balance(Node* node);

    // 왼쪽 회전을 수행하는 함수
    Node* rotateLeft(Node* node);

    // 오른쪽 회전을 수행하는 함수
    Node* rotateRight(Node* node);

    // 노드의 높이를 반환합니다.
    int height(Node* node) const;

    // 노드의 균형 계수를 반환합니다.
    int getBalanceFactor(Node* node) const;

    // 특정 값을 가진 노드를 찾는 함수
    Node* findNode(Node* node, int x) const;

    // 노드가 포함된 서브트리의 최소값과 최대값을 찾는 함수
    void findMinMax(Node* node, int& minVal, int& maxVal) const;

    // 노드의 높이와 서브트리 크기를 업데이트합니다.
    void updateHeightAndSize(Node* node);
};

#endif // AVLTREE_H
