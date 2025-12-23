/**
 * AVL Tree Operations in Java
 * Contains AVL Tree implementation and algorithms
 */

import java.util.*;

public class avl_tree {
    
    // ========================================
    // AVL TREE NODE STRUCTURE
    // ========================================
    static class AVLNode {
        int data;
        AVLNode left;
        AVLNode right;
        int height;
        
        AVLNode(int val) {
            data = val;
            left = null;
            right = null;
            height = 1;
        }
    }
    
    // ========================================
    // UTILITY FUNCTIONS
    // ========================================
    
    static int height(AVLNode node) {
        return node == null ? 0 : node.height;
    }
    
    static int getBalance(AVLNode node) {
        return node == null ? 0 : height(node.left) - height(node.right);
    }
    
    static void updateHeight(AVLNode node) {
        if (node != null) {
            node.height = 1 + Math.max(height(node.left), height(node.right));
        }
    }
    
    // ========================================
    // ROTATIONS
    // ========================================
    
    static AVLNode rightRotate(AVLNode y) {
        AVLNode x = y.left;
        AVLNode T2 = x.right;
        
        // Perform rotation
        x.right = y;
        y.left = T2;
        
        // Update heights
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    static AVLNode leftRotate(AVLNode x) {
        AVLNode y = x.right;
        AVLNode T2 = y.left;
        
        // Perform rotation
        y.left = x;
        x.right = T2;
        
        // Update heights
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    // ========================================
    // 1. INSERT IN AVL TREE
    // ========================================
    static AVLNode insert(AVLNode root, int value) {
        if (root == null) {
            System.out.println("Inserted " + value);
            return new AVLNode(value);
        }
        
        if (value < root.data) {
            root.left = insert(root.left, value);
        } else if (value > root.data) {
            root.right = insert(root.right, value);
        } else {
            return root; // Duplicates not allowed
        }
        
        updateHeight(root);
        
        int balance = getBalance(root);
        
        // Left Left Case
        if (balance > 1 && value < root.left.data) {
            System.out.println("LL Rotation at " + root.data);
            return rightRotate(root);
        }
        
        // Right Right Case
        if (balance < -1 && value > root.right.data) {
            System.out.println("RR Rotation at " + root.data);
            return leftRotate(root);
        }
        
        // Left Right Case
        if (balance > 1 && value > root.left.data) {
            System.out.println("LR Rotation at " + root.data);
            root.left = leftRotate(root.left);
            return rightRotate(root);
        }
        
        // Right Left Case
        if (balance < -1 && value < root.right.data) {
            System.out.println("RL Rotation at " + root.data);
            root.right = rightRotate(root.right);
            return leftRotate(root);
        }
        
        return root;
    }
    
    // ========================================
    // 2. DELETE FROM AVL TREE
    // ========================================
    static AVLNode findMin(AVLNode node) {
        while (node.left != null) {
            node = node.left;
        }
        return node;
    }
    
    static AVLNode deleteNode(AVLNode root, int value) {
        if (root == null) return null;
        
        if (value < root.data) {
            root.left = deleteNode(root.left, value);
        } else if (value > root.data) {
            root.right = deleteNode(root.right, value);
        } else {
            // Node found
            if (root.left == null || root.right == null) {
                AVLNode temp = (root.left != null) ? root.left : root.right;
                
                if (temp == null) {
                    temp = root;
                    root = null;
                } else {
                    root = temp; // Copy contents
                }
                System.out.println("Deleted " + value);
            } else {
                AVLNode temp = findMin(root.right);
                root.data = temp.data;
                root.right = deleteNode(root.right, temp.data);
            }
        }
        
        if (root == null) return null;
        
        updateHeight(root);
        
        int balance = getBalance(root);
        
        // Left Left Case
        if (balance > 1 && getBalance(root.left) >= 0) {
            return rightRotate(root);
        }
        
        // Left Right Case
        if (balance > 1 && getBalance(root.left) < 0) {
            root.left = leftRotate(root.left);
            return rightRotate(root);
        }
        
        // Right Right Case
        if (balance < -1 && getBalance(root.right) <= 0) {
            return leftRotate(root);
        }
        
        // Right Left Case
        if (balance < -1 && getBalance(root.right) > 0) {
            root.right = rightRotate(root.right);
            return leftRotate(root);
        }
        
        return root;
    }
    
    // ========================================
    // 3. SEARCH IN AVL TREE
    // ========================================
    static AVLNode search(AVLNode root, int value) {
        if (root == null || root.data == value) {
            return root;
        }
        
        if (value < root.data) {
            return search(root.left, value);
        }
        
        return search(root.right, value);
    }
    
    // ========================================
    // 4. CHECK IF BALANCED
    // ========================================
    static boolean isBalanced(AVLNode root) {
        if (root == null) return true;
        
        int balance = getBalance(root);
        
        if (Math.abs(balance) > 1) return false;
        
        return isBalanced(root.left) && isBalanced(root.right);
    }
    
    // ========================================
    // 5. INORDER TRAVERSAL
    // ========================================
    static void inorder(AVLNode root) {
        if (root == null) return;
        
        inorder(root.left);
        System.out.print(root.data + " ");
        inorder(root.right);
    }
    
    // ========================================
    // 6. PREORDER TRAVERSAL
    // ========================================
    static void preorder(AVLNode root) {
        if (root == null) return;
        
        System.out.print(root.data + " ");
        preorder(root.left);
        preorder(root.right);
    }
    
    // ========================================
    // 7. PRINT TREE WITH HEIGHTS
    // ========================================
    static void printTree(AVLNode root, int space, int indent) {
        if (root == null) return;
        
        space += indent;
        
        printTree(root.right, space, indent);
        
        System.out.println();
        for (int i = indent; i < space; i++) {
            System.out.print(" ");
        }
        System.out.println(root.data + "(h=" + root.height + ",b=" + getBalance(root) + ")");
        
        printTree(root.left, space, indent);
    }
    
    static void printTree(AVLNode root) {
        printTree(root, 0, 4);
    }
    
    // ========================================
    // 8. COUNT NODES
    // ========================================
    static int countNodes(AVLNode root) {
        if (root == null) return 0;
        return 1 + countNodes(root.left) + countNodes(root.right);
    }
    
    // ========================================
    // 9. FIND KTH SMALLEST
    // ========================================
    static int kVal, kResult;
    
    static void kthSmallestHelper(AVLNode root) {
        if (root == null) return;
        
        kthSmallestHelper(root.left);
        
        kVal--;
        if (kVal == 0) {
            kResult = root.data;
            return;
        }
        
        kthSmallestHelper(root.right);
    }
    
    static int kthSmallest(AVLNode root, int k) {
        kVal = k;
        kResult = -1;
        kthSmallestHelper(root);
        return kResult;
    }
    
    // ========================================
    // 10. RANGE QUERY
    // ========================================
    static void rangeQuery(AVLNode root, int low, int high) {
        if (root == null) return;
        
        if (root.data > low) {
            rangeQuery(root.left, low, high);
        }
        
        if (root.data >= low && root.data <= high) {
            System.out.print(root.data + " ");
        }
        
        if (root.data < high) {
            rangeQuery(root.right, low, high);
        }
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        AVLNode root = null;
        
        System.out.println("=== AVL Tree Operations ===");
        
        // Example usage - uncomment to use
        
        // Insert nodes
        // root = insert(root, 10);
        // root = insert(root, 20);
        // root = insert(root, 30);
        // root = insert(root, 40);
        // root = insert(root, 50);
        // root = insert(root, 25);
        
        // Print tree structure
        // System.out.println("\nTree Structure:");
        // printTree(root);
        
        // Inorder (sorted)
        // System.out.print("\nInorder: ");
        // inorder(root);
        // System.out.println();
        
        // Check if balanced
        // boolean balanced = isBalanced(root);
        // System.out.println("Is balanced: " + (balanced ? "Yes" : "No"));
        
        // Search
        // AVLNode found = search(root, 25);
        // System.out.println("Search 25: " + (found != null ? "Found" : "Not found"));
        
        // Count nodes
        // System.out.println("Total nodes: " + countNodes(root));
        
        // Delete node
        // root = deleteNode(root, 20);
        // System.out.println("\nAfter deleting 20:");
        // printTree(root);
        
        // Kth smallest
        // int kth = kthSmallest(root, 3);
        // System.out.println("3rd smallest: " + kth);
        
        // Range query
        // System.out.print("Range [20, 40]: ");
        // rangeQuery(root, 20, 40);
        // System.out.println();
    }
}
