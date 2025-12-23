#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

/**
 * Basic LSM-Tree Operations in C++
 * Implements MemTable (std::map) and mock SSTable flushing.
 */

struct SSTable {
    std::map<std::string, std::string> data;
    long long timestamp;
};

class LSMTree {
private:
    std::map<std::string, std::string> memTable;
    std::vector<SSTable> ssTables;
    int threshold;

    void flush() {
        std::cout << "Flushing MemTable to SSTable..." << std::endl;
        ssTables.insert(ssTables.begin(), {memTable, 12345}); // newest first
        memTable.clear();
    }

public:
    LSMTree(int t) : threshold(t) {}

    void put(std::string key, std::string val) {
        memTable[key] = val;
        if (memTable.size() >= threshold) flush();
    }

    std::string get(std::string key) {
        if (memTable.find(key) != memTable.end()) return memTable[key];
        for (const auto& table : ssTables) {
            if (table.data.find(key) != table.data.end()) return table.data.at(key);
        }
        return "NOT_FOUND";
    }

    int tableCount() { return ssTables.size(); }
};

int main() {
    LSMTree lsm(3);

    lsm.put("user:1", "Alice");
    lsm.put("user:2", "Bob");
    lsm.put("user:3", "Charlie"); // flush
    lsm.put("user:4", "David");
    lsm.put("user:1", "Alice_V2");

    std::cout << "Value for user:1: " << lsm.get("user:1") << std::endl;
    std::cout << "Value for user:3: " << lsm.get("user:3") << std::endl;
    std::cout << "Total Tables: " << lsm.tableCount() << std::endl;

    return 0;
}
