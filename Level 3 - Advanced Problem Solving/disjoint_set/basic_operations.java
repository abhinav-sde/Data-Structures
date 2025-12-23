// Disjoint Set Union with Path Compression and Union by Rank
class DSU {
    private int[] parent;
    private int[] rank;

    public DSU(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i; // Initially, each element is its own root
            rank[i] = 0;
        }
    }

    public int find(int i) {
        if (parent[i] != i) {
            // Path Compression: Point directly to the root
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    public void unite(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);

        if (rootI != rootJ) {
            // Union by Rank: Attach smaller tree to taller tree
            if (rank[rootI] < rank[rootJ]) {
                parent[rootI] = rootJ;
            } else if (rank[rootI] > rank[rootJ]) {
                parent[rootJ] = rootI;
            } else {
                parent[rootJ] = rootI;
                rank[rootI]++;
            }
        }
    }

    public boolean same(int i, int j) {
        return find(i) == find(j);
    }

    public static void main(String[] args) {
        DSU dsu = new DSU(5);

        dsu.unite(0, 1);
        dsu.unite(2, 3);

        System.out.println("0 and 1 same? " + dsu.same(0, 1)); // true
        System.out.println("0 and 3 same? " + dsu.same(0, 3)); // false

        dsu.unite(1, 3);
        System.out.println("0 and 3 same after union(1,3)? " + dsu.same(0, 3)); // true
    }
}
