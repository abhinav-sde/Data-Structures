# GRAPH ALGORITHMS - COMPLETE COMPARISON GUIDE
## Interview Preparation Reference

---

## 📋 TABLE OF CONTENTS
1. [Graph Basics](#graph-basics)
2. [Graph Representations](#graph-representations)
3. [Graph Traversals](#graph-traversals)
4. [Shortest Path Algorithms](#shortest-path-algorithms)
5. [Minimum Spanning Tree](#minimum-spanning-tree)
6. [Cycle Detection](#cycle-detection)
7. [Topological Sort](#topological-sort)
8. [Connectivity](#connectivity)
9. [Advanced Algorithms](#advanced-algorithms)
10. [Complete Comparison Table](#complete-comparison-table)
11. [Interview Questions](#interview-questions)
12. [Algorithm Selection Guide](#algorithm-selection-guide)

---

## 🎯 GRAPH BASICS

### What is a Graph?
A **graph** G = (V, E) consists of:
- **V**: Set of vertices (nodes)
- **E**: Set of edges (connections)

### Types of Graphs

#### **1. Directed vs Undirected**
- **Directed (Digraph)**: Edges have direction (u → v)
- **Undirected**: Edges are bidirectional (u ↔ v)

#### **2. Weighted vs Unweighted**
- **Weighted**: Edges have weights/costs
- **Unweighted**: All edges have equal weight (1)

#### **3. Cyclic vs Acyclic**
- **Cyclic**: Contains at least one cycle
- **Acyclic**: No cycles (DAG = Directed Acyclic Graph)

#### **4. Connected vs Disconnected**
- **Connected**: Path exists between any two vertices
- **Disconnected**: Some vertices unreachable

#### **5. Dense vs Sparse**
- **Dense**: |E| ≈ |V|² (many edges)
- **Sparse**: |E| ≈ |V| (few edges)

---

## 1️⃣ GRAPH REPRESENTATIONS

### Adjacency Matrix
```cpp
vector<vector<int>> adj(V, vector<int>(V, 0));
adj[u][v] = 1;  // or weight
```

**Pros**:
✅ O(1) edge lookup  
✅ Simple implementation  
✅ Good for dense graphs  

**Cons**:
❌ O(V²) space  
❌ Slow for sparse graphs  

**When to Use**:
- Dense graphs (|E| ≈ |V|²)
- Need fast edge lookup
- Floyd-Warshall algorithm

---

### Adjacency List
```cpp
vector<vector<int>> adj(V);
adj[u].push_back(v);
```

**Pros**:
✅ O(V + E) space  
✅ Fast iteration over neighbors  
✅ Good for sparse graphs  

**Cons**:
❌ O(degree) edge lookup  

**When to Use**:
- Sparse graphs (|E| ≈ |V|)
- Most graph algorithms
- **Default choice**

---

### Edge List
```cpp
vector<Edge> edges;
edges.push_back({u, v, weight});
```

**Pros**:
✅ O(E) space  
✅ Simple for some algorithms  

**Cons**:
❌ O(E) edge lookup  
❌ Slow neighbor iteration  

**When to Use**:
- Kruskal's MST
- Bellman-Ford
- Simple edge processing

---

## 2️⃣ GRAPH TRAVERSALS

### BFS (Breadth-First Search)
```cpp
queue<int> q;
q.push(start);
visited[start] = true;

while (!q.empty()) {
    int u = q.front();
    q.pop();
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            visited[v] = true;
            q.push(v);
        }
    }
}
```

**Time**: O(V + E)  
**Space**: O(V)  

**Use Cases**:
- Shortest path (unweighted)
- Level order traversal
- Connected components
- Bipartite check

---

### DFS (Depth-First Search)
```cpp
void dfs(int u, vector<bool>& visited) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, visited);
        }
    }
}
```

**Time**: O(V + E)  
**Space**: O(V)  

**Use Cases**:
- Cycle detection
- Topological sort
- Strongly connected components
- Path finding
- Backtracking

---

## 3️⃣ SHORTEST PATH ALGORITHMS

### Dijkstra's Algorithm
**Use**: Single source, non-negative weights  
**Time**: O((V + E) log V) with priority queue  
**Space**: O(V)  

```cpp
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
dist[src] = 0;
pq.push({0, src});

while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    
    for (auto [v, w] : adj[u]) {
        if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }
}
```

**Advantages**:
✅ Efficient for sparse graphs  
✅ Optimal for non-negative weights  

**Limitations**:
❌ Doesn't work with negative weights  

---

### Bellman-Ford Algorithm
**Use**: Single source, handles negative weights  
**Time**: O(VE)  
**Space**: O(V)  

**Advantages**:
✅ Handles negative weights  
✅ Detects negative cycles  

**Limitations**:
❌ Slower than Dijkstra  

**When to Use**:
- Negative edge weights
- Need to detect negative cycles

---

### Floyd-Warshall Algorithm
**Use**: All pairs shortest path  
**Time**: O(V³)  
**Space**: O(V²)  

```cpp
for (int k = 0; k < V; k++)
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
```

**When to Use**:
- Need all pairs distances
- Dense graphs
- Small graphs (V ≤ 400)

---

### BFS (Unweighted)
**Use**: Single source, unweighted  
**Time**: O(V + E)  
**Space**: O(V)  

**When to Use**:
- Unweighted graphs
- Shortest path in terms of edges
- Fastest option for unweighted

---

## 4️⃣ MINIMUM SPANNING TREE (MST)

### Prim's Algorithm
**Approach**: Greedy, grow tree from vertex  
**Time**: O((V + E) log V) with priority queue  
**Space**: O(V)  

```cpp
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
pq.push({0, 0});

while (!pq.empty()) {
    auto [w, u] = pq.top();
    pq.pop();
    
    if (inMST[u]) continue;
    inMST[u] = true;
    mstWeight += w;
    
    for (auto [v, weight] : adj[u]) {
        if (!inMST[v]) {
            pq.push({weight, v});
        }
    }
}
```

**When to Use**:
- Dense graphs
- Adjacency list representation
- Need MST edges incrementally

---

### Kruskal's Algorithm
**Approach**: Greedy, sort edges, use Union-Find  
**Time**: O(E log E)  
**Space**: O(V)  

```cpp
sort(edges.begin(), edges.end());

for (auto [u, v, w] : edges) {
    if (uf.find(u) != uf.find(v)) {
        uf.unite(u, v);
        mstWeight += w;
    }
}
```

**When to Use**:
- Sparse graphs
- Edge list representation
- Simple implementation

---

### Prim vs Kruskal

| Feature | Prim | Kruskal |
|---------|------|---------|
| Approach | Vertex-based | Edge-based |
| Time | O((V+E) log V) | O(E log E) |
| Best for | Dense graphs | Sparse graphs |
| Data Structure | Priority Queue | Union-Find |
| Implementation | More complex | Simpler |

---

## 5️⃣ CYCLE DETECTION

### Undirected Graph (DFS)
**Approach**: Track parent, check back edge  
**Time**: O(V + E)  

```cpp
bool hasCycle(int u, int parent) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (hasCycle(v, u)) return true;
        } else if (v != parent) {
            return true;  // Back edge
        }
    }
    return false;
}
```

---

### Directed Graph (DFS)
**Approach**: Track recursion stack  
**Time**: O(V + E)  

```cpp
bool hasCycle(int u) {
    visited[u] = true;
    recStack[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v] && hasCycle(v)) return true;
        else if (recStack[v]) return true;
    }
    
    recStack[u] = false;
    return false;
}
```

---

### Union-Find (Undirected)
**Approach**: Check if endpoints in same set  
**Time**: O(E α(V)) ≈ O(E)  

**When to Use**:
- Kruskal's algorithm
- Dynamic connectivity

---

## 6️⃣ TOPOLOGICAL SORT

### DFS-based
**Approach**: Post-order DFS, use stack  
**Time**: O(V + E)  

```cpp
void dfs(int u, stack<int>& st) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) dfs(v, st);
    }
    
    st.push(u);
}
```

**When to Use**:
- Simple implementation
- Need one valid ordering

---

### Kahn's Algorithm (BFS)
**Approach**: Remove vertices with in-degree 0  
**Time**: O(V + E)  

```cpp
queue<int> q;
for (int i = 0; i < V; i++) {
    if (inDegree[i] == 0) q.push(i);
}

while (!q.empty()) {
    int u = q.front();
    q.pop();
    result.push_back(u);
    
    for (int v : adj[u]) {
        if (--inDegree[v] == 0) q.push(v);
    }
}
```

**When to Use**:
- Detect cycles (if result.size() != V)
- Need in-degree information

---

## 7️⃣ CONNECTIVITY

### Connected Components (Undirected)
**Approach**: DFS/BFS from each unvisited vertex  
**Time**: O(V + E)  

---

### Strongly Connected Components (Directed)

#### Kosaraju's Algorithm
**Approach**: DFS twice (original + transpose)  
**Time**: O(V + E)  

**Steps**:
1. DFS on original graph, fill stack
2. Create transpose graph
3. DFS on transpose in stack order

---

#### Tarjan's Algorithm
**Approach**: Single DFS with low-link values  
**Time**: O(V + E)  

**Advantage**: Single pass  

---

### Bridges (Cut Edges)
**Approach**: Tarjan's algorithm  
**Time**: O(V + E)  

**Use**: Find critical edges  

---

### Articulation Points (Cut Vertices)
**Approach**: Tarjan's algorithm  
**Time**: O(V + E)  

**Use**: Find critical vertices  

---

## 8️⃣ ADVANCED ALGORITHMS

### A* Search
**Use**: Heuristic-based shortest path  
**Time**: Depends on heuristic  

**When to Use**:
- Game pathfinding
- Have good heuristic
- Need optimal path fast

---

### Travelling Salesman Problem (TSP)
**Approach**: Dynamic programming  
**Time**: O(n² × 2ⁿ)  

**Use**: Find shortest Hamiltonian cycle  

---

### Maximum Flow
**Algorithms**: Ford-Fulkerson, Edmonds-Karp  
**Time**: O(VE²) for Edmonds-Karp  

**Use**: Network flow problems  

---

### Graph Coloring
**Approach**: Backtracking  
**Time**: Exponential  

**Use**: Scheduling, register allocation  

---

## 📊 COMPLETE COMPARISON TABLE

| Algorithm | Problem | Time | Space | Graph Type |
|-----------|---------|------|-------|------------|
| **BFS** | Shortest path | O(V+E) | O(V) | Unweighted |
| **DFS** | Traversal | O(V+E) | O(V) | Any |
| **Dijkstra** | Shortest path | O((V+E)logV) | O(V) | Non-negative |
| **Bellman-Ford** | Shortest path | O(VE) | O(V) | Any weights |
| **Floyd-Warshall** | All pairs | O(V³) | O(V²) | Any weights |
| **Prim** | MST | O((V+E)logV) | O(V) | Undirected |
| **Kruskal** | MST | O(ElogE) | O(V) | Undirected |
| **Topological Sort** | Ordering | O(V+E) | O(V) | DAG |
| **Kosaraju** | SCC | O(V+E) | O(V) | Directed |
| **Tarjan** | SCC/Bridge | O(V+E) | O(V) | Any |

---

## 💡 INTERVIEW QUESTIONS & ANSWERS

### Q1: BFS vs DFS?
**Answer**:
| Feature | BFS | DFS |
|---------|-----|-----|
| Data Structure | Queue | Stack/Recursion |
| Path | Shortest | Any |
| Space | O(V) | O(h) height |
| Use | Level order | Backtracking |

### Q2: When to use Dijkstra vs Bellman-Ford?
**Answer**:
- **Dijkstra**: Non-negative weights, faster O((V+E) log V)
- **Bellman-Ford**: Negative weights, detects cycles O(VE)

### Q3: Prim vs Kruskal for MST?
**Answer**:
- **Prim**: Dense graphs, O((V+E) log V)
- **Kruskal**: Sparse graphs, O(E log E)

### Q4: How to detect cycle?
**Answer**:
- **Undirected**: DFS with parent or Union-Find
- **Directed**: DFS with recursion stack

### Q5: What is topological sort?
**Answer**:
Linear ordering of vertices in DAG where u comes before v for every edge u→v.

**Methods**:
1. DFS + Stack
2. Kahn's algorithm (BFS)

### Q6: Difference between bridge and articulation point?
**Answer**:
- **Bridge**: Edge whose removal disconnects graph
- **Articulation Point**: Vertex whose removal disconnects graph

### Q7: What is SCC?
**Answer**:
**Strongly Connected Component**: Maximal subgraph where every vertex is reachable from every other vertex.

**Algorithms**: Kosaraju, Tarjan

### Q8: When to use adjacency matrix vs list?
**Answer**:
- **Matrix**: Dense graphs, O(1) edge lookup, O(V²) space
- **List**: Sparse graphs, O(V+E) space, **default choice**

### Q9: What is bipartite graph?
**Answer**:
Graph whose vertices can be divided into two sets where no two vertices in same set are adjacent.

**Check**: 2-coloring using BFS/DFS

### Q10: What is DAG?
**Answer**:
**Directed Acyclic Graph**: Directed graph with no cycles.

**Uses**: Topological sort, dependency resolution

---

## 🎯 ALGORITHM SELECTION GUIDE

### Shortest Path
```
Single source, unweighted → BFS
Single source, non-negative → Dijkstra
Single source, any weights → Bellman-Ford
All pairs → Floyd-Warshall
```

### MST
```
Dense graph → Prim
Sparse graph → Kruskal
```

### Cycle Detection
```
Undirected → DFS with parent
Directed → DFS with recursion stack
```

### Connectivity
```
Connected components → DFS/BFS
SCC → Kosaraju/Tarjan
Bridges → Tarjan
Articulation points → Tarjan
```

### Traversal
```
Level order → BFS
Backtracking → DFS
Shortest path → BFS (unweighted)
```

---

## ✅ SUMMARY

### Must-Know Algorithms
1. **BFS** - Shortest path (unweighted)
2. **DFS** - Traversal, cycle detection
3. **Dijkstra** - Shortest path (weighted)
4. **Topological Sort** - DAG ordering
5. **Union-Find** - Disjoint sets
6. **MST** - Prim or Kruskal

### Common Patterns
- **Shortest Path**: BFS, Dijkstra, Bellman-Ford
- **Cycle**: DFS with tracking
- **Connectivity**: DFS/BFS components
- **Ordering**: Topological sort
- **Optimization**: MST, Max Flow

---

*Master graphs for interview success! 🚀*
