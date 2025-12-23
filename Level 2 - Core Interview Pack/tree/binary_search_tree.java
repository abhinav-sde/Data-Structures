/**
 * Binary Search Tree Operations in Java
 * Contains standard BST algorithms
 */

import java.util.*;

public class binary_search_tree {
    
    // ========================================
    // BST NODE STRUCTURE
    // ========================================
    static class BSTNode {
        int data;
        BSTNode left;
        BSTNode right;
        
        BSTNode(int val) {
            data = val;
            left = null;
            right = null;
        }
    }
    
    // ========================================
    // 1. INSERT IN BST
    // ========================================
    static BSTNode insert(BSTNode root, int value) {
        if (root == null) {
            System.out.println("Inserted " + value);
            return new BSTNode(value);
        }
        
        if (value < root.data) {
            root.left = insert(root.left, value);
        } else if (value > root.data) {
            root.right = insert(root.right, value);
        }
        
        return root;
    }
    
    // ========================================
    // 2. SEARCH IN BST
    // ========================================
    static BSTNode search(BSTNode root, int value) {
        if (root == null || root.data == value) {
            return root;
        }
        
        if (value < root.data) {
            return search(root.left, value);
        }
        
        return search(root.right, value);
    }
    
    // ========================================
    // 3. FIND MINIMUM
    // ========================================
    static BSTNode findMin(BSTNode root) {
        if (root == null) return null;
        
        while (root.left != null) {
            root = root.left;
        }
        
        return root;
    }
    
    // ========================================
    // 4. FIND MAXIMUM
    // ========================================
    static BSTNode findMax(BSTNode root) {
        if (root == null) return null;
        
        while (root.right != null) {
            root = root.right;
        }
        
        return root;
    }
    
    // ========================================
    // 5. DELETE NODE IN BST
    // ========================================
    static BSTNode deleteNode(BSTNode root, int value) {
        if (root == null) return null;
        
        if (value < root.data) {
            root.left = deleteNode(root.left, value);
        } else if (value > root.data) {
            root.right = deleteNode(root.right, value);
        } else {
            // Node found
            
            // Case 1: Leaf node (no children)
            if (root.left == null && root.right == null) {
                return null;
            }
            
            // Case 2: One child
            if (root.left == null) {
                return root.right;
            }
            if (root.right == null) {
                return root.left;
            }
            
            // Case 3: Two children
            BSTNode successor = findMin(root.right);
            root.data = successor.data;
            root.right = deleteNode(root.right, successor.data);
        }
        
        return root;
    }
    
    // ========================================
    // 6. INORDER SUCCESSOR
    // ========================================
    static BSTNode inorderSuccessor(BSTNode root, BSTNode node) {
        if (node.right != null) {
            return findMin(node.right);
        }
        
        BSTNode successor = null;
        while (root != null) {
            if (node.data < root.data) {
                successor = root;
                root = root.left;
            } else if (node.data > root.data) {
                root = root.right;
            } else {
                break;
            }
        }
        
        return successor;
    }
    
    // ========================================
    // 7. INORDER PREDECESSOR
    // ========================================
    static BSTNode inorderPredecessor(BSTNode root, BSTNode node) {
        if (node.left != null) {
            return findMax(node.left);
        }
        
        BSTNode predecessor = null;
        while (root != null) {
            if (node.data > root.data) {
                predecessor = root;
                root = root.right;
            } else if (node.data < root.data) {
                root = root.left;
            } else {
                break;
            }
        }
        
        return predecessor;
    }
    
    // ========================================
    // 8. VALIDATE BST
    // ========================================
    static boolean isValidBSTHelper(BSTNode root, long min, long max) {
        if (root == null) return true;
        
        if (root.data <= min || root.data >= max) {
            return false;
        }
        
        return isValidBSTHelper(root.left, min, root.data) &&
               isValidBSTHelper(root.right, root.data, max);
    }
    
    static boolean isValidBST(BSTNode root) {
        return isValidBSTHelper(root, Long.MIN_VALUE, Long.MAX_VALUE);
    }
    
    // ========================================
    // 9. LOWEST COMMON ANCESTOR IN BST
    // ========================================
    static BSTNode lowestCommonAncestor(BSTNode root, int p, int q) {
        if (root == null) return null;
        
        if (p < root.data && q < root.data) {
            return lowestCommonAncestor(root.left, p, q);
        }
        
        if (p > root.data && q > root.data) {
            return lowestCommonAncestor(root.right, p, q);
        }
        
        return root;
    }
    
    // ========================================
    // 10. KTH SMALLEST ELEMENT
    // ========================================
    static int kVal, kResult;
    
    static void kthSmallestHelper(BSTNode root) {
        if (root == null) return;
        
        kthSmallestHelper(root.left);
        
        kVal--;
        if (kVal == 0) {
            kResult = root.data;
            return;
        }
        
        kthSmallestHelper(root.right);
    }
    
    static int kthSmallest(BSTNode root, int k) {
        kVal = k;
        kthSmallestHelper(root);
        return kResult;
    }
    
    // ========================================
    // 11. CONVERT SORTED ARRAY TO BST
    // ========================================
    static BSTNode sortedArrayToBST(int[] arr, int start, int end) {
        if (start > end) return null;
        
        int mid = start + (end - start) / 2;
        BSTNode root = new BSTNode(arr[mid]);
        
        root.left = sortedArrayToBST(arr, start, mid - 1);
        root.right = sortedArrayToBST(arr, mid + 1, end);
        
        return root;
    }
    
    // ========================================
    // 12. RANGE SUM IN BST
    // ========================================
    static int rangeSumBST(BSTNode root, int low, int high) {
        if (root == null) return 0;
        
        if (root.data < low) {
            return rangeSumBST(root.right, low, high);
        }
        
        if (root.data > high) {
            return rangeSumBST(root.left, low, high);
        }
        
        return root.data + 
               rangeSumBST(root.left, low, high) + 
               rangeSumBST(root.right, low, high);
    }
    
    // ========================================
    // 13. INORDER TRAVERSAL (SORTED ORDER)
    // ========================================
    static void inorder(BSTNode root) {
        if (root == null) return;
        
        inorder(root.left);
        System.out.print(root.data + " ");
        inorder(root.right);
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        BSTNode root = null;
        
        System.out.println("=== Binary Search Tree Operations ===");
        
        // Example usage - uncomment to use
        
        // Insert nodes
        // root = insert(root, 50);
        // root = insert(root, 30);
        // root = insert(root, 70);
        // root = insert(root, 20);
        // root = insert(root, 40);
        // root = insert(root, 60);
        // root = insert(root, 80);
        
        // Inorder (sorted)
        // System.out.print("Inorder: ");
        // inorder(root);
        // System.out.println();
        
        // Search
        // BSTNode found = search(root, 40);
        // System.out.println("Search 40: " + (found != null ? "Found" : "Not found"));
        
        // Min and Max
        // BSTNode minNode = findMin(root);
        // BSTNode maxNode = findMax(root);
        // if (minNode != null) System.out.println("Min: " + minNode.data);
        // if (maxNode != null) System.out.println("Max: " + maxNode.data);
        
        // Delete
        // root = deleteNode(root, 30);
        // System.out.print("After deleting 30: ");
        // inorder(root);
        // System.out.println();
        
        // Validate BST
        // boolean valid = isValidBST(root);
        // System.out.println("Is valid BST: " + (valid ? "Yes" : "No"));
        
        // LCA
        // BSTNode lca = lowestCommonAncestor(root, 20, 40);
        // if (lca != null) System.out.println("LCA of 20 and 40: " + lca.data);
        
        // Kth smallest
        // int kth = kthSmallest(root, 3);
        // System.out.println("3rd smallest: " + kth);
        
        // Range sum
        // int sum = rangeSumBST(root, 30, 70);
        // System.out.println("Sum in range [30, 70]: " + sum);
        
        // Convert sorted array to BST
        // int[] arr = {1, 2, 3, 4, 5, 6, 7};
        // BSTNode balancedBST = sortedArrayToBST(arr, 0, 6);
        // System.out.println("Balanced BST created from sorted array");
    }
}
