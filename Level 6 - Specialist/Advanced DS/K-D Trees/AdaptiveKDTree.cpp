/**
 * Adaptive K-D Tree Implementation
 * 
 * Uses variance-based dimension selection for better adaptation
 * to data characteristics and non-uniform distributions.
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
class AdaptiveKDTreeNode {
public:
    Point<K> point;
    int splitAxis;  // Store which axis was used for split
    unique_ptr<AdaptiveKDTreeNode> left;
    unique_ptr<AdaptiveKDTreeNode> right;
    
    AdaptiveKDTreeNode(const Point<K>& p, int axis) 
        : point(p), splitAxis(axis), left(nullptr), right(nullptr) {}
};

template<int K>
class AdaptiveKDTree {
private:
    unique_ptr<AdaptiveKDTreeNode<K>> root;
    
    // Calculate variance for a dimension
    double calculateVariance(const vector<Point<K>>& points, int start, int end, int axis) {
        if (start > end) return 0;
        
        double sum = 0, sumSq = 0;
        int count = end - start + 1;
        
        for (int i = start; i <= end; i++) {
            double val = points[i][axis];
            sum += val;
            sumSq += val * val;
        }
        
        double mean = sum / count;
        double variance = (sumSq / count) - (mean * mean);
        
        return variance;
    }
    
    // Choose split axis with maximum variance
    int chooseSplitAxis(const vector<Point<K>>& points, int start, int end) {
        int bestAxis = 0;
        double maxVariance = -1;
        
        for (int axis = 0; axis < K; axis++) {
            double variance = calculateVariance(points, start, end, axis);
            if (variance > maxVariance) {
                maxVariance = variance;
                bestAxis = axis;
            }
        }
        
        return bestAxis;
    }
    
    // Build adaptive tree
    unique_ptr<AdaptiveKDTreeNode<K>> buildTree(vector<Point<K>>& points,
                                                int start, int end) {
        if (start > end) return nullptr;
        
        // Choose axis with maximum variance
        int axis = chooseSplitAxis(points, start, end);
        
        // Sort by chosen axis
        sort(points.begin() + start, points.begin() + end + 1,
             [axis](const Point<K>& a, const Point<K>& b) {
                 return a[axis] < b[axis];
             });
        
        int median = start + (end - start) / 2;
        auto node = make_unique<AdaptiveKDTreeNode<K>>(points[median], axis);
        
        node->left = buildTree(points, start, median - 1);
        node->right = buildTree(points, median + 1, end);
        
        return node;
    }
    
    // Nearest neighbor helper
    void nearestHelper(AdaptiveKDTreeNode<K>* node, const Point<K>& target,
                      Point<K>*& best, double& bestDist) {
        if (!node) return;
        
        double dist = node->point.distanceTo(target);
        if (dist < bestDist) {
            bestDist = dist;
            best = &node->point;
        }
        
        int axis = node->splitAxis;
        double diff = target[axis] - node->point[axis];
        
        AdaptiveKDTreeNode<K>* nearSubtree = (diff < 0) ? node->left.get() : node->right.get();
        AdaptiveKDTreeNode<K>* farSubtree = (diff < 0) ? node->right.get() : node->left.get();
        
        nearestHelper(nearSubtree, target, best, bestDist);
        
        if (abs(diff) < bestDist) {
            nearestHelper(farSubtree, target, best, bestDist);
        }
    }
    
    // Print tree structure
    void printStructure(AdaptiveKDTreeNode<K>* node, int depth = 0) {
        if (!node) return;
        
        string indent(depth * 2, ' ');
        cout << indent << "Split on axis " << node->splitAxis << ": ";
        node->point.print();
        cout << endl;
        
        if (node->left || node->right) {
            if (node->left) printStructure(node->left.get(), depth + 1);
            if (node->right) printStructure(node->right.get(), depth + 1);
        }
    }
    
public:
    AdaptiveKDTree() : root(nullptr) {}
    
    void build(vector<Point<K>> points) {
        if (points.empty()) return;
        root = buildTree(points, 0, points.size() - 1);
    }
    
    Point<K>* nearestNeighbor(const Point<K>& target) {
        Point<K>* best = nullptr;
        double bestDist = numeric_limits<double>::max();
        nearestHelper(root.get(), target, best, bestDist);
        return best;
    }
    
    void printTreeStructure() {
        cout << "Adaptive K-D Tree Structure:" << endl;
        printStructure(root.get());
    }
};

// Example usage
int main() {
    cout << "=== Adaptive K-D Tree Demo ===" << endl << endl;
    cout << "Chooses split axis based on maximum variance" << endl << endl;
    
    AdaptiveKDTree<2> kdtree;
    
    // Create points with varying distribution
    vector<Point<2>> points = {
        Point<2>({1, 5}, "A"),
        Point<2>({2, 6}, "B"),
        Point<2>({3, 4}, "C"),
        Point<2>({4, 8}, "D"),
        Point<2>({5, 3}, "E"),
        Point<2>({15, 4}, "F"),  // Outlier in x-direction
        Point<2>({16, 5}, "G"),
        Point<2>({17, 6}, "H")
    };
    
    cout << "Building adaptive tree with " << points.size() << " points..." << endl;
    cout << "(Note: x-axis has higher variance due to outliers)" << endl << endl;
    
    kdtree.build(points);
    
    // Show tree structure
    kdtree.printTreeStructure();
    
    // Nearest neighbor query
    cout << "\nNearest neighbor to (10, 5):" << endl;
    Point<2> target({10, 5});
    Point<2>* nearest = kdtree.nearestNeighbor(target);
    if (nearest) {
        cout << "  ";
        nearest->print();
        cout << " at distance " << target.distanceTo(*nearest) << endl;
    }
    
    cout << "\nKey Feature: Split axis chosen by variance, not fixed cycling!" << endl;
    
    return 0;
}
