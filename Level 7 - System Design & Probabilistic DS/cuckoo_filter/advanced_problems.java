import java.util.*;

/**
 * Advanced Cuckoo Filter Problems in Java
 * Focuses on Capacity Saturation and Load Factor analysis.
 */
public class advanced_problems {

    public static void main(String[] args) {
        int capacity = 1000;
        basic_operations filter = new basic_operations(capacity);

        System.out.println("Filling filter until insertion failure...");
        int count = 0;
        while (count < 2000) {
            if (!filter.insert("element_" + count)) {
                break;
            }
            count++;
        }

        double loadFactor = (double) count / capacity * 100;
        System.out.println("Insertion failed at count: " + count);
        System.out.println("Achieved Load Factor: " + String.format("%.2f", loadFactor) + "%");
        System.out.println("Note: Cuckoo filters typically achieve 90-95% load factor with 4-slot buckets.");

        System.out.println("\nTesting deletion to free up space...");
        for (int i = 0; i < 100; i++) {
            filter.delete("element_" + i);
        }

        System.out.println("Trying to insert after deletion...");
        System.out.println("Insert successful: " + filter.insert("new_element_999"));
    }
}
