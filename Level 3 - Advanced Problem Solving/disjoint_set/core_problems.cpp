#include <iostream>
#include <vector>
#include "basic_operations.cpp" // Assuming DSU class is accessible or redefined here

using namespace std;

// Redefining simpler DSU for the problem context if needed, 
// strictly speaking in C++ strict compilation unit terms we should include headers.
// For this concise example, I will assume DSU struct/class availability or inline it.

struct SimpleDSU {
    vector<int> parent;
    SimpleDSU(int n) {
        parent.resize(n);
        for(int i=0; i<n; ++i) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true; // Union successful
        }
        return false; // Already in same set
    }
};

// Problem: Cycle Detection in Undirected Graph
// Given an edge list, determine if the graph has a cycle.
bool hasCycle(int n, vector<pair<int, int>>& edges) {
    SimpleDSU dsu(n);
    for (auto& edge : edges) {
        // If two nodes are already in the same set, adding this edge creates a cycle
        if (!dsu.unite(edge.first, edge.second)) {
            return true;
        }
    }
    return false;
}

int main() {
    int n = 4;
    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 0}}; // Cycle: 0-1-2-0
    
    cout << "Graph has cycle? " << (hasCycle(n, edges) ? "Yes" : "No") << endl;

    return 0;
}
