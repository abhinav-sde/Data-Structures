/**
 * Adaptive K-D Tree Implementation in Java
 * Uses variance-based dimension selection
 */

import java.util.*;

class AdaptiveKDTreeNode {
    Point point;
    int splitAxis;
    AdaptiveKDTreeNode left, right;
    
    public AdaptiveKDTreeNode(Point point, int axis) {
        this.point = point;
        this.splitAxis = axis;
    }
}

public class AdaptiveKDTree {
    private AdaptiveKDTreeNode root;
    private int k;
    
    public AdaptiveKDTree(int k) {
        this.k = k;
    }
    
    public void build(List<Point> points) {
        root = buildTree(new ArrayList<>(points), 0, points.size() - 1);
    }
    
    private double calculateVariance(List<Point> points, int start, int end, int axis) {
        if (start > end) return 0;
        
        double sum = 0, sumSq = 0;
        int count = end - start + 1;
        
        for (int i = start; i <= end; i++) {
            double val = points.get(i).coords[axis];
            sum += val;
            sumSq += val * val;
        }
        
        double mean = sum / count;
        return (sumSq / count) - (mean * mean);
    }
    
    private int chooseSplitAxis(List<Point> points, int start, int end) {
        int bestAxis = 0;
        double maxVariance = -1;
        
        for (int axis = 0; axis < k; axis++) {
            double variance = calculateVariance(points, start, end, axis);
            if (variance > maxVariance) {
                maxVariance = variance;
                bestAxis = axis;
            }
        }
        
        return bestAxis;
    }
    
    private AdaptiveKDTreeNode buildTree(List<Point> points, int start, int end) {
        if (start > end) return null;
        
        // Choose axis with maximum variance
        int axis = chooseSplitAxis(points, start, end);
        
        points.subList(start, end + 1).sort(
            Comparator.comparingDouble(p -> p.coords[axis]));
        
        int median = start + (end - start) / 2;
        AdaptiveKDTreeNode node = new AdaptiveKDTreeNode(points.get(median), axis);
        
        node.left = buildTree(points, start, median - 1);
        node.right = buildTree(points, median + 1, end);
        
        return node;
    }
    
    public Point nearestNeighbor(Point target) {
        Point[] best = new Point[]{null};
        double[] bestDist = new double[]{Double.MAX_VALUE};
        nearestHelper(root, target, best, bestDist);
        return best[0];
    }
    
    private void nearestHelper(AdaptiveKDTreeNode node, Point target,
                              Point[] best, double[] bestDist) {
        if (node == null) return;
        
        double dist = node.point.distanceTo(target);
        if (dist < bestDist[0]) {
            bestDist[0] = dist;
            best[0] = node.point;
        }
        
        int axis = node.splitAxis;
        double diff = target.coords[axis] - node.point.coords[axis];
        
        AdaptiveKDTreeNode nearSubtree = (diff < 0) ? node.left : node.right;
        AdaptiveKDTreeNode farSubtree = (diff < 0) ? node.right : node.left;
        
        nearestHelper(nearSubtree, target, best, bestDist);
        
        if (Math.abs(diff) < bestDist[0]) {
            nearestHelper(farSubtree, target, best, bestDist);
        }
    }
    
    public void printStructure() {
        System.out.println("Adaptive K-D Tree Structure:");
        printHelper(root, 0);
    }
    
    private void printHelper(AdaptiveKDTreeNode node, int depth) {
        if (node == null) return;
        
        String indent = "  ".repeat(depth);
        System.out.println(indent + "Split on axis " + node.splitAxis + 
                          ": " + node.point);
        
        if (node.left != null || node.right != null) {
            if (node.left != null) printHelper(node.left, depth + 1);
            if (node.right != null) printHelper(node.right, depth + 1);
        }
    }
    
    public static void main(String[] args) {
        System.out.println("=== Adaptive K-D Tree Demo ===\n");
        System.out.println("Chooses split axis by maximum variance\n");
        
        AdaptiveKDTree kdtree = new AdaptiveKDTree(2);
        
        // Points with varying distribution
        List<Point> points = Arrays.asList(
            new Point(new double[]{1, 5}, "A"),
            new Point(new double[]{2, 6}, "B"),
            new Point(new double[]{3, 4}, "C"),
            new Point(new double[]{15, 4}, "D"),  // x-axis outlier
            new Point(new double[]{16, 5}, "E"),
            new Point(new double[]{17, 6}, "F")
        );
        
        System.out.println("Building adaptive tree...");
        System.out.println("(x-axis has higher variance)\n");
        
        kdtree.build(points);
        kdtree.printStructure();
        
        System.out.println("\nNearest neighbor to (10, 5):");
        Point target = new Point(new double[]{10, 5}, null);
        Point nearest = kdtree.nearestNeighbor(target);
        if (nearest != null) {
            System.out.printf("  %s at %.2f%n", nearest, target.distanceTo(nearest));
        }
        
        System.out.println("\nKey: Split axis chosen by variance!");
    }
}
