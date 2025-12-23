package bst;

/**
 * Core BST Problems in Java
 */

import java.util.*;

public class core_problems {

    static class TreeNode {
        int val;
        TreeNode left, right;

        TreeNode(int v) {
            val = v;
        }
    }

    // Problem 1: Validate BST
    static boolean isValidBST(TreeNode root) {
        return isValidBSTHelper(root, null, null);
    }

    static boolean isValidBSTHelper(TreeNode node, Integer min, Integer max) {
        if (node == null)
            return true;

        if ((min != null && node.val <= min) || (max != null && node.val >= max)) {
            return false;
        }

        return isValidBSTHelper(node.left, min, node.val) &&
                isValidBSTHelper(node.right, node.val, max);
    }

    // Problem 2: Lowest Common Ancestor
    static TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null)
            return null;

        if (p.val < root.val && q.val < root.val) {
            return lowestCommonAncestor(root.left, p, q);
        }

        if (p.val > root.val && q.val > root.val) {
            return lowestCommonAncestor(root.right, p, q);
        }

        return root;
    }

    // Problem 3: Kth Smallest Element
    static int kthSmallest(TreeNode root, int k) {
        List<Integer> result = new ArrayList<>();
        inorderK(root, k, result);
        return result.get(k - 1);
    }

    static void inorderK(TreeNode node, int k, List<Integer> result) {
        if (node == null || result.size() >= k)
            return;

        inorderK(node.left, k, result);
        result.add(node.val);
        inorderK(node.right, k, result);
    }

    // Problem 4: Convert Sorted Array to BST
    static TreeNode sortedArrayToBST(int[] nums) {
        return sortedArrayToBSTHelper(nums, 0, nums.length - 1);
    }

    static TreeNode sortedArrayToBSTHelper(int[] nums, int left, int right) {
        if (left > right)
            return null;

        int mid = left + (right - left) / 2;
        TreeNode node = new TreeNode(nums[mid]);

        node.left = sortedArrayToBSTHelper(nums, left, mid - 1);
        node.right = sortedArrayToBSTHelper(nums, mid + 1, right);

        return node;
    }

    // Problem 5: Range Sum Query
    static int rangeSumBST(TreeNode root, int low, int high) {
        if (root == null)
            return 0;

        int sum = 0;
        if (root.val >= low && root.val <= high) {
            sum += root.val;
        }

        if (root.val > low) {
            sum += rangeSumBST(root.left, low, high);
        }

        if (root.val < high) {
            sum += rangeSumBST(root.right, low, high);
        }

        return sum;
    }

    // Problem 6: Inorder Successor
    static TreeNode inorderSuccessor(TreeNode root, TreeNode p) {
        TreeNode successor = null;

        while (root != null) {
            if (p.val < root.val) {
                successor = root;
                root = root.left;
            } else {
                root = root.right;
            }
        }

        return successor;
    }

    // Problem 7: Delete Node in BST
    static TreeNode deleteNode(TreeNode root, int key) {
        if (root == null)
            return null;

        if (key < root.val) {
            root.left = deleteNode(root.left, key);
        } else if (key > root.val) {
            root.right = deleteNode(root.right, key);
        } else {
            if (root.left == null)
                return root.right;
            if (root.right == null)
                return root.left;

            TreeNode min = findMin(root.right);
            root.val = min.val;
            root.right = deleteNode(root.right, min.val);
        }

        return root;
    }

    static TreeNode findMin(TreeNode node) {
        while (node.left != null)
            node = node.left;
        return node;
    }

    // Helper: Build BST for testing
    static TreeNode buildBST(int[] values) {
        TreeNode root = null;
        for (int val : values) {
            root = insert(root, val);
        }
        return root;
    }

    static TreeNode insert(TreeNode node, int val) {
        if (node == null)
            return new TreeNode(val);
        if (val < node.val)
            node.left = insert(node.left, val);
        else if (val > node.val)
            node.right = insert(node.right, val);
        return node;
    }

    static void inorder(TreeNode node) {
        if (node == null)
            return;
        inorder(node.left);
        System.out.print(node.val + " ");
        inorder(node.right);
    }

    public static void main(String[] args) {
        System.out.println("=== Core BST Problems ===\n");

        // Test 1: Validate BST
        System.out.println("Test 1: Validate BST");
        TreeNode bst1 = buildBST(new int[] { 50, 30, 70, 20, 40, 60, 80 });
        System.out.println("Is valid BST: " + isValidBST(bst1));
        System.out.println();

        // Test 2: LCA
        System.out.println("Test 2: Lowest Common Ancestor");
        TreeNode p = new TreeNode(20);
        TreeNode q = new TreeNode(40);
        TreeNode lca = lowestCommonAncestor(bst1, p, q);
        System.out.println("LCA of 20 and 40: " + (lca != null ? lca.val : "null"));
        System.out.println();

        // Test 3: Kth Smallest
        System.out.println("Test 3: Kth Smallest Element");
        System.out.println("3rd smallest: " + kthSmallest(bst1, 3));
        System.out.println();

        // Test 4: Sorted Array to BST
        System.out.println("Test 4: Convert Sorted Array to BST");
        int[] sorted = { 1, 2, 3, 4, 5, 6, 7 };
        TreeNode balanced = sortedArrayToBST(sorted);
        System.out.print("Inorder of balanced BST: ");
        inorder(balanced);
        System.out.println("\n");

        // Test 5: Range Sum
        System.out.println("Test 5: Range Sum Query");
        int sum = rangeSumBST(bst1, 30, 70);
        System.out.println("Sum in range [30, 70]: " + sum);
        System.out.println();

        // Test 6: Inorder Successor
        System.out.println("Test 6: Inorder Successor");
        TreeNode node = new TreeNode(30);
        TreeNode succ = inorderSuccessor(bst1, node);
        System.out.println("Successor of 30: " + (succ != null ? succ.val : "null"));
    }
}
