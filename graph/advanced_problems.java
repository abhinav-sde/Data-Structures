/**
 * Advanced Graph Problems in Java
 * Contains complex graph algorithms
 */

import java.util.*;

public class advanced_problems {
    
    // ========================================
    // 1. DIJKSTRA'S ALGORITHM
    // ========================================
    static class Node implements Comparable<Node> {
        int vertex, weight;
        public Node(int v, int w) { vertex = v; weight = w; }
        public int compareTo(Node other) { return Integer.compare(this.weight, other.weight); }
    }
    
    static int[] dijkstra(List<List<Node>> adj, int V, int src) {
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        PriorityQueue<Node> pq = new PriorityQueue<>();
        
        dist[src] = 0;
        pq.add(new Node(src, 0));
        
        while (!pq.isEmpty()) {
            Node node = pq.poll();
            int u = node.vertex;
            int d = node.weight;
            
            if (d > dist[u]) continue;
            
            for (Node neighbor : adj.get(u)) {
                int v = neighbor.vertex;
                int weight = neighbor.weight;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.add(new Node(v, dist[v]));
                }
            }
        }
        return dist;
    }
    
    // ========================================
    // 2. BELLMAN-FORD ALGORITHM
    // ========================================
    static class Edge {
        int u, v, weight;
        public Edge(int u, int v, int weight) { this.u = u; this.v = v; this.weight = weight; }
    }
    
    static boolean bellmanFord(List<Edge> edges, int V, int src, int[] dist) {
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[src] = 0;
        
        for (int i = 0; i < V - 1; i++) {
            for (Edge e : edges) {
                if (dist[e.u] != Integer.MAX_VALUE && dist[e.u] + e.weight < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.weight;
                }
            }
        }
        
        for (Edge e : edges) {
            if (dist[e.u] != Integer.MAX_VALUE && dist[e.u] + e.weight < dist[e.v]) {
                return false; // Negative cycle exists
            }
        }
        return true;
    }
    
    // ========================================
    // 3. FLOYD-WARSHALL ALGORITHM
    // ========================================
    static void floydWarshall(int[][] graph, int V) {
        int[][] dist = new int[V][V];
        for (int i = 0; i < V; i++) dist[i] = graph[i].clone();
        
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != Integer.MAX_VALUE && dist[k][j] != Integer.MAX_VALUE) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        
        System.out.println("Shortest distances between all pairs:");
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == Integer.MAX_VALUE)
                    System.out.print("INF ");
                else
                    System.out.print(dist[i][j] + " ");
            }
            System.out.println();
        }
    }
    
    // ========================================
    // 4. PRIM'S ALGORITHM (MST)
    // ========================================
    static int primMST(List<List<Node>> adj, int V) {
        int[] key = new int[V];
        Arrays.fill(key, Integer.MAX_VALUE);
        boolean[] inMST = new boolean[V];
        PriorityQueue<Node> pq = new PriorityQueue<>();
        
        key[0] = 0;
        pq.add(new Node(0, 0));
        
        int mstWeight = 0;
        
        while (!pq.isEmpty()) {
            Node node = pq.poll();
            int u = node.vertex;
            int weight = node.weight;
            
            if (inMST[u]) continue;
            
            inMST[u] = true;
            mstWeight += weight;
            
            for (Node neighbor : adj.get(u)) {
                int v = neighbor.vertex;
                int w = neighbor.weight;
                
                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    pq.add(new Node(v, w));
                }
            }
        }
        return mstWeight;
    }
    
    // ========================================
    // 5. KRUSKAL'S ALGORITHM (MST)
    // ========================================
    static class UnionFind {
        int[] parent, rank;
        
        public UnionFind(int n) {
            parent = new int[n];
            rank = new int[n];
            for (int i = 0; i < n; i++) parent[i] = i;
        }
        
        public int find(int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }
        
        public boolean unite(int x, int y) {
            int px = find(x);
            int py = find(y);
            if (px == py) return false;
            
            if (rank[px] < rank[py]) parent[px] = py;
            else if (rank[px] > rank[py]) parent[py] = px;
            else { parent[py] = px; rank[px]++; }
            return true;
        }
    }
    
    static int kruskalMST(List<Edge> edges, int V) {
        edges.sort(Comparator.comparingInt(e -> e.weight));
        UnionFind uf = new UnionFind(V);
        int mstWeight = 0, edgeCount = 0;
        
        for (Edge e : edges) {
            if (uf.unite(e.u, e.v)) {
                mstWeight += e.weight;
                edgeCount++;
                if (edgeCount == V - 1) break;
            }
        }
        return mstWeight;
    }
    
    // ========================================
    // 6. 0-1 BFS
    // ========================================
    static int[] bfs01(List<List<Node>> adj, int V, int src) {
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        Deque<Integer> dq = new LinkedList<>();
        
        dist[src] = 0;
        dq.addLast(src);
        
        while (!dq.isEmpty()) {
            int u = dq.pollFirst();
            
            for (Node neighbor : adj.get(u)) {
                int v = neighbor.vertex;
                int weight = neighbor.weight;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    if (weight == 0) dq.addFirst(v);
                    else dq.addLast(v);
                }
            }
        }
        return dist;
    }
    
    // ========================================
    // 7. A* ALGORITHM
    // ========================================
    static int heuristic(int u, int v) { return Math.abs(u - v); }
    
    static int[] astar(List<List<Node>> adj, int V, int src, int dest) {
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        int[] f = new int[V];
        Arrays.fill(f, Integer.MAX_VALUE);
        PriorityQueue<Node> pq = new PriorityQueue<>();
        
        dist[src] = 0;
        f[src] = heuristic(src, dest);
        pq.add(new Node(src, f[src]));
        
        while (!pq.isEmpty()) {
            Node node = pq.poll();
            int u = node.vertex;
            
            if (u == dest) break;
            
            for (Node neighbor : adj.get(u)) {
                int v = neighbor.vertex;
                int weight = neighbor.weight;
                int newDist = dist[u] + weight;
                
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    f[v] = dist[v] + heuristic(v, dest);
                    pq.add(new Node(v, f[v]));
                }
            }
        }
        return dist;
    }
    
    // ========================================
    // 8. TRAVELLING SALESMAN PROBLEM (DP)
    // ========================================
    static int tsp(int[][] dist, int n) {
        int[][] dp = new int[1 << n][n];
        for (int[] row : dp) Arrays.fill(row, Integer.MAX_VALUE);
        
        dp[1][0] = 0;
        
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int u = 0; u < n; u++) {
                if ((mask & (1 << u)) == 0) continue;
                if (dp[mask][u] == Integer.MAX_VALUE) continue;
                
                for (int v = 0; v < n; v++) {
                    if ((mask & (1 << v)) != 0) continue;
                    int newMask = mask | (1 << v);
                    dp[newMask][v] = Math.min(dp[newMask][v], dp[mask][u] + dist[u][v]);
                }
            }
        }
        
        int result = Integer.MAX_VALUE;
        int fullMask = (1 << n) - 1;
        
        for (int u = 1; u < n; u++) {
            if (dp[fullMask][u] != Integer.MAX_VALUE) {
                result = Math.min(result, dp[fullMask][u] + dist[u][0]);
            }
        }
        return result;
    }
    
    // ========================================
    // 9. EULERIAN PATH/CIRCUIT
    // ========================================
    static boolean hasEulerianPath(List<List<Integer>> adj, int V) {
        int oddCount = 0;
        for (int i = 0; i < V; i++) {
            if (adj.get(i).size() % 2 != 0) oddCount++;
        }
        return oddCount == 0 || oddCount == 2;
    }
    
    // ========================================
    // 10. HAMILTONIAN PATH (BACKTRACKING)
    // ========================================
    static boolean hamiltonianUtil(int[][] adj, int V, int[] path, boolean[] visited, int pos) {
        if (pos == V) return true;
        
        for (int v = 0; v < V; v++) {
            if (!visited[v] && adj[path[pos - 1]][v] == 1) {
                visited[v] = true;
                path[pos] = v;
                if (hamiltonianUtil(adj, V, path, visited, pos + 1)) return true;
                visited[v] = false;
            }
        }
        return false;
    }
    
    static boolean hasHamiltonianPath(int[][] adj, int V) {
        int[] path = new int[V];
        boolean[] visited = new boolean[V];
        
        for (int start = 0; start < V; start++) {
            Arrays.fill(visited, false);
            visited[start] = true;
            path[0] = start;
            if (hamiltonianUtil(adj, V, path, visited, 1)) return true;
        }
        return false;
    }
    
    // ========================================
    // 11. GRAPH COLORING (CHROMATIC NUMBER)
    // ========================================
    static boolean isSafe(List<List<Integer>> adj, int v, int[] color, int c) {
        for (int u : adj.get(v)) {
            if (color[u] == c) return false;
        }
        return true;
    }
    
    static boolean graphColoringUtil(List<List<Integer>> adj, int V, int m, int[] color, int v) {
        if (v == V) return true;
        
        for (int c = 1; c <= m; c++) {
            if (isSafe(adj, v, color, c)) {
                color[v] = c;
                if (graphColoringUtil(adj, V, m, color, v + 1)) return true;
                color[v] = 0;
            }
        }
        return false;
    }
    
    static boolean graphColoring(List<List<Integer>> adj, int V, int m) {
        int[] color = new int[V];
        return graphColoringUtil(adj, V, m, color, 0);
    }
    
    // ========================================
    // 12. MAXIMUM FLOW (FORD-FULKERSON)
    // ========================================
    static boolean bfsFlow(int[][] residual, int V, int s, int t, int[] parent) {
        boolean[] visited = new boolean[V];
        Queue<Integer> q = new LinkedList<>();
        
        q.add(s);
        visited[s] = true;
        parent[s] = -1;
        
        while (!q.isEmpty()) {
            int u = q.poll();
            for (int v = 0; v < V; v++) {
                if (!visited[v] && residual[u][v] > 0) {
                    q.add(v);
                    parent[v] = u;
                    visited[v] = true;
                    if (v == t) return true;
                }
            }
        }
        return false;
    }
    
    static int maxFlow(int[][] capacity, int V, int s, int t) {
        int[][] residual = new int[V][V];
        for(int i=0; i<V; i++) residual[i] = capacity[i].clone();
        
        int[] parent = new int[V];
        int maxFlow = 0;
        
        while (bfsFlow(residual, V, s, t, parent)) {
            int pathFlow = Integer.MAX_VALUE;
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                pathFlow = Math.min(pathFlow, residual[u][v]);
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
    public static void main(String[] args) {
        System.out.println("=== GRAPH ADVANCED PROBLEMS ===");
        
        // Example usage - uncomment to test
        
        // Dijkstra example
        // int V = 5;
        // List<List<Node>> graph = new ArrayList<>();
        // for(int i=0; i<V; i++) graph.add(new ArrayList<>());
        // graph.get(0).add(new Node(1, 10)); graph.get(0).add(new Node(4, 5));
        // // ... add edges
        
        // int[] dist = dijkstra(graph, V, 0);
        // System.out.print("Shortest distances from 0: ");
        // for (int d : dist) System.out.print(d + " ");
        // System.out.println();
    }
}
