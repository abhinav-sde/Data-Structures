#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

/**
 * Core Fibonacci Heap Problems in C++
 * Implements Decrease-Key and Delete operations.
 */

struct Node {
    int key;
    int degree;
    bool mark;
    Node *parent, *child, *left, *right;

    Node(int k) : key(k), degree(0), mark(false), parent(nullptr), child(nullptr) {
        left = right = this;
    }
};

class FibonacciHeap {
public:
    Node* min_node;
    int n;

    FibonacciHeap() : min_node(nullptr), n(0) {}

    void insert(Node* node) {
        if (!min_node) {
            min_node = node;
            node->left = node->right = node;
        } else {
            node->right = min_node->right;
            node->left = min_node;
            min_node->right->left = node;
            min_node->right = node;
            if (node->key < min_node->key) min_node = node;
        }
        n++;
    }

    void decreaseKey(Node* x, int k) {
        if (k > x->key) return;
        x->key = k;
        Node* y = x->parent;
        if (y && x->key < y->key) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x->key < min_node->key) min_node = x;
    }

    void cut(Node* x, Node* y) {
        if (x->right == x) {
            y->child = nullptr;
        } else {
            x->left->right = x->right;
            x->right->left = x->left;
            if (y->child == x) y->child = x->right;
        }
        y->degree--;
        x->parent = nullptr;
        x->mark = false;
        x->right = min_node->right;
        x->left = min_node;
        min_node->right->left = x;
        min_node->right = x;
    }

    void cascadingCut(Node* y) {
        Node* z = y->parent;
        if (z) {
            if (!y->mark) y->mark = true;
            else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

    Node* extractMin() {
        Node* z = min_node;
        if (z) {
            if (z->child) {
                Node* start = z->child;
                Node* curr = start;
                do {
                    Node* next = curr->right;
                    curr->parent = nullptr;
                    curr->right = min_node->right;
                    curr->left = min_node;
                    min_node->right->left = curr;
                    min_node->right = curr;
                    curr = next;
                } while (curr != start);
            }
            z->left->right = z->right;
            z->right->left = z->left;
            if (z == z->right) min_node = nullptr;
            else {
                min_node = z->right;
                consolidate();
            }
            n--;
        }
        return z;
    }

    void consolidate() {
        int max_deg = (int)(std::log2(n + 1) / std::log2(1.618)) + 2;
        std::vector<Node*> A(max_deg, nullptr);
        std::vector<Node*> roots;
        Node* curr = min_node;
        if (curr) {
            Node* start = curr;
            do {
                roots.push_back(curr);
                curr = curr->right;
            } while (curr != start);
        }
        for (Node* x : roots) {
            int d = x->degree;
            while (A[d]) {
                Node* y = A[d];
                if (x->key > y->key) std::swap(x, y);
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }
        min_node = nullptr;
        for (Node* node : A) {
            if (node) {
                if (!min_node) {
                    min_node = node;
                    node->left = node->right = node;
                } else {
                    node->right = min_node->right;
                    node->left = min_node;
                    min_node->right->left = node;
                    min_node->right = node;
                    if (node->key < min_node->key) min_node = node;
                }
            }
        }
    }

    void link(Node* y, Node* x) {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        if (!x->child) {
            x->child = y; y->left = y->right = y;
        } else {
            y->right = x->child;
            y->left = x->child->left;
            x->child->left->right = y;
            x->child->left = y;
        }
        x->degree++;
        y->mark = false;
    }

    void remove(Node* x) {
        decreaseKey(x, INT_MIN);
        Node* z = extractMin();
        delete z;
    }
};

int main() {
    FibonacciHeap heap;
    Node* n1 = new Node(10);
    Node* n2 = new Node(20);
    Node* n3 = new Node(5);
    Node* n4 = new Node(15);

    heap.insert(n1); heap.insert(n2); heap.insert(n3); heap.insert(n4);
    std::cout << "Inserted node 10, 20, 5, 15. Min is: " << heap.min_node->key << std::endl;

    std::cout << "Decreasing key of node 20 to 2..." << std::endl;
    heap.decreaseKey(n2, 2);
    std::cout << "New Min is: " << heap.min_node->key << std::endl;

    std::cout << "Deleting node 5..." << std::endl;
    heap.remove(n3);
    std::cout << "Min after deletion: " << (heap.min_node ? std::to_string(heap.min_node->key) : "null") << std::endl;

    return 0;
}
