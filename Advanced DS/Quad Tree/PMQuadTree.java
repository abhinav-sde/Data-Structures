/**
 * PM Quad Tree (Point-Morton Quad Tree) Implementation in Java
 * 
 * Combines features of point and region quad trees.
 * Uses Morton codes (Z-order curve) for efficient spatial indexing.
 */

import java.util.*;

class Point {
    double x, y;
    String data;
    
    public Point(double x, double y, String data) {
        this.x = x;
        this.y = y;
        this.data = data;
    }
    
    public double distanceTo(double px, double py) {
        return Math.sqrt((x - px) * (x - px) + (y - py) * (y - py));
    }
}

class PMQuadTreeNode {
    double x, y, size;
    int capacity;
    Map<Long, Point> points;
    boolean isLeaf;
    
    // Four children
    PMQuadTreeNode nw, ne, sw, se;
    
    public PMQuadTreeNode(double x, double y, double size, int capacity) {
        this.x = x;
        this.y = y;
        this.size = size;
        this.capacity = capacity;
        this.points = new HashMap<>();
        this.isLeaf = true;
    }
}

public class PMQuadTree {
    private PMQuadTreeNode root;
    
    public PMQuadTree(double x, double y, double size, int capacity) {
        root = new PMQuadTreeNode(x, y, size, capacity);
    }
    
    // Calculate Morton code (Z-order) for point
    public static long mortonCode(int x, int y, int maxDepth) {
        long code = 0;
        for (int i = 0; i < maxDepth; i++) {
            code |= ((long) (x & (1 << i)) << i) | 
                    ((long) (y & (1 << i)) << (i + 1));
        }
        return code;
    }
    
    public static long mortonCode(int x, int y) {
        return mortonCode(x, y, 16);
    }
    
    private void subdivide(PMQuadTreeNode node) {
        double half = node.size / 2.0;
        int cap = node.capacity;
        
        node.nw = new PMQuadTreeNode(node.x, node.y + half, half, cap);
        node.ne = new PMQuadTreeNode(node.x + half, node.y + half, half, cap);
        node.sw = new PMQuadTreeNode(node.x, node.y, half, cap);
        node.se = new PMQuadTreeNode(node.x + half, node.y, half, cap);
        
        node.isLeaf = false;
    }
    
    public boolean insert(Point point) {
        long morton = mortonCode((int) point.x, (int) point.y);
        return insertRecursive(root, point, morton);
    }
    
    private boolean insertRecursive(PMQuadTreeNode node, Point point, long morton) {
        if (node == null) return false;
        
        // Check if point is within bounds
        if (point.x < node.x || point.x >= node.x + node.size ||
            point.y < node.y || point.y >= node.y + node.size) {
            return false;
        }
        
        if (node.isLeaf) {
            // Check capacity
            if (node.points.size() < node.capacity) {
                node.points.put(morton, point);
                return true;
            } else {
                // Subdivide
                subdivide(node);
                
                // Redistribute points
                for (Map.Entry<Long, Point> entry : node.points.entrySet()) {
                    insertIntoChild(node, entry.getValue(), entry.getKey());
                }
                node.points.clear();
                
                // Insert new point
                return insertIntoChild(node, point, morton);
            }
        } else {
            return insertIntoChild(node, point, morton);
        }
    }
    
    private boolean insertIntoChild(PMQuadTreeNode node, Point point, long morton) {
        double midX = node.x + node.size / 2.0;
        double midY = node.y + node.size / 2.0;
        
        if (point.x < midX) {
            if (point.y < midY) {
                return insertRecursive(node.sw, point, morton);
            } else {
                return insertRecursive(node.nw, point, morton);
            }
        } else {
            if (point.y < midY) {
                return insertRecursive(node.se, point, morton);
            } else {
                return insertRecursive(node.ne, point, morton);
            }
        }
    }
    
    public Point nearestNeighbor(double x, double y) {
        Point[] best = new Point[1];
        double[] bestDist = new double[]{Double.MAX_VALUE};
        nearestRecursive(root, x, y, best, bestDist);
        return best[0];
    }
    
    private void nearestRecursive(PMQuadTreeNode node, double x, double y,
                                  Point[] best, double[] bestDist) {
        if (node == null) return;
        
        if (node.isLeaf) {
            // Check all points in this leaf
            for (Point p : node.points.values()) {
                double dist = p.distanceTo(x, y);
                if (dist < bestDist[0]) {
                    bestDist[0] = dist;
                    best[0] = p;
                }
            }
        } else {
            // Check children
            PMQuadTreeNode[] children = {node.sw, node.se, node.nw, node.ne};
            
            for (PMQuadTreeNode child : children) {
                if (child != null) {
                    // Distance to child's bounding box
                    double closestX = Math.max(child.x, 
                                              Math.min(x, child.x + child.size));
                    double closestY = Math.max(child.y, 
                                              Math.min(y, child.y + child.size));
                    double distToBounds = Math.sqrt((x - closestX) * (x - closestX) + 
                                                   (y - closestY) * (y - closestY));
                    
                    // Only search if child could contain closer point
                    if (distToBounds < bestDist[0]) {
                        nearestRecursive(child, x, y, best, bestDist);
                    }
                }
            }
        }
    }
    
    private int countNodes(PMQuadTreeNode node) {
        if (node == null) return 0;
        
        if (node.isLeaf) {
            return 1;
        }
        
        return 1 + countNodes(node.nw) + countNodes(node.ne) +
                   countNodes(node.sw) + countNodes(node.se);
    }
    
    public void printStats() {
        int nodes = countNodes(root);
        System.out.println("Total nodes: " + nodes);
    }
    
    public static void demonstrateMortonCode() {
        System.out.println("Morton Code Examples:");
        int[][] points = {
            {0, 0}, {1, 0}, {0, 1}, {1, 1},
            {2, 0}, {3, 0}, {2, 2}, {3, 3}
        };
        
        for (int[] p : points) {
            long code = mortonCode(p[0], p[1]);
            System.out.printf("  (%d, %d) -> %d%n", p[0], p[1], code);
        }
    }
    
    // Example usage
    public static void main(String[] args) {
        System.out.println("=== PM Quad Tree Demo ===\n");
        
        // Demonstrate Morton coding
        demonstrateMortonCode();
        System.out.println();
        
        // Create quad tree
        PMQuadTree qt = new PMQuadTree(0, 0, 100, 4);
        
        // Insert points
        Point[] points = {
            new Point(10, 10, "A"),
            new Point(20, 20, "B"),
            new Point(30, 30, "C"),
            new Point(80, 80, "D"),
            new Point(25, 25, "E"),
            new Point(15, 85, "F"),
            new Point(90, 10, "G")
        };
        
        System.out.println("Inserting points:");
        for (Point p : points) {
            qt.insert(p);
            System.out.printf("  %s: (%.0f, %.0f)%n", p.data, p.x, p.y);
        }
        
        // Print statistics
        System.out.println("\nTree Statistics:");
        qt.printStats();
        
        // Find nearest neighbors
        System.out.println("\nNearest Neighbor Queries:");
        
        double[][] queries = {
            {25, 25},
            {50, 50},
            {85, 85}
        };
        
        for (double[] q : queries) {
            Point nearest = qt.nearestNeighbor(q[0], q[1]);
            if (nearest != null) {
                double dist = nearest.distanceTo(q[0], q[1]);
                System.out.printf("  Nearest to (%.0f, %.0f): %s at (%.0f, %.0f), " +
                                "distance = %.2f%n", 
                                q[0], q[1], nearest.data, nearest.x, nearest.y, dist);
            }
        }
    }
}
