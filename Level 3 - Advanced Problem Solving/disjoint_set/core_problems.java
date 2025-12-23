import java.util.ArrayList;
import java.util.List;

public class core_problems {

    static class SimpleDSU {
        int[] parent;

        public SimpleDSU(int n) {
            parent = new int[n];
            for (int i = 0; i < n; i++)
                parent[i] = i;
        }

        public int find(int i) {
            if (parent[i] == i)
                return i;
            return parent[i] = find(parent[i]);
        }

        public boolean unite(int i, int j) {
            int rootI = find(i);
            int rootJ = find(j);
            if (rootI != rootJ) {
                parent[rootI] = rootJ;
                return true; // Merged
            }
            return false; // Already same set
        }
    }

    // Problem: Cycle Detection
    public static boolean hasCycle(int n, int[][] edges) {
        SimpleDSU dsu = new SimpleDSU(n);
        for (int[] edge : edges) {
            if (!dsu.unite(edge[0], edge[1])) {
                return true; // Cycle found
            }
        }
        return false;
    }

    public static void main(String[] args) {
        int n = 3;
        int[][] edges = { { 0, 1 }, { 1, 2 }, { 2, 0 } };
        System.out.println("Has Cycle: " + hasCycle(n, edges));
    }
}
