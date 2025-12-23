/**
 * PM Quad Tree (Point-Morton Quad Tree) Implementation
 * 
 * Combines features of point and region quad trees.
 * Uses Morton codes (Z-order curve) for efficient spatial indexing.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <cmath>
#include <limits>
using namespace std;

// Point structure
struct Point {
    double x, y;
    string data;
    
    Point(double x = 0, double y = 0, string data = "") 
        : x(x), y(y), data(data) {}
    
    double distanceTo(double px, double py) const {
        return sqrt((x - px) * (x - px) + (y - py) * (y - py));
    }
};

// PM Quad Tree Node
class PMQuadTreeNode {
public:
    double x, y, size;
    int capacity;
    map<uint64_t, Point> points;  // Morton code -> Point
    bool isLeaf;
    
    // Four children
    unique_ptr<PMQuadTreeNode> nw;
    unique_ptr<PMQuadTreeNode> ne;
    unique_ptr<PMQuadTreeNode> sw;
    unique_ptr<PMQuadTreeNode> se;
    
    PMQuadTreeNode(double x, double y, double size, int capacity = 4)
        : x(x), y(y), size(size), capacity(capacity), isLeaf(true),
          nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr) {}
};

// PM Quad Tree class
class PMQuadTree {
private:
    unique_ptr<PMQuadTreeNode> root;
    
    // Calculate Morton code (Z-order) for point
    static uint64_t mortonCode(int x, int y, int maxDepth = 16) {
        uint64_t code = 0;
        for (int i = 0; i < maxDepth; i++) {
            code |= ((uint64_t)(x & (1 << i)) << i) | 
                    ((uint64_t)(y & (1 << i)) << (i + 1));
        }
        return code;
    }
    
    // Subdivide a node
    void subdivide(PMQuadTreeNode* node) {
        double half = node->size / 2.0;
        int cap = node->capacity;
        
        node->nw = make_unique<PMQuadTreeNode>(node->x, node->y + half, half, cap);
        node->ne = make_unique<PMQuadTreeNode>(node->x + half, node->y + half, half, cap);
        node->sw = make_unique<PMQuadTreeNode>(node->x, node->y, half, cap);
        node->se = make_unique<PMQuadTreeNode>(node->x + half, node->y, half, cap);
        
        node->isLeaf = false;
    }
    
    // Insert point into appropriate child
    bool insertIntoChild(PMQuadTreeNode* node, const Point& point, uint64_t morton) {
        double midX = node->x + node->size / 2.0;
        double midY = node->y + node->size / 2.0;
        
        if (point.x < midX) {
            if (point.y < midY) {
                return insertRecursive(node->sw.get(), point, morton);
            } else {
                return insertRecursive(node->nw.get(), point, morton);
            }
        } else {
            if (point.y < midY) {
                return insertRecursive(node->se.get(), point, morton);
            } else {
                return insertRecursive(node->ne.get(), point, morton);
            }
        }
    }
    
    // Recursive insert
    bool insertRecursive(PMQuadTreeNode* node, const Point& point, uint64_t morton) {
        if (!node) return false;
        
        // Check if point is within bounds
        if (point.x < node->x || point.x >= node->x + node->size ||
            point.y < node->y || point.y >= node->y + node->size) {
            return false;
        }
        
        if (node->isLeaf) {
            // Check capacity
            if (node->points.size() < (size_t)node->capacity) {
                node->points[morton] = point;
                return true;
            } else {
                // Subdivide
                subdivide(node);
                
                // Redistribute points
                for (const auto& pair : node->points) {
                    insertIntoChild(node, pair.second, pair.first);
                }
                node->points.clear();
                
                // Insert new point
                return insertIntoChild(node, point, morton);
            }
        } else {
            return insertIntoChild(node, point, morton);
        }
    }
    
    // Find nearest neighbor recursively
    void nearestRecursive(PMQuadTreeNode* node, double x, double y, 
                         Point*& best, double& bestDist) {
        if (!node) return;
        
        if (node->isLeaf) {
            // Check all points in this leaf
            for (auto& pair : node->points) {
                double dist = pair.second.distanceTo(x, y);
                if (dist < bestDist) {
                    bestDist = dist;
                    best = &pair.second;
                }
            }
        } else {
            // Check children (could be optimized with distance pruning)
            vector<PMQuadTreeNode*> children = {
                node->sw.get(), node->se.get(), 
                node->nw.get(), node->ne.get()
            };
            
            for (auto* child : children) {
                if (child) {
                    // Simple distance check to child's bounding box
                    double closestX = max(child->x, min(x, child->x + child->size));
                    double closestY = max(child->y, min(y, child->y + child->size));
                    double distToBounds = sqrt((x - closestX) * (x - closestX) + 
                                              (y - closestY) * (y - closestY));
                    
                    // Only search if child could contain closer point
                    if (distToBounds < bestDist) {
                        nearestRecursive(child, x, y, best, bestDist);
                    }
                }
            }
        }
    }
    
    // Count nodes for statistics
    int countNodes(PMQuadTreeNode* node) {
        if (!node) return 0;
        
        if (node->isLeaf) {
            return 1;
        }
        
        return 1 + countNodes(node->nw.get()) + 
                   countNodes(node->ne.get()) +
                   countNodes(node->sw.get()) + 
                   countNodes(node->se.get());
    }
    
public:
    PMQuadTree(double x, double y, double size, int capacity = 4) {
        root = make_unique<PMQuadTreeNode>(x, y, size, capacity);
    }
    
    // Insert a point using Morton encoding
    bool insert(const Point& point) {
        uint64_t morton = mortonCode((int)point.x, (int)point.y);
        return insertRecursive(root.get(), point, morton);
    }
    
    // Find nearest neighbor
    Point* nearestNeighbor(double x, double y) {
        Point* best = nullptr;
        double bestDist = numeric_limits<double>::max();
        nearestRecursive(root.get(), x, y, best, bestDist);
        return best;
    }
    
    // Get distance to nearest neighbor
    double nearestNeighborDistance(double x, double y) {
        Point* nearest = nearestNeighbor(x, y);
        if (nearest) {
            return nearest->distanceTo(x, y);
        }
        return -1.0;
    }
    
    // Print statistics
    void printStats() {
        int nodes = countNodes(root.get());
        cout << "Total nodes: " << nodes << endl;
    }
    
    // Static function to demonstrate Morton code
    static void demonstrateMortonCode() {
        cout << "Morton Code Examples:" << endl;
        vector<pair<int, int>> points = {
            {0, 0}, {1, 0}, {0, 1}, {1, 1},
            {2, 0}, {3, 0}, {2, 2}, {3, 3}
        };
        
        for (const auto& p : points) {
            uint64_t code = mortonCode(p.first, p.second);
            cout << "  (" << p.first << ", " << p.second << ") -> " 
                 << code << endl;
        }
    }
};

// Example usage
int main() {
    cout << "=== PM Quad Tree Demo ===" << endl << endl;
    
    // Demonstrate Morton coding
    PMQuadTree::demonstrateMortonCode();
    cout << endl;
    
    // Create quad tree
    PMQuadTree qt(0, 0, 100, 4);
    
    // Insert points
    vector<Point> points = {
        Point(10, 10, "A"),
        Point(20, 20, "B"),
        Point(30, 30, "C"),
        Point(80, 80, "D"),
        Point(25, 25, "E"),
        Point(15, 85, "F"),
        Point(90, 10, "G")
    };
    
    cout << "Inserting points:" << endl;
    for (const auto& p : points) {
        qt.insert(p);
        cout << "  " << p.data << ": (" << p.x << ", " << p.y << ")" << endl;
    }
    
    // Print statistics
    cout << "\nTree Statistics:" << endl;
    qt.printStats();
    
    // Find nearest neighbors
    cout << "\nNearest Neighbor Queries:" << endl;
    
    vector<pair<double, double>> queries = {
        {25, 25},
        {50, 50},
        {85, 85}
    };
    
    for (const auto& q : queries) {
        Point* nearest = qt.nearestNeighbor(q.first, q.second);
        if (nearest) {
            double dist = nearest->distanceTo(q.first, q.second);
            cout << "  Nearest to (" << q.first << ", " << q.second << "): "
                 << nearest->data << " at (" << nearest->x << ", " << nearest->y 
                 << "), distance = " << dist << endl;
        }
    }
    
    return 0;
}
