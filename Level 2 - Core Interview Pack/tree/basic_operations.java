/**
 * Binary Tree Basic Operations in Java
 * Contains standard Binary Tree operations
 */

import java.util.*;

public class basic_operations {
    
    // ========================================
    // BINARY TREE NODE STRUCTURE
    // ========================================
    static class TreeNode {
        int data;
        TreeNode left;
        TreeNode right;
        
        TreeNode(int val) {
            data = val;
            left = null;
            right = null;
        }
    }
    
    // ========================================
    // 1. CREATE A NEW NODE
    // ========================================
    static TreeNode createNode(int value) {
        return new TreeNode(value);
    }
    
    // ========================================
    // 2. INSERT NODE (LEVEL ORDER)
    // ========================================
    static TreeNode insert(TreeNode root, int value) {
        if (root == null) {
            System.out.println("Inserted " + value + " as root.");
            return createNode(value);
        }
        
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        
        while (!q.isEmpty()) {
            TreeNode temp = q.poll();
            
            if (temp.left == null) {
                temp.left = createNode(value);
                System.out.println("Inserted " + value + " as left child of " + temp.data);
                return root;
            } else {
                q.add(temp.left);
            }
            
            if (temp.right == null) {
                temp.right = createNode(value);
                System.out.println("Inserted " + value + " as right child of " + temp.data);
                return root;
            } else {
                q.add(temp.right);
            }
        }
        
        return root;
    }
    
    // ========================================
    // 3. INORDER TRAVERSAL (Left-Root-Right)
    // ========================================
    static void inorder(TreeNode root) {
        if (root == null) return;
        
        inorder(root.left);
        System.out.print(root.data + " ");
        inorder(root.right);
    }
    
    // ========================================
    // 4. PREORDER TRAVERSAL (Root-Left-Right)
    // ========================================
    static void preorder(TreeNode root) {
        if (root == null) return;
        
        System.out.print(root.data + " ");
        preorder(root.left);
        preorder(root.right);
    }
    
    // ========================================
    // 5. POSTORDER TRAVERSAL (Left-Right-Root)
    // ========================================
    static void postorder(TreeNode root) {
        if (root == null) return;
        
        postorder(root.left);
        postorder(root.right);
        System.out.print(root.data + " ");
    }
    
    // ========================================
    // 6. LEVEL ORDER TRAVERSAL (BFS)
    // ========================================
    static void levelOrder(TreeNode root) {
        if (root == null) return;
        
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        
        while (!q.isEmpty()) {
            TreeNode temp = q.poll();
            System.out.print(temp.data + " ");
            
            if (temp.left != null) {
                q.add(temp.left);
            }
            if (temp.right != null) {
                q.add(temp.right);
            }
        }
    }
    
    // ========================================
    // 7. HEIGHT OF TREE
    // ========================================
    static int height(TreeNode root) {
        if (root == null) return 0;
        
        int leftHeight = height(root.left);
        int rightHeight = height(root.right);
        
        return Math.max(leftHeight, rightHeight) + 1;
    }
    
    // ========================================
    // 8. COUNT NODES
    // ========================================
    static int countNodes(TreeNode root) {
        if (root == null) return 0;
        
        return 1 + countNodes(root.left) + countNodes(root.right);
    }
    
    // ========================================
    // 9. COUNT LEAF NODES
    // ========================================
    static int countLeaves(TreeNode root) {
        if (root == null) return 0;
        
        if (root.left == null && root.right == null) {
            return 1;
        }
        
        return countLeaves(root.left) + countLeaves(root.right);
    }
    
    // ========================================
    // 10. SEARCH FOR A VALUE
    // ========================================
    static boolean search(TreeNode root, int value) {
        if (root == null) return false;
        
        if (root.data == value) return true;
        
        return search(root.left, value) || search(root.right, value);
    }
    
    // ========================================
    // 11. FIND MINIMUM VALUE
    // ========================================
    static int findMin(TreeNode root) {
        if (root == null) {
            System.out.println("Tree is empty!");
            return -1;
        }
        
        int minVal = root.data;
        
        if (root.left != null) {
            minVal = Math.min(minVal, findMin(root.left));
        }
        
        if (root.right != null) {
            minVal = Math.min(minVal, findMin(root.right));
        }
        
        return minVal;
    }
    
    // ========================================
    // 12. FIND MAXIMUM VALUE
    // ========================================
    static int findMax(TreeNode root) {
        if (root == null) {
            System.out.println("Tree is empty!");
            return -1;
        }
        
        int maxVal = root.data;
        
        if (root.left != null) {
            maxVal = Math.max(maxVal, findMax(root.left));
        }
        
        if (root.right != null) {
            maxVal = Math.max(maxVal, findMax(root.right));
        }
        
        return maxVal;
    }
    
    // ========================================
    // 13. DELETE TREE
    // ========================================
    // In Java, Garbage Collection handles memory deallocation.
    // We just need to remove the reference to the root.
    static TreeNode deleteTree(TreeNode root) {
        return null;
    }
    
    // ========================================
    // 14. PRINT TREE STRUCTURE
    // ========================================
    static void printTree(TreeNode root, int space, int indent) {
        if (root == null) return;
        
        space += indent;
        
        printTree(root.right, space, indent);
        
        System.out.println();
        for (int i = indent; i < space; i++) {
            System.out.print(" ");
        }
        System.out.println(root.data);
        
        printTree(root.left, space, indent);
    }
    
    static void printTree(TreeNode root) {
        printTree(root, 0, 4);
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        TreeNode root = null;
        
        System.out.println("=== Binary Tree Basic Operations ===");
        
        // Example usage - uncomment to use
        
        // Create a sample tree
        //       1
        //      / \
        //     2   3
        //    / \
        //   4   5
        
        // root = insert(root, 1);
        // root = insert(root, 2);
        // root = insert(root, 3);
        // root = insert(root, 4);
        // root = insert(root, 5);
        
        // Print tree structure
        // System.out.println("\nTree Structure:");
        // printTree(root);
        
        // Traversals
        // System.out.print("\nInorder: ");
        // inorder(root);
        // System.out.println();
        
        // System.out.print("Preorder: ");
        // preorder(root);
        // System.out.println();
        
        // System.out.print("Postorder: ");
        // postorder(root);
        // System.out.println();
        
        // System.out.print("Level Order: ");
        // levelOrder(root);
        // System.out.println();
        
        // Height
        // System.out.println("\nHeight: " + height(root));
        
        // Count nodes
        // System.out.println("Total nodes: " + countNodes(root));
        
        // Count leaves
        // System.out.println("Leaf nodes: " + countLeaves(root));
        
        // Search
        // boolean found = search(root, 4);
        // System.out.println("Search 4: " + (found ? "Found" : "Not found"));
        
        // Min and Max
        // System.out.println("Min: " + findMin(root) + ", Max: " + findMax(root));
        
        // Delete tree
        // root = deleteTree(root);
        // System.out.println("\nTree deleted.");
    }
}
