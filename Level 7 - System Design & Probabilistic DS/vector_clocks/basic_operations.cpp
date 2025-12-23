#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

/**
 * Basic Vector Clock Operations in C++
 * Implements increment, merge, and comparison for causality detection.
 */

class VectorClock {
public:
    enum Comparison { BEFORE, AFTER, EQUAL, CONCURRENT };

    std::string nodeId;
    std::map<std::string, int> clock;

    VectorClock(std::string id) : nodeId(id) {
        clock[nodeId] = 0;
    }

    void increment() {
        clock[nodeId]++;
    }

    void merge(const std::map<std::string, int>& other) {
        for (auto const& [node, count] : other) {
            clock[node] = std::max(clock[node], count);
        }
        increment();
    }

    static Comparison compare(const std::map<std::string, int>& v1, const std::map<std::string, int>& v2) {
        bool less = false;
        bool greater = false;

        std::set<std::string> allKeys;
        for (auto const& [k, v] : v1) allKeys.insert(k);
        for (auto const& [k, v] : v2) allKeys.insert(k);

        for (const auto& node : allKeys) {
            int c1 = v1.count(node) ? v1.at(node) : 0;
            int c2 = v2.count(node) ? v2.at(node) : 0;

            if (c1 < c2) less = true;
            else if (c1 > c2) greater = true;
        }

        if (less && greater) return CONCURRENT;
        if (less) return BEFORE;
        if (greater) return AFTER;
        return EQUAL;
    }

    std::string toString() const {
        std::string s = "Node[" + nodeId + "]: {";
        for (auto const& [k, v] : clock) s += k + ":" + std::to_string(v) + " ";
        s += "}";
        return s;
    }
};

std::string compToString(VectorClock::Comparison c) {
    if (c == VectorClock::BEFORE) return "BEFORE";
    if (c == VectorClock::AFTER) return "AFTER";
    if (c == VectorClock::EQUAL) return "EQUAL";
    return "CONCURRENT";
}

int main() {
    VectorClock a("A"), b("B");

    a.increment();
    b.increment();

    std::cout << a.toString() << std::endl;
    std::cout << b.toString() << std::endl;
    std::cout << "A vs B: " << compToString(VectorClock::compare(a.clock, b.clock)) << std::endl;

    std::cout << "\nA sending to B..." << std::endl;
    a.increment();
    b.merge(a.clock);

    std::cout << a.toString() << std::endl;
    std::cout << b.toString() << std::endl;
    std::cout << "A vs B: " << compToString(VectorClock::compare(a.clock, b.clock)) << std::endl;

    return 0;
}
