import java.util.Random;

/**
 * Advanced Treap Problems in Java
 * Implements an "Implicit Treap" for range operations.
 * Allows range reversal in O(log N).
 */
public class advanced_problems {
    private static final Random rand = new Random();

    static class Node {
        int priority, size;
        int value;
        boolean reverse;
        Node left, right;

        Node(int value) {
            this.value = value;
            this.priority = rand.nextInt();
            this.size = 1;
            this.reverse = false;
        }

        void update() {
            this.size = 1 + (left != null ? left.size : 0) + (right != null ? right.size : 0);
        }

        void push() {
            if (reverse) {
                reverse = false;
                Node temp = left;
                left = right;
                right = temp;
                if (left != null)
                    left.reverse ^= true;
                if (right != null)
                    right.reverse ^= true;
            }
        }
    }

    static class Pair {
        Node first, second;

        Pair(Node first, Node second) {
            this.first = first;
            this.second = second;
        }
    }

    public static Pair split(Node root, int k) {
        if (root == null)
            return new Pair(null, null);
        root.push();
        int leftSize = (root.left != null ? root.left.size : 0);
        if (leftSize < k) {
            Pair p = split(root.right, k - leftSize - 1);
            root.right = p.first;
            root.update();
            return new Pair(root, p.second);
        } else {
            Pair p = split(root.left, k);
            root.left = p.second;
            root.update();
            return new Pair(p.first, root);
        }
    }

    public static Node merge(Node L, Node R) {
        if (L == null)
            return R;
        if (R == null)
            return L;
        L.push();
        R.push();
        if (L.priority > R.priority) {
            L.right = merge(L.right, R);
            L.update();
            return L;
        } else {
            R.left = merge(L, R.left);
            R.update();
            return R;
        }
    }

    public static void reverseRange(Node root, int L, int R) {
        // Assume 0-indexed, L and R inclusive
        // Wait, split takes count. For range [L, R]:
        // 1. Split after R+1 to get (T1, T_rem)
        // 2. Split T1 after L to get (T_left, T_target)
        // 3. Reverse T_target
        // 4. Merge back
    }

    public static void printTreap(Node root) {
        if (root == null)
            return;
        root.push();
        printTreap(root.left);
        System.out.print(root.value + " ");
        printTreap(root.right);
    }

    public static void main(String[] args) {
        Node root = null;
        System.out.println("Building implicit treap with values [0, 9]...");
        for (int i = 0; i < 10; i++) {
            root = merge(root, new Node(i));
        }

        System.out.print("Original Array: ");
        printTreap(root);
        System.out.println();

        // Reverse range [2, 7]
        System.out.println("Reversing range [2, 7]...");
        Pair p1 = split(root, 8); // k is count
        Pair p2 = split(p1.first, 2);

        // p2.second is our target range [2, 7]
        if (p2.second != null)
            p2.second.reverse ^= true;

        root = merge(merge(p2.first, p2.second), p1.second);

        System.out.print("Array after reversal: ");
        printTreap(root);
        System.out.println();
    }
}
