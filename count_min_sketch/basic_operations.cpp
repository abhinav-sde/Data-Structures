#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

/**
 * Count-Min Sketch for frequency estimation
 */
class CountMinSketch {
    int width, depth;
    vector<vector<long long>> table;
    vector<int> seeds;

public:
    CountMinSketch(double epsilon, double delta) {
        width = ceil(2 / epsilon);
        depth = ceil(log(1 / delta));
        table.assign(depth, vector<long long>(width, 0));
        for (int i = 0; i < depth; i++) seeds.push_back(rand());
    }

    int hash(const string& str, int i) {
        size_t h = hash<string>{}(str) ^ seeds[i];
        return h % width;
    }

    void add(const string& str) {
        for (int i = 0; i < depth; i++) {
            table[i][hash(str, i)]++;
        }
    }

    long long estimate(const string& str) {
        long long res = 1e18;
        for (int i = 0; i < depth; i++) {
            res = min(res, table[i][hash(str, i)]);
        }
        return res;
    }
};

int main() {
    CountMinSketch cms(0.01, 0.01);
    cms.add("SDE3");
    cms.add("SDE3");
    cout << "SDE3 frequency: " << cms.estimate("SDE3") << endl;
    return 0;
}
