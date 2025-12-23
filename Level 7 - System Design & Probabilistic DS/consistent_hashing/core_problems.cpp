#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>

/**
 * Core Consistent Hashing Problems in C++
 * Focuses on measuring Load Distribution and Churn.
 */

class ConsistentHash {
public:
    std::map<int, std::string> ring;
    int replicas;
    std::hash<std::string> hasher;

    ConsistentHash(int r) : replicas(r) {}

    void add(const std::string& node) {
        for (int i = 0; i < replicas; ++i) ring[hasher(node + std::to_string(i))] = node;
    }

    void remove(const std::string& node) {
        for (int i = 0; i < replicas; ++i) ring.erase(hasher(node + std::to_string(i)));
    }

    std::string get(const std::string& key) {
        if (ring.empty()) return "";
        size_t h = hasher(key);
        auto it = ring.lower_bound(h);
        if (it == ring.end()) return ring.begin()->second;
        return it->second;
    }
};

int main() {
    ConsistentHash ch(50);
    std::vector<std::string> servers = {"S1", "S2", "S3", "S4", "S5"};
    for (const auto& s : servers) ch.add(s);

    std::unordered_map<std::string, int> distribution;
    for (int i = 0; i < 10000; ++i) {
        std::string node = ch.get("key_" + std::to_string(i));
        distribution[node]++;
    }

    std::cout << "Initial Load Distribution (10k keys):" << std::endl;
    for (const auto& pair : distribution) {
        std::cout << pair.first << ": " << pair.second << " keys" << std::endl;
    }

    std::cout << "\nRemoving server S2..." << std::endl;
    int moved = 0;
    for (int i = 0; i < 10000; ++i) {
        std::string key = "key_" + std::to_string(i);
        std::string oldNode = ch.get(key);
        ch.remove("S2");
        std::string newNode = ch.get(key);
        if (oldNode != newNode) moved++;
        ch.add("S2");
    }

    std::cout << "Keys that would move if S2 is removed: " << moved << std::endl;
    std::cout << "Ideal churn (1/N = 1/5): 2000. Actual: " << moved << std::endl;

    return 0;
}
