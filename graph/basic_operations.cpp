#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
using namespace std;

// ========================================
// GRAPH REPRESENTATIONS
// ========================================

// ========================================
// 1. ADJACENCY MATRIX
// ========================================
// Space: O(V^2)
// Edge lookup: O(1)
// Add edge: O(1)
// Good for: Dense graphs

class GraphMatrix {
private:
    int V;  // Number of vertices
    vector<vector<int>> adj;  // Adjacency matrix
    
public:
    GraphMatrix(int vertices) {
        V = vertices;
        adj.resize(V, vector<int>(V, 0));
    }
    
    // Add edge (undirected)
    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;  // For undirected graph
    }
    
    // Add directed edge
    void addDirectedEdge(int u, int v) {
        adj[u][v] = 1;
    }
    
    // Add weighted edge
    void addWeightedEdge(int u, int v, int weight) {
        adj[u][v] = weight;
        adj[v][u] = weight;
    }
    
    // Check if edge exists
    bool hasEdge(int u, int v) {
        return adj[u][v] != 0;
    }
    
    // Display matrix
    void display() {
        cout << "Adjacency Matrix:" << endl;
        cout << "   ";
        for (int i = 0; i < V; i++) cout << i << " ";
        cout << endl;
        
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int j = 0; j < V; j++) {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// ========================================
// 2. ADJACENCY LIST
// ========================================
// Space: O(V + E)
// Edge lookup: O(degree)
// Add edge: O(1)
// Good for: Sparse graphs

class GraphList {
private:
    int V;
    vector<list<int>> adj;  // Adjacency list
    
public:
    GraphList(int vertices) {
        V = vertices;
        adj.resize(V);
    }
    
    // Add edge (undirected)
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Add directed edge
    void addDirectedEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    // Display list
    void display() {
        cout << "Adjacency List:" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
    
    // Get adjacency list (for algorithms)
    vector<list<int>>& getAdj() {
        return adj;
    }
    
    int getV() {
        return V;
    }
};

// ========================================
// 3. EDGE LIST
// ========================================
// Space: O(E)
// Good for: Kruskal's algorithm

struct Edge {
    int u, v, weight;
    
    Edge(int _u, int _v, int _w) : u(_u), v(_v), weight(_w) {}
};

class GraphEdgeList {
private:
    int V;
    vector<Edge> edges;
    
public:
    GraphEdgeList(int vertices) {
        V = vertices;
    }
    
    void addEdge(int u, int v, int weight = 1) {
        edges.push_back(Edge(u, v, weight));
    }
    
    void display() {
        cout << "Edge List:" << endl;
        for (auto& e : edges) {
            cout << e.u << " - " << e.v << " (weight: " << e.weight << ")" << endl;
        }
    }
    
    vector<Edge>& getEdges() {
        return edges;
    }
};

// ========================================
// 4. WEIGHTED GRAPH (ADJACENCY LIST)
// ========================================

class WeightedGraph {
private:
    int V;
    vector<vector<pair<int, int>>> adj;  // {neighbor, weight}
    
public:
    WeightedGraph(int vertices) {
        V = vertices;
        adj.resize(V);
    }
    
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }
    
    void addDirectedEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
    }
    
    void display() {
        cout << "Weighted Adjacency List:" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (auto& [neighbor, weight] : adj[i]) {
                cout << "(" << neighbor << "," << weight << ") ";
            }
            cout << endl;
        }
    }
    
    vector<vector<pair<int, int>>>& getAdj() {
        return adj;
    }
    
    int getV() {
        return V;
    }
};

// ========================================
// GRAPH TRAVERSALS
// ========================================

// BFS - Breadth First Search
void BFS(GraphList& g, int start) {
    int V = g.getV();
    vector<bool> visited(V, false);
    queue<int> q;
    
    visited[start] = true;
    q.push(start);
    
    cout << "BFS from " << start << ": ";
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";
        
        for (int v : g.getAdj()[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << endl;
}

// DFS - Depth First Search (Recursive)
void DFSUtil(vector<list<int>>& adj, int u, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            DFSUtil(adj, v, visited);
        }
    }
}

void DFS(GraphList& g, int start) {
    int V = g.getV();
    vector<bool> visited(V, false);
    
    cout << "DFS from " << start << ": ";
    DFSUtil(g.getAdj(), start, visited);
    cout << endl;
}

// DFS Iterative (using stack)
void DFSIterative(GraphList& g, int start) {
    int V = g.getV();
    vector<bool> visited(V, false);
    stack<int> st;
    
    st.push(start);
    
    cout << "DFS Iterative from " << start << ": ";
    
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        
        if (!visited[u]) {
            visited[u] = true;
            cout << u << " ";
            
            // Push neighbors in reverse order for same order as recursive
            for (auto it = g.getAdj()[u].rbegin(); it != g.getAdj()[u].rend(); ++it) {
                if (!visited[*it]) {
                    st.push(*it);
                }
            }
        }
    }
    cout << endl;
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    cout << "=== GRAPH BASIC OPERATIONS ===" << endl;
    
    // ========================================
    // 1. ADJACENCY MATRIX
    // ========================================
    
    cout << "\n1. ADJACENCY MATRIX" << endl;
    cout << "-------------------" << endl;
    
    GraphMatrix gm(5);
    gm.addEdge(0, 1);
    gm.addEdge(0, 4);
    gm.addEdge(1, 2);
    gm.addEdge(1, 3);
    gm.addEdge(1, 4);
    gm.addEdge(2, 3);
    gm.addEdge(3, 4);
    
    gm.display();
    
    cout << "\nEdge (0,1) exists: " << (gm.hasEdge(0, 1) ? "Yes" : "No") << endl;
    cout << "Edge (0,3) exists: " << (gm.hasEdge(0, 3) ? "Yes" : "No") << endl;
    
    // ========================================
    // 2. ADJACENCY LIST
    // ========================================
    
    cout << "\n2. ADJACENCY LIST" << endl;
    cout << "-----------------" << endl;
    
    GraphList gl(5);
    gl.addEdge(0, 1);
    gl.addEdge(0, 4);
    gl.addEdge(1, 2);
    gl.addEdge(1, 3);
    gl.addEdge(1, 4);
    gl.addEdge(2, 3);
    gl.addEdge(3, 4);
    
    gl.display();
    
    // ========================================
    // 3. EDGE LIST
    // ========================================
    
    cout << "\n3. EDGE LIST" << endl;
    cout << "------------" << endl;
    
    GraphEdgeList ge(5);
    ge.addEdge(0, 1, 10);
    ge.addEdge(0, 4, 20);
    ge.addEdge(1, 2, 30);
    ge.addEdge(1, 3, 40);
    ge.addEdge(2, 3, 50);
    
    ge.display();
    
    // ========================================
    // 4. WEIGHTED GRAPH
    // ========================================
    
    cout << "\n4. WEIGHTED GRAPH" << endl;
    cout << "-----------------" << endl;
    
    WeightedGraph wg(5);
    wg.addEdge(0, 1, 10);
    wg.addEdge(0, 4, 20);
    wg.addEdge(1, 2, 30);
    wg.addEdge(1, 3, 40);
    wg.addEdge(2, 3, 50);
    wg.addEdge(3, 4, 60);
    
    wg.display();
    
    // ========================================
    // 5. GRAPH TRAVERSALS
    // ========================================
    
    cout << "\n5. GRAPH TRAVERSALS" << endl;
    cout << "-------------------" << endl;
    
    BFS(gl, 0);
    DFS(gl, 0);
    DFSIterative(gl, 0);
    
    // ========================================
    // 6. COMPARISON
    // ========================================
    
    cout << "\n6. REPRESENTATION COMPARISON" << endl;
    cout << "----------------------------" << endl;
    cout << "Representation | Space    | Add Edge | Check Edge | Best For" << endl;
    cout << "---------------|----------|----------|------------|----------" << endl;
    cout << "Adj Matrix     | O(V^2)   | O(1)     | O(1)       | Dense" << endl;
    cout << "Adj List       | O(V+E)   | O(1)     | O(degree)  | Sparse" << endl;
    cout << "Edge List      | O(E)     | O(1)     | O(E)       | Kruskal" << endl;
    
    cout << "\n7. TRAVERSAL COMPARISON" << endl;
    cout << "-----------------------" << endl;
    cout << "Algorithm | Time     | Space   | Use Case" << endl;
    cout << "----------|----------|---------|----------" << endl;
    cout << "BFS       | O(V+E)   | O(V)    | Shortest path, Level order" << endl;
    cout << "DFS       | O(V+E)   | O(V)    | Cycle detection, Topological sort" << endl;
    
    return 0;
}
