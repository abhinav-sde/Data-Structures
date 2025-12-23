#include <iostream>
#include <vector>
#include <string>
#include <map>

/**
 * Advanced Roaring Bitmap Problems in C++
 * Simulation of Inverted Index for Tag-based Search.
 */

#include "basic_operations.cpp"

class SearchEngine {
private:
    std::map<std::string, RoaringBitmap> index;

public:
    void addDoc(uint32_t docId, const std::vector<std::string>& tags) {
        for (const auto& tag : tags) {
            index[tag].add(docId);
        }
    }

    std::vector<uint32_t> findByTags(const std::vector<std::string>& tags) {
        std::vector<uint32_t> results;
        if (tags.empty()) return results;

        // Simplified scan (In real Roaring, we'd intersect the Bitmaps)
        for (uint32_t i = 0; i < 1000; ++i) {
            bool all_match = true;
            for (const auto& tag : tags) {
                if (index.find(tag) == index.end() || !index[tag].contains(i)) {
                    all_match = false;
                    break;
                }
            }
            if (all_match) results.push_back(i);
        }
        return results;
    }
};

int main() {
    SearchEngine engine;
    engine.addDoc(100, {"tech", "java"});
    engine.addDoc(200, {"tech", "cpp"});
    engine.addDoc(300, {"finance", "java"});

    std::cout << "Search 'tech' AND 'java':" << std::endl;
    auto res = engine.findByTags({"tech", "java"});
    for (auto id : res) std::cout << "Doc " << id << std::endl;

    return 0;
}
