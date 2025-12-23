#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>

/**
 * Advanced Consistent Hashing Problems in C++
 * Implements Weighted Consistent Hashing.
 */

class WeightedConsistentHash {
private:
    std::map<size_t, std::string> ring;
    int baseReplicas;
    std::hash<std::string> hasher;

public:
    WeightedConsistentHash(int base) : baseReplicas(base) {}

    void addNode(const std::string& node, int weight) {
        int replicas = baseReplicas * weight;
        for (int i = 0; i < replicas; ++i) {
            ring[hasher(node + "_vnode_" + std::to_string(i))] = node;
        }
    }

    std::string getNode(const std::string& key) {
        if (ring.empty()) return "";
        size_t h = hasher(key);
        auto it = ring.lower_bound(h);
        if (it == ring.end()) return ring.begin()->second;
        return it->second;
    }
};

int main() {
    WeightedConsistentHash ch(10);

    // Server A is 3x more powerful
    ch.addNode("PowerServer_A", 3);
    ch.addNode("StandardServer_B", 1);

    std::unordered_map<std::string, int> load;
    for (int i = 0; i < 10000; ++i) {
        load[ch.getNode("req_" + std::to_string(i))]++;
    }

    std::cout << "Weighted Load Distribution (Server A has 3x weight):" << std::endl;
    for (const auto& p : load) {
        std::cout << p.first << ": " << p.second << " requests" << std::endl;
    }

    double ratio = (double)load["PowerServer_A"] / load["StandardServer_B"];
    std::cout << "\nMeasured Ratio (A/B): " << std::fixed << std::setprecision(2) << ratio << std::endl;
    std::cout << "Expected Ratio: 3.00" << std::endl;

    return 0;
}
