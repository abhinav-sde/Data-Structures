/**
 * Binary Tree Core Problems in Java
 * Contains standard Binary Tree algorithms
 */

import java.util.*;

public class core_problems {
    
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
    // 1. MAXIMUM DEPTH / HEIGHT
    // ========================================
    static int maxDepth(TreeNode root) {
        if (root == null) return 0;
        
        return 1 + Math.max(maxDepth(root.left), maxDepth(root.right));
    }
    
    // ========================================
    // 2. MINIMUM DEPTH
    // ========================================
    static int minDepth(TreeNode root) {
        if (root == null) return 0;
        
        if (root.left == null && root.right == null) {
            return 1;
        }
        
        if (root.left == null) {
            return 1 + minDepth(root.right);
        }
        
        if (root.right == null) {
            return 1 + minDepth(root.left);
        }
        
        return 1 + Math.min(minDepth(root.left), minDepth(root.right));
    }
    
    // ========================================
    // 3. DIAMETER OF TREE
    // ========================================
    static class HeightDiameter {
        int diameter;
    }
    
    static int diameterHelper(TreeNode root, HeightDiameter hd) {
        if (root == null) return 0;
        
        int leftHeight = diameterHelper(root.left, hd);
        int rightHeight = diameterHelper(root.right, hd);
        
        hd.diameter = Math.max(hd.diameter, leftHeight + rightHeight);
        
        return 1 + Math.max(leftHeight, rightHeight);
    }
    
    static int diameter(TreeNode root) {
        HeightDiameter hd = new HeightDiameter();
        hd.diameter = 0;
        diameterHelper(root, hd);
        return hd.diameter;
    }
    
    // ========================================
    // 4. CHECK IF BALANCED
    // ========================================
    static class BalancedStatus {
        boolean isBalanced = true;
    }
    
    static int checkHeight(TreeNode root, BalancedStatus bs) {
        if (root == null) return 0;
        
        int leftHeight = checkHeight(root.left, bs);
        int rightHeight = checkHeight(root.right, bs);
        
        if (Math.abs(leftHeight - rightHeight) > 1) {
            bs.isBalanced = false;
        }
        
        return 1 + Math.max(leftHeight, rightHeight);
    }
    
    static boolean isBalanced(TreeNode root) {
        BalancedStatus bs = new BalancedStatus();
        checkHeight(root, bs);
        return bs.isBalanced;
    }
    
    // ========================================
    // 5. CHECK IF SYMMETRIC (MIRROR)
    // ========================================
    static boolean isMirror(TreeNode left, TreeNode right) {
        if (left == null && right == null) return true;
        if (left == null || right == null) return false;
        
        return (left.data == right.data) &&
               isMirror(left.left, right.right) &&
               isMirror(left.right, right.left);
    }
    
    static boolean isSymmetric(TreeNode root) {
        if (root == null) return true;
        return isMirror(root.left, root.right);
    }
    
    // ========================================
    // 6. INVERT/MIRROR TREE
    // ========================================
    static TreeNode invertTree(TreeNode root) {
        if (root == null) return null;
        
        TreeNode temp = root.left;
        root.left = root.right;
        root.right = temp;
        
        invertTree(root.left);
        invertTree(root.right);
        
        return root;
    }
    
    // ========================================
    // 7. LOWEST COMMON ANCESTOR (LCA)
    // ========================================
    static TreeNode findLCA(TreeNode root, int p, int q) {
        if (root == null) return null;
        
        if (root.data == p || root.data == q) {
            return root;
        }
        
        TreeNode left = findLCA(root.left, p, q);
        TreeNode right = findLCA(root.right, p, q);
        
        if (left != null && right != null) {
            return root;
        }
        
        return (left != null) ? left : right;
    }
    
    // ========================================
    // 8. PATH SUM
    // ========================================
    static boolean hasPathSum(TreeNode root, int targetSum) {
        if (root == null) return false;
        
        if (root.left == null && root.right == null) {
            return root.data == targetSum;
        }
        
        return hasPathSum(root.left, targetSum - root.data) ||
               hasPathSum(root.right, targetSum - root.data);
    }
    
    // ========================================
    // 9. ALL ROOT-TO-LEAF PATHS
    // ========================================
    static void findPaths(TreeNode root, List<Integer> path, List<List<Integer>> paths) {
        if (root == null) return;
        
        path.add(root.data);
        
        if (root.left == null && root.right == null) {
            paths.add(new ArrayList<>(path));
        } else {
            findPaths(root.left, path, paths);
            findPaths(root.right, path, paths);
        }
        
        path.remove(path.size() - 1);
    }
    
    static List<List<Integer>> allPaths(TreeNode root) {
        List<List<Integer>> paths = new ArrayList<>();
        List<Integer> path = new ArrayList<>();
        findPaths(root, path, paths);
        return paths;
    }
    
    // ========================================
    // 10. LEVEL ORDER TRAVERSAL (BY LEVELS)
    // ========================================
    static List<List<Integer>> levelOrderByLevels(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;
        
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        
        while (!q.isEmpty()) {
            int size = q.size();
            List<Integer> level = new ArrayList<>();
            
            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                level.add(node.data);
                
                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
            
            result.add(level);
        }
        
        return result;
    }
    
    // ========================================
    // 11. ZIGZAG LEVEL ORDER
    // ========================================
    static List<List<Integer>> zigzagLevelOrder(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;
        
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        boolean leftToRight = true;
        
        while (!q.isEmpty()) {
            int size = q.size();
            List<Integer> level = new ArrayList<>();
            
            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                
                if (leftToRight) {
                   level.add(node.data);
                } else {
                   level.add(0, node.data);
                }
                
                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
            
            result.add(level);
            leftToRight = !leftToRight;
        }
        
        return result;
    }
    
    // ========================================
    // 12. RIGHT SIDE VIEW
    // ========================================
    static List<Integer> rightSideView(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) return result;
        
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        
        while (!q.isEmpty()) {
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                
                if (i == size - 1) {
                    result.add(node.data);
                }
                
                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
        }
        
        return result;
    }
    
    // ========================================
    // 13. LEFT SIDE VIEW
    // ========================================
    static List<Integer> leftSideView(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) return result;
        
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        
        while (!q.isEmpty()) {
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                
                if (i == 0) {
                    result.add(node.data);
                }
                
                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
        }
        
        return result;
    }
    
    // ========================================
    // 14. VERTICAL ORDER TRAVERSAL
    // ========================================
    static void verticalOrderHelper(TreeNode root, int col, TreeMap<Integer, List<Integer>> m) {
        if (root == null) return;
        
        m.putIfAbsent(col, new ArrayList<>());
        m.get(col).add(root.data);
        
        verticalOrderHelper(root.left, col - 1, m);
        verticalOrderHelper(root.right, col + 1, m);
    }
    
    static void verticalOrder(TreeNode root) {
        TreeMap<Integer, List<Integer>> m = new TreeMap<>();
        verticalOrderHelper(root, 0, m);
        
        System.out.println("Vertical Order:");
        for (Map.Entry<Integer, List<Integer>> entry : m.entrySet()) {
            System.out.print("Column " + entry.getKey() + ": ");
            for (int val : entry.getValue()) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }
    
    // ========================================
    // 15. BOUNDARY TRAVERSAL
    // ========================================
    static void printLeftBoundary(TreeNode root) {
        if (root == null) return;
        if (root.left != null || root.right != null) {
            System.out.print(root.data + " ");
        }
        if (root.left != null) {
            printLeftBoundary(root.left);
        } else {
            printLeftBoundary(root.right);
        }
    }
    
    static void printLeaves(TreeNode root) {
        if (root == null) return;
        
        printLeaves(root.left);
        
        if (root.left == null && root.right == null) {
            System.out.print(root.data + " ");
        }
        
        printLeaves(root.right);
    }
    
    static void printRightBoundary(TreeNode root) {
        if (root == null) return;
        
        if (root.right != null) {
            printRightBoundary(root.right);
        } else {
            printRightBoundary(root.left);
        }
        
        if (root.left != null || root.right != null) {
            System.out.print(root.data + " ");
        }
    }
    
    static void boundaryTraversal(TreeNode root) {
        if (root == null) return;
        
        System.out.print("Boundary: " + root.data + " ");
        
        printLeftBoundary(root.left);
        printLeaves(root.left);
        printLeaves(root.right);
        printRightBoundary(root.right);
        
        System.out.println();
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Binary Tree Core Problems ===");
        
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        
        // Example usage - uncomment to use
        
        // 1. Max Depth
        // System.out.println("Max Depth: " + maxDepth(root));
        
        // 2. Min Depth
        // System.out.println("Min Depth: " + minDepth(root));
        
        // 3. Diameter
        // System.out.println("Diameter: " + diameter(root));
        
        // 4. Is Balanced
        // System.out.println("Is Balanced: " + (isBalanced(root) ? "Yes" : "No"));
        
        // 5. Is Symmetric
        // System.out.println("Is Symmetric: " + (isSymmetric(root) ? "Yes" : "No"));
        
        // 7. LCA
        // TreeNode lca = findLCA(root, 4, 5);
        // System.out.println("LCA of 4 and 5: " + lca.data);
        
        // 8. Path Sum
        // System.out.println("Has path sum 7: " + (hasPathSum(root, 7) ? "Yes" : "No"));
        
        // 9. All Paths
        // System.out.println("All paths: " + allPaths(root));
        
        // 10. Level Order by Levels
        // System.out.println("Level Order: " + levelOrderByLevels(root));
        
        // 11. Zigzag Level Order
        // System.out.println("Zigzag Order: " + zigzagLevelOrder(root));
        
        // 12. Right Side View
        // System.out.println("Right View: " + rightSideView(root));
        
        // 14. Vertical Order
        // verticalOrder(root);
        
        // 15. Boundary Traversal
        // boundaryTraversal(root);
    }
}
