/**
 * R*-Tree Implementation
 * 
 * Enhanced R-Tree with optimized split heuristics and forced reinsert.
 * Minimizes overlap and area for better query performance.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <limits>
#include <cmath>
using namespace std;

struct Rectangle {
    double xMin, xMax, yMin, yMax;
    
    Rectangle(double xMin = 0, double xMax = 0, double yMin = 0, double yMax = 0)
        : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {}
    
    double area() const {
        return max(0.0, xMax - xMin) * max(0.0, yMax - yMin);
    }
    
    double perimeter() const {
        return 2 * (max(0.0, xMax - xMin) + max(0.0, yMax - yMin));
    }
    
    double overlap(const Rectangle& other) const {
        double xOverlap = max(0.0, min(xMax, other.xMax) - max(xMin, other.xMin));
        double yOverlap = max(0.0, min(yMax, other.yMax) - max(yMin, other.yMin));
        return xOverlap * yOverlap;
    }
    
    void expand(const Rectangle& other) {
        xMin = min(xMin, other.xMin);
        xMax = max(xMax, other.xMax);
        yMin = min(yMin, other.yMin);
        yMax = max(yMax, other.yMax);
    }
    
    bool intersects(const Rectangle& other) const {
        return !(xMax < other.xMin || other.xMax < xMin ||
                 yMax < other.yMin || other.yMax < yMin);
    }
};

struct SpatialObject {
    Rectangle mbr;
    string data;
    
    SpatialObject(const Rectangle& mbr, const string& data)
        : mbr(mbr), data(data) {}
};

struct RStarTreeEntry {
    Rectangle mbr;
    void* childPtr;
    bool isLeaf;
    
    RStarTreeEntry(const Rectangle& mbr, void* ptr, bool isLeaf)
        : mbr(mbr), childPtr(ptr), isLeaf(isLeaf) {}
};

class RStarTreeNode {
public:
    vector<RStarTreeEntry> entries;
    bool isLeaf;
    static const int MAX_ENTRIES = 4;
    static const int MIN_ENTRIES = 2;
    bool hasBeenReinserted;  // Track forced reinsert
    
    RStarTreeNode(bool isLeaf) : isLeaf(isLeaf), hasBeenReinserted(false) {}
    
    bool isFull() const {
        return entries.size() >= MAX_ENTRIES;
    }
    
    Rectangle computeMBR() const {
        if (entries.empty()) return Rectangle();
        
        Rectangle mbr = entries[0].mbr;
        for (size_t i = 1; i < entries.size(); i++) {
            mbr.expand(entries[i].mbr);
        }
        return mbr;
    }
};

class RStarTree {
private:
    unique_ptr<RStarTreeNode> root;
    
    // Choose subtree (minimize overlap enlargement for leaves)
    RStarTreeNode* chooseSubtree(RStarTreeNode* node, const Rectangle& mbr) {
        if (node->isLeaf) {
            return node;
        }
        
        int bestIdx = 0;
        double minValue = numeric_limits<double>::max();
        
        // For leaf level, minimize overlap enlargement
        for (size_t i = 0; i < node->entries.size(); i++) {
            Rectangle enlarged = node->entries[i].mbr;
            enlarged.expand(mbr);
            
            // Calculate overlap with siblings
            double overlapEnlargement = 0;
            for (size_t j = 0; j < node->entries.size(); j++) {
                if (i != j) {
                    double before = node->entries[i].mbr.overlap(node->entries[j].mbr);
                    double after = enlarged.overlap(node->entries[j].mbr);
                    overlapEnlargement += (after - before);
                }
            }
            
            if (overlapEnlargement < minValue) {
                minValue = overlapEnlargement;
                bestIdx = i;
            }
        }
        
        return chooseSubtree(static_cast<RStarTreeNode*>(
            node->entries[bestIdx].childPtr), mbr);
    }
    
    // R*-Tree split (choose axis with minimum perimeter sum)
    pair<RStarTreeNode*, RStarTreeNode*> splitNode(RStarTreeNode* node) {
        RStarTreeNode* node1 = new RStarTreeNode(node->isLeaf);
        RStarTreeNode* node2 = new RStarTreeNode(node->isLeaf);
        
        // Try both axes
        double minPerimeterSum = numeric_limits<double>::max();
        int bestAxis = 0;  // 0 for x, 1 for y
        int bestSplit = 0;
        
        for (int axis = 0; axis < 2; axis++) {
            // Sort by lower bound, then upper bound
            vector<RStarTreeEntry> sorted = node->entries;
            
            if (axis == 0) {  // x-axis
                sort(sorted.begin(), sorted.end(), 
                     [](const RStarTreeEntry& a, const RStarTreeEntry& b) {
                         return a.mbr.xMin < b.mbr.xMin;
                     });
            } else {  // y-axis
                sort(sorted.begin(), sorted.end(),
                     [](const RStarTreeEntry& a, const RStarTreeEntry& b) {
                         return a.mbr.yMin < b.mbr.yMin;
                     });
            }
            
            // Try different split points
            for (size_t k = RStarTreeNode::MIN_ENTRIES; 
                 k <= sorted.size() - RStarTreeNode::MIN_ENTRIES; k++) {
                
                // Compute MBRs for split
                Rectangle mbr1, mbr2;
                for (size_t i = 0; i < k; i) {
                    if (i == 0) mbr1 = sorted[i].mbr;
                    else mbr1.expand(sorted[i].mbr);
                }
                for (size_t i = k; i < sorted.size(); i++) {
                    if (i == k) mbr2 = sorted[i].mbr;
                    else mbr2.expand(sorted[i].mbr);
                }
                
                double perimeterSum = mbr1.perimeter() + mbr2.perimeter();
                
                if (perimeterSum < minPerimeterSum) {
                    minPerimeterSum = perimeterSum;
                    bestAxis = axis;
                    bestSplit = k;
                }
            }
        }
        
        // Perform best split
        vector<RStarTreeEntry> sorted = node->entries;
        if (bestAxis == 0) {
            sort(sorted.begin(), sorted.end(),
                 [](const RStarTreeEntry& a, const RStarTreeEntry& b) {
                     return a.mbr.xMin < b.mbr.xMin;
                 });
        } else {
            sort(sorted.begin(), sorted.end(),
                 [](const RStarTreeEntry& a, const RStarTreeEntry& b) {
                     return a.mbr.yMin < b.mbr.yMin;
                 });
        }
        
        for (size_t i = 0; i < sorted.size(); i++) {
            if (i < bestSplit) {
                node1->entries.push_back(sorted[i]);
            } else {
                node2->entries.push_back(sorted[i]);
            }
        }
        
        return {node1, node2};
    }
    
    // Search helper
    void searchHelper(RStarTreeNode* node, const Rectangle& query,
                     vector<SpatialObject*>& results) {
        if (!node) return;
        
        for (auto& entry : node->entries) {
            if (entry.mbr.intersects(query)) {
                if (node->isLeaf) {
                    results.push_back(static_cast<SpatialObject*>(entry.childPtr));
                } else {
                    searchHelper(static_cast<RStarTreeNode*>(entry.childPtr), 
                               query, results);
                }
            }
        }
    }
    
public:
    RStarTree() {
        root = make_unique<RStarTreeNode>(true);
    }
    
    // Insert a spatial object
    void insert(const SpatialObject& obj) {
        SpatialObject* objPtr = new SpatialObject(obj);
        
        // Choose subtree to insert
        RStarTreeNode* leaf = chooseSubtree(root.get(), obj.mbr);
        
        // Add entry to leaf
        leaf->entries.emplace_back(obj.mbr, objPtr, true);
        
        // Handle overflow (simplified - no forced reinsert in this demo)
        if (leaf->isFull()) {
            auto [n1, n2] = splitNode(leaf);
            
            // Create new root if root split
            if (leaf == root.get()) {
                RStarTreeNode* newRoot = new RStarTreeNode(false);
                newRoot->entries.emplace_back(n1->computeMBR(), n1, false);
                newRoot->entries.emplace_back(n2->computeMBR(), n2, false);
                root.release();
                root.reset(newRoot);
            }
        }
    }
    
    // Search for objects intersecting query rectangle
    vector<SpatialObject*> search(const Rectangle& query) {
        vector<SpatialObject*> results;
        searchHelper(root.get(), query, results);
        return results;
    }
    
    // Print tree statistics
    void printStats() {
        int nodeCount = 0;
        int leafCount = 0;
        int objectCount = 0;
        
        function<void(RStarTreeNode*)> countNodes = [&](RStarTreeNode* node) {
            if (!node) return;
            nodeCount++;
            
            if (node->isLeaf) {
                leafCount++;
                objectCount += node->entries.size();
            } else {
                for (auto& entry : node->entries) {
                    countNodes(static_cast<RStarTreeNode*>(entry.childPtr));
                }
            }
        };
        
        countNodes(root.get());
        
        cout << "Total nodes: " << nodeCount << endl;
        cout << "Leaf nodes: " << leafCount << endl;
        cout << "Objects: " << objectCount << endl;
    }
};

// Example usage
int main() {
    cout << "=== R*-Tree Demo ===" << endl << endl;
    
    RStarTree rtree;
    
    // Insert spatial objects
    vector<SpatialObject> objects = {
        SpatialObject(Rectangle(10, 20, 10, 20), "A"),
        SpatialObject(Rectangle(15, 25, 15, 25), "B"),
        SpatialObject(Rectangle(30, 40, 30, 40), "C"),
        SpatialObject(Rectangle(50, 60, 50, 60), "D"),
        SpatialObject(Rectangle(55, 65, 55, 65), "E"),
        SpatialObject(Rectangle(70, 80, 10, 20), "F")
    };
    
    cout << "Inserting objects:" << endl;
    for (const auto& obj : objects) {
        rtree.insert(obj);
        cout << "  " << obj.data << ": [" << obj.mbr.xMin << ","
             << obj.mbr.xMax << "] x [" << obj.mbr.yMin << ","
             << obj.mbr.yMax << "]" << endl;
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
        cout << "    " << obj->data << endl;
    }
    
    return 0;
}
