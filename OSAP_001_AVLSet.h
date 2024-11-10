#ifndef OSAPAVLSET_H
#define OSAPAVLSET_H

class AVLTree
{
private:
    // avl树节点
    struct AVLNode
    {
        // 
        int key;
        int height;
        AVLNode *left;
        AVLNode *right;

        AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    AVLNode *root;

    int height(AVLNode *node);
    int balanceFactor(AVLNode *node);
    void updateHeight(AVLNode *node);
    AVLNode *rightRotate(AVLNode *y);
    AVLNode *leftRotate(AVLNode *x);
    AVLNode *insertNode(AVLNode *node, int key);
    bool findNode(AVLNode *node, int key);
    void clearTree(AVLNode *node);
    int sizeNode(AVLNode *node);
    bool emptyNode(AVLNode *node);


public:
    AVLTree();
    ~AVLTree();
    void clear();
    void insert(int key);
    bool find(int key);
    int size();
    bool empty();
};

#endif