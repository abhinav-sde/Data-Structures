/**
 * Hilbert R-Tree Implementation in Java (Simplified)
 * Uses Hilbert space-filling curve for spatial ordering
 */

import java.util.*;

public class HilbertRTree {
    private HilbertNode root;
    
    static class HilbertNode {
        List<HilbertEntry> entries = new ArrayList<>();
        boolean isLeaf;
        static final int MAX_ENTRIES = 4;
        
        HilbertNode(boolean isLeaf) {
            this.isLeaf = isLeaf;
        }
        
        Rectangle computeMBR() {
            if (entries.isEmpty()) return new Rectangle(0, 0, 0, 0);
            Rectangle mbr = new Rectangle(entries.get(0).mbr.xMin, entries.get(0).mbr.xMax,
                                         entries.get(0).mbr.yMin, entries.get(0).mbr.yMax);
            for (int i = 1; i < entries.size(); i++) {
                mbr.expand(entries.get(i).mbr);
            }
            return mbr;
        }
        
        int largestHilbert() {
            return entries.isEmpty() ? 0 : entries.get(entries.size() - 1).hilbertValue;
        }
    }
    
    static class HilbertEntry {
        Rectangle mbr;
        Object childPtr;
        boolean isLeaf;
        int hilbertValue;
        
        HilbertEntry(Rectangle mbr, Object ptr, boolean isLeaf, int hValue) {
            this.mbr = mbr;
            this.childPtr = ptr;
            this.isLeaf = isLeaf;
            this.hilbertValue = hValue;
        }
    }
    
    // Hilbert curve calculation
    static class HilbertCurve {
        static int xy2d(int n, int x, int y) {
            int d = 0;
            for (int s = n / 2; s > 0; s /= 2) {
                int rx = (x & s) > 0 ? 1 : 0;
                int ry = (y & s) > 0 ? 1 : 0;
                d += s * s * ((3 * rx) ^ ry);
                rot(s, new int[]{x, y}, rx, ry);
            }
            return d;
        }
        
        static void rot(int n, int[] xy, int rx, int ry) {
            if (ry == 0) {
                if (rx == 1) {
                    xy[0] = n - 1 - xy[0];
                    xy[1] = n - 1 - xy[1];
                }
                int t = xy[0];
                xy[0] = xy[1];
                xy[1] = t;
            }
        }
        
        static int hilbertValue(Rectangle mbr) {
            double cx = (mbr.xMin + mbr.xMax) / 2.0;
            double cy = (mbr.yMin + mbr.yMax) / 2.0;
            int x = ((int) cx) % 256;
            int y = ((int) cy) % 256;
            return xy2d(256, x, y);
        }
    }
    
    public HilbertRTree() {
        root = new HilbertNode(true);
    }
    
    public void insert(SpatialObject obj) {
        int hilbert = HilbertCurve.hilbertValue(obj.mbr);
        obj.data = obj.data + "(" + hilbert + ")";  // Store Hilbert value
        
        HilbertNode leaf = chooseLeaf(root, hilbert);
        
        // Insert in sorted position
        HilbertEntry newEntry = new HilbertEntry(obj.mbr, obj, true, hilbert);
        int insertPos = 0;
        while (insertPos < leaf.entries.size() && 
               leaf.entries.get(insertPos).hilbertValue < hilbert) {
            insertPos++;
        }
        leaf.entries.add(insertPos, newEntry);
        
        // Handle overflow (simplified)
        if (leaf.entries.size() > HilbertNode.MAX_ENTRIES && leaf == root) {
            HilbertNode[] split = splitNode(leaf);
            HilbertNode newRoot = new HilbertNode(false);
            newRoot.entries.add(new HilbertEntry(split[0].computeMBR(), 
                split[0], false, split[0].largestHilbert()));
            newRoot.entries.add(new HilbertEntry(split[1].computeMBR(), 
                split[1], false, split[1].largestHilbert()));
            root = newRoot;
        }
    }
    
    private HilbertNode chooseLeaf(HilbertNode node, int hilbert) {
        if (node.isLeaf) return node;
        
        for (HilbertEntry entry : node.entries) {
            if (hilbert <= entry.hilbertValue) {
                return chooseLeaf((HilbertNode) entry.childPtr, hilbert);
            }
        }
        return chooseLeaf((HilbertNode) node.entries.get(node.entries.size() - 1).childPtr, hilbert);
    }
    
    private HilbertNode[] splitNode(HilbertNode node) {
        int mid = node.entries.size() / 2;
        HilbertNode node1 = new HilbertNode(node.isLeaf);
        HilbertNode node2 = new HilbertNode(node.isLeaf);
        
        for (int i = 0; i < node.entries.size(); i++) {
            if (i < mid) node1.entries.add(node.entries.get(i));
            else node2.entries.add(node.entries.get(i));
        }
        return new HilbertNode[]{node1, node2};
    }
    
    public List<SpatialObject> search(Rectangle query) {
        List<SpatialObject> results = new ArrayList<>();
        searchHelper(root, query, results);
        return results;
    }
    
    private void searchHelper(HilbertNode node, Rectangle query, List<SpatialObject> results) {
        for (HilbertEntry entry : node.entries) {
            if (entry.mbr.intersects(query)) {
                if (node.isLeaf) results.add((SpatialObject) entry.childPtr);
                else searchHelper((HilbertNode) entry.childPtr, query, results);
            }
        }
    }
    
    public static void main(String[] args) {
        System.out.println("=== Hilbert R-Tree Demo ===\n");
        System.out.println("Objects ordered by Hilbert space-filling curve\n");
        
        // Demonstrate Hilbert values
        System.out.println("Hilbert Value Examples:");
        int[][] points = {{0, 0}, {16, 16}, {32, 32}, {64, 64}, {96, 96}};
        for (int[] p : points) {
            Rectangle r = new Rectangle(p[0], p[0], p[1], p[1]);
            System.out.printf("  (%d, %d) -> Hilbert: %d%n", 
                p[0], p[1], HilbertCurve.hilbertValue(r));
        }
        
        System.out.println("\nInserting objects:");
        HilbertRTree rtree = new HilbertRTree();
        
        SpatialObject[] objects = {
            new SpatialObject(new Rectangle(10, 20, 10, 20), "A"),
            new SpatialObject(new Rectangle(30, 40, 30, 40), "B"),
            new SpatialObject(new Rectangle(50, 60, 50, 60), "C"),
            new SpatialObject(new Rectangle(70, 80, 70, 80), "D")
        };
        
        for (SpatialObject obj : objects) {
            rtree.insert(obj);
            System.out.printf("  %s with Hilbert value%n", obj.data);
        }
        
        System.out.println("\nSearch query [25, 55] x [25, 55]:");
        List<SpatialObject> results = rtree.search(new Rectangle(25, 55, 25, 55));
        System.out.println("  Found: " + results.stream()
            .map(o -> o.data).reduce("", (a, b) -> a + " " + b));
        
        System.out.println("\nKey: Objects spatially clustered by Hilbert ordering!");
    }
}
