#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

/**
 * HyperLogLog for unique count estimation
 */
class HyperLogLog {
    int p, m;
    double alpha;
    vector<int> registers;

public:
    HyperLogLog(int precision) : p(precision) {
        m = 1 << p;
        registers.assign(m, 0);
        if (m == 16) alpha = 0.673;
        else if (m == 32) alpha = 0.697;
        else if (m == 64) alpha = 0.709;
        else alpha = 0.7213 / (1 + 1.079 / m);
    }

    void add(const string& str) {
        size_t h = hash<string>{}(str);
        int index = h >> (64 - p);
        long long w = h << p;
        int rho = __builtin_clzll(w | 1) + 1;
        registers[index] = max(registers[index], rho);
    }

    long long count() {
        double Z = 0;
        for (int r : registers) Z += pow(2.0, -r);
        double estimate = alpha * m * m / Z;

        if (estimate <= 2.5 * m) {
            int V = 0;
            for (int r : registers) if (r == 0) V++;
            if (V > 0) estimate = m * log((double)m / V);
        }
        return round(estimate);
    }
};

int main() {
    HyperLogLog hll(10);
    for (int i = 0; i < 1000; i++) hll.add("data_" + to_string(i));
    cout << "Unique count estimate: " << hll.count() << endl;
    return 0;
}
