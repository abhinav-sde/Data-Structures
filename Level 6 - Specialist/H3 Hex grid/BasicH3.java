/**
 * Basic H3-style Hexagonal Grid Implementation in Java (Simplified Educational Version)
 * 
 * Demonstrates core H3 concepts: coordinate conversion, indexing, and basic operations.
 * This is a simplified version for learning - use official H3 library for production.
 */

import java.util.*;

// Hex coordinate using axial coordinates (q, r)
class HexCoord {
    int q, r;
    
    public HexCoord(int q, int r) {
        this.q = q;
        this.r = r;
    }
    
    public int s() {
        return -q - r;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof HexCoord)) return false;
        HexCoord other = (HexCoord) obj;
        return q == other.q && r == other.r;
    }
    
    @Override
    public int hashCode() {
        return Objects.hash(q, r);
    }
}

// Geographic coordinate
class GeoCoord {
    double lat, lng;
    
    public GeoCoord(double lat, double lng) {
        this.lat = lat;
        this.lng = lng;
    }
    
    @Override
    public String toString() {
        return String.format("(%.4f, %.4f)", lat, lng);
    }
}

// Simplified H3 Index (educational - not actual H3 format)
class H3Index {
    int resolution;
    HexCoord coord;
    
    public H3Index(int resolution, HexCoord coord) {
        this.resolution = resolution;
        this.coord = coord;
    }
    
    @Override
    public String toString() {
        return String.format("R%d_Q%d_R%d", resolution, coord.q, coord.r);
    }
    
    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof H3Index)) return false;
        H3Index other = (H3Index) obj;
        return resolution == other.resolution && coord.equals(other.coord);
    }
    
    @Override
    public int hashCode() {
        return Objects.hash(resolution, coord);
    }
}

// Basic H3-style operations
public class BasicH3 {
    private static final double HEX_SIZE_BASE = 100.0;  // km at resolution 0
    private static final double SQRT3 = Math.sqrt(3);
    
    // Get hexagon size for resolution (simplified)
    private static double getHexSize(int resolution) {
        return HEX_SIZE_BASE / Math.pow(7, resolution * 0.5);
    }
    
    // Convert lat/lng to hexagon (simplified flat projection)
    private static HexCoord geoToHex(double lat, double lng, int resolution) {
        double hexSize = getHexSize(resolution);
        
        // Simplified conversion (not actual H3 icosahedral projection)
        double x = lng;
        double y = lat;
        
        // Convert to hex axial coordinates
        double q = (SQRT3/3.0 * x - 1.0/3.0 * y) / hexSize;
        double r = (2.0/3.0 * y) / hexSize;
        
        // Round to nearest hex
        return hexRound(q, r);
    }
    
    // Round fractional hex coordinates to nearest hex
    private static HexCoord hexRound(double q, double r) {
        double s = -q - r;
        
        int rq = (int) Math.round(q);
        int rr = (int) Math.round(r);
        int rs = (int) Math.round(s);
        
        double q_diff = Math.abs(rq - q);
        double r_diff = Math.abs(rr - r);
        double s_diff = Math.abs(rs - s);
        
        if (q_diff > r_diff && q_diff > s_diff) {
            rq = -rr - rs;
        } else if (r_diff > s_diff) {
            rr = -rq - rs;
        }
        
        return new HexCoord(rq, rr);
    }
    
    // Convert geographic coordinate to H3 index
    public static H3Index geoToH3(double lat, double lng, int resolution) {
        HexCoord hex = geoToHex(lat, lng, resolution);
        return new H3Index(resolution, hex);
    }
    
    // Convert H3 index to geographic coordinate (center)
    public static GeoCoord h3ToGeo(H3Index h3) {
        double hexSize = getHexSize(h3.resolution);
        
        // Convert hex coordinates to lat/lng
        double x = hexSize * (SQRT3 * h3.coord.q + SQRT3/2.0 * h3.coord.r);
        double y = hexSize * (3.0/2.0 * h3.coord.r);
        
        return new GeoCoord(y, x);
    }
    
    // Get the 6 neighbors of a hexagon
    public static List<H3Index> getNeighbors(H3Index h3) {
        List<H3Index> neighbors = new ArrayList<>();
        
        // 6 directions in axial coordinates
        int[][] directions = {
            {1, 0}, {1, -1}, {0, -1},
            {-1, 0}, {-1, 1}, {0, 1}
        };
        
        for (int[] dir : directions) {
            HexCoord neighbor = new HexCoord(
                h3.coord.q + dir[0],
                h3.coord.r + dir[1]
            );
            neighbors.add(new H3Index(h3.resolution, neighbor));
        }
        
        return neighbors;
    }
    
    // Get all hexagons within k steps (k-ring)
    public static List<H3Index> kRing(H3Index h3, int k) {
        List<H3Index> results = new ArrayList<>();
        
        for (int dq = -k; dq <= k; dq++) {
            for (int dr = Math.max(-k, -dq - k); dr <= Math.min(k, -dq + k); dr++) {
                HexCoord hex = new HexCoord(h3.coord.q + dq, h3.coord.r + dr);
                results.add(new H3Index(h3.resolution, hex));
            }
        }
        
        return results;
    }
    
    // Get hollow ring at distance k
    public static List<H3Index> hexRing(H3Index h3, int k) {
        if (k == 0) {
            return Collections.singletonList(h3);
        }
        
        List<H3Index> results = new ArrayList<>();
        
        // Start at k steps from hex in direction 4
        HexCoord current = new HexCoord(h3.coord.q - k, h3.coord.r + k);
        
        // 6 directions for the ring
        int[][] directions = {
            {1, 0}, {1, -1}, {0, -1},
            {-1, 0}, {-1, 1}, {0, 1}
        };
        
        // Walk around the ring
        for (int[] dir : directions) {
            for (int i = 0; i < k; i++) {
                results.add(new H3Index(h3.resolution, current));
                current = new HexCoord(current.q + dir[0], current.r + dir[1]);
            }
        }
        
        return results;
    }
    
    // Calculate grid distance between two hexagons
    public static int gridDistance(H3Index a, H3Index b) {
        if (a.resolution != b.resolution) {
            System.err.println("Cannot calculate distance between different resolutions");
            return -1;
        }
        
        int dq = Math.abs(a.coord.q - b.coord.q);
        int dr = Math.abs(a.coord.r - b.coord.r);
        int ds = Math.abs(a.coord.s() - b.coord.s());
        
        return Math.max(Math.max(dq, dr), ds);
    }
    
    // Get area of hexagon at resolution (km²)
    public static double hexArea(int resolution) {
        double hexSize = getHexSize(resolution);
        return 2.598 * hexSize * hexSize;  // Area = (3√3/2) * side²
    }
    
    // Example usage
    public static void main(String[] args) {
        System.out.println("=== Basic H3-Style Hexagonal Grid Demo ===\n");
        System.out.println("Note: This is a simplified educational implementation.");
        System.out.println("For production use, please use official H3 library.\n");
        
        // Example 1: Convert coordinates to H3
        System.out.println("1. Geographic to H3 Index:");
        double lat = 37.7749, lng = -122.4194;  // San Francisco
        int resolution = 8;
        
        H3Index h3 = geoToH3(lat, lng, resolution);
        System.out.println("  Coords: (" + lat + ", " + lng + ")");
        System.out.println("  H3 Index: " + h3);
        System.out.println("  Resolution: " + h3.resolution);
        
        // Example 2: Convert H3 back to coordinates
        System.out.println("\n2. H3 Index to Geographic:");
        GeoCoord center = h3ToGeo(h3);
        System.out.println("  H3 Index: " + h3);
        System.out.println("  Center: " + center);
        
        // Example 3: Get neighbors
        System.out.println("\n3. Get 6 Neighbors:");
        List<H3Index> neighbors = getNeighbors(h3);
        System.out.println("  Neighbors of " + h3 + ":");
        for (H3Index neighbor : neighbors) {
            System.out.println("    " + neighbor);
        }
        
        // Example 4: k-Ring
        System.out.println("\n4. k-Ring (k=1):");
        List<H3Index> kring1 = kRing(h3, 1);
        System.out.println("  k-Ring contains " + kring1.size() + " hexagons");
        System.out.println("  (1 center + 6 neighbors = 7 total)");
        
        System.out.println("\n5. k-Ring (k=2):");
        List<H3Index> kring2 = kRing(h3, 2);
        System.out.println("  k-Ring contains " + kring2.size() + " hexagons");
        System.out.println("  (1 center + 6 + 12 = 19 total)");
        
        // Example 5: Hex Ring (hollow)
        System.out.println("\n6. Hollow Ring (k=2):");
        List<H3Index> ring2 = hexRing(h3, 2);
        System.out.println("  Hollow ring contains " + ring2.size() + " hexagons");
        
        // Example 6: Grid distance
        System.out.println("\n7. Grid Distance:");
        H3Index h3_2 = geoToH3(37.8, -122.4, resolution);
        int dist = gridDistance(h3, h3_2);
        System.out.println("  Distance between " + h3 + " and " + h3_2 + ": " + dist + " steps");
        
        // Example 7: Hex area
        System.out.println("\n8. Hexagon Area at Resolution " + resolution + ":");
        double area = hexArea(resolution);
        System.out.printf("  Area: %.2f km²%n", area);
        
        System.out.println("\n=== Demo Complete ===");
        System.out.println("Key Concepts Demonstrated:");
        System.out.println("  ✓ Coordinate conversion (geo ↔ H3)");
        System.out.println("  ✓ Neighbor finding (6 adjacent hexagons)");
        System.out.println("  ✓ k-Ring generation (all hexagons within k steps)");
        System.out.println("  ✓ Grid distance calculation");
        System.out.println("  ✓ Hexagon area calculation");
    }
}
