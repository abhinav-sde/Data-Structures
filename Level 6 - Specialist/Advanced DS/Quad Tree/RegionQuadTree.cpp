/**
 * Region Quad Tree (PR Quad Tree) Implementation
 * 
 * Stores rectangular regions with capacity-based subdivision.
 * Each node can hold multiple points up to a capacity limit.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

// Point structure
struct Point {
    double x, y;
    string data;
    
    Point(double x = 0, double y = 0, string data = "") 
        : x(x), y(y), data(data) {}
};

// Rectangle structure for boundaries
struct Rectangle {
    double x, y, width, height;
    
    Rectangle(double x = 0, double y = 0, double w = 0, double h = 0)
        : x(x), y(y), width(w), height(h) {}
    
    bool contains(double px, double py) const {
        return px >= x && px < x + width && 
               py >= y && py < y + height;
    }
    
    bool intersects(const Rectangle& other) const {
        return !(x + width <= other.x || 
                 other.x + other.width <= x ||
                 y + height <= other.y || 
                 other.y + other.height <= y);
    }
};

// Node class for Region Quad Tree
class RegionQuadTreeNode {
public:
    Rectangle boundary;
    int capacity;
    vector<Point> points;
    bool divided;
    
    // Four children
    unique_ptr<RegionQuadTreeNode> nw;
    unique_ptr<RegionQuadTreeNode> ne;
    unique_ptr<RegionQuadTreeNode> sw;
    unique_ptr<RegionQuadTreeNode> se;
    
    RegionQuadTreeNode(const Rectangle& boundary, int capacity = 4)
        : boundary(boundary), capacity(capacity), divided(false),
          nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr) {}
    
    // Subdivide this node into 4 children
    void subdivide() {
        double x = boundary.x;
        double y = boundary.y;
        double w = boundary.width / 2.0;
        double h = boundary.height / 2.0;
        
        Rectangle nwBoundary(x, y + h, w, h);
        Rectangle neBoundary(x + w, y + h, w, h);
        Rectangle swBoundary(x, y, w, h);
        Rectangle seBoundary(x + w, y, w, h);
        
        nw = make_unique<RegionQuadTreeNode>(nwBoundary, capacity);
        ne = make_unique<RegionQuadTreeNode>(neBoundary, capacity);
        sw = make_unique<RegionQuadTreeNode>(swBoundary, capacity);
        se = make_unique<RegionQuadTreeNode>(seBoundary, capacity);
        
        divided = true;
    }
};

// Region Quad Tree class
class RegionQuadTree {
private:
    unique_ptr<RegionQuadTreeNode> root;
    
    // Helper function for recursive insertion
    bool insertRecursive(RegionQuadTreeNode* node, const Point& point) {
        // Check if point is within boundary
        if (!node->boundary.contains(point.x, point.y)) {
            return false;
        }
        
        // If capacity not reached, add point here
        if (node->points.size() < (size_t)node->capacity) {
            node->points.push_back(point);
            return true;
        }
        
        // Otherwise, subdivide and redistribute
        if (!node->divided) {
            node->subdivide();
            
            // Redistribute existing points
            for (const auto& p : node->points) {
                insertIntoChildren(node, p);
            }
            node->points.clear();
        }
        
        // Insert into appropriate child
        return insertIntoChildren(node, point);
    }
    
    // Insert point into appropriate child
    bool insertIntoChildren(RegionQuadTreeNode* node, const Point& point) {
        if (insertRecursive(node->nw.get(), point)) return true;
        if (insertRecursive(node->ne.get(), point)) return true;
        if (insertRecursive(node->sw.get(), point)) return true;
        if (insertRecursive(node->se.get(), point)) return true;
        return false;
    }
    
    // Helper function for range query
    void queryRangeRecursive(RegionQuadTreeNode* node, 
                            const Rectangle& range, 
                            vector<Point>& found) {
        if (!node) return;
        
        // Check if range intersects with node's boundary
        if (!node->boundary.intersects(range)) {
            return;
        }
        
        // Check points in this node
        for (const auto& p : node->points) {
            if (range.contains(p.x, p.y)) {
                found.push_back(p);
            }
        }
        
        // Recurse into children if divided
        if (node->divided) {
            queryRangeRecursive(node->nw.get(), range, found);
            queryRangeRecursive(node->ne.get(), range, found);
            queryRangeRecursive(node->sw.get(), range, found);
            queryRangeRecursive(node->se.get(), range, found);
        }
    }
    
    // Count total nodes (for statistics)
    int countNodes(RegionQuadTreeNode* node) {
        if (!node) return 0;
        
        if (!node->divided) {
            return 1;
        }
        
        return 1 + countNodes(node->nw.get()) + 
                   countNodes(node->ne.get()) +
                   countNodes(node->sw.get()) + 
                   countNodes(node->se.get());
    }
    
public:
    RegionQuadTree(const Rectangle& boundary, int capacity = 4) {
        root = make_unique<RegionQuadTreeNode>(boundary, capacity);
    }
    
    // Insert a point into the quad tree
    bool insert(const Point& point) {
        return insertRecursive(root.get(), point);
    }
    
    // Find all points within a range
    vector<Point> queryRange(const Rectangle& range) {
        vector<Point> found;
        queryRangeRecursive(root.get(), range, found);
        return found;
    }
    
    // Get statistics about the tree
    void printStats() {
        int nodes = countNodes(root.get());
        cout << "Total nodes: " << nodes << endl;
    }
};

// Example usage
int main() {
    cout << "=== Region Quad Tree Demo ===" << endl << endl;
    
    Rectangle boundary(0, 0, 100, 100);
    RegionQuadTree qt(boundary, 4);
    
    // Insert points
    cout << "Inserting 20 random points..." << endl;
    srand(42); // Fixed seed for reproducibility
    
    for (int i = 0; i < 20; i++) {
        double x = (rand() % 100);
        double y = (rand() % 100);
        Point p(x, y, to_string(i));
        qt.insert(p);
        cout << "  Point " << i << ": (" << x << ", " << y << ")" << endl;
    }
    
    // Print stats
    cout << "\nTree Statistics:" << endl;
    qt.printStats();
    
    // Range query
    cout << "\nRange query (25, 25) to (75, 75):" << endl;
    Rectangle searchArea(25, 25, 50, 50);
    vector<Point> found = qt.queryRange(searchArea);
    
    cout << "  Found " << found.size() << " points:" << endl;
    for (const auto& p : found) {
        cout << "    Point " << p.data << ": (" 
             << p.x << ", " << p.y << ")" << endl;
    }
    
    return 0;
}
