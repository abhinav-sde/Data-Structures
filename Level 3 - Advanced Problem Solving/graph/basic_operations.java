/**
 * Basic Graph Operations in Java
 * Contains graph representations and basic traversals
 */

import java.util.*;

public class basic_operations {
    
    // ========================================
    // 1. ADJACENCY MATRIX
    // ========================================
    static class GraphMatrix {
        private int V;
        private int[][] adj;
        
        public GraphMatrix(int vertices) {
            V = vertices;
            adj = new int[V][V];
        }
        
        // Add edge (undirected)
        public void addEdge(int u, int v) {
            adj[u][v] = 1;
            adj[v][u] = 1;
        }
        
        // Add directed edge
        public void addDirectedEdge(int u, int v) {
            adj[u][v] = 1;
        }
        
        // Check if edge exists
        public boolean hasEdge(int u, int v) {
            return adj[u][v] != 0;
        }
        
        // Display matrix
        public void display() {
            System.out.println("Adjacency Matrix:");
            System.out.print("   ");
            for (int i = 0; i < V; i++) System.out.print(i + " ");
            System.out.println();
            
            for (int i = 0; i < V; i++) {
                System.out.print(i + ": ");
                for (int j = 0; j < V; j++) {
                    System.out.print(adj[i][j] + " ");
                }
                System.out.println();
            }
        }
    }
    
    // ========================================
    // 2. ADJACENCY LIST
    // ========================================
    static class GraphList {
        private int V;
        private List<List<Integer>> adj;
        
        public GraphList(int vertices) {
            V = vertices;
            adj = new ArrayList<>(V);
            for (int i = 0; i < V; i++) {
                adj.add(new LinkedList<>());
            }
        }
        
        // Add edge (undirected)
        public void addEdge(int u, int v) {
            adj.get(u).add(v);
            adj.get(v).add(u);
        }
        
        // Add directed edge
        public void addDirectedEdge(int u, int v) {
            adj.get(u).add(v);
        }
        
        // Display list
        public void display() {
            System.out.println("Adjacency List:");
            for (int i = 0; i < V; i++) {
                System.out.print(i + ": ");
                for (int neighbor : adj.get(i)) {
                    System.out.print(neighbor + " ");
                }
                System.out.println();
            }
        }
        
        public List<List<Integer>> getAdj() {
            return adj;
        }
        
        public int getV() {
            return V;
        }
    }
    
    // ========================================
    // 3. EDGE LIST
    // ========================================
    static class Edge {
        int u, v, weight;
        public Edge(int u, int v, int weight) {
            this.u = u;
            this.v = v;
            this.weight = weight;
        }
    }
    
    static class GraphEdgeList {
        private int V;
        private List<Edge> edges;
        
        public GraphEdgeList(int vertices) {
            V = vertices;
            edges = new ArrayList<>();
        }
        
        public void addEdge(int u, int v, int weight) {
            edges.add(new Edge(u, v, weight));
        }
        
        public void display() {
            System.out.println("Edge List:");
            for (Edge e : edges) {
                System.out.println(e.u + " - " + e.v + " (weight: " + e.weight + ")");
            }
        }
    }
    
    // ========================================
    // 4. WEIGHTED GRAPH (ADJACENCY LIST)
    // ========================================
    static class Node {
        int vertex, weight;
        public Node(int v, int w) { vertex = v; weight = w; }
    }
    
    static class WeightedGraph {
        private int V;
        private List<List<Node>> adj;
        
        public WeightedGraph(int vertices) {
            V = vertices;
            adj = new ArrayList<>(V);
            for (int i = 0; i < V; i++) {
                adj.add(new LinkedList<>());
            }
        }
        
        public void addEdge(int u, int v, int weight) {
            adj.get(u).add(new Node(v, weight));
            adj.get(v).add(new Node(u, weight));
        }
        
        public void display() {
            System.out.println("Weighted Adjacency List:");
            for (int i = 0; i < V; i++) {
                System.out.print(i + ": ");
                for (Node node : adj.get(i)) {
                    System.out.print("(" + node.vertex + "," + node.weight + ") ");
                }
                System.out.println();
            }
        }
    }
    
    // ========================================
    // GRAPH TRAVERSALS
    // ========================================
    
    // BFS - Breadth First Search
    static void BFS(GraphList g, int start) {
        int V = g.getV();
        boolean[] visited = new boolean[V];
        Queue<Integer> q = new LinkedList<>();
        
        visited[start] = true;
        q.add(start);
        
        System.out.print("BFS from " + start + ": ");
        
        while (!q.isEmpty()) {
            int u = q.poll();
            System.out.print(u + " ");
            
            for (int v : g.getAdj().get(u)) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.add(v);
                }
            }
        }
        System.out.println();
    }
    
    // DFS - Depth First Search (Recursive)
    static void DFSUtil(List<List<Integer>> adj, int u, boolean[] visited) {
        visited[u] = true;
        System.out.print(u + " ");
        
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                DFSUtil(adj, v, visited);
            }
        }
    }
    
    static void DFS(GraphList g, int start) {
        int V = g.getV();
        boolean[] visited = new boolean[V];
        
        System.out.print("DFS from " + start + ": ");
        DFSUtil(g.getAdj(), start, visited);
        System.out.println();
    }
    
    // DFS Iterative (using stack)
    static void DFSIterative(GraphList g, int start) {
        int V = g.getV();
        boolean[] visited = new boolean[V];
        Stack<Integer> st = new Stack<>();
        
        st.push(start);
        
        System.out.print("DFS Iterative from " + start + ": ");
        
        while (!st.isEmpty()) {
            int u = st.pop();
            
            if (!visited[u]) {
                visited[u] = true;
                System.out.print(u + " ");
                
                // Push neighbors in reverse order
                List<Integer> neighbors = g.getAdj().get(u);
                for (int i = neighbors.size() - 1; i >= 0; i--) {
                    int v = neighbors.get(i);
                    if (!visited[v]) {
                        st.push(v);
                    }
                }
            }
        }
        System.out.println();
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== GRAPH BASIC OPERATIONS ===");
        
        System.out.println("\n1. ADJACENCY MATRIX");
        System.out.println("-------------------");
        
        GraphMatrix gm = new GraphMatrix(5);
        gm.addEdge(0, 1);
        gm.addEdge(0, 4);
        gm.addEdge(1, 2);
        gm.addEdge(1, 3);
        gm.addEdge(1, 4);
        gm.addEdge(2, 3);
        gm.addEdge(3, 4);
        
        gm.display();
        System.out.println("\nEdge (0,1) exists: " + (gm.hasEdge(0, 1) ? "Yes" : "No"));
        
        System.out.println("\n2. ADJACENCY LIST");
        System.out.println("-----------------");
        
        GraphList gl = new GraphList(5);
        gl.addEdge(0, 1);
        gl.addEdge(0, 4);
        gl.addEdge(1, 2);
        gl.addEdge(1, 3);
        gl.addEdge(1, 4);
        gl.addEdge(2, 3);
        gl.addEdge(3, 4);
        
        gl.display();
        
        System.out.println("\n3. EDGE LIST");
        System.out.println("------------");
        
        GraphEdgeList ge = new GraphEdgeList(5);
        ge.addEdge(0, 1, 10);
        ge.addEdge(0, 4, 20);
        ge.addEdge(1, 2, 30);
        ge.addEdge(1, 3, 40);
        ge.addEdge(2, 3, 50);
        
        ge.display();
        
        System.out.println("\n4. WEIGHTED GRAPH");
        System.out.println("-----------------");
        
        WeightedGraph wg = new WeightedGraph(5);
        wg.addEdge(0, 1, 10);
        wg.addEdge(0, 4, 20);
        wg.addEdge(1, 2, 30);
        wg.addEdge(1, 3, 40);
        wg.addEdge(2, 3, 50);
        wg.addEdge(3, 4, 60);
        
        wg.display();
        
        System.out.println("\n5. GRAPH TRAVERSALS");
        System.out.println("-------------------");
        
        BFS(gl, 0);
        DFS(gl, 0);
        DFSIterative(gl, 0);
    }
}
