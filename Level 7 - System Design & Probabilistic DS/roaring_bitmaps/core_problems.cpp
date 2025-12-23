#include <iostream>
#include <map>
#include <bitset>
#include <vector>

/**
 * Core Roaring Bitmap Problems in C++
 * Focuses on Set Operations (AND, OR).
 */

class SimpleRoaring {
public:
    std::map<uint16_t, std::bitset<65536>> chunks;

    void add(uint32_t x) {
        chunks[x >> 16].set(x & 0xFFFF);
    }

    int cardinality() const {
        int c = 0;
        for (auto const& [key, bits] : chunks) c += bits.count();
        return c;
    }

    static SimpleRoaring intersect(const SimpleRoaring& r1, const SimpleRoaring& r2) {
        SimpleRoaring res;
        for (auto const& [key, bits] : r1.chunks) {
            if (r2.chunks.count(key)) {
                auto combined = bits & r2.chunks.at(key);
                if (combined.any()) res.chunks[key] = combined;
            }
        }
        return res;
    }

    static SimpleRoaring unite(const SimpleRoaring& r1, const SimpleRoaring& r2) {
        SimpleRoaring res = r1;
        for (auto const& [key, bits] : r2.chunks) {
            res.chunks[key] |= bits;
        }
        return res;
    }
};

int main() {
    SimpleRoaring r1, r2;
    for (int i = 0; i < 1000; i += 2) r1.add(i);
    for (int i = 0; i < 1000; i += 3) r2.add(i);

    std::cout << "S1 Size: " << r1.cardinality() << std::endl;
    std::cout << "S2 Size: " << r2.cardinality() << std::endl;

    auto intersection = SimpleRoaring::intersect(r1, r2);
    auto union_set = SimpleRoaring::unite(r1, r2);

    std::cout << "Intersection Size: " << intersection.cardinality() << std::endl;
    std::cout << "Union Size: " << union_set.cardinality() << std::endl;

    return 0;
}
