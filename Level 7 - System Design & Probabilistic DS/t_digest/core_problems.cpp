#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>

/**
 * Core T-Digest Problems in C++
 * Focuses on Quantile Estimation.
 */

struct Centroid {
    double mean, weight;
    bool operator<(const Centroid& o) const { return mean < o.mean; }
};

class TDigest {
private:
    std::vector<Centroid> centroids;
    double totalWeight = 0;

public:
    void add(double v) { centroids.push_back({v, 1.0}); totalWeight++; }

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
    TDigest td;
    std::vector<double> data;
    for (int i = 0; i < 10000; ++i) {
        double v = (double)rand() / RAND_MAX * 100;
        td.add(v);
        data.push_back(v);
    }
    std::sort(data.begin(), data.end());

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "P50 Estimate: " << td.quantile(0.5) << " Actual: " << data[5000] << std::endl;
    std::cout << "P99 Estimate: " << td.quantile(0.99) << " Actual: " << data[9900] << std::endl;

    return 0;
}
