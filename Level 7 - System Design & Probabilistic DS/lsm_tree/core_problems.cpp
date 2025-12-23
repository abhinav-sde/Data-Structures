#include <iostream>
#include <map>
#include <vector>
#include <string>

/**
 * Core LSM-Tree Problems in C++
 * Focuses on Compaction (Merging SSTables) and Tombstones.
 */

struct SSTable {
    std::map<std::string, std::string> data;
    int id;
};

class LSMTree {
private:
    std::map<std::string, std::string> memTable;
    std::vector<SSTable> level0;
    std::vector<SSTable> level1;
    const std::string TOMBSTONE = "__DEL__";
    int nextId = 0;

    void compact() {
        std::cout << "Triggering Compaction (L0 -> L1)..." << std::endl;
        std::map<std::string, std::string> merged;
        
        // Merge newest to oldest (reverse of Java logic to show different approach)
        // If we iterate newest to oldest, we only add if key isn't already there.
        for (auto it = level0.begin(); it != level0.end(); ++it) {
            for (auto const& [key, val] : it->data) {
                if (merged.find(key) == merged.end()) {
                    merged[key] = val;
                }
            }
        }

        // Final level: remove tombstones
        for (auto it = merged.begin(); it != merged.end(); ) {
            if (it->second == TOMBSTONE) it = merged.erase(it);
            else ++it;
        }

        level1.push_back({merged, nextId++});
        level0.clear();
    }

public:
    void put(std::string k, std::string v) { memTable[k] = v; }
    void remove(std::string k) { memTable[k] = TOMBSTONE; }

    void flush() {
        if (memTable.empty()) return;
        level0.insert(level0.begin(), {memTable, nextId++});
        memTable.clear();
        if (level0.size() >= 3) compact();
    }

    std::string get(std::string k) {
        if (memTable.count(k)) return memTable[k] == TOMBSTONE ? "DELETED" : memTable[k];
        for (auto& t : level0) if (t.data.count(k)) return t.data[k] == TOMBSTONE ? "DELETED" : t.data[k];
        for (auto& t : level1) if (t.data.count(k)) return t.data[k];
        return "NOT_FOUND";
    }
};

int main() {
    LSMTree lsm;
    lsm.put("apple", "red");
    lsm.flush();
    lsm.put("banana", "yellow");
    lsm.flush();
    lsm.remove("apple");
    lsm.put("cherry", "red");
    lsm.flush(); // triggers compaction

    std::cout << "apple: " << lsm.get("apple") << std::endl;
    std::cout << "banana: " << lsm.get("banana") << std::endl;
    std::cout << "cherry: " << lsm.get("cherry") << std::endl;

    return 0;
}
