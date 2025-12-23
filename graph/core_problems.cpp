#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

// ========================================
// GRAPH CORE PROBLEMS
// ========================================

// ========================================
// 1. DETECT CYCLE IN UNDIRECTED GRAPH
// ========================================
// Concept: DFS with parent tracking
bool isCyclicUtil(vector<vector<int>>& adj, int u, vector<bool>& visited, int parent) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (isCyclicUtil(adj, v, visited, u))
                return true;
        } else if (v != parent) {
            return true;  // Back edge found
        }
    }
    
    return false;
}

bool hasCycleUndirected(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(adj, i, visited, -1))
                return true;
        }
    }
    
    return false;
}

// ========================================
// 2. DETECT CYCLE IN DIRECTED GRAPH
// ========================================
// Concept: DFS with recursion stack
bool isCyclicDirectedUtil(vector<vector<int>>& adj, int u, vector<bool>& visited, vector<bool>& recStack) {
    visited[u] = true;
    recStack[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (isCyclicDirectedUtil(adj, v, visited, recStack))
                return true;
        } else if (recStack[v]) {
            return true;  // Back edge in recursion stack
        }
    }
    
    recStack[u] = false;
    return false;
}

bool hasCycleDirected(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (isCyclicDirectedUtil(adj, i, visited, recStack))
                return true;
        }
    }
    
    return false;
}

// ========================================
// 3. TOPOLOGICAL SORT (DFS)
// ========================================
// Concept: DFS with stack (post-order)
void topologicalSortUtil(vector<vector<int>>& adj, int u, vector<bool>& visited, stack<int>& st) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            topologicalSortUtil(adj, v, visited, st);
        }
    }
    
    st.push(u);
}

vector<int> topologicalSort(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    stack<int> st;
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(adj, i, visited, st);
        }
    }
    
    vector<int> result;
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    
    return result;
}

// ========================================
// 4. TOPOLOGICAL SORT (KAHN'S ALGORITHM - BFS)
// ========================================
// Concept: Remove vertices with in-degree 0
vector<int> topologicalSortKahn(vector<vector<int>>& adj, int V) {
    vector<int> inDegree(V, 0);
    
    // Calculate in-degree
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            inDegree[v]++;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> result;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);
        
        for (int v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    // If result size != V, graph has cycle
    return result;
}

// ========================================
// 5. SHORTEST PATH IN UNWEIGHTED GRAPH (BFS)
// ========================================
vector<int> shortestPathBFS(vector<vector<int>>& adj, int V, int src) {
    vector<int> dist(V, INT_MAX);
    queue<int> q;
    
    dist[src] = 0;
    q.push(src);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    return dist;
}

// ========================================
// 6. CONNECTED COMPONENTS
// ========================================
void dfsComponent(vector<vector<int>>& adj, int u, vector<bool>& visited) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfsComponent(adj, v, visited);
        }
    }
}

int countConnectedComponents(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    int count = 0;
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfsComponent(adj, i, visited);
            count++;
        }
    }
    
    return count;
}

// ========================================
// 7. BIPARTITE GRAPH CHECK
// ========================================
// Concept: 2-coloring using BFS
bool isBipartite(vector<vector<int>>& adj, int V) {
    vector<int> color(V, -1);
    
    for (int start = 0; start < V; start++) {
        if (color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

// ========================================
// 8. BRIDGE DETECTION (TARJAN'S ALGORITHM)
// ========================================
void bridgeUtil(vector<vector<int>>& adj, int u, vector<bool>& visited,
                vector<int>& disc, vector<int>& low, vector<int>& parent,
                vector<pair<int,int>>& bridges, int& time) {
    visited[u] = true;
    disc[u] = low[u] = ++time;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            bridgeUtil(adj, v, visited, disc, low, parent, bridges, time);
            
            low[u] = min(low[u], low[v]);
            
            if (low[v] > disc[u]) {
                bridges.push_back({u, v});
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

vector<pair<int,int>> findBridges(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    vector<int> disc(V, -1);
    vector<int> low(V, -1);
    vector<int> parent(V, -1);
    vector<pair<int,int>> bridges;
    int time = 0;
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            bridgeUtil(adj, i, visited, disc, low, parent, bridges, time);
        }
    }
    
    return bridges;
}

// ========================================
// 9. ARTICULATION POINTS
// ========================================
void articulationUtil(vector<vector<int>>& adj, int u, vector<bool>& visited,
                      vector<int>& disc, vector<int>& low, vector<int>& parent,
                      vector<bool>& ap, int& time) {
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            children++;
            parent[v] = u;
            articulationUtil(adj, v, visited, disc, low, parent, ap, time);
            
            low[u] = min(low[u], low[v]);
            
            if (parent[u] == -1 && children > 1) {
                ap[u] = true;
            }
            
            if (parent[u] != -1 && low[v] >= disc[u]) {
                ap[u] = true;
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

vector<int> findArticulationPoints(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    vector<int> disc(V, -1);
    vector<int> low(V, -1);
    vector<int> parent(V, -1);
    vector<bool> ap(V, false);
    int time = 0;
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            articulationUtil(adj, i, visited, disc, low, parent, ap, time);
        }
    }
    
    vector<int> result;
    for (int i = 0; i < V; i++) {
        if (ap[i]) {
            result.push_back(i);
        }
    }
    
    return result;
}

// ========================================
// 10. STRONGLY CONNECTED COMPONENTS (KOSARAJU)
// ========================================
void fillOrder(vector<vector<int>>& adj, int u, vector<bool>& visited, stack<int>& st) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            fillOrder(adj, v, visited, st);
        }
    }
    
    st.push(u);
}

void dfsTranspose(vector<vector<int>>& transpose, int u, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";
    
    for (int v : transpose[u]) {
        if (!visited[v]) {
            dfsTranspose(transpose, v, visited);
        }
    }
}

int countSCC(vector<vector<int>>& adj, int V) {
    stack<int> st;
    vector<bool> visited(V, false);
    
    // Fill vertices in stack according to finish times
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            fillOrder(adj, i, visited, st);
        }
    }
    
    // Create transpose graph
    vector<vector<int>> transpose(V);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            transpose[v].push_back(u);
        }
    }
    
    // Do DFS on transpose
    fill(visited.begin(), visited.end(), false);
    int count = 0;
    
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        
        if (!visited[u]) {
            cout << "SCC " << (count + 1) << ": ";
            dfsTranspose(transpose, u, visited);
            cout << endl;
            count++;
        }
    }
    
    return count;
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    cout << "=== GRAPH CORE PROBLEMS ===" << endl;
    
    // Example usage - uncomment to test
    
    // Undirected graph for cycle detection
    // vector<vector<int>> undirected(5);
    // undirected[0] = {1, 4};
    // undirected[1] = {0, 2, 3, 4};
    // undirected[2] = {1, 3};
    // undirected[3] = {1, 2, 4};
    // undirected[4] = {0, 1, 3};
    
    // cout << "Has cycle (undirected): " << (hasCycleUndirected(undirected, 5) ? "Yes" : "No") << endl;
    
    // Directed graph for topological sort
    // vector<vector<int>> directed(6);
    // directed[5] = {2, 0};
    // directed[4] = {0, 1};
    // directed[2] = {3};
    // directed[3] = {1};
    
    // vector<int> topo = topologicalSort(directed, 6);
    // cout << "Topological Sort: ";
    // for (int v : topo) cout << v << " ";
    // cout << endl;
    
    return 0;
}
