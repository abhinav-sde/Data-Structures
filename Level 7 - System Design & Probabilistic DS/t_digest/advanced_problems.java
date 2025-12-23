import java.util.*;

/**
 * Advanced T-Digest Problems in Java
 * Focuses on merging multiple independent T-Digests.
 */
public class advanced_problems {

    static class SimpleTDigest {
        List<basic_operations.Centroid> centroids = new ArrayList<>();
        double totalWeight = 0;

        void add(double val) {
            centroids.add(new basic_operations.Centroid(val, 1.0));
            totalWeight++;
        }

        void merge(SimpleTDigest other) {
            this.centroids.addAll(other.centroids);
            this.totalWeight += other.totalWeight;
            // Re-compression would happen here in a real impl
        }

        double getQuantile(double q) {
            Collections.sort(centroids);
            double target = q * totalWeight;
            double current = 0;
            for (basic_operations.Centroid c : centroids) {
                if (current + c.weight >= target)
                    return c.mean;
                current += c.weight;
            }
            return centroids.get(centroids.size() - 1).mean;
        }
    }

    public static void main(String[] args) {
        SimpleTDigest regionA = new SimpleTDigest();
        SimpleTDigest regionB = new SimpleTDigest();

        // Simulate two different data streams
        for (int i = 0; i < 5000; i++)
            regionA.add(i);
        for (int i = 5000; i < 10000; i++)
            regionB.add(i);

        System.out.println("Region A P50: " + regionA.getQuantile(0.5)); // ~2500
        System.out.println("Region B P50: " + regionB.getQuantile(0.5)); // ~7500

        System.out.println("\nMerging Region A and Region B...");
        regionA.merge(regionB);
        System.out.println("Global P50: " + regionA.getQuantile(0.5)); // ~5000
        System.out.println("Global P99: " + regionA.getQuantile(0.99)); // ~9900
    }
}
