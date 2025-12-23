#include <iostream>
#include <map>
#include <string>
#include <vector>

/**
 * Core Vector Clock Problems in C++
 * Simulation of Distributed KV Store with Conflict Detection.
 */

typedef std::map<std::string, int> VC;

struct VersionedValue {
    std::string val;
    VC clock;
};

// Simplified comparison for the example
enum Comp { BEFORE, AFTER, CONCURRENT };
Comp compare(const VC& v1, const VC& v2) {
    bool less = false, greater = false;
    for (auto const& [k, v] : v1) {
        int c2 = v2.count(k) ? v2.at(k) : 0;
        if (v < c2) less = true;
        if (v > c2) greater = true;
    }
    for (auto const& [k, v] : v2) {
        if (v1.find(k) == v1.end() && v > 0) less = true;
    }
    if (less && greater) return CONCURRENT;
    if (less) return BEFORE;
    return AFTER; // Includes EQUAL as AFTER for overwriting
}

class DistributedKV {
public:
    std::map<std::string, std::vector<VersionedValue>> store;

    void update(std::string key, std::string val, VC clock) {
        auto& versions = store[key];
        std::vector<VersionedValue> survivors;
        bool conflicted = false;

        for (auto const& v : versions) {
            Comp c = compare(clock, v.clock);
            if (c == AFTER) continue; 
            if (c == BEFORE) return;
            if (c == CONCURRENT) {
                survivors.push_back(v);
                conflicted = true;
            }
        }
        survivors.push_back({val, clock});
        store[key] = survivors;
        if (conflicted) std::cout << "Conflict on '" << key << "'!" << std::endl;
    }
};

int main() {
    DistributedKV kv;
    VC clockA = {{"A", 1}}, clockB = {{"B", 1}};

    kv.update("status", "on", clockA);
    kv.update("status", "off", clockB);

    std::cout << "Versions for 'status': " << kv.store["status"].size() << std::endl;

    VC clockC = {{"A", 2}, {"B", 1}, {"C", 1}};
    kv.update("status", "merged", clockC);
    std::cout << "Versions for 'status' after causal update: " << kv.store["status"].size() << std::endl;

    return 0;
}
