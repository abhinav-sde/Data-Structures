package bst;

/**
 * Advanced BST Problems in Java
 * Including AVL Tree implementation
 */

import java.util.*;

public class advanced_problems {

    static class TreeNode {
        int val;
        TreeNode left, right;
        int height;

        TreeNode(int v) {
            val = v;
            height = 1;
        }
    }

    // AVL Tree Implementation
    static class AVLTree {
        private TreeNode root;

        // Get height
        private int height(TreeNode node) {
            return node == null ? 0 : node.height;
        }

        // Get balance factor
        private int getBalance(TreeNode node) {
            return node == null ? 0 : height(node.left) - height(node.right);
        }

        // Right rotate
        private TreeNode rightRotate(TreeNode y) {
            TreeNode x = y.left;
            TreeNode T2 = x.right;

            x.right = y;
            y.left = T2;

            y.height = Math.max(height(y.left), height(y.right)) + 1;
            x.height = Math.max(height(x.left), height(x.right)) + 1;

            return x;
        }

        // Left rotate
        private TreeNode leftRotate(TreeNode x) {
            TreeNode y = x.right;
            TreeNode T2 = y.left;

            y.left = x;
            x.right = T2;

            x.height = Math.max(height(x.left), height(x.right)) + 1;
            y.height = Math.max(height(y.left), height(y.right)) + 1;

            return y;
        }

        // Insert with balancing
        public void insert(int val) {
            root = insertHelper(root, val);
        }

        private TreeNode insertHelper(TreeNode node, int val) {
            if (node == null)
                return new TreeNode(val);

            if (val < node.val) {
                node.left = insertHelper(node.left, val);
            } else if (val > node.val) {
                node.right = insertHelper(node.right, val);
            } else {
                return node;
            }

            node.height = 1 + Math.max(height(node.left), height(node.right));

            int balance = getBalance(node);

            // Left Left
            if (balance > 1 && val < node.left.val) {
                return rightRotate(node);
            }

            // Right Right
            if (balance < -1 && val > node.right.val) {
                return leftRotate(node);
            }

            // Left Right
            if (balance > 1 && val > node.left.val) {
                node.left = leftRotate(node.left);
                return rightRotate(node);
            }

            // Right Left
            if (balance < -1 && val < node.right.val) {
                node.right = rightRotate(node.right);
                return leftRotate(node);
            }

            return node;
        }

        public void inorder() {
            inorderHelper(root);
            System.out.println();
        }

        private void inorderHelper(TreeNode node) {
            if (node == null)
                return;
            inorderHelper(node.left);
            System.out.print(node.val + " ");
            inorderHelper(node.right);
        }

        public int getHeight() {
            return height(root);
        }
    }

    // Problem: Serialize and Deserialize BST
    static class Codec {
        public String serialize(TreeNode root) {
            StringBuilder sb = new StringBuilder();
            serializeHelper(root, sb);
            return sb.toString();
        }

        private void serializeHelper(TreeNode node, StringBuilder sb) {
            if (node == null) {
                sb.append("#,");
                return;
            }
            sb.append(node.val).append(",");
            serializeHelper(node.left, sb);
            serializeHelper(node.right, sb);
        }

        public TreeNode deserialize(String data) {
            Queue<String> queue = new LinkedList<>(Arrays.asList(data.split(",")));
            return deserializeHelper(queue);
        }

        private TreeNode deserializeHelper(Queue<String> queue) {
            String val = queue.poll();
            if (val.equals("#"))
                return null;

            TreeNode node = new TreeNode(Integer.parseInt(val));
            node.left = deserializeHelper(queue);
            node.right = deserializeHelper(queue);
            return node;
        }
    }

    // Problem: Recover BST (two nodes swapped)
    static TreeNode first = null, second = null, prev = null;

    static void recoverTree(TreeNode root) {
        first = second = prev = null;
        inorderRecover(root);

        if (first != null && second != null) {
            int temp = first.val;
            first.val = second.val;
            second.val = temp;
        }
    }

    static void inorderRecover(TreeNode node) {
        if (node == null)
            return;

        inorderRecover(node.left);

        if (prev != null && prev.val > node.val) {
            if (first == null)
                first = prev;
            second = node;
        }
        prev = node;

        inorderRecover(node.right);
    }

    // Problem: Balance a BST
    static TreeNode balanceBST(TreeNode root) {
        List<Integer> sorted = new ArrayList<>();
        inorderToList(root, sorted);
        return sortedListToBST(sorted, 0, sorted.size() - 1);
    }

    static void inorderToList(TreeNode node, List<Integer> list) {
        if (node == null)
            return;
        inorderToList(node.left, list);
        list.add(node.val);
        inorderToList(node.right, list);
    }

    static TreeNode sortedListToBST(List<Integer> list, int left, int right) {
        if (left > right)
            return null;

        int mid = left + (right - left) / 2;
        TreeNode node = new TreeNode(list.get(mid));

        node.left = sortedListToBST(list, left, mid - 1);
        node.right = sortedListToBST(list, mid + 1, right);

        return node;
    }

    public static void main(String[] args) {
        System.out.println("=== Advanced BST Problems ===\n");

        // Test AVL Tree
        System.out.println("Test 1: AVL Tree");
        AVLTree avl = new AVLTree();
        int[] values = { 10, 20, 30, 40, 50, 25 };

        for (int v : values) {
            avl.insert(v);
        }

        System.out.print("AVL Inorder: ");
        avl.inorder();
        System.out.println("AVL Height: " + avl.getHeight());
        System.out.println();

        // Test Serialize/Deserialize
        System.out.println("Test 2: Serialize and Deserialize BST");
        TreeNode bst = new TreeNode(50);
        bst.left = new TreeNode(30);
        bst.right = new TreeNode(70);

        Codec codec = new Codec();
        String serialized = codec.serialize(bst);
        System.out.println("Serialized: " + serialized);

        TreeNode deserialized = codec.deserialize(serialized);
        System.out.println("Deserialized successfully");
        System.out.println();

        // Test Balance BST
        System.out.println("Test 3: Balance BST");
        TreeNode unbalanced = new TreeNode(1);
        unbalanced.right = new TreeNode(2);
        unbalanced.right.right = new TreeNode(3);
        unbalanced.right.right.right = new TreeNode(4);

        TreeNode balanced = balanceBST(unbalanced);
        System.out.println("BST balanced successfully");
    }
}
