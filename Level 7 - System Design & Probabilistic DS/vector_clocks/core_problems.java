import java.util.*;

/**
 * Core Vector Clock Problems in Java
 * Simulation of a Distributed Key-Value Store with Conflict Detection.
 */
public class core_problems {

    static class VersionedValue {
        String value;
        Map<String, Integer> vectorClock;

        VersionedValue(String value, Map<String, Integer> vc) {
            this.value = value;
            this.vectorClock = new HashMap<>(vc);
        }

        @Override
        public String toString() {
            return "'" + value + "' VC: " + vectorClock;
        }
    }

    static class DistributedKVStore {
        Map<String, List<VersionedValue>> store = new HashMap<>();

        public void update(String key, String newValue, Map<String, Integer> newClock) {
            List<VersionedValue> existing = store.getOrDefault(key, new ArrayList<>());
            List<VersionedValue> survivors = new ArrayList<>();
            boolean concurrent = false;

            for (VersionedValue v : existing) {
                basic_operations.Comparison comp = basic_operations.compare(newClock, v.vectorClock);
                if (comp == basic_operations.Comparison.AFTER) {
                    // New update is newer, discard old
                    continue;
                } else if (comp == basic_operations.Comparison.BEFORE) {
                    // New update is older (stale), ignore it
                    return;
                } else if (comp == basic_operations.Comparison.CONCURRENT) {
                    survivors.add(v);
                    concurrent = true;
                }
            }

            survivors.add(new VersionedValue(newValue, newClock));
            store.put(key, survivors);

            if (concurrent) {
                System.out.println("(!) Conflict detected for key '" + key + "'. Multiple versions stored.");
            }
        }

        public void printState(String key) {
            System.out.println("State for '" + key + "': " + store.get(key));
        }
    }

    public static void main(String[] args) {
        DistributedKVStore kv = new DistributedKVStore();

        basic_operations nodeA = new basic_operations("A");
        basic_operations nodeB = new basic_operations("B");

        // 1. Concurrent updates
        System.out.println("Event 1: Node A updates 'price' to 100");
        nodeA.increment();
        kv.update("price", "100", nodeA.getClockCopy());

        System.out.println("Event 2: Node B updates 'price' to 120 (unaware of A)");
        nodeB.increment();
        kv.update("price", "120", nodeB.getClockCopy());

        kv.printState("price"); // Should have 2 versions

        // 2. Causal update
        System.out.println("\nEvent 3: Node A merges B's state and updates 'price' to 110 (Resolves conflict)");
        nodeA.merge(nodeB.getClockCopy());
        nodeA.increment();
        kv.update("price", "110", nodeA.getClockCopy());

        kv.printState("price"); // Should have 1 version
    }
}
