/**
 * Core Graph Problems in Java
 * Contains standard graph algorithms
 */

import java.util.*;

public class core_problems {
    
    // ========================================
    // 1. DETECT CYCLE IN UNDIRECTED GRAPH
    // ========================================
    static boolean isCyclicUtil(List<List<Integer>> adj, int u, boolean[] visited, int parent) {
        visited[u] = true;
        
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                if (isCyclicUtil(adj, v, visited, u))
                    return true;
            } else if (v != parent) {
                return true; // Back edge found
            }
        }
        return false;
    }
    
    static boolean hasCycleUndirected(List<List<Integer>> adj, int V) {
        boolean[] visited = new boolean[V];
        
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
    static boolean isCyclicDirectedUtil(List<List<Integer>> adj, int u, boolean[] visited, boolean[] recStack) {
        visited[u] = true;
        recStack[u] = true;
        
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                if (isCyclicDirectedUtil(adj, v, visited, recStack))
                    return true;
            } else if (recStack[v]) {
                return true; // Back edge in recursion stack
            }
        }
        
        recStack[u] = false;
        return false;
    }
    
    static boolean hasCycleDirected(List<List<Integer>> adj, int V) {
        boolean[] visited = new boolean[V];
        boolean[] recStack = new boolean[V];
        
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
    static void topologicalSortUtil(List<List<Integer>> adj, int u, boolean[] visited, Stack<Integer> st) {
        visited[u] = true;
        
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                topologicalSortUtil(adj, v, visited, st);
            }
        }
        
        st.push(u);
    }
    
    static List<Integer> topologicalSort(List<List<Integer>> adj, int V) {
        boolean[] visited = new boolean[V];
        Stack<Integer> st = new Stack<>();
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(adj, i, visited, st);
            }
        }
        
        List<Integer> result = new ArrayList<>();
        while (!st.isEmpty()) {
            result.add(st.pop());
        }
        return result;
    }
    
    // ========================================
    // 4. TOPOLOGICAL SORT (KAHN'S ALGORITHM - BFS)
    // ========================================
    static List<Integer> topologicalSortKahn(List<List<Integer>> adj, int V) {
        int[] inDegree = new int[V];
        
        for (int u = 0; u < V; u++) {
            for (int v : adj.get(u)) {
                inDegree[v]++;
            }
        }
        
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                q.add(i);
            }
        }
        
        List<Integer> result = new ArrayList<>();
        while (!q.isEmpty()) {
            int u = q.poll();
            result.add(u);
            
            for (int v : adj.get(u)) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.add(v);
                }
            }
        }
        
        return result;
    }
    
    // ========================================
    // 5. SHORTEST PATH IN UNWEIGHTED GRAPH (BFS)
    // ========================================
    static int[] shortestPathBFS(List<List<Integer>> adj, int V, int src) {
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        Queue<Integer> q = new LinkedList<>();
        
        dist[src] = 0;
        q.add(src);
        
        while (!q.isEmpty()) {
            int u = q.poll();
            
            for (int v : adj.get(u)) {
                if (dist[v] == Integer.MAX_VALUE) {
                    dist[v] = dist[u] + 1;
                    q.add(v);
                }
            }
        }
        return dist;
    }
    
    // ========================================
    // 6. CONNECTED COMPONENTS
    // ========================================
    static void dfsComponent(List<List<Integer>> adj, int u, boolean[] visited) {
        visited[u] = true;
        
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                dfsComponent(adj, v, visited);
            }
        }
    }
    
    static int countConnectedComponents(List<List<Integer>> adj, int V) {
        boolean[] visited = new boolean[V];
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
    static boolean isBipartite(List<List<Integer>> adj, int V) {
        int[] color = new int[V];
        Arrays.fill(color, -1);
        
        for (int start = 0; start < V; start++) {
            if (color[start] == -1) {
                Queue<Integer> q = new LinkedList<>();
                q.add(start);
                color[start] = 0;
                
                while (!q.isEmpty()) {
                    int u = q.poll();
                    
                    for (int v : adj.get(u)) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            q.add(v);
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
    static int time = 0;
    
    static void bridgeUtil(List<List<Integer>> adj, int u, boolean[] visited,
                          int[] disc, int[] low, int[] parent,
                          List<int[]> bridges) {
        visited[u] = true;
        disc[u] = low[u] = ++time;
        
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                parent[v] = u;
                bridgeUtil(adj, v, visited, disc, low, parent, bridges);
                
                low[u] = Math.min(low[u], low[v]);
                
                if (low[v] > disc[u]) {
                    bridges.add(new int[]{u, v});
                }
            } else if (v != parent[u]) {
                low[u] = Math.min(low[u], disc[v]);
            }
        }
    }
    
    static List<int[]> findBridges(List<List<Integer>> adj, int V) {
        boolean[] visited = new boolean[V];
        int[] disc = new int[V];
        int[] low = new int[V];
        int[] parent = new int[V];
        Arrays.fill(parent, -1);
        List<int[]> bridges = new ArrayList<>();
        time = 0;
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                bridgeUtil(adj, i, visited, disc, low, parent, bridges);
            }
        }
        return bridges;
    }
    
    // ========================================
    // 9. ARTICULATION POINTS
    // ========================================
    static void articulationUtil(List<List<Integer>> adj, int u, boolean[] visited,
                                int[] disc, int[] low, int[] parent,
                                boolean[] ap) {
        int children = 0;
        visited[u] = true;
        disc[u] = low[u] = ++time;
        
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                articulationUtil(adj, v, visited, disc, low, parent, ap);
                
                low[u] = Math.min(low[u], low[v]);
                
                if (parent[u] == -1 && children > 1) {
                    ap[u] = true;
                }
                
                if (parent[u] != -1 && low[v] >= disc[u]) {
                    ap[u] = true;
                }
            } else if (v != parent[u]) {
                low[u] = Math.min(low[u], disc[v]);
            }
        }
    }
    
    static List<Integer> findArticulationPoints(List<List<Integer>> adj, int V) {
        boolean[] visited = new boolean[V];
        int[] disc = new int[V];
        int[] low = new int[V];
        int[] parent = new int[V];
        Arrays.fill(parent, -1);
        boolean[] ap = new boolean[V];
        time = 0;
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                articulationUtil(adj, i, visited, disc, low, parent, ap);
            }
        }
        
        List<Integer> result = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            if (ap[i]) {
                result.add(i);
            }
        }
        return result;
    }
    
    // ========================================
    // 10. STRONGLY CONNECTED COMPONENTS (KOSARAJU)
    // ========================================
    static void fillOrder(List<List<Integer>> adj, int u, boolean[] visited, Stack<Integer> st) {
        visited[u] = true;
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                fillOrder(adj, v, visited, st);
            }
        }
        st.push(u);
    }
    
    static void dfsTranspose(List<List<Integer>> transpose, int u, boolean[] visited) {
        visited[u] = true;
        System.out.print(u + " ");
        for (int v : transpose.get(u)) {
            if (!visited[v]) {
                dfsTranspose(transpose, v, visited);
            }
        }
    }
    
    static int countSCC(List<List<Integer>> adj, int V) {
        Stack<Integer> st = new Stack<>();
        boolean[] visited = new boolean[V];
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                fillOrder(adj, i, visited, st);
            }
        }
        
        List<List<Integer>> transpose = new ArrayList<>(V);
        for (int i = 0; i < V; i++) transpose.add(new ArrayList<>());
        
        for (int u = 0; u < V; u++) {
            for (int v : adj.get(u)) {
                transpose.get(v).add(u);
            }
        }
        
        Arrays.fill(visited, false);
        int count = 0;
        
        while (!st.isEmpty()) {
            int u = st.pop();
            
            if (!visited[u]) {
                System.out.print("SCC " + (count + 1) + ": ");
                dfsTranspose(transpose, u, visited);
                System.out.println();
                count++;
            }
        }
        return count;
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== GRAPH CORE PROBLEMS ===");
        
        // Example usage - uncomment to test
        
        // Undirected graph for cycle detection
        // int V = 5;
        // List<List<Integer>> undirected = new ArrayList<>(V);
        // for(int i=0; i<V; i++) undirected.add(new ArrayList<>());
        // undirected.get(0).add(1); undirected.get(0).add(4);
        // undirected.get(1).add(0); undirected.get(1).add(2); undirected.get(1).add(3); undirected.get(1).add(4);
        // // ... add edges symmetrically
        
        // System.out.println("Has cycle (undirected): " + (hasCycleUndirected(undirected, V) ? "Yes" : "No"));
    }
}
