/**
 * Basic R-Tree Implementation in Java
 * 
 * Original R-Tree design with quadratic split algorithm.
 */

import java.util.*;

class Rectangle {
    double xMin, xMax, yMin, yMax;
    
    public Rectangle(double xMin, double xMax, double yMin, double yMax) {
        this.xMin = xMin;
        this.xMax = xMax;
        this.yMin = yMin;
        this.yMax = yMax;
    }
    
    public double area() {
        return Math.max(0, xMax - xMin) * Math.max(0, yMax - yMin);
    }
    
    public double enlargement(Rectangle other) {
        Rectangle combined = new Rectangle(this.xMin, this.xMax, this.yMin, this.yMax);
        combined.expand(other);
        return combined.area() - area();
    }
    
    public void expand(Rectangle other) {
        xMin = Math.min(xMin, other.xMin);
        xMax = Math.max(xMax, other.xMax);
        yMin = Math.min(yMin, other.yMin);
        yMax = Math.max(yMax, other.yMax);
    }
    
    public boolean intersects(Rectangle other) {
        return !(xMax < other.xMin || other.xMax < xMin ||
                 yMax < other.yMin || other.yMax < yMin);
    }
}

class SpatialObject {
    Rectangle mbr;
    String data;
    
    public SpatialObject(Rectangle mbr, String data) {
        this.mbr = mbr;
        this.data = data;
    }
}

class RTreeEntry {
    Rectangle mbr;
    Object childPtr;  // RTreeNode or SpatialObject
    boolean isLeaf;
    
    public RTreeEntry(Rectangle mbr, Object ptr, boolean isLeaf) {
        this.mbr = mbr;
        this.childPtr = ptr;
        this.isLeaf = isLeaf;
    }
}

class RTreeNode {
    List<RTreeEntry> entries;
    boolean isLeaf;
    static final int MAX_ENTRIES = 4;
    static final int MIN_ENTRIES = 2;
    
    public RTreeNode(boolean isLeaf) {
        this.isLeaf = isLeaf;
        this.entries = new ArrayList<>();
    }
    
    public boolean isFull() {
        return entries.size() >= MAX_ENTRIES;
    }
    
    public Rectangle computeMBR() {
        if (entries.isEmpty()) return new Rectangle(0, 0, 0, 0);
        
        Rectangle mbr = new Rectangle(
            entries.get(0).mbr.xMin, entries.get(0).mbr.xMax,
            entries.get(0).mbr.yMin, entries.get(0).mbr.yMax
        );
        
        for (int i = 1; i < entries.size(); i++) {
            mbr.expand(entries.get(i).mbr);
        }
        return mbr;
    }
}

public class BasicRTree {
    private RTreeNode root;
    
    public BasicRTree() {
        root = new RTreeNode(true);
    }
    
    private RTreeNode chooseLeaf(RTreeNode node, Rectangle mbr) {
        if (node.isLeaf) {
            return node;
        }
        
        // Find entry with minimum enlargement
        int bestIdx = 0;
        double minEnlargement = node.entries.get(0).mbr.enlargement(mbr);
        
        for (int i = 1; i < node.entries.size(); i++) {
            double enlargement = node.entries.get(i).mbr.enlargement(mbr);
            if (enlargement < minEnlargement) {
                minEnlargement = enlargement;
                bestIdx = i;
            }
        }
        
        return chooseLeaf((RTreeNode) node.entries.get(bestIdx).childPtr, mbr);
    }
    
    private RTreeNode[] splitNode(RTreeNode node) {
        RTreeNode node1 = new RTreeNode(node.isLeaf);
        RTreeNode node2 = new RTreeNode(node.isLeaf);
        
        // Find pair with maximum waste (simplified quadratic split)
        int seed1 = 0, seed2 = 1;
        double maxWaste = -1;
        
        for (int i = 0; i < node.entries.size(); i++) {
            for (int j = i + 1; j < node.entries.size(); j++) {
                Rectangle combined = new Rectangle(
                    node.entries.get(i).mbr.xMin, node.entries.get(i).mbr.xMax,
                    node.entries.get(i).mbr.yMin, node.entries.get(i).mbr.yMax
                );
                combined.expand(node.entries.get(j).mbr);
                
                double waste = combined.area() -
                              node.entries.get(i).mbr.area() -
                              node.entries.get(j).mbr.area();
                
                if (waste > maxWaste) {
                    maxWaste = waste;
                    seed1 = i;
                    seed2 = j;
                }
            }
        }
        
        // Add seeds
        node1.entries.add(node.entries.get(seed1));
        node2.entries.add(node.entries.get(seed2));
        
        // Distribute remaining entries
        for (int i = 0; i < node.entries.size(); i++) {
            if (i == seed1 || i == seed2) continue;
            
            Rectangle mbr1 = node1.computeMBR();
            Rectangle mbr2 = node2.computeMBR();
            
            double enlargement1 = mbr1.enlargement(node.entries.get(i).mbr);
            double enlargement2 = mbr2.enlargement(node.entries.get(i).mbr);
            
            if (enlargement1 < enlargement2) {
                node1.entries.add(node.entries.get(i));
            } else {
                node2.entries.add(node.entries.get(i));
            }
        }
        
        return new RTreeNode[]{node1, node2};
    }
    
    public void insert(SpatialObject obj) {
        // Choose leaf
        RTreeNode leaf = chooseLeaf(root, obj.mbr);
        
        // Add entry
        leaf.entries.add(new RTreeEntry(obj.mbr, obj, true));
        
        // Handle overflow (simplified)
        if (leaf.isFull() && leaf == root) {
            RTreeNode[] split = splitNode(leaf);
            
            // Create new root
            RTreeNode newRoot = new RTreeNode(false);
            newRoot.entries.add(new RTreeEntry(split[0].computeMBR(), split[0], false));
            newRoot.entries.add(new RTreeEntry(split[1].computeMBR(), split[1], false));
            root = newRoot;
        }
    }
    
    public List<SpatialObject> search(Rectangle query) {
        List<SpatialObject> results = new ArrayList<>();
        searchHelper(root, query, results);
        return results;
    }
    
    private void searchHelper(RTreeNode node, Rectangle query, 
                             List<SpatialObject> results) {
        if (node == null) return;
        
        for (RTreeEntry entry : node.entries) {
            if (entry.mbr.intersects(query)) {
                if (node.isLeaf) {
                    results.add((SpatialObject) entry.childPtr);
                } else {
                    searchHelper((RTreeNode) entry.childPtr, query, results);
                }
            }
        }
    }
    
    public void printStats() {
        int[] stats = new int[3]; // nodes, leaves, objects
        countNodes(root, stats);
        
        System.out.println("Total nodes: " + stats[0]);
        System.out.println("Leaf nodes: " + stats[1]);
        System.out.println("Objects: " + stats[2]);
    }
    
    private void countNodes(RTreeNode node, int[] stats) {
        if (node == null) return;
        stats[0]++;
        
        if (node.isLeaf) {
            stats[1]++;
            stats[2] += node.entries.size();
        } else {
            for (RTreeEntry entry : node.entries) {
                countNodes((RTreeNode) entry.childPtr, stats);
            }
        }
    }
    
    public static void main(String[] args) {
        System.out.println("=== Basic R-Tree Demo ===\n");
        
        BasicRTree rtree = new BasicRTree();
        
        // Insert objects
        SpatialObject[] objects = {
            new SpatialObject(new Rectangle(10, 20, 10, 20), "A"),
            new SpatialObject(new Rectangle(15, 25, 15, 25), "B"),
            new SpatialObject(new Rectangle(30, 40, 30, 40), "C"),
            new SpatialObject(new Rectangle(50, 60, 50, 60), "D"),
            new SpatialObject(new Rectangle(55, 65, 55, 65), "E"),
            new SpatialObject(new Rectangle(70, 80, 10, 20), "F")
        };
        
        System.out.println("Inserting objects:");
        for (SpatialObject obj : objects) {
            rtree.insert(obj);
            System.out.printf("  %s: [%.0f,%.0f] x [%.0f,%.0f]%n",
                obj.data, obj.mbr.xMin, obj.mbr.xMax, obj.mbr.yMin, obj.mbr.yMax);
        }
        
        System.out.println("\nTree Statistics:");
        rtree.printStats();
        
        System.out.println("\nSearch query [12, 35] x [12, 35]:");
        Rectangle query = new Rectangle(12, 35, 12, 35);
        List<SpatialObject> results = rtree.search(query);
        
        System.out.println("  Found " + results.size() + " objects:");
        for (SpatialObject obj : results) {
            System.out.println("    " + obj.data);
        }
    }
}
