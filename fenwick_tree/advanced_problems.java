package fenwick_tree;

import java.util.*;

public class advanced_problems {

    // 2D Fenwick Tree
    static class FenwickTree2D {
        private int[][] tree;
        private int m, n;

        public FenwickTree2D(int rows, int cols) {
            m = rows;
            n = cols;
            tree = new int[m + 1][n + 1];
        }

        public void update(int row, int col, int delta) {
            for (int i = row + 1; i <= m; i += (i & -i)) {
                for (int j = col + 1; j <= n; j += (j & -j)) {
                    tree[i][j] += delta;
                }
            }
        }

        public int query(int row, int col) {
            int sum = 0;
            for (int i = row + 1; i > 0; i -= (i & -i)) {
                for (int j = col + 1; j > 0; j -= (j & -j)) {
                    sum += tree[i][j];
                }
            }
            return sum;
        }

        public int rangeQuery(int row1, int col1, int row2, int col2) {
            int total = query(row2, col2);
            if (row1 > 0)
                total -= query(row1 - 1, col2);
            if (col1 > 0)
                total -= query(row2, col1 - 1);
            if (row1 > 0 && col1 > 0)
                total += query(row1 - 1, col1 - 1);
            return total;
        }
    }

    // Fenwick Tree with Range Update
    static class FenwickTreeRangeUpdate {
        private int[] tree1, tree2;
        private int n;

        public FenwickTreeRangeUpdate(int size) {
            n = size;
            tree1 = new int[n + 1];
            tree2 = new int[n + 1];
        }

        private void update(int[] tree, int i, int delta) {
            i++;
            while (i <= n) {
                tree[i] += delta;
                i += (i & -i);
            }
        }

        public void rangeUpdate(int left, int right, int delta) {
            update(tree1, left, delta);
            update(tree1, right + 1, -delta);
            update(tree2, left, delta * (left - 1));
            update(tree2, right + 1, -delta * right);
        }

        private int query(int[] tree, int i) {
            i++;
            int sum = 0;
            while (i > 0) {
                sum += tree[i];
                i -= (i & -i);
            }
            return sum;
        }

        public int pointQuery(int i) {
            return query(tree1, i) * i - query(tree2, i);
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Advanced Fenwick Tree Problems ===\n");

        // Test 2D Fenwick Tree
        System.out.println("Test 1: 2D Fenwick Tree");
        FenwickTree2D ft2d = new FenwickTree2D(3, 3);
        ft2d.update(0, 0, 1);
        ft2d.update(1, 1, 2);
        ft2d.update(2, 2, 3);
        System.out.println("Range sum [0,0] to [2,2]: " + ft2d.rangeQuery(0, 0, 2, 2));
        System.out.println();

        // Test Range Update
        System.out.println("Test 2: Range Update Fenwick Tree");
        FenwickTreeRangeUpdate ftRange = new FenwickTreeRangeUpdate(10);
        ftRange.rangeUpdate(2, 5, 10);
        System.out.println("Value at index 3: " + ftRange.pointQuery(3));
        System.out.println("Value at index 6: " + ftRange.pointQuery(6));
    }
}
