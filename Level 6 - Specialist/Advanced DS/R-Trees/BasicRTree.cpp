/**
 * Basic R-Tree Implementation (Classic R-Tree)
 * 
 * Original R-Tree design by Antonin Guttman (1984).
 * Uses quadratic split algorithm for node overflow.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <limits>
#include <cmath>
using namespace std;

// Rectangle structure for MBR (Minimum Bounding Rectangle)
struct Rectangle {
    double xMin, xMax, yMin, yMax;
    
    Rectangle(double xMin = 0, double xMax = 0, double yMin = 0, double yMax = 0)
        : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {}
    
    double area() const {
        return (xMax - xMin) * (yMax - yMin);
    }
    
    double enlargement(const Rectangle& other) const {
        Rectangle combined = *this;
        combined.expand(other);
        return combined.area() - area();
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
    
    bool contains(const Rectangle& other) const {
        return xMin <= other.xMin && xMax >= other.xMax &&
               yMin <= other.yMin && yMax >= other.yMax;
    }
};

// Spatial object with MBR and data
struct SpatialObject {
    Rectangle mbr;
    string data;
    
    SpatialObject(const Rectangle& mbr, const string& data)
        : mbr(mbr), data(data) {}
};

// R-Tree entry (can be object or child node pointer)
struct RTreeEntry {
    Rectangle mbr;
    void* childPtr;  // Points to RTreeNode or SpatialObject
    bool isLeaf;
    
    RTreeEntry(const Rectangle& mbr, void* ptr, bool isLeaf)
        : mbr(mbr), childPtr(ptr), isLeaf(isLeaf) {}
};

// R-Tree node
class RTreeNode {
public:
    vector<RTreeEntry> entries;
    bool isLeaf;
    static const int MAX_ENTRIES = 4;
    static const int MIN_ENTRIES = 2;
    
    RTreeNode(bool isLeaf) : isLeaf(isLeaf) {}
    
    bool isFull() const {
        return entries.size() >= MAX_ENTRIES;
    }
    
    bool isUnderflow() const {
        return entries.size() < MIN_ENTRIES;
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

// Basic R-Tree class
class BasicRTree {
private:
    unique_ptr<RTreeNode> root;
    
    // Choose leaf for insertion (minimize area enlargement)
    RTreeNode* chooseLeaf(RTreeNode* node, const Rectangle& mbr) {
        if (node->isLeaf) {
            return node;
        }
        
        // Find entry with minimum enlargement
        int bestIdx = 0;
        double minEnlargement = node->entries[0].mbr.enlargement(mbr);
        
        for (size_t i = 1; i < node->entries.size(); i++) {
            double enlargement = node->entries[i].mbr.enlargement(mbr);
            if (enlargement < minEnlargement) {
                minEnlargement = enlargement;
                bestIdx = i;
            }
        }
        
        return chooseLeaf(static_cast<RTreeNode*>(node->entries[bestIdx].childPtr), mbr);
    }
    
    // Quadratic split algorithm
    pair<RTreeNode*, RTreeNode*> splitNode(RTreeNode* node) {
        RTreeNode* node1 = new RTreeNode(node->isLeaf);
        RTreeNode* node2 = new RTreeNode(node->isLeaf);
        
        // Find pair with maximum waste
        int seed1 = 0, seed2 = 1;
        double maxWaste = -1;
        
        for (size_t i = 0; i < node->entries.size(); i++) {
            for (size_t j = i + 1; j < node->entries.size(); j++) {
                Rectangle combined = node->entries[i].mbr;
                combined.expand(node->entries[j].mbr);
                double waste = combined.area() - 
                              node->entries[i].mbr.area() - 
                              node->entries[j].mbr.area();
                
                if (waste > maxWaste) {
                    maxWaste = waste;
                    seed1 = i;
                    seed2 = j;
                }
            }
        }
        
        // Add seeds to new nodes
        node1->entries.push_back(node->entries[seed1]);
        node2->entries.push_back(node->entries[seed2]);
        
        // Distribute remaining entries
        for (size_t i = 0; i < node->entries.size(); i++) {
            if (i == seed1 || i == seed2) continue;
            
            Rectangle mbr1 = node1->computeMBR();
            Rectangle mbr2 = node2->computeMBR();
            
            double enlargement1 = mbr1.enlargement(node->entries[i].mbr);
            double enlargement2 = mbr2.enlargement(node->entries[i].mbr);
            
            if (enlargement1 < enlargement2) {
                node1->entries.push_back(node->entries[i]);
            } else {
                node2->entries.push_back(node->entries[i]);
            }
        }
        
        return {node1, node2};
    }
    
    // Adjust tree after insertion
    void adjustTree(RTreeNode* node, RTreeNode* splitNode, RTreeNode* parent) {
        if (node == root.get()) {
            if (splitNode) {
                // Create new root
                RTreeNode* newRoot = new RTreeNode(false);
                newRoot->entries.emplace_back(node->computeMBR(), node, false);
                newRoot->entries.emplace_back(splitNode->computeMBR(), splitNode, false);
                root.release();
                root.reset(newRoot);
            }
            return;
        }
        
        // Update parent's MBR for this node
        for (auto& entry : parent->entries) {
            if (entry.childPtr == node) {
                entry.mbr = node->computeMBR();
                break;
            }
        }
        
        // Handle split
        if (splitNode) {
            parent->entries.emplace_back(splitNode->computeMBR(), splitNode, false);
            
            if (parent->isFull()) {
                auto [p1, p2] = splitNode(parent);
                // Continue adjusting tree upward (simplified here)
            }
        }
    }
    
    // Search helper
    void searchHelper(RTreeNode* node, const Rectangle& query, 
                     vector<SpatialObject*>& results) {
        if (!node) return;
        
        for (auto& entry : node->entries) {
            if (entry.mbr.intersects(query)) {
                if (node->isLeaf) {
                    results.push_back(static_cast<SpatialObject*>(entry.childPtr));
                } else {
                    searchHelper(static_cast<RTreeNode*>(entry.childPtr), query, results);
                }
            }
        }
    }
    
public:
    BasicRTree() {
        root = make_unique<RTreeNode>(true);
    }
    
    // Insert a spatial object
    void insert(const SpatialObject& obj) {
        SpatialObject* objPtr = new SpatialObject(obj);
        
        // Choose leaf to insert
        RTreeNode* leaf = chooseLeaf(root.get(), obj.mbr);
        
        // Add entry to leaf
        leaf->entries.emplace_back(obj.mbr, objPtr, true);
        
        // Handle overflow
        if (leaf->isFull()) {
            auto [n1, n2] = splitNode(leaf);
            adjustTree(n1, n2, nullptr);
        } else {
            adjustTree(leaf, nullptr, nullptr);
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
        
        function<void(RTreeNode*)> countNodes = [&](RTreeNode* node) {
            if (!node) return;
            nodeCount++;
            
            if (node->isLeaf) {
                leafCount++;
                objectCount += node->entries.size();
            } else {
                for (auto& entry : node->entries) {
                    countNodes(static_cast<RTreeNode*>(entry.childPtr));
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
    cout << "=== Basic R-Tree Demo ===" << endl << endl;
    
    BasicRTree rtree;
    
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
