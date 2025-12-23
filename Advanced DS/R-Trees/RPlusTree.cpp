/**
 * R+-Tree Implementation (Simplified)
 * 
 * R+-Tree variant that eliminates overlap by allowing object duplication.
 * No overlapping MBRs between siblings for faster queries.
 * 
 * Note: This is a simplified educational implementation.
 * Full implementation requires complex splitting and clipping algorithms.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

struct Rectangle {
    double xMin, xMax, yMin, yMax;
    
    Rectangle(double xMin = 0, double xMax = 0, double yMin = 0, double yMax = 0)
        : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {}
    
    double area() const {
        return max(0.0, xMax - xMin) * max(0.0, yMax - yMin);
    }
    
    bool intersects(const Rectangle& other) const {
        return !(xMax <= other.xMin || other.xMax <= xMin ||
                 yMax <= other.yMin || other.yMax <= yMin);
    }
    
    bool contains(const Rectangle& other) const {
        return xMin <= other.xMin && xMax >= other.xMax &&
               yMin <= other.yMin && yMax >= other.yMax;
    }
    
    // Clip this rectangle to bounds
    Rectangle clip(const Rectangle& bounds) const {
        return Rectangle(
            max(xMin, bounds.xMin),
            min(xMax, bounds.xMax),
            max(yMin, bounds.yMin),
            min(yMax, bounds.yMax)
        );
    }
};

struct SpatialObject {
    Rectangle mbr;
    string data;
    
    SpatialObject(const Rectangle& mbr, const string& data)
        : mbr(mbr), data(data) {}
};

struct RPlusEntry {
    Rectangle mbr;
    void* childPtr;
    bool isLeaf;
    
    RPlusEntry(const Rectangle& mbr, void* ptr, bool isLeaf)
        : mbr(mbr), childPtr(ptr), isLeaf(isLeaf) {}
};

class RPlusTreeNode {
public:
    vector<RPlusEntry> entries;
    bool isLeaf;
    Rectangle bounds;  // Non-overlapping partition bounds
    static const int MAX_ENTRIES = 4;
    
    RPlusTreeNode(bool isLeaf, const Rectangle& bounds = Rectangle())
        : isLeaf(isLeaf), bounds(bounds) {}
    
    bool isFull() const {
        return entries.size() >= MAX_ENTRIES;
    }
};

class RPlusTree {
private:
    unique_ptr<RPlusTreeNode> root;
    Rectangle worldBounds;  // Total space
    
    // Insert with potential duplication
    void insertHelper(RPlusTreeNode* node, const SpatialObject& obj) {
        if (node->isLeaf) {
            // Check if object intersects this node's bounds
            if (obj.mbr.intersects(node->bounds)) {
                // Clip object to node bounds and insert
                Rectangle clipped = obj.mbr.clip(node->bounds);
                SpatialObject* objPtr = new SpatialObject(clipped, obj.data);
                node->entries.emplace_back(clipped, objPtr, true);
            }
        } else {
            // Recursively insert into all intersecting children
            for (auto& entry : node->entries) {
                if (obj.mbr.intersects(entry.mbr)) {
                    insertHelper(static_cast<RPlusTreeNode*>(entry.childPtr), obj);
                }
            }
        }
    }
    
    // Search helper
    void searchHelper(RPlusTreeNode* node, const Rectangle& query,
                     vector<SpatialObject*>& results) {
        if (!node) return;
        
        for (auto& entry : node->entries) {
            if (entry.mbr.intersects(query)) {
                if (node->isLeaf) {
                    SpatialObject* obj = static_cast<SpatialObject*>(entry.childPtr);
                    // Check if not already in results (due to duplication)
                    bool found = false;
                    for (auto* r : results) {
                        if (r->data == obj->data) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        results.push_back(obj);
                    }
                } else {
                    searchHelper(static_cast<RPlusTreeNode*>(entry.childPtr),
                               query, results);
                }
            }
        }
    }
    
public:
    RPlusTree(const Rectangle& bounds) : worldBounds(bounds) {
        root = make_unique<RPlusTreeNode>(true, bounds);
        
        // Initialize with 4 non-overlapping quadrants (simplified)
        double midX = (bounds.xMin + bounds.xMax) / 2.0;
        double midY = (bounds.yMin + bounds.yMax) / 2.0;
        
        // For demo, create leaf quadrants
        root->isLeaf = false;
        
        Rectangle nw(bounds.xMin, midX, midY, bounds.yMax);
        Rectangle ne(midX, bounds.xMax, midY, bounds.yMax);
        Rectangle sw(bounds.xMin, midX, bounds.yMin, midY);
        Rectangle se(midX, bounds.xMax, bounds.yMin, midY);
        
        root->entries.emplace_back(nw, new RPlusTreeNode(true, nw), false);
        root->entries.emplace_back(ne, new RPlusTreeNode(true, ne), false);
        root->entries.emplace_back(sw, new RPlusTreeNode(true, sw), false);
        root->entries.emplace_back(se, new RPlusTreeNode(true, se), false);
    }
    
    // Insert spatial object (may be duplicated across partitions)
    void insert(const SpatialObject& obj) {
        insertHelper(root.get(), obj);
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
        int totalEntries = 0;
        
        function<void(RPlusTreeNode*)> countNodes = [&](RPlusTreeNode* node) {
            if (!node) return;
            nodeCount++;
            
            if (node->isLeaf) {
                leafCount++;
                objectCount += node->entries.size();
            } else {
                for (auto& entry : node->entries) {
                    totalEntries++;
                    countNodes(static_cast<RPlusTreeNode*>(entry.childPtr));
                }
            }
        };
        
        countNodes(root.get());
        
        cout << "Total nodes: " << nodeCount << endl;
        cout << "Leaf nodes: " << leafCount << endl;
        cout << "Object entries: " << objectCount << " (may include duplicates)" << endl;
    }
};

// Example usage
int main() {
    cout << "=== R+-Tree Demo ===" << endl << endl;
    cout << "Note: R+-Tree eliminates overlap by allowing object duplication" << endl;
    cout << "across non-overlapping partitions." << endl << endl;
    
    Rectangle worldBounds(0, 100, 0, 100);
    RPlusTree rtree(worldBounds);
    
    // Insert spatial objects
    vector<SpatialObject> objects = {
        SpatialObject(Rectangle(10, 20, 10, 20), "A"),
        SpatialObject(Rectangle(45, 55, 45, 55), "B"),  // Spans multiple quadrants
        SpatialObject(Rectangle(30, 40, 30, 40), "C"),
        SpatialObject(Rectangle(60, 70, 60, 70), "D"),
        SpatialObject(Rectangle(80, 90, 80, 90), "E")
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
    cout << "\nSearch query [40, 60] x [40, 60]:" << endl;
    Rectangle query(40, 60, 40, 60);
    vector<SpatialObject*> results = rtree.search(query);
    
    cout << "  Found " << results.size() << " unique objects:" << endl;
    for (auto* obj : results) {
        cout << "    " << obj->data << endl;
    }
    
    cout << "\nKey R+-Tree Feature: No overlapping MBRs between siblings!" << endl;
    cout << "Object B (45-55, 45-55) may appear in multiple quadrants." << endl;
    
    return 0;
}
