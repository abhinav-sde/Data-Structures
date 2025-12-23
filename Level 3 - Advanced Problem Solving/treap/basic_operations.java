import java.util.Random;

/**
 * Basic Treap Operations in Java
 * Implements a balanced BST using randomized priorities.
 */
public class basic_operations {
    private static final Random rand = new Random();

    static class Node {
        int key;
        int priority;
        Node left, right;

        Node(int key) {
            this.key = key;
            this.priority = rand.nextInt();
            this.left = this.right = null;
        }
    }

    static class Pair {
        Node first, second;

        Pair(Node first, Node second) {
            this.first = first;
            this.second = second;
        }
    }

    // Split treap into two: keys <= target and keys > target
    public static Pair split(Node root, int target) {
        if (root == null)
            return new Pair(null, null);

        if (root.key <= target) {
            Pair pair = split(root.right, target);
            root.right = pair.first;
            return new Pair(root, pair.second);
        } else {
            Pair pair = split(root.left, target);
            root.left = pair.second;
            return new Pair(pair.first, root);
        }
    }

    // Merge two treaps: all keys in L < all keys in R
    public static Node merge(Node L, Node R) {
        if (L == null)
            return R;
        if (R == null)
            return L;

        if (L.priority > R.priority) {
            L.right = merge(L.right, R);
            return L;
        } else {
            R.left = merge(L, R.left);
            return R;
        }
    }

    public static Node insert(Node root, int key) {
        Pair pair = split(root, key);
        Node newNode = new Node(key);
        return merge(merge(pair.first, newNode), pair.second);
    }

    public static Node delete(Node root, int key) {
        Pair p1 = split(root, key - 1);
        Pair p2 = split(p1.second, key);
        // p2.first is the node(s) with key
        return merge(p1.first, p2.second);
    }

    public static boolean search(Node root, int key) {
        if (root == null)
            return false;
        if (root.key == key)
            return true;
        return key < root.key ? search(root.left, key) : search(root.right, key);
    }

    public static void inorder(Node root) {
        if (root != null) {
            inorder(root.left);
            System.out.print(root.key + " ");
            inorder(root.right);
        }
    }

    public static void main(String[] args) {
        Node root = null;
        int[] keys = { 10, 20, 5, 15, 25, 30 };

        System.out.println("Inserting keys: 10, 20, 5, 15, 25, 30");
        for (int k : keys)
            root = insert(root, k);

        System.out.print("Inorder traversal: ");
        inorder(root);
        System.out.println();

        System.out.println("Searching for 15: " + search(root, 15));
        System.out.println("Searching for 100: " + search(root, 100));

        System.out.println("Deleting 15...");
        root = delete(root, 15);
        System.out.print("Inorder traversal after deletion: ");
        inorder(root);
        System.out.println();
    }
}
