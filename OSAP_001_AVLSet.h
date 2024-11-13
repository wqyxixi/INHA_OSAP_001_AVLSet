#ifndef OSAPAVLSET_H
#define OSAPAVLSET_H
class Node {
public:
    Node(int val);
    ~Node();

    int getKey() const;
    void setKey(int val);
    Node* getLeft() const;
    void setLeft(Node* leftChild);
    Node* getRight() const;
    void setRight(Node* rightChild);
    int getHeight() const;
    void setHeight(int h);

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

    // 插入节点
    int insert(int key);

    // 查找节点
    int find(int key);

    // 检查树是否为空
    bool empty() const;

    // 获取树中节点数量
    int size() const;

    // 获取树的高度
    int height() const;

private:
    Node* root;
    int tree_size;

    int getHeight(Node* N) const;
    int max(int a, int b) const;
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    int getBalance(Node* N) const;
    Node* insert(Node* node, int key, int& depth);
    Node* find(Node* node, int key, int& depth) const;
    void clear(Node* node);
    int countNodes(Node* node) const;
    int treeHeight(Node* node) const;
};


#endif
