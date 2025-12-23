import java.util.*;

/**
 * Advanced Vector Clock Problems in Java
 * Focuses on Pruning (Garbage Collection) to prevent unbounded growth.
 */
public class advanced_problems {

    static class PrunableVectorClock {
        Map<String, Integer> clock = new HashMap<>();
        Map<String, Long> lastUpdate = new HashMap<>(); // Physical time or logical sequence
        int maxNodes;

        PrunableVectorClock(int maxNodes) {
            this.maxNodes = maxNodes;
        }

        public void put(String nodeId, int count) {
            clock.put(nodeId, count);
            lastUpdate.put(nodeId, System.currentTimeMillis());

            if (clock.size() > maxNodes) {
                prune();
            }
        }

        /**
         * Pruning (Garbage Collection): Removes the oldest entry to keep size bounded.
         * Trade-off: Might lead to "False Independence" (missing a causality link).
         */
        private void prune() {
            String oldestNode = null;
            long oldestTime = Long.MAX_VALUE;

            for (Map.Entry<String, Long> entry : lastUpdate.entrySet()) {
                if (entry.getValue() < oldestTime) {
                    oldestTime = entry.getValue();
                    oldestNode = entry.getKey();
                }
            }

            if (oldestNode != null) {
                System.out.println("[Pruning] Removing node '" + oldestNode + "' to save space.");
                clock.remove(oldestNode);
                lastUpdate.remove(oldestNode);
            }
        }

        @Override
        public String toString() {
            return clock.toString() + " (Size: " + clock.size() + ")";
        }
    }

    public static void main(String[] args) throws InterruptedException {
        // Limit to 3 nodes
        PrunableVectorClock pvc = new PrunableVectorClock(3);

        System.out.println("Adding Node A, B, C...");
        pvc.put("A", 1);
        Thread.sleep(10);
        pvc.put("B", 5);
        Thread.sleep(10);
        pvc.put("C", 2);
        System.out.println("Current: " + pvc);

        System.out.println("\nAdding Node D (Should trigger pruning of A)...");
        pvc.put("D", 1);
        System.out.println("Current: " + pvc);

        System.out.println("\nUpdating Node B...");
        pvc.put("B", 6);

        System.out.println("\nAdding Node E (Should trigger pruning of C)...");
        pvc.put("E", 1);
        System.out.println("Final state: " + pvc);
    }
}
