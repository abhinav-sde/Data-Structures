#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <functional>

/**
 * Basic Consistent Hashing Implementation in C++
 * Uses std::map to simulate the Hash Ring.
 */

class ConsistentHash {
private:
    std::map<size_t, std::string> circle;
    int numReplicas;
    std::hash<std::string> hasher;

public:
    ConsistentHash(int replicas) : numReplicas(replicas) {}

    void addNode(const std::string& node) {
        for (int i = 0; i < numReplicas; ++i) {
            size_t h = hasher(node + ":" + std::to_string(i));
            circle[h] = node;
        }
    }

    void removeNode(const std::string& node) {
        for (int i = 0; i < numReplicas; ++i) {
            size_t h = hasher(node + ":" + std::to_string(i));
            circle.erase(h);
        }
    }

    std::string getNode(const std::string& key) {
        if (circle.empty()) return "";
        size_t h = hasher(key);
        auto it = circle.lower_bound(h);
        if (it == circle.end()) {
            return circle.begin()->second;
        }
        return it->second;
    }
};

int main() {
    ConsistentHash ch(100);

    ch.addNode("Server_A");
    ch.addNode("Server_B");
    ch.addNode("Server_C");

    std::cout << "Node for 'my_photo.jpg': " << ch.getNode("my_photo.jpg") << std::endl;
    std::cout << "Node for 'user_1234.json': " << ch.getNode("user_1234.json") << std::endl;
    std::cout << "Node for 'session_abc': " << ch.getNode("session_abc") << std::endl;

    std::cout << "\nRemoving Server_B..." << std::endl;
    ch.removeNode("Server_B");
    std::cout << "Node for 'my_photo.jpg' now: " << ch.getNode("my_photo.jpg") << std::endl;

    return 0;
}
