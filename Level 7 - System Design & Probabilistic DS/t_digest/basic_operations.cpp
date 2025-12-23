#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

/**
 * Basic T-Digest Operations in C++
 * Implements centroid-based clustering for quantile estimation.
 */

struct Centroid {
    double mean;
    double weight;
    bool operator<(const Centroid& other) const { return mean < other.mean; }
};

class TDigest {
private:
    std::vector<Centroid> centroids;
    double totalWeight = 0;
    double compression;

public:
    TDigest(double delta) : compression(delta) {}

    void add(double val, double w = 1.0) {
        centroids.push_back({val, w});
        totalWeight += w;
        if (centroids.size() > compression * 10) compress();
    }

    void compress() {
        if (centroids.empty()) return;
        std::sort(centroids.begin(), centroids.end());

        std::vector<Centroid> compressed;
        Centroid current = centroids[0];
        double weightSoFar = 0;

        for (size_t i = 1; i < centroids.size(); ++i) {
            Centroid& next = centroids[i];
            double q = (weightSoFar + (current.weight + next.weight) / 2.0) / totalWeight;
            double k = totalWeight * (q * (1 - q)) / compression;

            if (current.weight + next.weight <= k || k < 1.0) {
                double newW = current.weight + next.weight;
                current.mean = (current.mean * current.weight + next.mean * next.weight) / newW;
                current.weight = newW;
            } else {
                compressed.push_back(current);
                weightSoFar += current.weight;
                current = next;
            }
        }
        compressed.push_back(current);
        centroids = std::move(compressed);
    }

    int size() const { return centroids.size(); }
};

int main() {
    TDigest td(100);
    for (int i = 0; i < 10000; ++i) {
        td.add(rand() % 1000 / 10.0);
    }
    td.compress();
    std::cout << "Centroids after compression: " << td.size() << std::endl;
    return 0;
}
