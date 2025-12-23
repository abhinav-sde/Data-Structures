#include <iostream>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int key;
    Node *left, *right, *parent;
    Color color;

    Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

class RedBlackTree {
    Node *root;
    Node *NIL;

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node *k) {
        while (k->parent && k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
                Node *u = k->parent->parent->right;
                if (u->color == RED) {
                    k->parent->color = BLACK;
                    u->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            } else {
                Node *u = k->parent->parent->left;
                if (u->color == RED) {
                    k->parent->color = BLACK;
                    u->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

public:
    RedBlackTree() {
        NIL = new Node(0);
        NIL->color = BLACK;
        root = NIL;
    }

    void insert(int key) {
        Node *node = new Node(key);
        node->left = node->right = NIL;
        Node *y = nullptr;
        Node *x = root;
        while (x != NIL) {
            y = x;
            if (node->key < x->key) x = x->left;
            else x = x->right;
        }
        node->parent = y;
        if (!y) root = node;
        else if (node->key < y->key) y->left = node;
        else y->right = node;
        fixInsert(node);
    }
};

int main() {
    RedBlackTree rbt;
    rbt.insert(10);
    rbt.insert(20);
    return 0;
}
