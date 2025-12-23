/**
 * R+-Tree Implementation in Java (Simplified)
 * No-overlap variant with object clipping
 */

import java.util.*;

public class RPlusTree {
    private RPlusNode root;
    private Rectangle worldBounds;
    
    static class RPlusNode {
        List<RPlusEntry> entries = new ArrayList<>();
        boolean isLeaf;
        Rectangle bounds;
        static final int MAX_ENTRIES = 4;
        
        RPlusNode(boolean isLeaf, Rectangle bounds) {
            this.isLeaf = isLeaf;
            this.bounds = bounds;
        }
    }
    
    static class RPlusEntry {
        Rectangle mbr;
        Object childPtr;
        boolean isLeaf;
        
        RPlusEntry(Rectangle mbr, Object ptr, boolean isLeaf) {
            this.mbr = mbr;
            this.childPtr = ptr;
            this.isLeaf = isLeaf;
        }
    }
    
    public RPlusTree(Rectangle bounds) {
        this.worldBounds = bounds;
        root = new RPlusNode(false, bounds);
        
        // Create 4 non-overlapping quadrants
        double midX = (bounds.xMin + bounds.xMax) / 2.0;
        double midY = (bounds.yMin + bounds.yMax) / 2.0;
        
        root.entries.add(new RPlusEntry(new Rectangle(bounds.xMin, midX, midY, bounds.yMax),
            new RPlusNode(true, new Rectangle(bounds.xMin, midX, midY, bounds.yMax)), false));
        root.entries.add(new RPlusEntry(new Rectangle(midX, bounds.xMax, midY, bounds.yMax),
            new RPlusNode(true, new Rectangle(midX, bounds.xMax, midY, bounds.yMax)), false));
        root.entries.add(new RPlusEntry(new Rectangle(bounds.xMin, midX, bounds.yMin, midY),
            new RPlusNode(true, new Rectangle(bounds.xMin, midX, bounds.yMin, midY)), false));
        root.entries.add(new RPlusEntry(new Rectangle(midX, bounds.xMax, bounds.yMin, midY),
            new RPlusNode(true, new Rectangle(midX, bounds.xMax, bounds.yMin, midY)), false));
    }
    
    public void insert(SpatialObject obj) {
        insertHelper(root, obj);
    }
    
    private void insertHelper(RPlusNode node, SpatialObject obj) {
        if (node.isLeaf) {
            if (obj.mbr.intersects(node.bounds)) {
                // Clip object to bounds
                Rectangle clipped = clip(obj.mbr, node.bounds);
                node.entries.add(new RPlusEntry(clipped, 
                    new SpatialObject(clipped, obj.data), true));
            }
        } else {
            for (RPlusEntry entry : node.entries) {
                if (obj.mbr.intersects(entry.mbr)) {
                    insertHelper((RPlusNode) entry.childPtr, obj);
                }
            }
        }
    }
    
    private Rectangle clip(Rectangle r, Rectangle bounds) {
        return new Rectangle(
            Math.max(r.xMin, bounds.xMin), Math.min(r.xMax, bounds.xMax),
            Math.max(r.yMin, bounds.yMin), Math.min(r.yMax, bounds.yMax));
    }
    
    public List<SpatialObject> search(Rectangle query) {
        List<SpatialObject> results = new ArrayList<>();
        Set<String> seen = new HashSet<>();
        searchHelper(root, query, results, seen);
        return results;
    }
    
    private void searchHelper(RPlusNode node, Rectangle query, 
                             List<SpatialObject> results, Set<String> seen) {
        for (RPlusEntry entry : node.entries) {
            if (entry.mbr.intersects(query)) {
                if (node.isLeaf) {
                    SpatialObject obj = (SpatialObject) entry.childPtr;
                    if (!seen.contains(obj.data)) {
                        results.add(obj);
                        seen.add(obj.data);
                    }
                } else {
                    searchHelper((RPlusNode) entry.childPtr, query, results, seen);
                }
            }
        }
    }
    
    public static void main(String[] args) {
        System.out.println("=== R+-Tree Demo ===\n");
        System.out.println("R+-Tree: No overlapping MBRs!\n");
        
        RPlusTree rtree = new RPlusTree(new Rectangle(0, 100, 0, 100));
        
        SpatialObject[] objects = {
            new SpatialObject(new Rectangle(10, 20, 10, 20), "A"),
            new SpatialObject(new Rectangle(45, 55, 45, 55), "B"),  // Spans quadrants
            new SpatialObject(new Rectangle(70, 80, 70, 80), "C")
        };
        
        System.out.println("Inserting objects:");
        for (SpatialObject obj : objects) {
            rtree.insert(obj);
            System.out.printf("  %s: [%.0f,%.0f] x [%.0f,%.0f]%n",
                obj.data, obj.mbr.xMin, obj.mbr.xMax, obj.mbr.yMin, obj.mbr.yMax);
        }
        
        System.out.println("\nSearch query [40, 60] x [40, 60]:");
        List<SpatialObject> results = rtree.search(new Rectangle(40, 60, 40, 60));
        System.out.println("  Found: " + results.stream()
            .map(o -> o.data).reduce("", (a, b) -> a + b + " "));
        
        System.out.println("\nNote: Object B may be clipped across multiple quadrants.");
    }
}
