#include <iostream>
#include <random>
#include <ctime>

/**
 * Core Treap Problems in C++
 * Focuses on set size and order statistics.
 */

struct Node {
    int key, priority, size;
    Node *left, *right;

    Node(int k) : key(k), priority(std::rand()), size(1), left(nullptr), right(nullptr) {}

    void updateSize() {
        size = 1 + (left ? left->size : 0) + (right ? right->size : 0);
    }
};

void split(Node* root, int target, Node*& L, Node*& R) {
    if (!root) { L = R = nullptr; return; }
    if (root->key <= target) {
        split(root->right, target, root->right, R);
        L = root;
    } else {
        split(root->left, target, L, root->left);
        R = root;
    }
    if (root) root->updateSize();
}

void merge(Node*& root, Node* L, Node* R) {
    if (!L || !R) { root = L ? L : R; return; }
    if (L->priority > R->priority) {
        merge(L->right, L->right, R);
        root = L;
    } else {
        merge(R->left, L, R->left);
        root = R;
    }
    if (root) root->updateSize();
}

int countLessEqual(Node*& root, int X) {
    Node *L, *R;
    split(root, X, L, R);
    int res = (L ? L->size : 0);
    merge(root, L, R);
    return res;
}

int findKth(Node* root, int k) {
    int leftSize = (root->left ? root->left->size : 0);
    if (k == leftSize + 1) return root->key;
    if (k <= leftSize) return findKth(root->left, k);
    return findKth(root->right, k - leftSize - 1);
}

int main() {
    std::srand(std::time(0));
    Node* root = nullptr;
    int data[] = {5, 12, 7, 20, 15, 3, 10};

    for (int x : data) {
        Node *L, *R;
        split(root, x, L, R);
        Node* newNode = new Node(x);
        Node* temp;
        merge(temp, L, newNode);
        merge(root, temp, R);
    }

    std::cout << "Current Set Size: " << (root ? root->size : 0) << std::endl;
    std::cout << "Elements <= 12: " << countLessEqual(root, 12) << std::endl;
    std::cout << "2nd smallest element: " << findKth(root, 2) << std::endl;
    std::cout << "5th smallest element: " << findKth(root, 5) << std::endl;

    return 0;
}
