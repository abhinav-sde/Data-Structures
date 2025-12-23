/**
 * Range K-D Tree Implementation (Simplified)
 * 
 * Enhanced for efficient range queries with optimizations.
 * Includes bounding box checks and efficient pruning.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
using namespace std;

template<int K>
struct Point {
    double coords[K];
    string data;
    
    Point() : data("") {
        for (int i = 0; i < K; i++) coords[i] = 0;
    }
    
    Point(const vector<double>& c, const string& d = "") : data(d) {
        for (int i = 0; i < K && i < c.size(); i++) coords[i] = c[i];
    }
    
    double operator[](int index) const { return coords[index]; }
    
    void print() const {
        cout << "(";
        for (int i = 0; i < K; i++) {
            cout << coords[i];
            if (i < K - 1) cout << ", ";
        }
        cout << ")";
        if (!data.empty()) cout << " -" << data;
    }
};

template<int K>
struct BoundingBox {
    Point<K> lower, upper;
    
    BoundingBox() {}
    
    bool intersects(const BoundingBox& other) const {
        for (int i = 0; i < K; i++) {
            if (upper[i] < other.lower[i] || lower[i] > other.upper[i]) {
                return false;
            }
        }
        return true;
    }
    
    bool contains(const Point<K>& p) const {
        for (int i = 0; i < K; i++) {
            if (p[i] < lower[i] || p[i] > upper[i]) {
                return false;
            }
        }
        return true;
    }
};

template<int K>
class RangeKDTreeNode {
public:
    Point<K> point;
    BoundingBox<K> bbox;  // Bounding box of subtree
    unique_ptr<RangeKDTreeNode> left;
    unique_ptr<RangeKDTreeNode> right;
    
    RangeKDTreeNode(const Point<K>& p) : point(p), left(nullptr), right(nullptr) {
        for (int i = 0; i < K; i++) {
            bbox.lower[i] = bbox.upper[i] = p[i];
        }
    }
    
    void updateBBox() {
        bbox.lower = bbox.upper = point;
        
        if (left) {
            for (int i = 0; i < K; i++) {
                bbox.lower[i] = min(bbox.lower[i], left->bbox.lower[i]);
                bbox.upper[i] = max(bbox.upper[i], left->bbox.upper[i]);
            }
        }
        
        if (right) {
            for (int i = 0; i < K; i++) {
                bbox.lower[i] = min(bbox.lower[i], right->bbox.lower[i]);
                bbox.upper[i] = max(bbox.upper[i], right->bbox.upper[i]);
            }
        }
    }
};

template<int K>
class RangeKDTree {
private:
    unique_ptr<RangeKDTreeNode<K>> root;
    
    unique_ptr<RangeKDTreeNode<K>> buildTree(vector<Point<K>>& points,
                                             int start, int end, int depth) {
        if (start > end) return nullptr;
        
        int axis = depth % K;
        
        sort(points.begin() + start, points.begin() + end + 1,
             [axis](const Point<K>& a, const Point<K>& b) {
                 return a[axis] < b[axis];
             });
        
        int median = start + (end - start) / 2;
        auto node = make_unique<RangeKDTreeNode<K>>(points[median]);
        
        node->left = buildTree(points, start, median - 1, depth + 1);
        node->right = buildTree(points, median + 1, end, depth + 1);
        
        node->updateBBox();
        
        return node;
    }
    
    void rangeQueryHelper(RangeKDTreeNode<K>* node, const BoundingBox<K>& query,
                         vector<Point<K>>& results, int& nodesVisited) {
        if (!node) return;
        
        nodesVisited++;
        
        // Early rejection using bounding box
        if (!node->bbox.intersects(query)) {
            return;
        }
        
        // Check if point is in range
        if (query.contains(node->point)) {
            results.push_back(node->point);
        }
        
        // Recursively search children
        rangeQueryHelper(node->left.get(), query, results, nodesVisited);
        rangeQueryHelper(node->right.get(), query, results, nodesVisited);
    }
    
public:
    RangeKDTree() : root(nullptr) {}
    
    void build(vector<Point<K>> points) {
        if (points.empty()) return;
        root = buildTree(points, 0, points.size() - 1, 0);
    }
    
    vector<Point<K>> rangeQuery(const Point<K>& lower, const Point<K>& upper,
                               int* nodesVisited = nullptr) {
        vector<Point<K>> results;
        BoundingBox<K> query;
        query.lower = lower;
        query.upper = upper;
        
        int visited = 0;
        rangeQueryHelper(root.get(), query, results, visited);
        
        if (nodesVisited) *nodesVisited = visited;
        
        return results;
    }
};

// Example usage
int main() {
    cout << "=== Range K-D Tree Demo ===" << endl << endl;
    
    RangeKDTree<2> kdtree;
    
    vector<Point<2>> points = {
        Point<2>({2, 3}, "A"), Point<2>({5, 4}, "B"),
        Point<2>({9, 6}, "C"), Point<2>({4, 7}, "D"),
        Point<2>({8, 1}, "E"), Point<2>({7, 2}, "F")
    };
    
    cout << "Building range-optimized K-D tree..." << endl;
    kdtree.build(points);
    
    cout << "\nRange query [3, 8] x [2, 7]:" << endl;
    Point<2> lower({3, 2}), upper({8, 7});
    
    int nodesVisited = 0;
    vector<Point<2>> results = kdtree.rangeQuery(lower, upper, &nodesVisited);
    
    cout << "  Found " << results.size() << " points (visited " 
         << nodesVisited << " nodes):" << endl;
    for (const auto& p : results) {
        cout << "    ";
        p.print();
        cout << endl;
    }
    
    cout << "\nOptimization: Bounding boxes allow early rejection!" << endl;
    
    return 0;
}
