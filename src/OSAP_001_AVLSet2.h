#ifndef OSAPAVLSET_H
#define OSAPAVLSET_H
//AVLTree 클래스:AVL 트리의 데이터 구조를 구현하며 삽입, 찾기, 빈 위치 판단, 크기 계산 등을 지원한다.
//AVL 트리는 삽입, 삭제, 찾기 작업의 시간 복잡도를 O(log n)로 하는 자기균형 이진 검색 트리이다.
class AVLTree
{
private:
    // AVL 트리 노드
    struct AVLNode
    {
         
        int key;         //노드의 키 값이다.
        int height;      //노드 높이, 평형인자 계산에 사용된다.
        AVLNode *left;   //왼쪽 자식 노드의 포인터를 가리킨다.
        AVLNode *right;  //오른쪽 자식 노드에 대한 포인터이다.

        //생성자 함수를 사용하여 노드의 키, 자식 노드 포인터, 높이를 초기화한다.
        AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    AVLNode *root;
    //AVL 트리 루트 노드에 대한 포인터이다.

    int node_count;
    // 트리의 전체 노드 개수를 추적하기 위한 변수

    int height(AVLNode *node);
    //노드의 높이를 가져옵니다.
    int balanceFactor(AVLNode *node);
    //노드의 평형인자를 계산한다.
    void updateHeight(AVLNode *node);
    //노드의 높이를 업데이트합니다.
    AVLNode *rightRotate(AVLNode *y);
    //오른쪽 회전 동작으로 트리의 균형을 유지한다.
    AVLNode *leftRotate(AVLNode *x);
    //왼쪽 회전 동작으로 트리의 균형을 유지한다.
    AVLNode *insertNode(AVLNode *node, int key);
    //노드의 재귀 함수를 삽입한다.
    bool findNode(AVLNode *node, int key);
    //노드의 재귀 함수를 찾습니다.
    void clearTree(AVLNode *node);
    //트리의 재귀 함수를 비운다.
  


public:
    AVLTree();
    //생성자, 초기화 AVL 트리를 빈 상태로 만든다
    ~AVLTree();
    //분석자, 트리를 비우고 메모리를 비운다.
    void clear();
    //트리의 모든 노드를 비운다의 클 리어() 한다.
    void insert(int key);
    //키를 AVL 트리에 삽입한다.
    bool find(int key);
    //avl 트리에 키가 존재하는지 찾기.
    int size()const;
    //AVL 트리의 노드 개수를 반환한다.
    bool empty()const;
    //AVL 트리가 비어 있는지 여부를 판단한다.
};

#endif