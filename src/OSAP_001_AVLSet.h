#ifndef OSAPAVLSET_H
#define OSAPAVLSET_H
class Node {
public:
    Node(int val);
    ~Node();

    int getKey() const;// 키 값 가져오기
    void setKey(int val);// 키 값 설정
    Node* getLeft() const;// 왼쪽 자식 가져오기
    void setLeft(Node* leftChild);// 왼쪽 자식 설정
    Node* getRight() const;// 오른쪽 자식 가져오기
    void setRight(Node* rightChild);// 오른쪽 자식 설정
    int getHeight() const;// 노드 높이 가져오기
    void setHeight(int h);// 노드 높이 설정

private:
    int key;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    // 노드 삽입
    int insert(int key);

    // 노드 찾기
    int find(int key);

    // 트리가 비어 있는지 확인
    bool empty() const;

    // 트리의 노드 수를 가져오다
    int size() const;

    // 트리의 높이를 가져옵니다
    int height() const;

private:
    Node* root;
    int tree_size;

    int getHeight(Node* N) const;
    int max(int a, int b) const;
    Node* rightRotate(Node* y);// 오른쪽 회전
    Node* leftRotate(Node* x);// 왼쪽 회전
    int getBalance(Node* N) const;// 균형 계수 가져오기
    Node* insert(Node* node, int key, int& depth);// 노드 삽입 도우미
    Node* find(Node* node, int key, int& depth) const;// 노드 검색 도우미
    void clear(Node* node);
    int countNodes(Node* node) const;
    int treeHeight(Node* node) const;
};


#endif
