/**
 * Range K-D Tree Implementation in Java (Simplified)
 * Enhanced for efficient range queries with bounding box optimization
 */

import java.util.*;

class BoundingBox {
    double[] lower, upper;
    int k;
    
    public BoundingBox(int k) {
        this.k = k;
        lower = new double[k];
        upper = new double[k];
    }
    
    public boolean intersects(BoundingBox other) {
        for (int i = 0; i < k; i++) {
            if (upper[i] < other.lower[i] || lower[i] > other.upper[i]) {
                return false;
            }
        }
        return true;
    }
    
    public boolean contains(Point p) {
        for (int i = 0; i < k; i++) {
            if (p.coords[i] < lower[i] || p.coords[i] > upper[i]) {
                return false;
            }
        }
        return true;
    }
}

class RangeKDTreeNode {
    Point point;
    BoundingBox bbox;
    RangeKDTreeNode left, right;
    
    public RangeKDTreeNode(Point point, int k) {
        this.point = point;
        this.bbox = new BoundingBox(k);
        Arrays.fill(bbox.lower, point.coords[0]);
        Arrays.fill(bbox.upper, point.coords[0]);
        for (int i = 0; i < k; i++) {
            bbox.lower[i] = bbox.upper[i] = point.coords[i];
        }
    }
    
    public void updateBBox() {
        for (int i = 0; i < bbox.k; i++) {
            bbox.lower[i] = bbox.upper[i] = point.coords[i];
            
            if (left != null) {
                bbox.lower[i] = Math.min(bbox.lower[i], left.bbox.lower[i]);
                bbox.upper[i] = Math.max(bbox.upper[i], left.bbox.upper[i]);
            }
            if (right != null) {
                bbox.lower[i] = Math.min(bbox.lower[i], right.bbox.lower[i]);
                bbox.upper[i] = Math.max(bbox.upper[i], right.bbox.upper[i]);
            }
        }
    }
}

public class RangeKDTree {
    private RangeKDTreeNode root;
    private int k;
    
    public RangeKDTree(int k) {
        this.k = k;
    }
    
    public void build(List<Point> points) {
        root = buildTree(new ArrayList<>(points), 0, points.size() - 1, 0);
    }
    
    private RangeKDTreeNode buildTree(List<Point> points, int start, int end, int depth) {
        if (start > end) return null;
        
        int axis = depth % k;
        points.subList(start, end + 1).sort(
            Comparator.comparingDouble(p -> p.coords[axis]));
        
        int median = start + (end - start) / 2;
        RangeKDTreeNode node = new RangeKDTreeNode(points.get(median), k);
        
        node.left = buildTree(points, start, median - 1, depth + 1);
        node.right = buildTree(points, median + 1, end, depth + 1);
        
        node.updateBBox();
        return node;
    }
    
    public List<Point> rangeQuery(Point lower, Point upper) {
        List<Point> results = new ArrayList<>();
        BoundingBox query = new BoundingBox(k);
        query.lower = lower.coords;
        query.upper = upper.coords;
        
        int[] visited = new int[]{0};
        rangeQueryHelper(root, query, results, visited);
        
        System.out.println("  (Visited " + visited[0] + " nodes)");
        return results;
    }
    
    private void rangeQueryHelper(RangeKDTreeNode node, BoundingBox query,
                                  List<Point> results, int[] visited) {
        if (node == null) return;
        
        visited[0]++;
        
        // Early rejection using bounding box
        if (!node.bbox.intersects(query)) {
            return;
        }
        
        if (query.contains(node.point)) {
            results.add(node.point);
        }
        
        rangeQueryHelper(node.left, query, results, visited);
        rangeQueryHelper(node.right, query, results, visited);
    }
    
    public static void main(String[] args) {
        System.out.println("=== Range K-D Tree Demo ===\n");
        
        RangeKDTree kdtree = new RangeKDTree(2);
        
        List<Point> points = Arrays.asList(
            new Point(new double[]{2, 3}, "A"),
            new Point(new double[]{5, 4}, "B"),
            new Point(new double[]{9, 6}, "C"),
            new Point(new double[]{4, 7}, "D"),
            new Point(new double[]{8, 1}, "E")
        );
        
        System.out.println("Building range-optimized tree...");
        kdtree.build(points);
        
        System.out.println("\nRange query [3, 8] x [2, 7]:");
        Point lower = new Point(new double[]{3, 2}, null);
        Point upper = new Point(new double[]{8, 7}, null);
        List<Point> results = kdtree.rangeQuery(lower, upper);
        
        System.out.println("  Found " + results.size() + " points:");
        for (Point p : results) {
            System.out.println("    " + p);
        }
        
        System.out.println("\nOptimization: Bounding boxes enable early rejection!");
    }
}
