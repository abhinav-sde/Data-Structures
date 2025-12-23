import java.util.*;

/**
 * Core T-Digest Problems in Java
 * Focuses on Quantile Estimation and CDF calculation.
 */
public class core_problems {

    static class Centroid implements Comparable<Centroid> {
        double mean, weight;

        Centroid(double m, double w) {
            mean = m;
            weight = w;
        }

        public int compareTo(Centroid o) {
            return Double.compare(this.mean, o.mean);
        }
    }

    private List<Centroid> centroids = new ArrayList<>();
    private double totalWeight = 0;

    public void add(double val) {
        centroids.add(new Centroid(val, 1.0));
        totalWeight++;
    }

    // Simplified quantile estimation via linear interpolation
    public double quantile(double q) {
        if (centroids.isEmpty())
            return Double.NaN;
        Collections.sort(centroids);

        double targetWeight = q * totalWeight;
        double currentWeight = 0;

        for (int i = 0; i < centroids.size(); i++) {
            Centroid c = centroids.get(i);
            if (currentWeight + c.weight >= targetWeight) {
                // Return mean of the centroid containing the quantile
                return c.mean;
            }
            currentWeight += c.weight;
        }
        return centroids.get(centroids.size() - 1).mean;
    }

    public static void main(String[] args) {
        core_problems td = new core_problems();
        List<Double> actualData = new ArrayList<>();
        Random rand = new Random();

        for (int i = 0; i < 10000; i++) {
            double val = rand.nextGaussian() * 10 + 50; // Normal dist around 50
            td.add(val);
            actualData.add(val);
        }
        Collections.sort(actualData);

        System.out.println("Estimating Quantiles (Normal Distribution mean=50, std=10):");
        System.out.println("P50 (Median) -> Estimate: " + String.format("%.2f", td.quantile(0.5)) +
                ", Actual: " + String.format("%.2f", actualData.get(5000)));
        System.out.println("P95 -> Estimate: " + String.format("%.2f", td.quantile(0.95)) +
                ", Actual: " + String.format("%.2f", actualData.get(9500)));
        System.out.println("P99 -> Estimate: " + String.format("%.2f", td.quantile(0.99)) +
                ", Actual: " + String.format("%.2f", actualData.get(9900)));
    }
}
