import java.util.*;

/**
 * Advanced Consistent Hashing Problems in Java
 * Implements Weighted Consistent Hashing.
 * Servers with higher capacity (weight) get more virtual nodes.
 */
public class advanced_problems {

    static class WeightedConsistentHash {
        private final TreeMap<Integer, String> ring = new TreeMap<>();
        private final int baseReplicas;

        public WeightedConsistentHash(int baseReplicas) {
            this.baseReplicas = baseReplicas;
        }

        public void addNode(String node, int weight) {
            // Number of virtual nodes is proportional to weight
            int replicas = baseReplicas * weight;
            for (int i = 0; i < replicas; i++) {
                ring.put((node + "_vnode_" + i).hashCode(), node);
            }
        }

        public String getNode(String key) {
            if (ring.isEmpty())
                return null;
            int hash = key.hashCode();
            Map.Entry<Integer, String> entry = ring.ceilingEntry(hash);
            return (entry == null) ? ring.firstEntry().getValue() : entry.getValue();
        }
    }

    public static void main(String[] args) {
        WeightedConsistentHash ch = new WeightedConsistentHash(10);

        // Server A is 3x more powerful than B
        ch.addNode("PowerServer_A", 3);
        ch.addNode("StandardServer_B", 1);

        Map<String, Integer> load = new HashMap<>();
        for (int i = 0; i < 10000; i++) {
            String node = ch.getNode("req_" + i);
            load.put(node, load.getOrDefault(node, 0) + 1);
        }

        System.out.println("Weighted Load Distribution (Server A has 3x weight):");
        load.forEach((k, v) -> System.out.println(k + ": " + v + " requests"));

        double ratio = (double) load.get("PowerServer_A") / load.get("StandardServer_B");
        System.out.println("\nMeasured Ratio (A/B): " + String.format("%.2f", ratio));
        System.out.println("Expected Ratio: 3.00");
    }
}
