/**
 * Balanced K-D Tree Implementation
 * 
 * Uses median finding to guarantee balanced tree construction.
 * Optimal for static datasets requiring fast query performance.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <limits>
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
        for (int i = 0; i < K && i < c.size(); i++) {
            coords[i] = c[i];
        }
    }
    
    double operator[](int index) const { return coords[index]; }
    double& operator[](int index) { return coords[index]; }
    
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

template<int K>
class KDTreeNode {
public:
    Point<K> point;
    unique_ptr<KDTreeNode> left;
    unique_ptr<KDTreeNode> right;
    
    KDTreeNode(const Point<K>& p) : point(p), left(nullptr), right(nullptr) {}
};

template<int K>
class BalancedKDTree {
private:
    unique_ptr<KDTreeNode<K>> root;
    
    // Build balanced tree using median
    unique_ptr<KDTreeNode<K>> buildTree(vector<Point<K>>& points, 
                                        int start, int end, int depth) {
        if (start > end) return nullptr;
        
        int axis = depth % K;
        
        // Sort by current axis and find median
        sort(points.begin() + start, points.begin() + end + 1,
             [axis](const Point<K>& a, const Point<K>& b) {
                 return a[axis] < b[axis];
             });
        
        int median = start + (end - start) / 2;
        
        auto node = make_unique<KDTreeNode<K>>(points[median]);
        
        node->left = buildTree(points, start, median - 1, depth + 1);
        node->right = buildTree(points, median + 1, end, depth + 1);
        
        return node;
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
        
        // Choose which subtree to search first (near then far)
        KDTreeNode<K>* nearSubtree = (diff < 0) ? node->left.get() : node->right.get();
        KDTreeNode<K>* farSubtree = (diff < 0) ? node->right.get() : node->left.get();
        
        nearestHelper(nearSubtree, target, best, bestDist, depth + 1);
        
        // Check if we might find closer point in far subtree
        if (abs(diff) < bestDist) {
            nearestHelper(farSubtree, target, best, bestDist, depth + 1);
        }
    }
    
    // K-nearest neighbors helper
    void kNearestHelper(KDTreeNode<K>* node, const Point<K>& target,
                       vector<pair<double, Point<K>*>>& kBest, int k, int depth) {
        if (!node) return;
        
        double dist = node->point.distanceTo(target);
        
        // Add to k-best list
        if (kBest.size() < k) {
            kBest.push_back({dist, &node->point});
            push_heap(kBest.begin(), kBest.end());
        } else if (dist < kBest.front().first) {
            pop_heap(kBest.begin(), kBest.end());
            kBest.pop_back();
            kBest.push_back({dist, &node->point});
            push_heap(kBest.begin(), kBest.end());
        }
        
        int axis = depth % K;
        double diff = target[axis] - node->point[axis];
        
        KDTreeNode<K>* nearSubtree = (diff < 0) ? node->left.get() : node->right.get();
        KDTreeNode<K>* farSubtree = (diff < 0) ? node->right.get() : node->left.get();
        
        kNearestHelper(nearSubtree, target, kBest, k, depth + 1);
        
        // Check far subtree if necessary
        double worstBestDist = kBest.size() < k ? 
            numeric_limits<double>::max() : kBest.front().first;
        
        if (abs(diff) < worstBestDist) {
            kNearestHelper(farSubtree, target, kBest, k, depth + 1);
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
        
        if (lower[axis] <= node->point[axis]) {
            rangeQueryHelper(node->left.get(), lower, upper, results, depth + 1);
        }
        if (upper[axis] >= node->point[axis]) {
            rangeQueryHelper(node->right.get(), lower, upper, results, depth + 1);
        }
    }
    
    int getHeight(KDTreeNode<K>* node) {
        if (!node) return 0;
        return 1 + max(getHeight(node->left.get()), getHeight(node->right.get()));
    }
    
    int countNodes(KDTreeNode<K>* node) {
        if (!node) return 0;
        return 1 + countNodes(node->left.get()) + countNodes(node->right.get());
    }
    
public:
    BalancedKDTree() : root(nullptr) {}
    
    // Build balanced tree from points
    void build(vector<Point<K>> points) {
        if (points.empty()) return;
        root = buildTree(points, 0, points.size() - 1, 0);
    }
    
    // Find nearest neighbor
    Point<K>* nearestNeighbor(const Point<K>& target) {
        Point<K>* best = nullptr;
        double bestDist = numeric_limits<double>::max();
        nearestHelper(root.get(), target, best, bestDist, 0);
        return best;
    }
    
    // Find k-nearest neighbors
    vector<Point<K>*> kNearestNeighbors(const Point<K>& target, int k) {
        vector<pair<double, Point<K>*>> kBest;
        kNearestHelper(root.get(), target, kBest, k, 0);
        
        // Extract points from heap
        vector<Point<K>*> result;
        for (const auto& pair : kBest) {
            result.push_back(pair.second);
        }
        
        // Sort by distance
        sort(result.begin(), result.end(),
             [&target](const Point<K>* a, const Point<K>* b) {
                 return a->distanceTo(target) < b->distanceTo(target);
             });
        
        return result;
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
        double expectedHeight = log2(nodes + 1);
        cout << "Nodes: " << nodes 
             << ", Height: " << height
             << ", Expected: " << expectedHeight
             << ", Balance: " << (height <= expectedHeight + 1 ? "Good" : "Poor")
             << endl;
    }
};

// Example usage
int main() {
    cout << "=== Balanced 2D K-D Tree Demo ===" << endl << endl;
    
    BalancedKDTree<2> kdtree;
    
    // Create points
    vector<Point<2>> points = {
        Point<2>({7, 2}, "A"),
        Point<2>({5, 4}, "B"),
        Point<2>({9, 6}, "C"),
        Point<2>({2, 3}, "D"),
        Point<2>({4, 7}, "E"),
        Point<2>({8, 1}, "F"),
        Point<2>({1, 5}, "G"),
        Point<2>({6, 8}, "H")
    };
    
    cout << "Building balanced tree with " << points.size() << " points..." << endl;
    kdtree.build(points);
    
    // Print stats
    cout << "\nTree Statistics:" << endl;
    kdtree.printStats();
    
    // Nearest neighbor
    cout << "\nNearest neighbor to (6, 3):" << endl;
    Point<2> target({6, 3});
    Point<2>* nearest = kdtree.nearestNeighbor(target);
    if (nearest) {
        cout << "  ";
        nearest->print();
        cout << " at distance " << target.distanceTo(*nearest) << endl;
    }
    
    // K-nearest neighbors
    cout << "\n3-Nearest neighbors to (6, 3):" << endl;
    vector<Point<2>*> kNearest = kdtree.kNearestNeighbors(target, 3);
    for (int i = 0; i < kNearest.size(); i++) {
        cout << "  " << (i + 1) << ". ";
        kNearest[i]->print();
        cout << " at distance " << target.distanceTo(*kNearest[i]) << endl;
    }
    
    // Range query
    cout << "\nRange query [3, 8] x [2, 7]:" << endl;
    Point<2> lower({3, 2});
    Point<2> upper({8, 7});
    vector<Point<2>> results = kdtree.rangeQuery(lower, upper);
    cout << "  Found " << results.size() << " points:" << endl;
    for (const auto& p : results) {
        cout << "    ";
        p.print();
        cout << endl;
    }
    
    return 0;
}
