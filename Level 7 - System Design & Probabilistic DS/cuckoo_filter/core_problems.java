import java.util.*;

/**
 * Core Cuckoo Filter Problems in Java
 * Focuses on Empirical False Positive Rate (FPR) measurement.
 */
public class core_problems {

    public static void main(String[] args) {
        int capacity = 1000;
        basic_operations filter = new basic_operations(capacity);

        Set<String> inserted = new HashSet<>();

        // 1. Fill to 50% capacity
        System.out.println("Inserting 500 items...");
        for (int i = 0; i < 500; i++) {
            String item = "item_" + i;
            if (filter.insert(item)) {
                inserted.add(item);
            }
        }

        // 2. Measure False Positives
        int falsePositives = 0;
        int trials = 10000;
        System.out.println("Running " + trials + " trials for non-existent items...");
        for (int i = 0; i < trials; i++) {
            String testItem = "ghost_" + i;
            if (filter.lookup(testItem)) {
                falsePositives++;
            }
        }

        double fpr = (double) falsePositives / trials * 100;
        System.out.println("False Positives: " + falsePositives);
        System.out.println("Empirical FPR: " + String.format("%.4f", fpr) + "%");
        System.out.println("Theoretical FPR (8-bit fp): ~0.78%");

        // 3. Test Deletion Impact
        System.out.println("\nDeleting 100 items...");
        for (int i = 0; i < 100; i++) {
            filter.delete("item_" + i);
        }

        System.out.println("Lookup of deleted item_0: " + filter.lookup("item_0"));
        System.out.println("Lookup of existing item_200: " + filter.lookup("item_200"));
    }
}
