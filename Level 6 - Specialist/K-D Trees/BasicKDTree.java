/**
 * Basic K-D Tree Implementation in Java
 * Standard K-D Tree with sequential insertion
 */

import java.util.*;

class Point {
    double[] coords;
    String data;
    
    public Point(double[] coords, String data) {
        this.coords = coords.clone();
        this.data = data;
    }
    
    public int dimensions() {
        return coords.length;
    }
    
    public double distanceTo(Point other) {
        double sum = 0;
        for (int i = 0; i < coords.length; i++) {
            double diff = coords[i] - other.coords[i];
            sum += diff * diff;
        }
        return Math.sqrt(sum);
    }
    
    @Override
    public String toString() {
        return Arrays.toString(coords) + (data != null ? " - " + data : "");
    }
}

class KDTreeNode {
    Point point;
    KDTreeNode left, right;
    
    public KDTreeNode(Point point) {
        this.point = point;
    }
}

public class BasicKDTree {
    private KDTreeNode root;
    private int k;
    
    public BasicKDTree(int k) {
        this.k = k;
    }
    
    public void insert(Point point) {
        root = insertHelper(root, point, 0);
    }
    
    private KDTreeNode insertHelper(KDTreeNode node, Point point, int depth) {
        if (node == null) {
            return new KDTreeNode(point);
        }
        
        int axis = depth % k;
        
        if (point.coords[axis] < node.point.coords[axis]) {
            node.left = insertHelper(node.left, point, depth + 1);
        } else {
            node.right = insertHelper(node.right, point, depth + 1);
        }
        
        return node;
    }
    
    public Point nearestNeighbor(Point target) {
        if (root == null) return null;
        
        Point[] best = new Point[]{null};
        double[] bestDist = new double[]{Double.MAX_VALUE};
        
        nearestHelper(root, target, best, bestDist, 0);
        
        return best[0];
    }
    
    private void nearestHelper(KDTreeNode node, Point target, 
                              Point[] best, double[] bestDist, int depth) {
        if (node == null) return;
        
        double dist = node.point.distanceTo(target);
        if (dist < bestDist[0]) {
            bestDist[0] = dist;
            best[0] = node.point;
        }
        
        int axis = depth % k;
        double diff = target.coords[axis] - node.point.coords[axis];
        
        KDTreeNode nearSubtree = (diff < 0) ? node.left : node.right;
        KDTreeNode farSubtree = (diff < 0) ? node.right : node.left;
        
        nearestHelper(nearSubtree, target, best, bestDist, depth + 1);
        
        if (Math.abs(diff) < bestDist[0]) {
            nearestHelper(farSubtree, target, best, bestDist, depth + 1);
        }
    }
    
    public List<Point> rangeQuery(Point lower, Point upper) {
        List<Point> results = new ArrayList<>();
        rangeQueryHelper(root, lower, upper, results, 0);
        return results;
    }
    
    private void rangeQueryHelper(KDTreeNode node, Point lower, Point upper,
                                  List<Point> results, int depth) {
        if (node == null) return;
        
        boolean inRange = true;
        for (int i = 0; i < k; i++) {
            if (node.point.coords[i] < lower.coords[i] || 
                node.point.coords[i] > upper.coords[i]) {
                inRange = false;
                break;
            }
        }
        if (inRange) {
            results.add(node.point);
        }
        
        int axis = depth % k;
        
        if (lower.coords[axis] <= node.point.coords[axis]) {
            rangeQueryHelper(node.left, lower, upper, results, depth + 1);
        }
        if (upper.coords[axis] >= node.point.coords[axis]) {
            rangeQueryHelper(node.right, lower, upper, results, depth + 1);
        }
    }
    
    public static void main(String[] args) {
        System.out.println("=== Basic K-D Tree Demo ===\n");
        
        BasicKDTree kdtree = new BasicKDTree(2);
        
        Point[] points = {
            new Point(new double[]{7, 2}, "A"),
            new Point(new double[]{5, 4}, "B"),
            new Point(new double[]{9, 6}, "C"),
            new Point(new double[]{2, 3}, "D"),
            new Point(new double[]{4, 7}, "E"),
            new Point(new double[]{8, 1}, "F")
        };
        
        System.out.println("Inserting points:");
        for (Point p : points) {
            kdtree.insert(p);
            System.out.println("  " + p);
        }
        
        System.out.println("\nNearest neighbor to (6, 3):");
        Point target = new Point(new double[]{6, 3}, null);
        Point nearest = kdtree.nearestNeighbor(target);
        if (nearest != null) {
            System.out.println("  " + nearest + " at distance " + 
                              target.distanceTo(nearest));
        }
        
        System.out.println("\nRange query [3, 8] x [2, 6]:");
        Point lower = new Point(new double[]{3, 2}, null);
        Point upper = new Point(new double[]{8, 6}, null);
        List<Point> results = kdtree.rangeQuery(lower, upper);
        System.out.println("  Found " + results.size() + " points:");
        for (Point p : results) {
            System.out.println("    " + p);
        }
    }
}
