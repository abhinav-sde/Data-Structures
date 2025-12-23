#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Interval Tree for overlap queries
 */
struct Interval {
    int low, high;
    
    bool overlaps(const Interval& other) const {
        return low <= other.high && other.low <= high;
    }
};

struct Node {
    Interval interval;
    int max;
    Node *left, *right;
    
    Node(Interval i) : interval(i), max(i.high), left(nullptr), right(nullptr) {}
};

class IntervalTree {
    Node* root;
    
    Node* insert(Node* node, Interval interval) {
        if (!node) return new Node(interval);
        
        if (interval.low < node->interval.low)
            node->left = insert(node->left, interval);
        else
            node->right = insert(node->right, interval);
        
        node->max = max(node->max, interval.high);
        return node;
    }
    
    void searchOverlap(Node* node, Interval query, vector<Interval>& result) {
        if (!node) return;
        
        if (node->interval.overlaps(query))
            result.push_back(node->interval);
        
        if (node->left && node->left->max >= query.low)
            searchOverlap(node->left, query, result);
        
        searchOverlap(node->right, query, result);
    }
    
public:
    IntervalTree() : root(nullptr) {}
    
    void insert(Interval interval) {
        root = insert(root, interval);
    }
    
    vector<Interval> searchOverlap(Interval query) {
        vector<Interval> result;
        searchOverlap(root, query, result);
        return result;
    }
};

int main() {
    IntervalTree tree;
    tree.insert({15, 20});
    tree.insert({10, 30});
    tree.insert({17, 19});
    tree.insert({5, 20});
    
    auto overlaps = tree.searchOverlap({14, 16});
    cout << "Overlapping intervals with [14, 16]:" << endl;
    for (auto& i : overlaps) {
        cout << "[" << i.low << ", " << i.high << "]" << endl;
    }
    return 0;
}
