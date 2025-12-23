
/**
 * Basic Binary Search Tree Operations in Java
 * Contains fundamental BST operations
 */

import java.util.*;

public class basic_operations {

    // TreeNode class
    static class TreeNode {
        int val;
        TreeNode left, right;

        public TreeNode(int val) {
            this.val = val;
            this.left = null;
            this.right = null;
        }
    }

    // BST class
    static class BST {
        private TreeNode root;

        public BST() {
            root = null;
        }

        // Insert a value
        // Time Complexity: O(h) where h is height
        public void insert(int val) {
            root = insertHelper(root, val);
            System.out.println("Inserted: " + val);
        }

        private TreeNode insertHelper(TreeNode node, int val) {
            if (node == null) {
                return new TreeNode(val);
            }

            if (val < node.val) {
                node.left = insertHelper(node.left, val);
            } else if (val > node.val) {
                node.right = insertHelper(node.right, val);
            }

            return node;
        }

        // Search for a value
        // Time Complexity: O(h)
        public boolean search(int val) {
            return searchHelper(root, val);
        }

        private boolean searchHelper(TreeNode node, int val) {
            if (node == null)
                return false;

            if (node.val == val)
                return true;
            if (val < node.val)
                return searchHelper(node.left, val);
            return searchHelper(node.right, val);
        }

        // Delete a value
        // Time Complexity: O(h)
        public void delete(int val) {
            root = deleteHelper(root, val);
            System.out.println("Deleted: " + val);
        }

        private TreeNode deleteHelper(TreeNode node, int val) {
            if (node == null)
                return null;

            if (val < node.val) {
                node.left = deleteHelper(node.left, val);
            } else if (val > node.val) {
                node.right = deleteHelper(node.right, val);
            } else {
                // Node to delete found

                // Case 1: Leaf node
                if (node.left == null && node.right == null) {
                    return null;
                }

                // Case 2: One child
                if (node.left == null)
                    return node.right;
                if (node.right == null)
                    return node.left;

                // Case 3: Two children
                // Find inorder successor (minimum in right subtree)
                TreeNode successor = findMin(node.right);
                node.val = successor.val;
                node.right = deleteHelper(node.right, successor.val);
            }

            return node;
        }

        // Find minimum value node
        public TreeNode findMin(TreeNode node) {
            while (node.left != null) {
                node = node.left;
            }
            return node;
        }

        // Find maximum value node
        public TreeNode findMax(TreeNode node) {
            while (node.right != null) {
                node = node.right;
            }
            return node;
        }

        // Inorder traversal (Left-Root-Right) - gives sorted order
        public void inorder() {
            System.out.print("Inorder: ");
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

        // Preorder traversal (Root-Left-Right)
        public void preorder() {
            System.out.print("Preorder: ");
            preorderHelper(root);
            System.out.println();
        }

        private void preorderHelper(TreeNode node) {
            if (node == null)
                return;
            System.out.print(node.val + " ");
            preorderHelper(node.left);
            preorderHelper(node.right);
        }

        // Postorder traversal (Left-Right-Root)
        public void postorder() {
            System.out.print("Postorder: ");
            postorderHelper(root);
            System.out.println();
        }

        private void postorderHelper(TreeNode node) {
            if (node == null)
                return;
            postorderHelper(node.left);
            postorderHelper(node.right);
            System.out.print(node.val + " ");
        }

        // Level order traversal (BFS)
        public void levelOrder() {
            if (root == null)
                return;

            System.out.print("Level Order: ");
            Queue<TreeNode> queue = new LinkedList<>();
            queue.offer(root);

            while (!queue.isEmpty()) {
                TreeNode current = queue.poll();
                System.out.print(current.val + " ");

                if (current.left != null)
                    queue.offer(current.left);
                if (current.right != null)
                    queue.offer(current.right);
            }
            System.out.println();
        }

        // Get height of tree
        public int height() {
            return heightHelper(root);
        }

        private int heightHelper(TreeNode node) {
            if (node == null)
                return -1; // Height of empty tree is -1
            return 1 + Math.max(heightHelper(node.left), heightHelper(node.right));
        }

        // Count total nodes
        public int size() {
            return sizeHelper(root);
        }

        private int sizeHelper(TreeNode node) {
            if (node == null)
                return 0;
            return 1 + sizeHelper(node.left) + sizeHelper(node.right);
        }

        // Check if tree is BST
        public boolean isBST() {
            return isBSTHelper(root, null, null);
        }

        private boolean isBSTHelper(TreeNode node, Integer min, Integer max) {
            if (node == null)
                return true;

            if ((min != null && node.val <= min) || (max != null && node.val >= max)) {
                return false;
            }

            return isBSTHelper(node.left, min, node.val) &&
                    isBSTHelper(node.right, node.val, max);
        }
    }

    public static void main(String[] args) {
        System.out.println("=== BST Basic Operations Demo ===\n");

        BST bst = new BST();

        // Insert values
        System.out.println("--- Inserting Values ---");
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        bst.insert(60);
        bst.insert(80);
        System.out.println();

        // Traversals
        System.out.println("--- Traversals ---");
        bst.inorder();
        bst.preorder();
        bst.postorder();
        bst.levelOrder();
        System.out.println();

        // Search
        System.out.println("--- Search Operations ---");
        System.out.println("Search 40: " + bst.search(40));
        System.out.println("Search 25: " + bst.search(25));
        System.out.println();

        // Tree properties
        System.out.println("--- Tree Properties ---");
        System.out.println("Height: " + bst.height());
        System.out.println("Size: " + bst.size());
        System.out.println("Is BST: " + bst.isBST());
        System.out.println();

        // Delete
        System.out.println("--- Delete Operations ---");
        bst.delete(20); // Delete leaf
        bst.inorder();

        bst.delete(30); // Delete node with two children
        bst.inorder();

        bst.delete(50); // Delete root
        bst.inorder();
    }
}
