#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

/**
 * Advanced Fibonacci Heap Problems in C++
 * Implements optimized Dijkstra's Algorithm using Fibonacci Heap.
 * Performance: O(E + V log V)
 */

struct Node {
    int vertex;
    double dist;
    int degree;
    bool mark;
    Node *parent, *child, *left, *right;

    Node(int v, double d) : vertex(v), dist(d), degree(0), mark(false), parent(nullptr), child(nullptr) {
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
            if (node->dist < min_node->dist) min_node = node;
        }
        n++;
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

    void decreaseDist(Node* x, double d) {
        if (d > x->dist) return;
        x->dist = d;
        Node* y = x->parent;
        if (y && x->dist < y->dist) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x->dist < min_node->dist) min_node = x;
    }

    void cut(Node* x, Node* y) {
        if (x->right == x) y->child = nullptr;
        else {
            x->left->right = x->right;
            x->right->left = x->left;
            if (y->child == x) y->child = x->right;
        }
        y->degree--;
        x->parent = nullptr; x->mark = false;
        x->right = min_node->right; x->left = min_node;
        min_node->right->left = x; min_node->right = x;
    }

    void cascadingCut(Node* y) {
        Node* z = y->parent;
        if (z) {
            if (!y->mark) y->mark = true;
            else { cut(y, z); cascadingCut(z); }
        }
    }

    void consolidate() {
        int max_deg = (int)(std::log2(n + 1) / std::log2(1.618)) + 2;
        std::vector<Node*> A(max_deg, nullptr);
        std::vector<Node*> roots;
        Node* curr = min_node;
        if (curr) {
            Node* start = curr;
            do { roots.push_back(curr); curr = curr->right; } while (curr != start);
        }
        for (Node* x : roots) {
            int d = x->degree;
            while (A[d]) {
                Node* y = A[d];
                if (x->dist > y->dist) std::swap(x, y);
                link(y, x);A[d] = nullptr; d++;
            }
            A[d] = x;
        }
        min_node = nullptr;
        for (Node* node : A) {
            if (node) {
                if (!min_node) { min_node = node; node->left = node->right = node; }
                else {
                    node->right = min_node->right; node->left = min_node;
                    min_node->right->left = node; min_node->right = node;
                    if (node->dist < min_node->dist) min_node = node;
                }
            }
        }
    }

    void link(Node* y, Node* x) {
        y->left->right = y->right; y->right->left = y->left;
        y->parent = x;
        if (!x->child) { x->child = y; y->left = y->right = y; }
        else {
            y->right = x->child; y->left = x->child->left;
            x->child->left->right = y; x->child->left = y;
        }
        x->degree++; y->mark = false;
    }
};

struct Edge {
    int to; double weight;
};

std::vector<double> dijkstra(const std::vector<std::vector<Edge>>& adj, int start) {
    int v_count = adj.size();
    std::vector<double> dist(v_count, std::numeric_limits<double>::infinity());
    std::vector<Node*> nodes(v_count);
    FibonacciHeap heap;

    dist[start] = 0;
    for (int i = 0; i < v_count; ++i) {
        nodes[i] = new Node(i, dist[i]);
        heap.insert(nodes[i]);
    }

    while (heap.n > 0) {
        Node* uNode = heap.extractMin();
        int u = uNode->vertex;

        for (const auto& edge : adj[u]) {
            if (dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                heap.decreaseDist(nodes[edge.to], dist[edge.to]);
            }
        }
    }
    return dist;
}

int main() {
    int V = 5;
    std::vector<std::vector<Edge>> adj(V);

    adj[0].push_back({1, 10}); adj[0].push_back({4, 5});
    adj[1].push_back({2, 1});  adj[1].push_back({4, 2});
    adj[2].push_back({3, 4});
    adj[3].push_back({0, 7});  adj[3].push_back({2, 6});
    adj[4].push_back({1, 3});  adj[4].push_back({2, 9});  adj[4].push_back({3, 2});

    std::vector<double> distances = dijkstra(adj, 0);
    std::cout << "Dijkstra's Shortest Paths from source 0:" << std::endl;
    for (int i = 0; i < V; ++i) {
        std::cout << "To " << i << ": " << distances[i] << std::endl;
    }

    return 0;
}
