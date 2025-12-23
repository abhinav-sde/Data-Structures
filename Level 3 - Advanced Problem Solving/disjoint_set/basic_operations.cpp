#include <iostream>
#include <vector>

using namespace std;

// Disjoint Set Union with Path Compression and Union by Rank
class DSU {
    vector<int> parent;
    vector<int> rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // Initially, each element is its own parent (own set)
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find the representative of the set containing i
    int find(int i) {
        if (parent[i] != i) {
            // Path Compression
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    // Unite the sets containing i and j
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            // Union by Rank
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }

    // Check if i and j are in the same set
    bool same(int i, int j) {
        return find(i) == find(j);
    }
};

int main() {
    DSU dsu(5);
    
    dsu.unite(0, 1);
    dsu.unite(2, 3);
    
    cout << "0 and 1 same? " << (dsu.same(0, 1) ? "Yes" : "No") << endl; // Yes
    cout << "0 and 3 same? " << (dsu.same(0, 3) ? "Yes" : "No") << endl; // No
    
    dsu.unite(1, 3);
    cout << "0 and 3 same after union(1,3)? " << (dsu.same(0, 3) ? "Yes" : "No") << endl; // Yes

    return 0;
}
