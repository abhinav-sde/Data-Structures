#include <iostream>
#include <random>
#include <algorithm>

/**
 * Basic Treap Operations in C++
 * Implements a balanced BST using randomized priorities.
 */

struct Node {
    int key;
    int priority;
    Node *left, *right;

    Node(int k) : key(k), priority(std::rand()), left(nullptr), right(nullptr) {}
};

// Split treap into two: keys <= target and keys > target
void split(Node* root, int target, Node*& L, Node*& R) {
    if (!root) {
        L = R = nullptr;
        return;
    }

    if (root->key <= target) {
        split(root->right, target, root->right, R);
        L = root;
    } else {
        split(root->left, target, L, root->left);
        R = root;
    }
}

// Merge two treaps: L < R
void merge(Node*& root, Node* L, Node* R) {
    if (!L || !R) {
        root = L ? L : R;
        return;
    }

    if (L->priority > R->priority) {
        merge(L->right, L->right, R);
        root = L;
    } else {
        merge(R->left, L, R->left);
        root = R;
    }
}

void insert(Node*& root, int key) {
    Node *L, *R;
    split(root, key, L, R);
    Node* newNode = new Node(key);
    merge(L, L, newNode);
    merge(root, L, R);
}

void remove(Node*& root, int key) {
    Node *L, *M, *R;
    split(root, key - 1, L, R);
    split(R, key, M, R);
    // M contains node with key
    delete M;
    merge(root, L, R);
}

bool search(Node* root, int key) {
    if (!root) return false;
    if (root->key == key) return true;
    return key < root->key ? search(root->left, key) : search(root->right, key);
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        std::cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    std::srand(std::time(0));
    Node* root = nullptr;
    int keys[] = {10, 20, 5, 15, 25, 30};

    std::cout << "Inserting keys: 10, 20, 5, 15, 25, 30" << std::endl;
    for (int k : keys) insert(root, k);

    std::cout << "Inorder traversal: ";
    inorder(root);
    std::cout << std::endl;

    std::cout << "Searching for 15: " << (search(root, 15) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 100: " << (search(root, 100) ? "Found" : "Not Found") << std::endl;

    std::cout << "Deleting 15..." << std::endl;
    remove(root, 15);
    std::cout << "Inorder traversal after deletion: ";
    inorder(root);
    std::cout << std::endl;

    return 0;
}
