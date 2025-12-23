package sparse_table;

import java.util.*;

/**
 * Sparse Table Implementation
 * Provides O(1) Range Minimum Queries after O(N log N) preprocessing.
 * Works for idempotent functions: min, max, gcd, and, or.
 */
public class basic_operations {

    static class SparseTable {
        private int[][] st;
        private int[] logs;
        private final int N;
        private final int K;

        public SparseTable(int[] arr) {
            this.N = arr.length;
            this.K = (int) (Math.log(N) / Math.log(2)) + 1;
            this.st = new int[N][K];
            this.logs = new int[N + 1];

            // Precompute logs
            for (int i = 2; i <= N; i++) {
                logs[i] = logs[i / 2] + 1;
            }

            // Fill row 0
            for (int i = 0; i < N; i++) {
                st[i][0] = arr[i];
            }

            // Precompute table
            for (int j = 1; j < K; j++) {
                for (int i = 0; i + (1 << j) <= N; i++) {
                    st[i][j] = Math.min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
                }
            }
        }

        public int query(int L, int R) {
            if (L > R)
                return Integer.MAX_VALUE;
            int j = logs[R - L + 1];
            return Math.min(st[L][j], st[R - (1 << j) + 1][j]);
        }
    }

    public static void main(String[] args) {
        int[] arr = { 7, 2, 3, 0, 5, 10, 3, 12, 18 };
        SparseTable table = new SparseTable(arr);
        System.out.println("Min in [0, 4]: " + table.query(0, 4));
        System.out.println("Min in [4, 7]: " + table.query(4, 7));
        System.out.println("Min in [7, 8]: " + table.query(7, 8));
    }
}
