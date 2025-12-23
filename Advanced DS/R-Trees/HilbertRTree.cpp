/**
 * Hilbert R-Tree Implementation (Simplified)
 * 
 * Uses Hilbert space-filling curve for better spatial clustering.
 * Objects are ordered by their Hilbert value for improved locality.
 * 
 * Note: This is a simplified educational implementation.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
using namespace std;

struct Rectangle {
    double xMin, xMax, yMin, yMax;
    
    Rectangle(double xMin = 0, double xMax = 0, double yMin = 0, double yMax = 0)
        : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {}
    
    double area() const {
        return max(0.0, xMax - xMin) * max(0.0, yMax - yMin);
    }
    
    bool intersects(const Rectangle& other) const {
        return !(xMax < other.xMin || other.xMax < xMin ||
                 yMax < other.yMin || other.yMax < yMin);
    }
    
    // Get center point
    pair<double, double> center() const {
        return {(xMin + xMax) / 2.0, (yMin + yMax) / 2.0};
    }
};

struct SpatialObject {
    Rectangle mbr;
    string data;
    int hilbertValue;
    
    SpatialObject(const Rectangle& mbr, const string& data, int hValue = 0)
        : mbr(mbr), data(data), hilbertValue(hValue) {}
};

class HilbertCurve {
public:
    // Convert (x, y) to Hilbert distance
    static int xy2d(int n, int x, int y) {
        int d = 0;
        for (int s = n / 2; s > 0; s /= 2) {
            int rx = (x & s) > 0;
            int ry = (y & s) > 0;
            d += s * s * ((3 * rx) ^ ry);
            rot(s, &x, &y, rx, ry);
        }
        return d;
    }
    
    // Rotate/flip quadrant appropriately
    static void rot(int n, int* x, int* y, int rx, int ry) {
        if (ry == 0) {
            if (rx == 1) {
                *x = n - 1 - *x;
                *y = n - 1 - *y;
            }
            int t = *x;
            *x = *y;
            *y = t;
        }
    }
    
    // Calculate Hilbert value for a rectangle's center
    static int hilbertValue(const Rectangle& mbr, int gridSize = 256) {
        auto [cx, cy] = mbr.center();
        
        // Normalize to grid
        int x = static_cast<int>(cx) % gridSize;
        int y = static_cast<int>(cy) % gridSize;
        
        return xy2d(gridSize, x, y);
    }
};

struct HilbertEntry {
    Rectangle mbr;
    void* childPtr;
    bool isLeaf;
    int largestHilbert;  // Largest Hilbert value in subtree
    
    HilbertEntry(const Rectangle& mbr, void* ptr, bool isLeaf, int lh = 0)
        : mbr(mbr), childPtr(ptr), isLeaf(isLeaf), largestHilbert(lh) {}
};

class HilbertRTreeNode {
public:
    vector<HilbertEntry> entries;
    bool isLeaf;
    static const int MAX_ENTRIES = 4;
    static const int MIN_ENTRIES = 2;
    
    HilbertRTreeNode(bool isLeaf) : isLeaf(isLeaf) {}
    
    bool isFull() const {
        return entries.size() >= MAX_ENTRIES;
    }
    
    Rectangle computeMBR() const {
        if (entries.empty()) return Rectangle();
        
        Rectangle mbr = entries[0].mbr;
        for (size_t i = 1; i < entries.size(); i++) {
            mbr.xMin = min(mbr.xMin, entries[i].mbr.xMin);
            mbr.xMax = max(mbr.xMax, entries[i].mbr.xMax);
            mbr.yMin = min(mbr.yMin, entries[i].mbr.yMin);
            mbr.yMax = max(mbr.yMax, entries[i].mbr.yMax);
        }
        return mbr;
    }
    
    int largestHilbert() const {
        if (entries.empty()) return 0;
        return entries.back().largestHilbert;
    }
};

class HilbertRTree {
private:
    unique_ptr<HilbertRTreeNode> root;
    
    // Find appropriate leaf based on Hilbert value
    HilbertRTreeNode* chooseLeaf(HilbertRTreeNode* node, int hilbertValue) {
        if (node->isLeaf) {
            return node;
        }
        
        // Find child with largest Hilbert value >= target
        for (auto& entry : node->entries) {
            if (hilbertValue <= entry.largestHilbert) {
                return chooseLeaf(static_cast<HilbertRTreeNode*>(entry.childPtr), 
                                hilbertValue);
            }
        }
        
        // If not found, use last child
        return chooseLeaf(static_cast<HilbertRTreeNode*>(
            node->entries.back().childPtr), hilbertValue);
    }
    
    // Split node based on Hilbert ordering
    pair<HilbertRTreeNode*, HilbertRTreeNode*> splitNode(HilbertRTreeNode* node) {
        // Entries are already sorted by Hilbert value
        HilbertRTreeNode* node1 = new HilbertRTreeNode(node->isLeaf);
        HilbertRTreeNode* node2 = new HilbertRTreeNode(node->isLeaf);
        
        size_t mid = node->entries.size() / 2;
        
        for (size_t i = 0; i < node->entries.size(); i++) {
            if (i < mid) {
                node1->entries.push_back(node->entries[i]);
            } else {
                node2->entries.push_back(node->entries[i]);
            }
        }
        
        return {node1, node2};
    }
    
    // Search helper
    void searchHelper(HilbertRTreeNode* node, const Rectangle& query,
                     vector<SpatialObject*>& results) {
        if (!node) return;
        
        for (auto& entry : node->entries) {
            if (entry.mbr.intersects(query)) {
                if (node->isLeaf) {
                    results.push_back(static_cast<SpatialObject*>(entry.childPtr));
                } else {
                    searchHelper(static_cast<HilbertRTreeNode*>(entry.childPtr),
                               query, results);
                }
            }
        }
    }
    
public:
    HilbertRTree() {
        root = make_unique<HilbertRTreeNode>(true);
    }
    
    // Insert spatial object (ordered by Hilbert value)
    void insert(SpatialObject& obj) {
        // Calculate Hilbert value for object's center
        obj.hilbertValue = HilbertCurve::hilbertValue(obj.mbr);
        
        SpatialObject* objPtr = new SpatialObject(obj);
        
        // Find appropriate leaf
        HilbertRTreeNode* leaf = chooseLeaf(root.get(), obj.hilbertValue);
        
        // Insert in sorted position
        auto it = lower_bound(leaf->entries.begin(), leaf->entries.end(),
                             obj.hilbertValue,
                             [](const HilbertEntry& e, int val) {
                                 return e.largestHilbert < val;
                             });
        
        leaf->entries.insert(it, HilbertEntry(obj.mbr, objPtr, true, obj.hilbertValue));
        
        // Handle overflow
        if (leaf->isFull()) {
            auto [n1, n2] = splitNode(leaf);
            
            // Create new root if root split
            if (leaf == root.get()) {
                HilbertRTreeNode* newRoot = new HilbertRTreeNode(false);
                newRoot->entries.emplace_back(n1->computeMBR(), n1, false, n1->largestHilbert());
                newRoot->entries.emplace_back(n2->computeMBR(), n2, false, n2->largestHilbert());
                root.release();
                root.reset(newRoot);
            }
        }
    }
    
    // Search for objects intersecting query
    vector<SpatialObject*> search(const Rectangle& query) {
        vector<SpatialObject*> results;
        searchHelper(root.get(), query, results);
        return results;
    }
    
    // Print statistics
    void printStats() {
        int nodeCount = 0;
        int leafCount = 0;
        int objectCount = 0;
        
        function<void(HilbertRTreeNode*)> countNodes = [&](HilbertRTreeNode* node) {
            if (!node) return;
            nodeCount++;
            
            if (node->isLeaf) {
                leafCount++;
                objectCount += node->entries.size();
            } else {
                for (auto& entry : node->entries) {
                    countNodes(static_cast<HilbertRTreeNode*>(entry.childPtr));
                }
            }
        };
        
        countNodes(root.get());
        
        cout << "Total nodes: " << nodeCount << endl;
        cout << "Leaf nodes: " << leafCount << endl;
        cout << "Objects: " << objectCount << endl;
    }
    
    // Demonstrate Hilbert curve mapping
    static void demonstrateHilbertCurve() {
        cout << "Hilbert Curve Value Examples:" << endl;
        cout << "(showing how 2D coordinates map to 1D Hilbert values)" << endl << endl;
        
        vector<pair<int, int>> points = {
            {0, 0}, {16, 16}, {32, 32}, {48, 48},
            {64, 64}, {80, 80}, {96, 96}
        };
        
        for (const auto& [x, y] : points) {
            Rectangle rect(x, x, y, y);
            int hValue = HilbertCurve::hilbertValue(rect);
            cout << "  (" << x << ", " << y << ") -> Hilbert value: " << hValue << endl;
        }
        cout << endl;
    }
};

// Example usage
int main() {
    cout << "=== Hilbert R-Tree Demo ===" << endl << endl;
    
    // Demonstrate Hilbert curve
    HilbertRTree::demonstrateHilbertCurve();
    
    HilbertRTree rtree;
    
    // Insert spatial objects
    vector<SpatialObject> objects = {
        SpatialObject(Rectangle(10, 20, 10, 20), "A"),
        SpatialObject(Rectangle(15, 25, 15, 25), "B"),
        SpatialObject(Rectangle(30, 40, 30, 40), "C"),
        SpatialObject(Rectangle(50, 60, 50, 60), "D"),
        SpatialObject(Rectangle(55, 65, 55, 65), "E"),
        SpatialObject(Rectangle(70, 80, 10, 20), "F")
    };
    
    cout << "Inserting objects (ordered by Hilbert value):" << endl;
    for (auto& obj : objects) {
        rtree.insert(obj);
        cout << "  " << obj.data << ": [" << obj.mbr.xMin << ","
             << obj.mbr.xMax << "] x [" << obj.mbr.yMin << ","
             << obj.mbr.yMax << "] -> Hilbert: " << obj.hilbertValue << endl;
    }
    
    // Print tree statistics
    cout << "\nTree Statistics:" << endl;
    rtree.printStats();
    
    // Search query
    cout << "\nSearch query [12, 35] x [12, 35]:" << endl;
    Rectangle query(12, 35, 12, 35);
    vector<SpatialObject*> results = rtree.search(query);
    
    cout << "  Found " << results.size() << " objects:" << endl;
    for (auto* obj : results) {
        cout << "    " << obj->data << " (Hilbert: " << obj->hilbertValue << ")" << endl;
    }
    
    cout << "\nKey Feature: Objects stored in Hilbert curve order" << endl;
    cout << "for excellent spatial clustering!" << endl;
    
    return 0;
}
