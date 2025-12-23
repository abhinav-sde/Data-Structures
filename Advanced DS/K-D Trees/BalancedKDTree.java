/**
 * Balanced K-D Tree Implementation in Java
 * Uses median finding for guaranteed balance
 */

import java.util.*;

public class BalancedKDTree {
    private KDTreeNode root;
    private int k;
    
    public BalancedKDTree(int k) {
        this.k = k;
    }
    
    public void build(List<Point> points) {
        if (points.isEmpty()) return;
        root = buildTree(new ArrayList<>(points), 0, points.size() - 1, 0);
    }
    
    private KDTreeNode buildTree(List<Point> points, int start, int end, int depth) {
        if (start > end) return null;
        
        int axis = depth % k;
        
        // Sort by current axis
        points.subList(start, end + 1).sort(
            Comparator.comparingDouble(p -> p.coords[axis]));
        
        int median = start + (end - start) / 2;
        
        KDTreeNode node = new KDTreeNode(points.get(median));
        node.left = buildTree(points, start, median - 1, depth + 1);
        node.right = buildTree(points, median + 1, end, depth + 1);
        
        return node;
    }
    
    public Point nearestNeighbor(Point target) {
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
    
    public List<Point> kNearestNeighbors(Point target, int knn) {
        PriorityQueue<PointDist> pq = new PriorityQueue<>(
            (a, b) -> Double.compare(b.dist, a.dist));
        kNearestHelper(root, target, pq, knn, 0);
        
        List<Point> result = new ArrayList<>();
        while (!pq.isEmpty()) {
            result.add(0, pq.poll().point);
        }
        return result;
    }
    
    private void kNearestHelper(KDTreeNode node, Point target,
                               PriorityQueue<PointDist> pq, int knn, int depth) {
        if (node == null) return;
        
        double dist = node.point.distanceTo(target);
        
        if (pq.size() < knn) {
            pq.offer(new PointDist(node.point, dist));
        } else if (dist < pq.peek().dist) {
            pq.poll();
            pq.offer(new PointDist(node.point, dist));
        }
        
        int axis = depth % k;
        double diff = target.coords[axis] - node.point.coords[axis];
        
        KDTreeNode nearSubtree = (diff < 0) ? node.left : node.right;
        KDTreeNode farSubtree = (diff < 0) ? node.right : node.left;
        
        kNearestHelper(nearSubtree, target, pq, knn, depth + 1);
        
        double worstDist = pq.size() < knn ? Double.MAX_VALUE : pq.peek().dist;
        if (Math.abs(diff) < worstDist) {
            kNearestHelper(farSubtree, target, pq, knn, depth + 1);
        }
    }
    
    static class PointDist {
        Point point;
        double dist;
        PointDist(Point p, double d) { point = p; dist = d; }
    }
    
    private int getHeight(KDTreeNode node) {
        if (node == null) return 0;
        return 1 + Math.max(getHeight(node.left), getHeight(node.right));
    }
    
    public void printStats() {
        int height = getHeight(root);
        System.out.println("Tree height: " + height);
    }
    
    public static void main(String[] args) {
        System.out.println("=== Balanced K-D Tree Demo ===\n");
        
        BalancedKDTree kdtree = new BalancedKDTree(2);
        
        List<Point> points = Arrays.asList(
            new Point(new double[]{7, 2}, "A"),
            new Point(new double[]{5, 4}, "B"),
            new Point(new double[]{9, 6}, "C"),
            new Point(new double[]{2, 3}, "D"),
            new Point(new double[]{4, 7}, "E"),
            new Point(new double[]{8, 1}, "F")
        );
        
        System.out.println("Building balanced tree...");
        kdtree.build(points);
        kdtree.printStats();
        
        System.out.println("\n3-Nearest neighbors to (6, 3):");
        Point target = new Point(new double[]{6, 3}, null);
        List<Point> knn = kdtree.kNearestNeighbors(target, 3);
        for (int i = 0; i < knn.size(); i++) {
            System.out.printf("  %d. %s at %.2f%n", i + 1, knn.get(i),
                            target.distanceTo(knn.get(i)));
        }
    }
}
