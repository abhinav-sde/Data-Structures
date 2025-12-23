#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Problem: Kruskal's Algorithm for Minimum Spanning Tree
// Using DSU to greedily pick smallest edges without creating cycles.

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        for(int i=0; i<n; ++i) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

int kruskalMST(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    int mstWeight = 0;
    int edgesCount = 0;

    for (const auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mstWeight += edge.weight;
            edgesCount++;
        }
    }
    
    // Validate if MST is formed (should have n-1 edges)
    if (edgesCount != n - 1) return -1; 
    return mstWeight;
}

int main() {
    int n = 4;
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };
    
    // MST should pick: 2-3 (4), 0-3 (5), 0-1 (10) -> Total 19
    cout << "MST Weight: " << kruskalMST(n, edges) << endl; 
    return 0;
}
