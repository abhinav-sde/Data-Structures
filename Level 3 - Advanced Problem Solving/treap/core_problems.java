import java.util.Random;

/**
 * Core Treap Problems in Java
 * Focuses on set-like operations and range count queries.
 */
public class core_problems {
    private static final Random rand = new Random();

    static class Node {
        int key, priority, size;
        Node left, right;

        Node(int key) {
            this.key = key;
            this.priority = rand.nextInt();
            this.size = 1;
        }

        void updateSize() {
            this.size = 1 + (left != null ? left.size : 0) + (right != null ? right.size : 0);
        }
    }

    static class Pair {
        Node first, second;

        Pair(Node first, Node second) {
            this.first = first;
            this.second = second;
        }
    }

    public static Pair split(Node root, int target) {
        if (root == null)
            return new Pair(null, null);
        if (root.key <= target) {
            Pair p = split(root.right, target);
            root.right = p.first;
            root.updateSize();
            return new Pair(root, p.second);
        } else {
            Pair p = split(root.left, target);
            root.left = p.second;
            root.updateSize();
            return new Pair(p.first, root);
        }
    }

    public static Node merge(Node L, Node R) {
        if (L == null)
            return R;
        if (R == null)
            return L;
        if (L.priority > R.priority) {
            L.right = merge(L.right, R);
            L.updateSize();
            return L;
        } else {
            R.left = merge(L, R.left);
            R.updateSize();
            return R;
        }
    }

    // Problem 1: Count elements <= X
    public static int countLessEqual(Node root, int X) {
        Pair p = split(root, X);
        int count = (p.first != null ? p.first.size : 0);
        root = merge(p.first, p.second); // Reconstruct
        return count;
    }

    // Problem 2: Find K-th smallest element (1-indexed)
    public static int findKth(Node root, int k) {
        int leftSize = (root.left != null ? root.left.size : 0);
        if (k == leftSize + 1)
            return root.key;
        if (k <= leftSize)
            return findKth(root.left, k);
        return findKth(root.right, k - leftSize - 1);
    }

    public static void main(String[] args) {
        Node root = null;
        int[] data = { 5, 12, 7, 20, 15, 3, 10 };
        for (int x : data) {
            Pair p = split(root, x);
            root = merge(merge(p.first, new Node(x)), p.second);
        }

        System.out.println("Current Set Size: " + (root != null ? root.size : 0));
        System.out.println("Elements <= 12: " + countLessEqual(root, 12));
        System.out.println("2nd smallest element: " + findKth(root, 2));
        System.out.println("5th smallest element: " + findKth(root, 5));
    }
}
