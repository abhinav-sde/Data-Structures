#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Advanced T-Digest Problems in C++
 * Focuses on merging digests.
 */

struct Centroid {
    double mean, weight;
    bool operator<(const Centroid& o) const { return mean < o.mean; }
};

class SimpleTDigest {
public:
    std::vector<Centroid> centroids;
    double totalWeight = 0;

    void add(double v) { centroids.push_back({v, 1.0}); totalWeight++; }
    
    void merge(const SimpleTDigest& other) {
        centroids.insert(centroids.end(), other.centroids.begin(), other.centroids.end());
        totalWeight += other.totalWeight;
    }

    double quantile(double q) {
        if (centroids.empty()) return 0;
        std::sort(centroids.begin(), centroids.end());
        double target = q * totalWeight;
        double current = 0;
        for (const auto& c : centroids) {
            if (current + c.weight >= target) return c.mean;
            current += c.weight;
        }
        return centroids.back().mean;
    }
};

int main() {
    SimpleTDigest s1, s2;
    for(int i=0; i<1000; ++i) s1.add(i);
    for(int i=1000; i<2000; ++i) s2.add(i);

    std::cout << "S1 P50: " << s1.quantile(0.5) << std::endl;
    std::cout << "S2 P50: " << s2.quantile(0.5) << std::endl;

    s1.merge(s2);
    std::cout << "Merged P50: " << s1.quantile(0.5) << " (Expected: 1000)" << std::endl;

    return 0;
}
