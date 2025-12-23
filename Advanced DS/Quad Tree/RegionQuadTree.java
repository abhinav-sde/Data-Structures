/**
 * Region Quad Tree (PR Quad Tree) Implementation in Java
 * 
 * Stores rectangular regions with capacity-based subdivision.
 * Each node can hold multiple points up to a capacity limit.
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
}

class Rectangle {
    double x, y, width, height;
    
    public Rectangle(double x, double y, double width, double height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }
    
    public boolean contains(double px, double py) {
        return px >= x && px < x + width && 
               py >= y && py < y + height;
    }
    
    public boolean intersects(Rectangle other) {
        return !(x + width <= other.x || 
                 other.x + other.width <= x ||
                 y + height <= other.y || 
                 other.y + other.height <= y);
    }
}

class RegionQuadTreeNode {
    Rectangle boundary;
    int capacity;
    List<Point> points;
    boolean divided;
    
    // Four children
    RegionQuadTreeNode nw, ne, sw, se;
    
    public RegionQuadTreeNode(Rectangle boundary, int capacity) {
        this.boundary = boundary;
        this.capacity = capacity;
        this.points = new ArrayList<>();
        this.divided = false;
    }
    
    public void subdivide() {
        double x = boundary.x;
        double y = boundary.y;
        double w = boundary.width / 2.0;
        double h = boundary.height / 2.0;
        
        Rectangle nwBoundary = new Rectangle(x, y + h, w, h);
        Rectangle neBoundary = new Rectangle(x + w, y + h, w, h);
        Rectangle swBoundary = new Rectangle(x, y, w, h);
        Rectangle seBoundary = new Rectangle(x + w, y, w, h);
        
        nw = new RegionQuadTreeNode(nwBoundary, capacity);
        ne = new RegionQuadTreeNode(neBoundary, capacity);
        sw = new RegionQuadTreeNode(swBoundary, capacity);
        se = new RegionQuadTreeNode(seBoundary, capacity);
        
        divided = true;
    }
}

public class RegionQuadTree {
    private RegionQuadTreeNode root;
    
    public RegionQuadTree(Rectangle boundary, int capacity) {
        root = new RegionQuadTreeNode(boundary, capacity);
    }
    
    // Insert a point into the quad tree
    public boolean insert(Point point) {
        return insertRecursive(root, point);
    }
    
    private boolean insertRecursive(RegionQuadTreeNode node, Point point) {
        // Check if point is within boundary
        if (!node.boundary.contains(point.x, point.y)) {
            return false;
        }
        
        // If capacity not reached, add point here
        if (node.points.size() < node.capacity) {
            node.points.add(point);
            return true;
        }
        
        // Otherwise, subdivide and redistribute
        if (!node.divided) {
            node.subdivide();
            
            // Redistribute existing points
            for (Point p : node.points) {
                insertIntoChildren(node, p);
            }
            node.points.clear();
        }
        
        // Insert into appropriate child
        return insertIntoChildren(node, point);
    }
    
    private boolean insertIntoChildren(RegionQuadTreeNode node, Point point) {
        if (insertRecursive(node.nw, point)) return true;
        if (insertRecursive(node.ne, point)) return true;
        if (insertRecursive(node.sw, point)) return true;
        if (insertRecursive(node.se, point)) return true;
        return false;
    }
    
    // Find all points within a range
    public List<Point> queryRange(Rectangle range) {
        List<Point> found = new ArrayList<>();
        queryRangeRecursive(root, range, found);
        return found;
    }
    
    private void queryRangeRecursive(RegionQuadTreeNode node, 
                                    Rectangle range, 
                                    List<Point> found) {
        if (node == null) return;
        
        // Check if range intersects with node's boundary
        if (!node.boundary.intersects(range)) {
            return;
        }
        
        // Check points in this node
        for (Point p : node.points) {
            if (range.contains(p.x, p.y)) {
                found.add(p);
            }
        }
        
        // Recurse into children if divided
        if (node.divided) {
            queryRangeRecursive(node.nw, range, found);
            queryRangeRecursive(node.ne, range, found);
            queryRangeRecursive(node.sw, range, found);
            queryRangeRecursive(node.se, range, found);
        }
    }
    
    // Count total nodes
    private int countNodes(RegionQuadTreeNode node) {
        if (node == null) return 0;
        
        if (!node.divided) {
            return 1;
        }
        
        return 1 + countNodes(node.nw) + countNodes(node.ne) +
                   countNodes(node.sw) + countNodes(node.se);
    }
    
    public void printStats() {
        int nodes = countNodes(root);
        System.out.println("Total nodes: " + nodes);
    }
    
    // Example usage
    public static void main(String[] args) {
        System.out.println("=== Region Quad Tree Demo ===\n");
        
        Rectangle boundary = new Rectangle(0, 0, 100, 100);
        RegionQuadTree qt = new RegionQuadTree(boundary, 4);
        
        // Insert points
        System.out.println("Inserting 20 random points...");
        Random rand = new Random(42);
        
        for (int i = 0; i < 20; i++) {
            double x = rand.nextInt(100);
            double y = rand.nextInt(100);
            Point p = new Point(x, y, String.valueOf(i));
            qt.insert(p);
            System.out.printf("  Point %d: (%.0f, %.0f)%n", i, x, y);
        }
        
        // Print stats
        System.out.println("\nTree Statistics:");
        qt.printStats();
        
        // Range query
        System.out.println("\nRange query (25, 25) to (75, 75):");
        Rectangle searchArea = new Rectangle(25, 25, 50, 50);
        List<Point> found = qt.queryRange(searchArea);
        
        System.out.println("  Found " + found.size() + " points:");
        for (Point p : found) {
            System.out.printf("    Point %s: (%.0f, %.0f)%n", 
                            p.data, p.x, p.y);
        }
    }
}
