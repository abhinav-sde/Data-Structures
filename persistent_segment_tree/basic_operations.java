package persistent_segment_tree;

import java.util.*;

/**
 * Persistent Segment Tree Implementation
 * Allows querying any previous version of the tree.
 * Updates create O(log N) new nodes instead of modifying existing ones.
 */
public class basic_operations {

    static class Node {
        int sum;
        Node left, right;

        Node(int val) {
            this.sum = val;
        }

        Node(Node l, Node r) {
            this.left = l;
            this.right = r;
            this.sum = (l != null ? l.sum : 0) + (r != null ? r.sum : 0);
        }
    }

    static class PersistentSegTree {
        private Node[] roots;
        private int n;
        private int versionCount;

        public PersistentSegTree(int[] arr, int maxVersions) {
            this.n = arr.length;
            this.roots = new Node[maxVersions];
            this.roots[0] = build(arr, 0, n - 1);
            this.versionCount = 1;
        }

        private Node build(int[] arr, int L, int R) {
            if (L == R)
                return new Node(arr[L]);
            int mid = L + (R - L) / 2;
            return new Node(build(arr, L, mid), build(arr, mid + 1, R));
        }

        public void update(int prevVersion, int idx, int val) {
            roots[versionCount++] = update(roots[prevVersion], 0, n - 1, idx, val);
        }

        private Node update(Node prev, int L, int R, int idx, int val) {
            if (L == R)
                return new Node(val);
            int mid = L + (R - L) / 2;
            if (idx <= mid) {
                return new Node(update(prev.left, L, mid, idx, val), prev.right);
            } else {
                return new Node(prev.left, update(prev.right, mid + 1, R, idx, val));
            }
        }

        public int query(int version, int L, int R, int qL, int qR) {
            return query(roots[version], L, R, qL, qR);
        }

        private int query(Node node, int L, int R, int qL, int qR) {
            if (qL <= L && R <= qR)
                return node.sum;
            int mid = L + (R - L) / 2;
            int sum = 0;
            if (qL <= mid)
                sum += query(node.left, L, mid, qL, qR);
            if (qR > mid)
                sum += query(node.right, mid + 1, R, qL, qR);
            return sum;
        }

        public int getVersionCount() {
            return versionCount;
        }
    }

    public static void main(String[] args) {
        int[] arr = { 1, 2, 3, 4 };
        PersistentSegTree pst = new PersistentSegTree(arr, 10);
        System.out.println("V0 Sum [0,3]: " + pst.query(0, 0, 3, 0, 3));

        pst.update(0, 1, 10); // version 1: {1, 10, 3, 4}
        System.out.println("V0 Sum [0,2]: " + pst.query(0, 0, 3, 0, 2));
        System.out.println("V1 Sum [0,2]: " + pst.query(1, 0, 3, 0, 2));
    }
}
