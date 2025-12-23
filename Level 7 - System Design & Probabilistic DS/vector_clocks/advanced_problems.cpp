#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <chrono>

/**
 * Advanced Vector Clock Problems in C++
 * Focuses on Pruning strategy for bounded growth.
 */

class PrunableVC {
private:
    std::map<std::string, int> clock;
    std::map<std::string, long long> lastUpdate;
    int limit;

    long long now() {
        return std::chrono::system_clock::now().time_since_epoch().count();
    }

    void prune() {
        std::string oldest;
        long long minTime = -1;

        for (auto const& [node, time] : lastUpdate) {
            if (minTime == -1 || time < minTime) {
                minTime = time;
                oldest = node;
            }
        }
        if (!oldest.empty()) {
            std::cout << "[GC] Pruning node: " << oldest << std::endl;
            clock.erase(oldest);
            lastUpdate.erase(oldest);
        }
    }

public:
    PrunableVC(int l) : limit(l) {}

    void set(std::string node, int count) {
        clock[node] = count;
        lastUpdate[node] = now();
        if (clock.size() > limit) prune();
    }

    void print() {
        std::cout << "VC: { ";
        for (auto const& [k, v] : clock) std::cout << k << ":" << v << " ";
        std::cout << "} Size: " << clock.size() << std::endl;
    }
};

int main() {
    PrunableVC pvc(3);

    pvc.set("Node_1", 10);
    pvc.set("Node_2", 20);
    pvc.set("Node_3", 30);
    pvc.print();

    std::cout << "\nAdding Node_4..." << std::endl;
    pvc.set("Node_4", 1);
    pvc.print();

    return 0;
}
