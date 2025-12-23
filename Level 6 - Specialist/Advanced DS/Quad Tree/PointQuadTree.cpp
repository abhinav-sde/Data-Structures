/**
 * Point Quad Tree Implementation
 * 
 * Stores individual points in 2D space. Each node represents a point
 * and divides space into 4 quadrants based on that point.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
using namespace std;

// Point structure to store 2D coordinates and associated data
struct Point {
    double x, y;
    string data;
    
    Point(double x = 0, double y = 0, string data = "") 
        : x(x), y(y), data(data) {}
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Node class for Point Quad Tree
class PointQuadTreeNode {
public:
    Point point;
    double xMin, xMax, yMin, yMax;
    
    // Four quadrants: NW, NE, SW, SE
    unique_ptr<PointQuadTreeNode> nw;  // North-West (Top-Left)
    unique_ptr<PointQuadTreeNode> ne;  // North-East (Top-Right)
    unique_ptr<PointQuadTreeNode> sw;  // South-West (Bottom-Left)
    unique_ptr<PointQuadTreeNode> se;  // South-East (Bottom-Right)
    
    PointQuadTreeNode(const Point& p, double xMin, double xMax, 
                      double yMin, double yMax)
        : point(p), xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax),
          nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr) {}
};

// Point Quad Tree class
class PointQuadTree {
private:
    unique_ptr<PointQuadTreeNode> root;
    double xMin, xMax, yMin, yMax;
    
    // Helper function for recursive insertion
    void insertRecursive(unique_ptr<PointQuadTreeNode>& node, 
                        const Point& point, double xMin, double xMax, 
                        double yMin, double yMax) {
        if (!node) {
            node = make_unique<PointQuadTreeNode>(point, xMin, xMax, yMin, yMax);
            return;
        }
        
        double midX = (node->xMin + node->xMax) / 2.0;
        double midY = (node->yMin + node->yMax) / 2.0;
        
        // Determine which quadrant the point belongs to
        if (point.x < node->point.x) {
            if (point.y < node->point.y) {
                // Southwest quadrant
                insertRecursive(node->sw, point, node->xMin, midX, 
                              node->yMin, midY);
            } else {
                // Northwest quadrant
                insertRecursive(node->nw, point, node->xMin, midX, 
                              midY, node->yMax);
            }
        } else {
            if (point.y < node->point.y) {
                // Southeast quadrant
                insertRecursive(node->se, point, midX, node->xMax, 
                              node->yMin, midY);
            } else {
                // Northeast quadrant
                insertRecursive(node->ne, point, midX, node->xMax, 
                              midY, node->yMax);
            }
        }
    }
    
    // Helper function for recursive search
    Point* searchRecursive(PointQuadTreeNode* node, double x, double y) {
        if (!node) return nullptr;
        
        if (node->point.x == x && node->point.y == y) {
            return &(node->point);
        }
        
        // Navigate to appropriate quadrant
        if (x < node->point.x) {
            if (y < node->point.y) {
                return searchRecursive(node->sw.get(), x, y);
            } else {
                return searchRecursive(node->nw.get(), x, y);
            }
        } else {
            if (y < node->point.y) {
                return searchRecursive(node->se.get(), x, y);
            } else {
                return searchRecursive(node->ne.get(), x, y);
            }
        }
    }
    
    // Helper function for range query
    void rangeQueryRecursive(PointQuadTreeNode* node, double xMin, double xMax,
                            double yMin, double yMax, vector<Point>& result) {
        if (!node) return;
        
        // Check if current point is in range
        if (node->point.x >= xMin && node->point.x <= xMax &&
            node->point.y >= yMin && node->point.y <= yMax) {
            result.push_back(node->point);
        }
        
        // Check which quadrants might contain points in range
        if (xMin <= node->point.x) {
            if (yMin <= node->point.y) {
                rangeQueryRecursive(node->sw.get(), xMin, xMax, yMin, yMax, result);
            }
            if (yMax >= node->point.y) {
                rangeQueryRecursive(node->nw.get(), xMin, xMax, yMin, yMax, result);
            }
        }
        
        if (xMax >= node->point.x) {
            if (yMin <= node->point.y) {
                rangeQueryRecursive(node->se.get(), xMin, xMax, yMin, yMax, result);
            }
            if (yMax >= node->point.y) {
                rangeQueryRecursive(node->ne.get(), xMin, xMax, yMin, yMax, result);
            }
        }
    }
    
public:
    PointQuadTree(double xMin, double xMax, double yMin, double yMax)
        : root(nullptr), xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {}
    
    // Insert a point into the quad tree
    void insert(const Point& point) {
        if (!root) {
            root = make_unique<PointQuadTreeNode>(point, xMin, xMax, yMin, yMax);
        } else {
            insertRecursive(root, point, xMin, xMax, yMin, yMax);
        }
    }
    
    // Search for a point
    Point* search(double x, double y) {
        return searchRecursive(root.get(), x, y);
    }
    
    // Find all points within a rectangular range
    vector<Point> rangeQuery(double xMin, double xMax, double yMin, double yMax) {
        vector<Point> result;
        rangeQueryRecursive(root.get(), xMin, xMax, yMin, yMax, result);
        return result;
    }
};

// Example usage
int main() {
    cout << "=== Point Quad Tree Demo ===" << endl << endl;
    
    PointQuadTree qt(0, 100, 0, 100);
    
    // Insert points
    vector<Point> points = {
        Point(25, 25, "A"),
        Point(75, 75, "B"),
        Point(30, 70, "C"),
        Point(80, 20, "D"),
        Point(50, 50, "E")
    };
    
    cout << "Inserting points:" << endl;
    for (const auto& p : points) {
        qt.insert(p);
        cout << "  (" << p.x << ", " << p.y << ") - " << p.data << endl;
    }
    
    // Search for a point
    cout << "\nSearching for point (75, 75):" << endl;
    Point* found = qt.search(75, 75);
    if (found) {
        cout << "  Found: " << found->data << endl;
    } else {
        cout << "  Not found" << endl;
    }
    
    // Range query
    cout << "\nRange query (20, 60) x (20, 60):" << endl;
    vector<Point> inRange = qt.rangeQuery(20, 60, 20, 60);
    cout << "  Points found: ";
    for (const auto& p : inRange) {
        cout << p.data << " ";
    }
    cout << endl;
    
    return 0;
}
