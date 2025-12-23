import java.util.*;

/**
 * Core Consistent Hashing Problems in Java
 * Focuses on measuring Load Distribution and Churn.
 */
public class core_problems {

    static class ConsistentHash {
        TreeMap<Integer, String> ring = new TreeMap<>();
        int replicas;

        ConsistentHash(int replicas) {
            this.replicas = replicas;
        }

        void add(String node) {
            for (int i = 0; i < replicas; i++)
                ring.put((node + i).hashCode(), node);
        }

        void remove(String node) {
            for (int i = 0; i < replicas; i++)
                ring.remove((node + i).hashCode());
        }

        String get(String key) {
            if (ring.isEmpty())
                return null;
            int hash = key.hashCode();
            Map.Entry<Integer, String> entry = ring.ceilingEntry(hash);
            return (entry == null) ? ring.firstEntry().getValue() : entry.getValue();
        }
    }

    public static void main(String[] args) {
        ConsistentHash ch = new ConsistentHash(50);
        String[] servers = { "S1", "S2", "S3", "S4", "S5" };
        for (String s : servers)
            ch.add(s);

        // Simulation: Distribute 10,000 keys
        Map<String, Integer> distribution = new HashMap<>();
        for (int i = 0; i < 10000; i++) {
            String node = ch.get("key_" + i);
            distribution.put(node, distribution.getOrDefault(node, 0) + 1);
        }

        System.out.println("Initial Load Distribution (10k keys):");
        distribution.forEach((k, v) -> System.out.println(k + ": " + v + " keys"));

        // Churn Test: Remove S2
        System.out.println("\nRemoving server S2...");
        int movedKeys = 0;
        for (int i = 0; i < 10000; i++) {
            String oldNode = ch.get("key_" + i);
            ch.remove("S2"); // Temporarily remove to see where it would go
            String newNode = ch.get("key_" + i);
            if (!oldNode.equals(newNode))
                movedKeys++;
            ch.add("S2"); // Add back for next check
        }

        System.out.println("Keys that would move if S2 is removed: " + movedKeys);
        System.out.println("Ideal churn (1/N = 1/5): 2000. Actual: " + movedKeys);
    }
}
