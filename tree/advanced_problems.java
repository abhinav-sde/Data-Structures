/**
 * Binary Tree Advanced Problems in Java
 * Contains complex Binary Tree algorithms
 */

import java.util.*;

public class advanced_problems {
    
    // ========================================
    // NODE STRUCTURES
    // ========================================
    static class TreeNode {
        int data;
        TreeNode left;
        TreeNode right;
        TreeNode(int val) { this.data = val; }
    }
    
    static class NodeWithNext {
        int data;
        NodeWithNext left;
        NodeWithNext right;
        NodeWithNext next;
        NodeWithNext(int val) { this.data = val; }
    }
    
    // ========================================
    // 1. SERIALIZE AND DESERIALIZE TREE
    // ========================================
    static String serialize(TreeNode root) {
        if (root == null) return "#";
        
        return root.data + "," + serialize(root.left) + "," + serialize(root.right);
    }
    
    static TreeNode deserializeHelper(Queue<String> nodes) {
        String val = nodes.poll();
        
        if (val.equals("#")) return null;
        
        TreeNode root = new TreeNode(Integer.parseInt(val));
        root.left = deserializeHelper(nodes);
        root.right = deserializeHelper(nodes);
        
        return root;
    }
    
    static TreeNode deserialize(String data) {
        Queue<String> nodes = new LinkedList<>(Arrays.asList(data.split(",")));
        return deserializeHelper(nodes);
    }
    
    // ========================================
    // 2. CONSTRUCT TREE FROM INORDER AND PREORDER
    // ========================================
    static int preIdx = 0;
    
    static TreeNode buildTreeHelper(int[] preorder, int[] inorder, int inStart, int inEnd, Map<Integer, Integer> inMap) {
        if (inStart > inEnd) return null;
        
        int rootVal = preorder[preIdx++];
        TreeNode root = new TreeNode(rootVal);
        
        int inIdx = inMap.get(rootVal);
        
        root.left = buildTreeHelper(preorder, inorder, inStart, inIdx - 1, inMap);
        root.right = buildTreeHelper(preorder, inorder, inIdx + 1, inEnd, inMap);
        
        return root;
    }
    
    static TreeNode buildTree(int[] preorder, int[] inorder) {
        Map<Integer, Integer> inMap = new HashMap<>();
        for (int i = 0; i < inorder.length; i++) {
            inMap.put(inorder[i], i);
        }
        
        preIdx = 0;
        return buildTreeHelper(preorder, inorder, 0, inorder.length - 1, inMap);
    }
    
    // ========================================
    // 3. MAXIMUM PATH SUM
    // ========================================
    static int maxSum = Integer.MIN_VALUE;
    
    static int maxPathSumHelper(TreeNode root) {
        if (root == null) return 0;
        
        int left = Math.max(0, maxPathSumHelper(root.left));
        int right = Math.max(0, maxPathSumHelper(root.right));
        
        maxSum = Math.max(maxSum, left + right + root.data);
        
        return root.data + Math.max(left, right);
    }
    
    static int maxPathSum(TreeNode root) {
        maxSum = Integer.MIN_VALUE;
        maxPathSumHelper(root);
        return maxSum;
    }
    
    // ========================================
    // 4. FLATTEN TREE TO LINKED LIST
    // ========================================
    static void flatten(TreeNode root) {
        if (root == null) return;
        
        flatten(root.left);
        flatten(root.right);
        
        TreeNode rightSubtree = root.right;
        root.right = root.left;
        root.left = null;
        
        TreeNode current = root;
        while (current.right != null) {
            current = current.right;
        }
        current.right = rightSubtree;
    }
    
    // ========================================
    // 5. POPULATE NEXT RIGHT POINTERS
    // ========================================
    static NodeWithNext connect(NodeWithNext root) {
        if (root == null) return null;
        
        Queue<NodeWithNext> q = new LinkedList<>();
        q.add(root);
        
        while (!q.isEmpty()) {
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                NodeWithNext node = q.poll();
                
                if (i < size - 1) {
                    node.next = q.peek();
                }
                
                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
        }
        
        return root;
    }
    
    // ========================================
    // 6. KTH SMALLEST ELEMENT IN BST
    // ========================================
    static int kVal, kResult;
    
    static void kthSmallestHelper(TreeNode root) {
        if (root == null) return;
        
        kthSmallestHelper(root.left);
        
        kVal--;
        if (kVal == 0) {
            kResult = root.data;
            return;
        }
        
        kthSmallestHelper(root.right);
    }
    
    static int kthSmallest(TreeNode root, int k) {
        kVal = k;
        kthSmallestHelper(root);
        return kResult;
    }
    
    // ========================================
    // 7. VALIDATE BST
    // ========================================
    static boolean isValidBSTHelper(TreeNode root, long minVal, long maxVal) {
        if (root == null) return true;
        
        if (root.data <= minVal || root.data >= maxVal) {
            return false;
        }
        
        return isValidBSTHelper(root.left, minVal, root.data) &&
               isValidBSTHelper(root.right, root.data, maxVal);
    }
    
    static boolean isValidBST(TreeNode root) {
        return isValidBSTHelper(root, Long.MIN_VALUE, Long.MAX_VALUE);
    }
    
    // ========================================
    // 8. RECOVER BST
    // ========================================
    static TreeNode first = null, second = null, prev = null;
    
    static void recoverBSTHelper(TreeNode root) {
        if (root == null) return;
        
        recoverBSTHelper(root.left);
        
        if (prev != null && prev.data > root.data) {
            if (first == null) {
                first = prev;
            }
            second = root;
        }
        prev = root;
        
        recoverBSTHelper(root.right);
    }
    
    static void recoverBST(TreeNode root) {
        first = null; second = null; prev = null;
        recoverBSTHelper(root);
        
        if (first != null && second != null) {
            int temp = first.data;
            first.data = second.data;
            second.data = temp;
        }
    }
    
    // ========================================
    // 9. BINARY TREE CAMERAS
    // ========================================
    static int cameras = 0;
    static final int NOT_MONITORED = 0;
    static final int MONITORED = 1;
    static final int HAS_CAMERA = 2;
    
    static int minCamerasHelper(TreeNode root) {
        if (root == null) return MONITORED;
        
        int left = minCamerasHelper(root.left);
        int right = minCamerasHelper(root.right);
        
        if (left == NOT_MONITORED || right == NOT_MONITORED) {
            cameras++;
            return HAS_CAMERA;
        }
        
        if (left == HAS_CAMERA || right == HAS_CAMERA) {
            return MONITORED;
        }
        
        return NOT_MONITORED;
    }
    
    static int minCameraCover(TreeNode root) {
        cameras = 0;
        if (minCamerasHelper(root) == NOT_MONITORED) {
            cameras++;
        }
        return cameras;
    }
    
    // ========================================
    // 10. MORRIS TRAVERSAL (INORDER)
    // ========================================
    static List<Integer> morrisInorder(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode current = root;
        
        while (current != null) {
            if (current.left == null) {
                result.add(current.data);
                current = current.right;
            } else {
                TreeNode predecessor = current.left;
                while (predecessor.right != null && predecessor.right != current) {
                    predecessor = predecessor.right;
                }
                
                if (predecessor.right == null) {
                    predecessor.right = current;
                    current = current.left;
                } else {
                    predecessor.right = null;
                    result.add(current.data);
                    current = current.right;
                }
            }
        }
        
        return result;
    }
    
    // ========================================
    // 11. VERTICAL SUM
    // ========================================
    static void verticalSumHelper(TreeNode root, int col, Map<Integer, Integer> sumMap) {
        if (root == null) return;
        
        sumMap.put(col, sumMap.getOrDefault(col, 0) + root.data);
        
        verticalSumHelper(root.left, col - 1, sumMap);
        verticalSumHelper(root.right, col + 1, sumMap);
    }
    
    static void verticalSum(TreeNode root) {
        Map<Integer, Integer> sumMap = new TreeMap<>();
        verticalSumHelper(root, 0, sumMap);
        
        System.out.println("Vertical Sums:");
        for (Map.Entry<Integer, Integer> entry : sumMap.entrySet()) {
            System.out.println("Column " + entry.getKey() + ": " + entry.getValue());
        }
    }
    
    // ========================================
    // 12. DISTANCE BETWEEN TWO NODES
    // ========================================
    static TreeNode findLCA(TreeNode root, int p, int q) {
        if (root == null || root.data == p || root.data == q) {
            return root;
        }
        
        TreeNode left = findLCA(root.left, p, q);
        TreeNode right = findLCA(root.right, p, q);
        
        if (left != null && right != null) return root;
        return (left != null) ? left : right;
    }
    
    static int findLevel(TreeNode root, int val, int level) {
        if (root == null) return -1;
        if (root.data == val) return level;
        
        int left = findLevel(root.left, val, level + 1);
        if (left != -1) return left;
        
        return findLevel(root.right, val, level + 1);
    }
    
    static int findDistance(TreeNode root, int p, int q) {
        TreeNode lca = findLCA(root, p, q);
        
        int d1 = findLevel(lca, p, 0);
        int d2 = findLevel(lca, q, 0);
        
        return d1 + d2;
    }
    
    // ========================================
    // 13. PRINT ALL K-SUM PATHS
    // ========================================
    static int kSumCount = 0;
    
    static void kSumPathsHelper(TreeNode root, int k, List<Integer> path) {
        if (root == null) return;
        
        path.add(root.data);
        
        int sum = 0;
        for (int i = path.size() - 1; i >= 0; i--) {
            sum += path.get(i);
            if (sum == k) {
                kSumCount++;
            }
        }
        
        kSumPathsHelper(root.left, k, path);
        kSumPathsHelper(root.right, k, path);
        
        path.remove(path.size() - 1);
    }
    
    static int kSumPaths(TreeNode root, int k) {
        kSumCount = 0;
        kSumPathsHelper(root, k, new ArrayList<>());
        return kSumCount;
    }
    
    // ========================================
    // 14. CONVERT BST TO GREATER TREE
    // ========================================
    static int greaterSum = 0;
    
    static void convertBSTHelper(TreeNode root) {
        if (root == null) return;
        
        convertBSTHelper(root.right);
        
        greaterSum += root.data;
        root.data = greaterSum;
        
        convertBSTHelper(root.left);
    }
    
    static TreeNode convertBST(TreeNode root) {
        greaterSum = 0;
        convertBSTHelper(root);
        return root;
    }
    
    // ========================================
    // 15. HOUSE ROBBER III
    // ========================================
    static int[] robHelper(TreeNode root) {
        if (root == null) return new int[]{0, 0};
        
        int[] left = robHelper(root.left);
        int[] right = robHelper(root.right);
        
        int robCurrent = root.data + left[1] + right[1];
        int skipCurrent = Math.max(left[0], left[1]) + Math.max(right[0], right[1]);
        
        return new int[]{robCurrent, skipCurrent};
    }
    
    static int rob(TreeNode root) {
        int[] result = robHelper(root);
        return Math.max(result[0], result[1]);
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Binary Tree Advanced Problems ===");
        
        // Example usage - uncomment to use
        
        // TreeNode root = new TreeNode(1);
        // root.left = new TreeNode(2);
        // root.right = new TreeNode(3);
        // root.left.left = new TreeNode(4);
        // root.left.right = new TreeNode(5);
        
        // 1. Serialize/Deserialize
        // String ser = serialize(root);
        // System.out.println("Serialized: " + ser);
        // TreeNode des = deserialize(ser);
        // System.out.println("Deserialized root: " + des.data);
        
        // 3. Max Path Sum
        // System.out.println("Max Path Sum: " + maxPathSum(root));
        
        // 7. Valid BST
        // System.out.println("Is Valid BST: " + isValidBST(root));
        
        // 9. Camera Cover
        // System.out.println("Min Cameras: " + minCameraCover(root));
        
        // 11. Vertical Sum
        // verticalSum(root);
        
        // 12. Distance
        // System.out.println("Distance between 4 and 5: " + findDistance(root, 4, 5));
        
        // 15. House Robber III
        // System.out.println("Max money robbed: " + rob(root));
    }
}
