#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

// ========================================
// GRAPH ADVANCED PROBLEMS
// ========================================

// ========================================
// 1. DIJKSTRA'S ALGORITHM
// ========================================
// Concept: Shortest path from single source (non-negative weights)
// Time: O((V + E) log V) with priority queue

vector<int> dijkstra(vector<vector<pair<int,int>>>& adj, int V, int src) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    dist[src] = 0;
    pq.push({0, src});  // {distance, vertex}
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto& [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

// ========================================
// 2. BELLMAN-FORD ALGORITHM
// ========================================
// Concept: Shortest path with negative weights, detects negative cycles
// Time: O(VE)

struct Edge {
    int u, v, weight;
};

bool bellmanFord(vector<Edge>& edges, int V, int src, vector<int>& dist) {
    dist.assign(V, INT_MAX);
    dist[src] = 0;
    
    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (auto& e : edges) {
            if (dist[e.u] != INT_MAX && dist[e.u] + e.weight < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.weight;
            }
        }
    }
    
    // Check for negative cycles
    for (auto& e : edges) {
        if (dist[e.u] != INT_MAX && dist[e.u] + e.weight < dist[e.v]) {
            return false;  // Negative cycle exists
        }
    }
    
    return true;
}

// ========================================
// 3. FLOYD-WARSHALL ALGORITHM
// ========================================
// Concept: All pairs shortest path
// Time: O(V^3)

void floydWarshall(vector<vector<int>>& graph, int V) {
    vector<vector<int>> dist = graph;
    
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    // Print result
    cout << "Shortest distances between all pairs:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INT_MAX)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

// ========================================
// 4. PRIM'S ALGORITHM (MST)
// ========================================
// Concept: Minimum Spanning Tree
// Time: O((V + E) log V)

int primMST(vector<vector<pair<int,int>>>& adj, int V) {
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    key[0] = 0;
    pq.push({0, 0});  // {weight, vertex}
    
    int mstWeight = 0;
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();
        
        if (inMST[u]) continue;
        
        inMST[u] = true;
        mstWeight += weight;
        
        for (auto& [v, w] : adj[u]) {
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                pq.push({w, v});
            }
        }
    }
    
    return mstWeight;
}

// ========================================
// 5. KRUSKAL'S ALGORITHM (MST)
// ========================================
// Concept: MST using Union-Find
// Time: O(E log E)

class UnionFind {
private:
    vector<int> parent, rank;
    
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if (px == py) return false;
        
        // Union by rank
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        
        return true;
    }
};

int kruskalMST(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) {
        return a.weight < b.weight;
    });
    
    UnionFind uf(V);
    int mstWeight = 0;
    int edgeCount = 0;
    
    for (auto& e : edges) {
        if (uf.unite(e.u, e.v)) {
            mstWeight += e.weight;
            edgeCount++;
            
            if (edgeCount == V - 1) break;
        }
    }
    
    return mstWeight;
}

// ========================================
// 6. 0-1 BFS (SHORTEST PATH WITH 0-1 WEIGHTS)
// ========================================
// Concept: Deque-based BFS for 0-1 weighted graphs
// Time: O(V + E)

vector<int> bfs01(vector<vector<pair<int,int>>>& adj, int V, int src) {
    vector<int> dist(V, INT_MAX);
    deque<int> dq;
    
    dist[src] = 0;
    dq.push_back(src);
    
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        
        for (auto& [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                
                if (weight == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }
    
    return dist;
}

// ========================================
// 7. A* ALGORITHM
// ========================================
// Concept: Heuristic-based shortest path
// Time: Depends on heuristic

int heuristic(int u, int v) {
    // Manhattan distance or Euclidean distance
    return abs(u - v);  // Simplified
}

vector<int> astar(vector<vector<pair<int,int>>>& adj, int V, int src, int dest) {
    vector<int> dist(V, INT_MAX);
    vector<int> f(V, INT_MAX);  // f = g + h
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    dist[src] = 0;
    f[src] = heuristic(src, dest);
    pq.push({f[src], src});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (u == dest) break;
        
        for (auto& [v, weight] : adj[u]) {
            int newDist = dist[u] + weight;
            
            if (newDist < dist[v]) {
                dist[v] = newDist;
                f[v] = dist[v] + heuristic(v, dest);
                pq.push({f[v], v});
            }
        }
    }
    
    return dist;
}

// ========================================
// 8. TRAVELLING SALESMAN PROBLEM (DP)
// ========================================
// Concept: Find shortest Hamiltonian cycle
// Time: O(n^2 * 2^n)

int tsp(vector<vector<int>>& dist, int n) {
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
    
    dp[1][0] = 0;  // Start from city 0
    
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) continue;
            if (dp[mask][u] == INT_MAX) continue;
            
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                
                int newMask = mask | (1 << v);
                dp[newMask][v] = min(dp[newMask][v], dp[mask][u] + dist[u][v]);
            }
        }
    }
    
    int result = INT_MAX;
    int fullMask = (1 << n) - 1;
    
    for (int u = 1; u < n; u++) {
        if (dp[fullMask][u] != INT_MAX) {
            result = min(result, dp[fullMask][u] + dist[u][0]);
        }
    }
    
    return result;
}

// ========================================
// 9. EULERIAN PATH/CIRCUIT
// ========================================
// Concept: Path visiting every edge exactly once

bool hasEulerianPath(vector<vector<int>>& adj, int V) {
    vector<int> degree(V, 0);
    
    for (int u = 0; u < V; u++) {
        degree[u] = adj[u].size();
    }
    
    int oddCount = 0;
    for (int d : degree) {
        if (d % 2 != 0) oddCount++;
    }
    
    return oddCount == 0 || oddCount == 2;
}

// ========================================
// 10. HAMILTONIAN PATH (BACKTRACKING)
// ========================================
// Concept: Path visiting every vertex exactly once

bool hamiltonianUtil(vector<vector<int>>& adj, int V, vector<int>& path, vector<bool>& visited, int pos) {
    if (pos == V) {
        return true;
    }
    
    for (int v = 0; v < V; v++) {
        if (!visited[v]) {
            bool isAdjacent = false;
            for (int neighbor : adj[path[pos - 1]]) {
                if (neighbor == v) {
                    isAdjacent = true;
                    break;
                }
            }
            
            if (isAdjacent) {
                visited[v] = true;
                path[pos] = v;
                
                if (hamiltonianUtil(adj, V, path, visited, pos + 1))
                    return true;
                
                visited[v] = false;
            }
        }
    }
    
    return false;
}

bool hasHamiltonianPath(vector<vector<int>>& adj, int V) {
    vector<int> path(V);
    vector<bool> visited(V, false);
    
    for (int start = 0; start < V; start++) {
        fill(visited.begin(), visited.end(), false);
        visited[start] = true;
        path[0] = start;
        
        if (hamiltonianUtil(adj, V, path, visited, 1))
            return true;
    }
    
    return false;
}

// ========================================
// 11. GRAPH COLORING (CHROMATIC NUMBER)
// ========================================
// Concept: Minimum colors to color graph

bool isSafe(vector<vector<int>>& adj, int v, vector<int>& color, int c) {
    for (int u : adj[v]) {
        if (color[u] == c) return false;
    }
    return true;
}

bool graphColoringUtil(vector<vector<int>>& adj, int V, int m, vector<int>& color, int v) {
    if (v == V) return true;
    
    for (int c = 1; c <= m; c++) {
        if (isSafe(adj, v, color, c)) {
            color[v] = c;
            
            if (graphColoringUtil(adj, V, m, color, v + 1))
                return true;
            
            color[v] = 0;
        }
    }
    
    return false;
}

bool graphColoring(vector<vector<int>>& adj, int V, int m) {
    vector<int> color(V, 0);
    return graphColoringUtil(adj, V, m, color, 0);
}

// ========================================
// 12. MAXIMUM FLOW (FORD-FULKERSON)
// ========================================
// Concept: Maximum flow from source to sink

bool bfsFlow(vector<vector<int>>& residual, int V, int s, int t, vector<int>& parent) {
    vector<bool> visited(V, false);
    queue<int> q;
    
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v = 0; v < V; v++) {
            if (!visited[v] && residual[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                
                if (v == t) return true;
            }
        }
    }
    
    return false;
}

int maxFlow(vector<vector<int>>& capacity, int V, int s, int t) {
    vector<vector<int>> residual = capacity;
    vector<int> parent(V);
    int maxFlow = 0;
    
    while (bfsFlow(residual, V, s, t, parent)) {
        int pathFlow = INT_MAX;
        
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residual[u][v]);
        }
        
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= pathFlow;
            residual[v][u] += pathFlow;
        }
        
        maxFlow += pathFlow;
    }
    
    return maxFlow;
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    cout << "=== GRAPH ADVANCED PROBLEMS ===" << endl;
    
    // Example usage - uncomment to test
    
    // Dijkstra example
    // vector<vector<pair<int,int>>> graph(5);
    // graph[0] = {{1, 10}, {4, 5}};
    // graph[1] = {{2, 1}, {4, 2}};
    // graph[2] = {{3, 4}};
    // graph[3] = {{0, 7}, {2, 6}};
    // graph[4] = {{1, 3}, {2, 9}, {3, 2}};
    
    // vector<int> dist = dijkstra(graph, 5, 0);
    // cout << "Shortest distances from 0: ";
    // for (int d : dist) cout << d << " ";
    // cout << endl;
    
    return 0;
}
