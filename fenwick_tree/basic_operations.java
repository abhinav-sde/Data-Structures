package fenwick_tree;

/**
 * Basic Fenwick Tree (Binary Indexed Tree) Operations
 * Efficient for prefix sums and range queries
 */

import java.util.*;

public class basic_operations {

    static class FenwickTree {
        private int[] tree;
        private int n;

        // Constructor
        public FenwickTree(int size) {
            this.n = size;
            this.tree = new int[n + 1]; // 1-indexed
        }

        // Construct from array
        public FenwickTree(int[] arr) {
            this.n = arr.length;
            this.tree = new int[n + 1];

            for (int i = 0; i < n; i++) {
                update(i, arr[i]);
            }
        }

        // Update: Add delta to index i
        // Time Complexity: O(log n)
        public void update(int i, int delta) {
            i++; // Convert to 1-indexed

            while (i <= n) {
                tree[i] += delta;
                i += (i & -i); // Add last set bit
            }
        }

        // Query: Get prefix sum from 0 to i
        // Time Complexity: O(log n)
        public int query(int i) {
            i++; // Convert to 1-indexed
            int sum = 0;

            while (i > 0) {
                sum += tree[i];
                i -= (i & -i); // Remove last set bit
            }

            return sum;
        }

        // Range sum from left to right (inclusive)
        // Time Complexity: O(log n)
        public int rangeQuery(int left, int right) {
            if (left > right)
                return 0;
            if (left == 0)
                return query(right);
            return query(right) - query(left - 1);
        }

        // Set value at index i
        public void set(int i, int val) {
            int currentVal = rangeQuery(i, i);
            update(i, val - currentVal);
        }

        // Display tree
        public void display() {
            System.out.print("Fenwick Tree: ");
            for (int i = 1; i <= n; i++) {
                System.out.print(tree[i] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Fenwick Tree Basic Operations ===\n");

        // Create from array
        int[] arr = { 3, 2, -1, 6, 5, 4, -3, 3, 7, 2 };
        FenwickTree ft = new FenwickTree(arr);

        System.out.println("Original array: " + Arrays.toString(arr));
        ft.display();
        System.out.println();

        // Test prefix sums
        System.out.println("--- Prefix Sums ---");
        for (int i = 0; i < 5; i++) {
            System.out.println("Sum[0.." + i + "]: " + ft.query(i));
        }
        System.out.println();

        // Test range queries
        System.out.println("--- Range Queries ---");
        System.out.println("Sum[2..5]: " + ft.rangeQuery(2, 5));
        System.out.println("Sum[3..7]: " + ft.rangeQuery(3, 7));
        System.out.println();

        // Test update
        System.out.println("--- Update Operations ---");
        System.out.println("Adding 10 to index 3");
        ft.update(3, 10);
        System.out.println("New Sum[2..5]: " + ft.rangeQuery(2, 5));
        System.out.println();

        // Test set
        System.out.println("--- Set Operations ---");
        System.out.println("Setting index 5 to 100");
        ft.set(5, 100);
        System.out.println("New Sum[3..7]: " + ft.rangeQuery(3, 7));
    }
}
