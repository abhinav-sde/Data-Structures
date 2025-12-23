#include <iostream>
#include <vector>
#include <string>
#include <random>

/**
 * Basic Cuckoo Filter Operations in C++
 */

class CuckooFilter {
private:
    static const int SLOTS = 4;
    static const int MAX_KICKS = 500;

    std::vector<std::vector<uint8_t>> buckets;
    int numBuckets;

    uint8_t getFingerprint(const std::string& item) {
        size_t h = std::hash<std::string>{}(item);
        uint8_t fp = (uint8_t)((h ^ (h >> 16)) & 0xFF);
        return fp == 0 ? 1 : fp;
    }

    int getHash(const std::string& item) {
        return std::hash<std::string>{}(item) % numBuckets;
    }

    int getAltIndex(int index, uint8_t fp) {
        size_t hfp = std::hash<int>{}(fp);
        return (index ^ hfp) % numBuckets;
    }

public:
    CuckooFilter(int capacity) {
        numBuckets = (capacity + SLOTS - 1) / SLOTS;
        buckets.resize(numBuckets, std::vector<uint8_t>(SLOTS, 0));
    }

    bool insert(const std::string& item) {
        uint8_t fp = getFingerprint(item);
        int i1 = getHash(item);
        int i2 = getAltIndex(i1, fp);

        auto tryInsert = [&](int idx) {
            for (int i = 0; i < SLOTS; ++i) {
                if (buckets[idx][i] == 0) {
                    buckets[idx][i] = fp;
                    return true;
                }
            }
            return false;
        };

        if (tryInsert(i1) || tryInsert(i2)) return true;

        int curr = (rand() % 2 == 0) ? i1 : i2;
        for (int k = 0; k < MAX_KICKS; ++k) {
            int slot = rand() % SLOTS;
            std::swap(fp, buckets[curr][slot]);
            curr = getAltIndex(curr, fp);
            if (tryInsert(curr)) return true;
        }
        return false;
    }

    bool lookup(const std::string& item) {
        uint8_t fp = getFingerprint(item);
        int i1 = getHash(item);
        int i2 = getAltIndex(i1, fp);
        auto check = [&](int idx) {
            for (int i = 0; i < SLOTS; ++i) if (buckets[idx][i] == fp) return true;
            return false;
        };
        return check(i1) || check(i2);
    }

    bool remove(const std::string& item) {
        uint8_t fp = getFingerprint(item);
        int i1 = getHash(item);
        int i2 = getAltIndex(i1, fp);
        auto del = [&](int idx) {
            for (int i = 0; i < SLOTS; ++i) {
                if (buckets[idx][i] == fp) {
                    buckets[idx][i] = 0;
                    return true;
                }
            }
            return false;
        };
        return del(i1) || del(i2);
    }
};

int main() {
    CuckooFilter cf(100);
    cf.insert("data_1");
    cf.insert("data_2");

    std::cout << "Lookup data_1: " << (cf.lookup("data_1") ? "Found" : "Not Found") << std::endl;
    std::cout << "Lookup data_3: " << (cf.lookup("data_3") ? "Found" : "Not Found") << std::endl;

    cf.remove("data_1");
    std::cout << "After deleting data_1, lookup: " << (cf.lookup("data_1") ? "Found" : "Not Found") << std::endl;

    return 0;
}
