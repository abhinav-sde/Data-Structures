import java.util.Arrays;

// Problem: Kruskal's Algorithm for Minimum Spanning Tree
public class advanced_problems {

    static class Edge implements Comparable<Edge> {
        int u, v, weight;

        public Edge(int u, int v, int weight) {
            this.u = u;
            this.v = v;
            this.weight = weight;
        }

        @Override
        public int compareTo(Edge other) {
            return this.weight - other.weight;
        }
    }

    static class DSU {
        int[] parent;

        public DSU(int n) {
            parent = new int[n];
            for (int i = 0; i < n; i++)
                parent[i] = i;
        }

        public int find(int i) {
            if (parent[i] == i)
                return i;
            return parent[i] = find(parent[i]);
        }

        public void unite(int i, int j) {
            int rootI = find(i);
            int rootJ = find(j);
            if (rootI != rootJ)
                parent[rootI] = rootJ;
        }
    }

    public static int kruskalMST(int n, Edge[] edges) {
        Arrays.sort(edges);
        DSU dsu = new DSU(n);
        int mstWeight = 0;
        int count = 0;

        for (Edge edge : edges) {
            if (dsu.find(edge.u) != dsu.find(edge.v)) {
                dsu.unite(edge.u, edge.v);
                mstWeight += edge.weight;
                count++;
            }
        }
        return count == n - 1 ? mstWeight : -1;
    }

    public static void main(String[] args) {
        int n = 4;
        Edge[] edges = {
                new Edge(0, 1, 10),
                new Edge(0, 2, 6),
                new Edge(0, 3, 5),
                new Edge(1, 3, 15),
                new Edge(2, 3, 4)
        };

        System.out.println("MST Weight: " + kruskalMST(n, edges));
        // Expected: 19
    }
}
