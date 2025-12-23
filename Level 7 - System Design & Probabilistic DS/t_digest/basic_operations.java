import java.util.*;

/**
 * Basic T-Digest Operations in Java
 * Implements a simplified T-Digest with centroid-based clustering.
 */
public class basic_operations {

    static class Centroid implements Comparable<Centroid> {
        double mean;
        double weight;

        Centroid(double mean, double weight) {
            this.mean = mean;
            this.weight = weight;
        }

        @Override
        public int compareTo(Centroid other) {
            return Double.compare(this.mean, other.mean);
        }
    }

    private List<Centroid> centroids = new ArrayList<>();
    private double totalWeight = 0;
    private final double compression; // Compression factor (delta)

    public basic_operations(double compression) {
        this.compression = compression;
    }

    public void add(double value) {
        add(value, 1.0);
    }

    public void add(double value, double weight) {
        centroids.add(new Centroid(value, weight));
        totalWeight += weight;
        if (centroids.size() > compression * 10) {
            compress();
        }
    }

    public void compress() {
        if (centroids.isEmpty())
            return;
        Collections.sort(centroids);

        List<Centroid> compressed = new ArrayList<>();
        Centroid current = centroids.get(0);
        double weightSoFar = 0;

        for (int i = 1; i < centroids.size(); i++) {
            Centroid next = centroids.get(i);
            double q = (weightSoFar + (current.weight + next.weight) / 2.0) / totalWeight;

            // Scaling function (Simplified): Limit centroid size based on its position
            double k = totalWeight * (q * (1 - q)) / compression;

            if (current.weight + next.weight <= k) {
                // Merge
                double newWeight = current.weight + next.weight;
                current.mean = (current.mean * current.weight + next.mean * next.weight) / newWeight;
                current.weight = newWeight;
            } else {
                compressed.add(current);
                weightSoFar += current.weight;
                current = next;
            }
        }
        compressed.add(current);
        centroids = compressed;
    }

    public int size() {
        return centroids.size();
    }

    public static void main(String[] args) {
        basic_operations td = new basic_operations(100);
        Random rand = new Random();

        System.out.println("Adding 10,000 random values...");
        for (int i = 0; i < 10000; i++) {
            td.add(rand.nextDouble() * 100);
        }

        td.compress();
        System.out.println("Centroids count after compression: " + td.size());
    }
}
