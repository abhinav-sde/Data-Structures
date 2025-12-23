import java.util.*;

/**
 * Basic Vector Clock Operations in Java
 * Implements increment, merge, and comparison for causality detection.
 */
public class basic_operations {

    public enum Comparison {
        BEFORE, AFTER, EQUAL, CONCURRENT
    }

    private final String nodeId;
    private final Map<String, Integer> clock;

    public basic_operations(String nodeId) {
        this.nodeId = nodeId;
        this.clock = new HashMap<>();
        this.clock.put(nodeId, 0);
    }

    // Constructor for creating copies
    private basic_operations(String nodeId, Map<String, Integer> clock) {
        this.nodeId = nodeId;
        this.clock = new HashMap<>(clock);
    }

    public void increment() {
        clock.put(nodeId, clock.getOrDefault(nodeId, 0) + 1);
    }

    public void merge(Map<String, Integer> otherClock) {
        for (Map.Entry<String, Integer> entry : otherClock.entrySet()) {
            int currentVal = clock.getOrDefault(entry.getKey(), 0);
            clock.put(entry.getKey(), Math.max(currentVal, entry.getValue()));
        }
        increment();
    }

    public Map<String, Integer> getClockCopy() {
        return new HashMap<>(clock);
    }

    public static Comparison compare(Map<String, Integer> v1, Map<String, Integer> v2) {
        boolean lessThan = false;
        boolean greaterThan = false;

        Set<String> allKeys = new HashSet<>(v1.keySet());
        allKeys.addAll(v2.keySet());

        for (String node : allKeys) {
            int c1 = v1.getOrDefault(node, 0);
            int c2 = v2.getOrDefault(node, 0);

            if (c1 < c2)
                lessThan = true;
            else if (c1 > c2)
                greaterThan = true;
        }

        if (lessThan && greaterThan)
            return Comparison.CONCURRENT;
        if (lessThan)
            return Comparison.BEFORE;
        if (greaterThan)
            return Comparison.AFTER;
        return Comparison.EQUAL;
    }

    @Override
    public String toString() {
        return "Node[" + nodeId + "]: " + clock.toString();
    }

    public static void main(String[] args) {
        basic_operations nodeA = new basic_operations("A");
        basic_operations nodeB = new basic_operations("B");

        nodeA.increment();
        nodeB.increment();

        System.out.println("After one local event each:");
        System.out.println(nodeA);
        System.out.println(nodeB);
        System.out.println("Comparison A vs B: " + compare(nodeA.getClockCopy(), nodeB.getClockCopy())); // CONCURRENT

        System.out.println("\nNode A sends message to Node B...");
        nodeA.increment(); // Events on A before sending
        nodeB.merge(nodeA.getClockCopy());

        System.out.println("After merge:");
        System.out.println(nodeA);
        System.out.println(nodeB);
        System.out.println("Comparison A vs B: " + compare(nodeA.getClockCopy(), nodeB.getClockCopy())); // BEFORE (A <
                                                                                                         // B)
    }
}
