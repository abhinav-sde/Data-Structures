/**
 * Basic Geohash + Trie Implementation in Java
 * 
 * Demonstrates geohash encoding and trie-based spatial indexing.
 */

import java.util.*;

class GeoPoint {
    double lat, lng;
    String data;
    
    public GeoPoint(double lat, double lng, String data) {
        this.lat = lat;
        this.lng = lng;
        this.data = data;
    }
    
    public double distanceTo(GeoPoint other) {
        double R = 6371; // Earth radius in km
        double dLat = Math.toRadians(other.lat - lat);
        double dLng = Math.toRadians(other.lng - lng);
        
        double a = Math.sin(dLat/2) * Math.sin(dLat/2) +
                   Math.cos(Math.toRadians(lat)) * Math.cos(Math.toRadians(other.lat)) *
                   Math.sin(dLng/2) * Math.sin(dLng/2);
        double c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
        
        return R * c;
    }
    
    @Override
    public String toString() {
        return data + " (" + lat + ", " + lng + ")";
    }
}

class Geohash {
    private static final String BASE32 = "0123456789bcdefghjkmnpqrstuvwxyz";
    
    public static String encode(double lat, double lng, int precision) {
        StringBuilder hash = new StringBuilder();
        double[] latRange = {-90.0, 90.0};
        double[] lngRange = {-180.0, 180.0};
        
        int bit = 0, ch = 0;
        
        while (hash.length() < precision) {
            if (bit % 2 == 0) {
                double mid = (lngRange[0] + lngRange[1]) / 2;
                if (lng > mid) {
                    ch |= (1 << (4 - bit/2));
                    lngRange[0] = mid;
                } else {
                    lngRange[1] = mid;
                }
            } else {
                double mid = (latRange[0] + latRange[1]) / 2;
                if (lat > mid) {
                    ch |= (1 << (4 - bit/2));
                    latRange[0] = mid;
                } else {
                    latRange[1] = mid;
                }
            }
            
            bit++;
            if (bit == 10) {
                hash.append(BASE32.charAt(ch));
                bit = 0;
                ch = 0;
            }
        }
        
        return hash.toString();
    }
    
    public static GeoPoint decode(String hash) {
        double[] latRange = {-90.0, 90.0};
        double[] lngRange = {-180.0, 180.0};
        boolean isEven = true;
        
        for (char c : hash.toCharArray()) {
            int idx = BASE32.indexOf(c);
            if (idx == -1) continue;
            
            for (int mask = 16; mask > 0; mask >>= 1) {
                if (isEven) {
                    double mid = (lngRange[0] + lngRange[1]) / 2;
                    if ((idx & mask) != 0) {
                        lngRange[0] = mid;
                    } else {
                        lngRange[1] = mid;
                    }
                } else {
                    double mid = (latRange[0] + latRange[1]) / 2;
                    if ((idx & mask) != 0) {
                        latRange[0] = mid;
                    } else {
                        latRange[1] = mid;
                    }
                }
                isEven = !isEven;
            }
        }
        
        double lat = (latRange[0] + latRange[1]) / 2;
        double lng = (lngRange[0] + lngRange[1]) / 2;
        
        return new GeoPoint(lat, lng, "");
    }
    
    public static List<String> neighbors(String hash) {
        List<String> result = new ArrayList<>();
        GeoPoint center = decode(hash);
        
        double latError = 90.0 / Math.pow(2, hash.length() * 2.5);
        double lngError = 180.0 / Math.pow(2, hash.length() * 2.5);
        
        for (int dlat = -1; dlat <= 1; dlat++) {
            for (int dlng = -1; dlng <= 1; dlng++) {
                if (dlat == 0 && dlng == 0) continue;
                
                double lat = center.lat + (dlat * latError);
                double lng = center.lng + (dlng * lngError);
                
                result.add(encode(lat, lng, hash.length()));
            }
        }
        
        return result;
    }
}

class TrieNode {
    Map<Character, TrieNode> children = new HashMap<>();
    List<GeoPoint> points = new ArrayList<>();
    boolean isEnd = false;
}

public class BasicGeohashTrie {
    private TrieNode root;
    private int precision;
    
    public BasicGeohashTrie(int precision) {
        this.root = new TrieNode();
        this.precision = precision;
    }
    
    public void insert(GeoPoint point) {
        String hash = Geohash.encode(point.lat, point.lng, precision);
        TrieNode current = root;
        
        for (char c : hash.toCharArray()) {
            current.children.putIfAbsent(c, new TrieNode());
            current = current.children.get(c);
        }
        
        current.isEnd = true;
        current.points.add(point);
    }
    
    public List<GeoPoint> search(String hash) {
        TrieNode current = root;
        
        for (char c : hash.toCharArray()) {
            if (!current.children.containsKey(c)) {
                return new ArrayList<>();
            }
            current = current.children.get(c);
        }
        
        return current.points;
    }
    
    public List<GeoPoint> prefixSearch(String prefix) {
        TrieNode current = root;
        
        for (char c : prefix.toCharArray()) {
            if (!current.children.containsKey(c)) {
                return new ArrayList<>();
            }
            current = current.children.get(c);
        }
        
        List<GeoPoint> results = new ArrayList<>();
        collectPoints(current, results);
        return results;
    }
    
    private void collectPoints(TrieNode node, List<GeoPoint> results) {
        if (node == null) return;
        
        results.addAll(node.points);
        
        for (TrieNode child : node.children.values()) {
            collectPoints(child, results);
        }
    }
    
    public List<GeoPoint> findNearby(double lat, double lng, int searchDepth) {
        String centerHash = Geohash.encode(lat, lng, precision);
        List<GeoPoint> results = new ArrayList<>(search(centerHash));
        
        if (searchDepth > 0) {
            for (String hash : Geohash.neighbors(centerHash)) {
                results.addAll(search(hash));
            }
        }
        
        return results;
    }
    
    public List<GeoPoint> kNearest(double lat, double lng, int k) {
        GeoPoint query = new GeoPoint(lat, lng, "");
        
        for (int depth = 1; depth <= precision; depth++) {
            String prefix = Geohash.encode(lat, lng, depth);
            List<GeoPoint> candidates = prefixSearch(prefix);
            
            if (candidates.size() >= k) {
                candidates.sort(Comparator.comparingDouble(p -> query.distanceTo(p)));
                return candidates.subList(0, Math.min(candidates.size(), k));
            }
        }
        
        List<GeoPoint> all = prefixSearch("");
        all.sort(Comparator.comparingDouble(p -> query.distanceTo(p)));
        return all.subList(0, Math.min(all.size(), k));
    }
    
    public static void main(String[] args) {
        System.out.println("=== Geohash + Trie Demo ===\n");
        
        // Example 1: Encoding
        System.out.println("1. Geohash Encoding:");
        double lat = 37.7749, lng = -122.4194;
        String hash = Geohash.encode(lat, lng, 6);
        System.out.println("  Location: (" + lat + ", " + lng + ")");
        System.out.println("  Geohash: " + hash);
        
        // Example 2: Build trie
        System.out.println("\n2. Building Geohash Trie:");
        BasicGeohashTrie trie = new BasicGeohashTrie(6);
        
        List<GeoPoint> locations = Arrays.asList(
            new GeoPoint(37.7749, -122.4194, "San Francisco"),
            new GeoPoint(37.7849, -122.4094, "Fisherman's Wharf"),
            new GeoPoint(37.8044, -122.2712, "Oakland"),
            new GeoPoint(34.0522, -118.2437, "Los Angeles"),
            new GeoPoint(40.7128, -74.0060, "New York")
        );
        
        for (GeoPoint loc : locations) {
            trie.insert(loc);
            System.out.println("  Inserted: " + loc.data);
        }
        
        // Example 3: Prefix search
        System.out.println("\n3. Prefix Search (9q8 = SF Bay Area):");
        List<GeoPoint> sfArea = trie.prefixSearch("9q8");
        System.out.println("  Found " + sfArea.size() + " locations:");
        for (GeoPoint loc : sfArea) {
            System.out.println("    " + loc.data);
        }
        
        // Example 4: K-nearest
        System.out.println("\n4. 3-Nearest Neighbors:");
        List<GeoPoint> knn = trie.kNearest(37.7749, -122.4194, 3);
        for (int i = 0; i < knn.size(); i++) {
            GeoPoint query = new GeoPoint(37.7749, -122.4194, "");
            System.out.printf("  %d. %s (%.2f km)%n", 
                i+1, knn.get(i).data, query.distanceTo(knn.get(i)));
        }
        
        System.out.println("\n=== Demo Complete ===");
    }
}
