#include <iostream>
#include <random>
#include <ctime>
#include <vector>

/**
 * Advanced Treap Problems in C++
 * Implements an "Implicit Treap" for range operations.
 * Allows range reversal in O(log N).
 */

struct Node {
    int priority, size;
    int value;
    bool reverse;
    Node *left, *right;

    Node(int val) : value(val), priority(std::rand()), size(1), reverse(false), left(nullptr), right(nullptr) {}

    void update() {
        size = 1 + (left ? left->size : 0) + (right ? right->size : 0);
    }

    void push() {
        if (reverse) {
            reverse = false;
            std::swap(left, right);
            if (left) left->reverse ^= true;
            if (right) right->reverse ^= true;
        }
    }
};

void split(Node* root, int k, Node*& L, Node*& R) {
    if (!root) { L = R = nullptr; return; }
    root->push();
    int leftSize = (root->left ? root->left->size : 0);
    if (leftSize < k) {
        split(root->right, k - leftSize - 1, root->right, R);
        L = root;
    } else {
        split(root->left, k, L, root->left);
        R = root;
    }
    if (root) root->update();
}

void merge(Node*& root, Node* L, Node* R) {
    if (!L || !R) { root = L ? L : R; return; }
    L->push();
    R->push();
    if (L->priority > R->priority) {
        merge(L->right, L->right, R);
        root = L;
    } else {
        merge(R->left, L, R->left);
        root = R;
    }
    if (root) root->update();
}

void printTreap(Node* root) {
    if (!root) return;
    root->push();
    printTreap(root->left);
    std::cout << root->value << " ";
    printTreap(root->right);
}

int main() {
    std::srand(std::time(0));
    Node* root = nullptr;

    std::cout << "Building implicit treap with values [0, 9]..." << std::endl;
    for (int i = 0; i < 10; ++i) {
        Node* temp;
        merge(temp, root, new Node(i));
        root = temp;
    }

    std::cout << "Original Array: ";
    printTreap(root);
    std::cout << std::endl;

    std::cout << "Reversing range [2, 7]..." << std::endl;
    Node *L_rem, *M, *R_rem;
    split(root, 8, L_rem, R_rem);
    split(L_rem, 2, L_rem, M);
    
    if (M) M->reverse ^= true;
    
    Node* temp;
    merge(temp, L_rem, M);
    merge(root, temp, R_rem);

    std::cout << "Array after reversal: ";
    printTreap(root);
    std::cout << std::endl;

    return 0;
}
