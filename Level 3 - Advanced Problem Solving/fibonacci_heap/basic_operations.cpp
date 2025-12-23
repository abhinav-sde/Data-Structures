#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>

/**
 * Basic Fibonacci Heap Operations in C++
 * Min-priority queue with efficient amortized O(1) merge and decrease-key.
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
private:
    Node* min_node;
    int n;

    void addToRootList(Node* node) {
        if (!min_node) {
            min_node = node;
            node->left = node->right = node;
        } else {
            node->right = min_node->right;
            node->left = min_node;
            min_node->right->left = node;
            min_node->right = node;
        }
    }

    void removeFromRootList(Node* node) {
        node->left->right = node->right;
        node->right->left = node->left;
    }

    void link(Node* y, Node* x) {
        removeFromRootList(y);
        y->parent = x;
        if (!x->child) {
            x->child = y;
            y->left = y->right = y;
        } else {
            y->right = x->child;
            y->left = x->child->left;
            x->child->left->right = y;
            x->child->left = y;
        }
        x->degree++;
        y->mark = false;
    }

    void consolidate() {
        int max_deg = (int)(std::log2(n + 1) / std::log2(1.618)) + 2;
        std::vector<Node*> A(max_deg, nullptr);

        std::vector<Node*> rootList;
        Node* curr = min_node;
        if (curr) {
            Node* start = curr;
            do {
                rootList.push_back(curr);
                curr = curr->right;
            } while (curr != start);
        }

        for (Node* x : rootList) {
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
                    addToRootList(node);
                    if (node->key < min_node->key) min_node = node;
                }
            }
        }
    }

public:
    FibonacciHeap() : min_node(nullptr), n(0) {}

    void insert(int key) {
        Node* node = new Node(key);
        addToRootList(node);
        if (!min_node || key < min_node->key) min_node = node;
        n++;
    }

    int getMin() {
        if (!min_node) throw std::runtime_error("Heap is empty");
        return min_node->key;
    }

    int extractMin() {
        Node* z = min_node;
        if (z) {
            if (z->child) {
                Node* first = z->child;
                Node* curr = first;
                do {
                    Node* next = curr->right;
                    addToRootList(curr);
                    curr->parent = nullptr;
                    curr = next;
                } while (curr != first);
            }
            removeFromRootList(z);
            if (z == z->right) {
                min_node = nullptr;
            } else {
                min_node = z->right;
                consolidate();
            }
            int key = z->key;
            delete z;
            n--;
            return key;
        }
        throw std::runtime_error("Heap is empty");
    }

    bool isEmpty() { return min_node == nullptr; }
};

int main() {
    FibonacciHeap heap;
    int keys[] = {10, 20, 5, 15, 2, 30};

    std::cout << "Inserting: 10, 20, 5, 15, 2, 30" << std::endl;
    for (int k : keys) heap.insert(k);

    std::cout << "Min: " << heap.getMin() << std::endl;
    std::cout << "Extracting Min: " << heap.extractMin() << std::endl;
    std::cout << "New Min: " << heap.getMin() << std::endl;
    std::cout << "Extracting Min: " << heap.extractMin() << std::endl;
    std::cout << "New Min: " << heap.getMin() << std::endl;

    return 0;
}
