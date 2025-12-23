/**
 * Basic K-D Tree Implementation
 * 
 * Standard K-D Tree with sequential insertion.
 * Simple structure cycling through dimensions at each level.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

// Point in K-dimensional space
template<int K>
struct Point {
    double coords[K];
    string data;
    
    Point() : data("") {
        for (int i = 0; i < K; i++) coords[i] = 0;
    }
    
    Point(const vector<double>& c, const string& d = "") : data(d) {
        for (int i = 0; i < K && i < c.size(); i++) {
            coords[i] = c[i];
        }
    }
    
    double operator[](int index) const {
        return coords[index];
    }
    
    double& operator[](int index) {
        return coords[index];
    }
    
    // Euclidean distance to another point
    double distanceTo(const Point& other) const {
        double sum = 0;
        for (int i = 0; i < K; i++) {
            double diff = coords[i] - other.coords[i];
            sum += diff * diff;
        }
        return sqrt(sum);
    }
    
    void print() const {
        cout << "(";
        for (int i = 0; i < K; i++) {
            cout << coords[i];
            if (i < K - 1) cout << ", ";
        }
        cout << ")";
        if (!data.empty()) cout << " - " << data;
    }
};

// K-D Tree Node
template<int K>
class KDTreeNode {
public:
    Point<K> point;
    unique_ptr<KDTreeNode> left;
    unique_ptr<KDTreeNode> right;
    
    KDTreeNode(const Point<K>& p) : point(p), left(nullptr), right(nullptr) {}
};

// Basic K-D Tree
template<int K>
class BasicKDTree {
private:
    unique_ptr<KDTreeNode<K>> root;
    
    // Insert helper
    void insertHelper(unique_ptr<KDTreeNode<K>>& node, const Point<K>& point, int depth) {
        if (!node) {
            node = make_unique<KDTreeNode<K>>(point);
            return;
        }
        
        int axis = depth % K;
        
        if (point[axis] < node->point[axis]) {
            insertHelper(node->left, point, depth + 1);
        } else {
            insertHelper(node->right, point, depth + 1);
        }
    }
    
    // Search helper
    bool searchHelper(KDTreeNode<K>* node, const Point<K>& point, int depth) {
        if (!node) return false;
        
        // Check if this is the point
        bool match = true;
        for (int i = 0; i < K; i++) {
            if (node->point[i] != point[i]) {
                match = false;
                break;
            }
        }
        if (match) return true;
        
        int axis = depth % K;
        
        if (point[axis] < node->point[axis]) {
            return searchHelper(node->left.get(), point, depth + 1);
        } else {
            return searchHelper(node->right.get(), point, depth + 1);
        }
    }
    
    // Nearest neighbor helper
    void nearestHelper(KDTreeNode<K>* node, const Point<K>& target,
                      Point<K>*& best, double& bestDist, int depth) {
        if (!node) return;
        
        double dist = node->point.distanceTo(target);
        if (dist < bestDist) {
            bestDist = dist;
            best = &node->point;
        }
        
        int axis = depth % K;
        double diff = target[axis] - node->point[axis];
        
        // Choose which subtree to search first
        KDTreeNode<K>* nearSubtree = (diff < 0) ? node->left.get() : node->right.get();
        KDTreeNode<K>* farSubtree = (diff < 0) ? node->right.get() : node->left.get();
        
        // Search near subtree
        nearestHelper(nearSubtree, target, best, bestDist, depth + 1);
        
        // Check if we need to search far subtree
        if (abs(diff) < bestDist) {
            nearestHelper(farSubtree, target, best, bestDist, depth + 1);
        }
    }
    
    // Range query helper
    void rangeQueryHelper(KDTreeNode<K>* node, const Point<K>& lower,
                         const Point<K>& upper, vector<Point<K>>& results, int depth) {
        if (!node) return;
        
        // Check if point is in range
        bool inRange = true;
        for (int i = 0; i < K; i++) {
            if (node->point[i] < lower[i] || node->point[i] > upper[i]) {
                inRange = false;
                break;
            }
        }
        if (inRange) {
            results.push_back(node->point);
        }
        
        int axis = depth % K;
        
        // Check left subtree if necessary
        if (lower[axis] <= node->point[axis]) {
            rangeQueryHelper(node->left.get(), lower, upper, results, depth + 1);
        }
        
        // Check right subtree if necessary
        if (upper[axis] >= node->point[axis]) {
            rangeQueryHelper(node->right.get(), lower, upper, results, depth + 1);
        }
    }
    
    // Count nodes
    int countNodes(KDTreeNode<K>* node) {
        if (!node) return 0;
        return 1 + countNodes(node->left.get()) + countNodes(node->right.get());
    }
    
    // Calculate height
    int getHeight(KDTreeNode<K>* node) {
        if (!node) return 0;
        return 1 + max(getHeight(node->left.get()), getHeight(node->right.get()));
    }
    
public:
    BasicKDTree() : root(nullptr) {}
    
    // Insert a point
    void insert(const Point<K>& point) {
        insertHelper(root, point, 0);
    }
    
    // Search for a point
    bool search(const Point<K>& point) {
        return searchHelper(root.get(), point, 0);
    }
    
    // Find nearest neighbor
    Point<K>* nearestNeighbor(const Point<K>& target) {
        Point<K>* best = nullptr;
        double bestDist = numeric_limits<double>::max();
        nearestHelper(root.get(), target, best, bestDist, 0);
        return best;
    }
    
    // Range query
    vector<Point<K>> rangeQuery(const Point<K>& lower, const Point<K>& upper) {
        vector<Point<K>> results;
        rangeQueryHelper(root.get(), lower, upper, results, 0);
        return results;
    }
    
    // Print statistics
    void printStats() {
        int nodes = countNodes(root.get());
        int height = getHeight(root.get());
        cout << "Nodes: " << nodes << ", Height: " << height << endl;
    }
};

// Example usage
int main() {
    cout << "=== Basic 2D K-D Tree Demo ===" << endl << endl;
    
    BasicKDTree<2> kdtree;
    
    // Insert points
    vector<Point<2>> points = {
        Point<2>({7, 2}, "A"),
        Point<2>({5, 4}, "B"),
        Point<2>({9, 6}, "C"),
        Point<2>({2, 3}, "D"),
        Point<2>({4, 7}, "E"),
        Point<2>({8, 1}, "F")
    };
    
    cout << "Inserting points:" << endl;
    for (const auto& p : points) {
        kdtree.insert(p);
        cout << "  ";
        p.print();
        cout << endl;
    }
    
    // Print stats
    cout << "\nTree Statistics:" << endl;
    kdtree.printStats();
    
    // Search for a point
    cout << "\nSearching for point (5, 4):" << endl;
    Point<2> searchPoint({5, 4});
    bool found = kdtree.search(searchPoint);
    cout << "  " << (found ? "Found!" : "Not found") << endl;
    
    // Nearest neighbor
    cout << "\nNearest neighbor to (6, 3):" << endl;
    Point<2> target({6, 3});
    Point<2>* nearest = kdtree.nearestNeighbor(target);
    if (nearest) {
        cout << "  ";
        nearest->print();
        cout << " at distance " << target.distanceTo(*nearest) << endl;
    }
    
    // Range query
    cout << "\nRange query [3, 8] x [2, 6]:" << endl;
    Point<2> lower({3, 2});
    Point<2> upper({8, 6});
    vector<Point<2>> results = kdtree.rangeQuery(lower, upper);
    cout << "  Found " << results.size() << " points:" << endl;
    for (const auto& p : results) {
        cout << "    ";
        p.print();
        cout << endl;
    }
    
    return 0;
}
