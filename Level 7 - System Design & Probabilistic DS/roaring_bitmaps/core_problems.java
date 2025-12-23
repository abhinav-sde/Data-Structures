
import java.util.*;

/**
 * Core Roaring Bitmap Problems in Java
 * Focuses on Set Operations (AND, OR) and Space Comparison.
 */
public class core_problems {

    static class SimpleRoaring {
        Map<Integer, BitSet> chunks = new HashMap<>();

        void add(int x) {
            int key = x >>> 16;
            int val = x & 0xFFFF;
            chunks.computeIfAbsent(key, k -> new BitSet(65536)).set(val);
        }

        static SimpleRoaring and(SimpleRoaring r1, SimpleRoaring r2) {
            SimpleRoaring result = new SimpleRoaring();
            for (Integer key : r1.chunks.keySet()) {
                if (r2.chunks.containsKey(key)) {
                    BitSet b1 = r1.chunks.get(key);
                    BitSet b2 = r2.chunks.get(key);
                    BitSet intersect = (BitSet) b1.clone();
                    intersect.and(b2);
                    if (!intersect.isEmpty()) {
                        result.chunks.put(key, intersect);
                    }
                }
            }
            return result;
        }

        static SimpleRoaring or(SimpleRoaring r1, SimpleRoaring r2) {
            SimpleRoaring result = new SimpleRoaring();
            Set<Integer> allKeys = new HashSet<>(r1.chunks.keySet());
            allKeys.addAll(r2.chunks.keySet());
            for (Integer key : allKeys) {
                BitSet b1 = r1.chunks.getOrDefault(key, new BitSet(65536));
                BitSet b2 = r2.chunks.getOrDefault(key, new BitSet(65536));
                BitSet union = (BitSet) b1.clone();
                union.or(b2);
                result.chunks.put(key, union);
            }
            return result;
        }

        int cardinality() {
            int count = 0;
            for (BitSet bs : chunks.values())
                count += bs.cardinality();
            return count;
        }
    }

    public static void main(String[] args) {
        SimpleRoaring s1 = new SimpleRoaring();
        SimpleRoaring s2 = new SimpleRoaring();

        // Evens
        for (int i = 0; i < 10000; i += 2)
            s1.add(i);
        // Multiples of 3
        for (int i = 0; i < 10000; i += 3)
            s2.add(i);

        System.out.println("Set 1 (Evens < 10000) Cardinality: " + s1.cardinality());
        System.out.println("Set 2 (Mult of 3 < 10000) Cardinality: " + s2.cardinality());

        SimpleRoaring intersection = SimpleRoaring.and(s1, s2);
        System.out.println("Intersection (Mult of 6) Cardinality: " + intersection.cardinality());
        System.out.println("Expected (10000/6): " + (10000 / 6 + 1));

        SimpleRoaring union = SimpleRoaring.or(s1, s2);
        System.out.println("Union Cardinality: " + union.cardinality());

        // Memory analysis (Mental model)
        System.out.println("\nSpace Optimization Analysis:");
        System.out.println("- Standard Java BitSet(1000000) uses ~125KB regardless of set size.");
        System.out.println("- Roaring Bitmap for {1, 1000000} uses ~2 chunks (sparse) -> Very small.");
    }
}
