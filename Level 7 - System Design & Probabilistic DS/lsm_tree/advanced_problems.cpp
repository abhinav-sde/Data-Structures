#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <bitset>

/**
 * Advanced LSM-Tree Problems in C++
 * Focuses on Bloom Filter optimization.
 */

class BloomFilter {
private:
    std::vector<bool> bits;
    int numHash;
    int size;

public:
    BloomFilter(int expected, double fpr) {
        size = (int)(-expected * log(fpr) / (log(2) * log(2)));
        numHash = (int)(size / expected * log(2));
        if (size <= 0) size = 64;
        bits.resize(size, false);
    }

    void add(const std::string& key) {
        for (int i = 0; i < numHash; ++i) {
            size_t h = std::hash<std::string>{}(key + std::to_string(i));
            bits[h % size] = true;
        }
    }

    bool mightContain(const std::string& key) {
        for (int i = 0; i < numHash; ++i) {
            size_t h = std::hash<std::string>{}(key + std::to_string(i));
            if (!bits[h % size]) return false;
        }
        return true;
    }
};

struct SSTable {
    std::map<std::string, std::string> data;
    BloomFilter* filter;

    SSTable(std::map<std::string, std::string> d) : data(d) {
        filter = new BloomFilter(data.size() + 1, 0.01);
        for (auto const& [key, val] : data) filter->add(key);
    }
};

class LSMTree {
private:
    std::map<std::string, std::string> memTable;
    std::vector<SSTable*> ssTables;
    int threshold = 5;

    void flush() {
        ssTables.insert(ssTables.begin(), new SSTable(memTable));
        memTable.clear();
    }

public:
    void put(std::string k, std::string v) {
        memTable[k] = v;
        if (memTable.size() >= threshold) flush();
    }

    std::string get(std::string k) {
        if (memTable.count(k)) return memTable[k];

        int checked = 0, skips = 0;
        for (auto* table : ssTables) {
            checked++;
            if (!table->filter->mightContain(k)) {
                skips++;
                continue;
            }
            if (table->data.count(k)) {
                std::cout << "[Stats] Tables: " << checked << ", Skips: " << skips << std::endl;
                return table->data[k];
            }
        }
        std::cout << "[Stats] Tables: " << checked << ", Skips: " << skips << std::endl;
        return "NOT_FOUND";
    }
};

int main() {
    LSMTree lsm;
    for (int i = 0; i < 20; ++i) {
        lsm.put("key_" + std::to_string(i), "val_" + std::to_string(i));
    }

    std::cout << "Finding key_5:" << std::endl;
    lsm.get("key_5");

    std::cout << "\nFinding ghost_key (Expecting high Bloom Filter skips):" << std::endl;
    lsm.get("ghost_key");

    return 0;
}
