/**
 * Point Quad Tree Implementation in Java
 * 
 * Stores individual points in 2D space. Each node represents a point
 * and divides space into 4 quadrants based on that point.
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
    
    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Point)) return false;
        Point other = (Point) obj;
        return x == other.x && y == other.y;
    }
}

class PointQuadTreeNode {
    Point point;
    double xMin, xMax, yMin, yMax;
    
    // Four quadrants
    PointQuadTreeNode nw, ne, sw, se;
    
    public PointQuadTreeNode(Point point, double xMin, double xMax, 
                            double yMin, double yMax) {
        this.point = point;
        this.xMin = xMin;
        this.xMax = xMax;
        this.yMin = yMin;
        this.yMax = yMax;
    }
}

public class PointQuadTree {
    private PointQuadTreeNode root;
    private double xMin, xMax, yMin, yMax;
    
    public PointQuadTree(double xMin, double xMax, double yMin, double yMax) {
        this.xMin = xMin;
        this.xMax = xMax;
        this.yMin = yMin;
        this.yMax = yMax;
    }
    
    // Insert a point into the quad tree
    public void insert(Point point) {
        if (root == null) {
            root = new PointQuadTreeNode(point, xMin, xMax, yMin, yMax);
        } else {
            insertRecursive(root, point);
        }
    }
    
    private void insertRecursive(PointQuadTreeNode node, Point point) {
        double midX = (node.xMin + node.xMax) / 2.0;
        double midY = (node.yMin + node.yMax) / 2.0;
        
        // Determine which quadrant the point belongs to
        if (point.x < node.point.x) {
            if (point.y < node.point.y) {
                // Southwest quadrant
                if (node.sw == null) {
                    node.sw = new PointQuadTreeNode(point, node.xMin, midX, 
                                                   node.yMin, midY);
                } else {
                    insertRecursive(node.sw, point);
                }
            } else {
                // Northwest quadrant
                if (node.nw == null) {
                    node.nw = new PointQuadTreeNode(point, node.xMin, midX, 
                                                   midY, node.yMax);
                } else {
                    insertRecursive(node.nw, point);
                }
            }
        } else {
            if (point.y < node.point.y) {
                // Southeast quadrant
                if (node.se == null) {
                    node.se = new PointQuadTreeNode(point, midX, node.xMax, 
                                                   node.yMin, midY);
                } else {
                    insertRecursive(node.se, point);
                }
            } else {
                // Northeast quadrant
                if (node.ne == null) {
                    node.ne = new PointQuadTreeNode(point, midX, node.xMax, 
                                                   midY, node.yMax);
                } else {
                    insertRecursive(node.ne, point);
                }
            }
        }
    }
    
    // Search for a point
    public Point search(double x, double y) {
        return searchRecursive(root, x, y);
    }
    
    private Point searchRecursive(PointQuadTreeNode node, double x, double y) {
        if (node == null) return null;
        
        if (node.point.x == x && node.point.y == y) {
            return node.point;
        }
        
        // Navigate to appropriate quadrant
        if (x < node.point.x) {
            if (y < node.point.y) {
                return searchRecursive(node.sw, x, y);
            } else {
                return searchRecursive(node.nw, x, y);
            }
        } else {
            if (y < node.point.y) {
                return searchRecursive(node.se, x, y);
            } else {
                return searchRecursive(node.ne, x, y);
            }
        }
    }
    
    // Find all points within a rectangular range
    public List<Point> rangeQuery(double xMin, double xMax, 
                                  double yMin, double yMax) {
        List<Point> result = new ArrayList<>();
        rangeQueryRecursive(root, xMin, xMax, yMin, yMax, result);
        return result;
    }
    
    private void rangeQueryRecursive(PointQuadTreeNode node, 
                                    double xMin, double xMax,
                                    double yMin, double yMax, 
                                    List<Point> result) {
        if (node == null) return;
        
        // Check if current point is in range
        if (node.point.x >= xMin && node.point.x <= xMax &&
            node.point.y >= yMin && node.point.y <= yMax) {
            result.add(node.point);
        }
        
        // Check which quadrants might contain points in range
        if (xMin <= node.point.x) {
            if (yMin <= node.point.y) {
                rangeQueryRecursive(node.sw, xMin, xMax, yMin, yMax, result);
            }
            if (yMax >= node.point.y) {
                rangeQueryRecursive(node.nw, xMin, xMax, yMin, yMax, result);
            }
        }
        
        if (xMax >= node.point.x) {
            if (yMin <= node.point.y) {
                rangeQueryRecursive(node.se, xMin, xMax, yMin, yMax, result);
            }
            if (yMax >= node.point.y) {
                rangeQueryRecursive(node.ne, xMin, xMax, yMin, yMax, result);
            }
        }
    }
    
    // Example usage
    public static void main(String[] args) {
        System.out.println("=== Point Quad Tree Demo ===\n");
        
        PointQuadTree qt = new PointQuadTree(0, 100, 0, 100);
        
        // Insert points
        Point[] points = {
            new Point(25, 25, "A"),
            new Point(75, 75, "B"),
            new Point(30, 70, "C"),
            new Point(80, 20, "D"),
            new Point(50, 50, "E")
        };
        
        System.out.println("Inserting points:");
        for (Point p : points) {
            qt.insert(p);
            System.out.printf("  (%.0f, %.0f) - %s%n", p.x, p.y, p.data);
        }
        
        // Search for a point
        System.out.println("\nSearching for point (75, 75):");
        Point found = qt.search(75, 75);
        if (found != null) {
            System.out.println("  Found: " + found.data);
        } else {
            System.out.println("  Not found");
        }
        
        // Range query
        System.out.println("\nRange query (20, 60) x (20, 60):");
        List<Point> inRange = qt.rangeQuery(20, 60, 20, 60);
        System.out.print("  Points found: ");
        for (Point p : inRange) {
            System.out.print(p.data + " ");
        }
        System.out.println();
    }
}
