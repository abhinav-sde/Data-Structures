/**
 * R*-Tree Implementation in Java (Simplified)
 * Enhanced R-Tree with optimized split heuristics
 */

import java.util.*;

// Reuse Rectangle and SpatialObject from BasicRTree
class RStarEntry {
    Rectangle mbr;
    Object childPtr;
    boolean isLeaf;
    
    public RStarEntry(Rectangle mbr, Object ptr, boolean isLeaf) {
        this.mbr = mbr;
        this.childPtr = ptr;
        this.isLeaf = isLeaf;
    }
}

class RStarNode {
    List<RStarEntry> entries;
    boolean isLeaf;
    static final int MAX_ENTRIES = 4;
    
    public RStarNode(boolean isLeaf) {
        this.isLeaf = isLeaf;
        this.entries = new ArrayList<>();
    }
    
    public boolean isFull() {
        return entries.size() >= MAX_ENTRIES;
    }
    
    public Rectangle computeMBR() {
        if (entries.isEmpty()) return new Rectangle(0, 0, 0, 0);
        Rectangle mbr = new Rectangle(entries.get(0).mbr.xMin, entries.get(0).mbr.xMax,
                                     entries.get(0).mbr.yMin, entries.get(0).mbr.yMax);
        for (int i = 1; i < entries.size(); i++) {
            mbr.expand(entries.get(i).mbr);
        }
        return mbr;
    }
    
    public double perimeter() {
        Rectangle mbr = computeMBR();
        return 2 * ((mbr.xMax - mbr.xMin) + (mbr.yMax - mbr.yMin));
    }
}

public class RStarTree {
    private RStarNode root;
    
    public RStarTree() {
        root = new RStarNode(true);
    }
    
    private RStarNode chooseSubtree(RStarNode node, Rectangle mbr) {
        if (node.isLeaf) return node;
        
        // Choose entry with minimum overlap enlargement
        int bestIdx = 0;
        double minOverlap = Double.MAX_VALUE;
        
        for (int i = 0; i < node.entries.size(); i++) {
            Rectangle enlarged = new Rectangle(node.entries.get(i).mbr.xMin,
                node.entries.get(i).mbr.xMax, node.entries.get(i).mbr.yMin,
                node.entries.get(i).mbr.yMax);
            enlarged.expand(mbr);
            
            // Calculate overlap change (simplified)
            double overlapChange = 0;
            for (int j = 0; j < node.entries.size(); j++) {
                if (i != j) {
                    overlapChange += calculateOverlap(enlarged, node.entries.get(j).mbr);
                }
            }
            
            if (overlapChange < minOverlap) {
                minOverlap = overlapChange;
                bestIdx = i;
            }
        }
        
        return chooseSubtree((RStarNode) node.entries.get(bestIdx).childPtr, mbr);
    }
    
    private double calculateOverlap(Rectangle r1, Rectangle r2) {
        double xOverlap = Math.max(0, Math.min(r1.xMax, r2.xMax) - Math.max(r1.xMin, r2.xMin));
        double yOverlap = Math.max(0, Math.min(r1.yMax, r2.yMax) - Math.max(r1.yMin, r2.yMin));
        return xOverlap * yOverlap;
    }
    
    public void insert(SpatialObject obj) {
        RStarNode leaf = chooseSubtree(root, obj.mbr);
        leaf.entries.add(new RStarEntry(obj.mbr, obj, true));
        
        // Handle overflow (simplified - no forced reinsert)
        if (leaf.isFull() && leaf == root) {
            RStarNode[] split = splitNode(leaf);
            RStarNode newRoot = new RStarNode(false);
            newRoot.entries.add(new RStarEntry(split[0].computeMBR(), split[0], false));
            newRoot.entries.add(new RStarEntry(split[1].computeMBR(), split[1], false));
            root = newRoot;
        }
    }
    
    private RStarNode[] splitNode(RStarNode node) {
        // Sort by x-axis and try split
        List<RStarEntry> sorted = new ArrayList<>(node.entries);
        sorted.sort(Comparator.comparingDouble(e -> e.mbr.xMin));
        
        int mid = sorted.size() / 2;
        RStarNode node1 = new RStarNode(node.isLeaf);
        RStarNode node2 = new RStarNode(node.isLeaf);
        
        for (int i = 0; i < sorted.size(); i++) {
            if (i < mid) node1.entries.add(sorted.get(i));
            else node2.entries.add(sorted.get(i));
        }
        
        return new RStarNode[]{node1, node2};
    }
    
    public List<SpatialObject> search(Rectangle query) {
        List<SpatialObject> results = new ArrayList<>();
        searchHelper(root, query, results);
        return results;
    }
    
    private void searchHelper(RStarNode node, Rectangle query, List<SpatialObject> results) {
        if (node == null) return;
        for (RStarEntry entry : node.entries) {
            if (entry.mbr.intersects(query)) {
                if (node.isLeaf) results.add((SpatialObject) entry.childPtr);
                else searchHelper((RStarNode) entry.childPtr, query, results);
            }
        }
    }
    
    public void printStats() {
        int[] stats = new int[3];
        countNodes(root, stats);
        System.out.println("Total nodes: " + stats[0] + ", Leaf nodes: " + stats[1] + 
                          ", Objects: " + stats[2]);
    }
    
    private void countNodes(RStarNode node, int[] stats) {
        if (node == null) return;
        stats[0]++;
        if (node.isLeaf) {
            stats[1]++;
            stats[2] += node.entries.size();
        } else {
            for (RStarEntry entry : node.entries) {
                countNodes((RStarNode) entry.childPtr, stats);
            }
        }
    }
    
    public static void main(String[] args) {
        System.out.println("=== R*-Tree Demo ===\n");
        RStarTree rtree = new RStarTree();
        
        SpatialObject[] objects = {
            new SpatialObject(new Rectangle(10, 20, 10, 20), "A"),
            new SpatialObject(new Rectangle(15, 25, 15, 25), "B"),
            new SpatialObject(new Rectangle(30, 40, 30, 40), "C"),
            new SpatialObject(new Rectangle(50, 60, 50, 60), "D")
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
        List<SpatialObject> results = rtree.search(new Rectangle(12, 35, 12, 35));
        System.out.println("  Found: " + results.stream()
            .map(o -> o.data).reduce("", (a, b) -> a + b + " "));
    }
}
