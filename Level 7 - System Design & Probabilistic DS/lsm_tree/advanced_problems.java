import java.util.*;

/**
 * Advanced LSM-Tree Problems in Java
 * Focuses on Bloom Filter optimization for the read path.
 */
public class advanced_problems {

    static class BloomFilter {
        private BitSet bitSet;
        private int size;
        private int numHashFunctions;

        BloomFilter(int expectedElements, double falsePositiveRate) {
            this.size = (int) (-expectedElements * Math.log(falsePositiveRate) / (Math.log(2) * Math.log(2)));
            this.numHashFunctions = (int) (size / expectedElements * Math.log(2));
            this.bitSet = new BitSet(size);
        }

        void add(String key) {
            for (int i = 0; i < numHashFunctions; i++) {
                int hash = hash(key, i);
                bitSet.set(Math.abs(hash % size));
            }
        }

        boolean mightContain(String key) {
            for (int i = 0; i < numHashFunctions; i++) {
                int hash = hash(key, i);
                if (!bitSet.get(Math.abs(hash % size)))
                    return false;
            }
            return true;
        }

        private int hash(String key, int seed) {
            return (key + seed).hashCode();
        }
    }

    static class SSTable {
        TreeMap<String, String> data;
        BloomFilter bloomFilter;

        SSTable(TreeMap<String, String> data) {
            this.data = new TreeMap<>(data);
            this.bloomFilter = new BloomFilter(data.size() + 1, 0.01);
            for (String key : data.keySet())
                bloomFilter.add(key);
        }
    }

    private TreeMap<String, String> memTable = new TreeMap<>();
    private final List<SSTable> ssTables = new ArrayList<>();
    private final int threshold = 5;

    public void put(String key, String val) {
        memTable.put(key, val);
        if (memTable.size() >= threshold)
            flush();
    }

    private void flush() {
        ssTables.add(0, new SSTable(memTable));
        memTable.clear();
    }

    public String get(String key) {
        if (memTable.containsKey(key))
            return memTable.get(key);

        int tablesChecked = 0;
        int bloomFilterSkips = 0;

        for (SSTable table : ssTables) {
            tablesChecked++;
            if (!table.bloomFilter.mightContain(key)) {
                bloomFilterSkips++;
                continue; // Skip the O(log N) map lookup
            }
            if (table.data.containsKey(key)) {
                System.out.println("[Search Stats] Checked: " + tablesChecked + ", Bloom Skips: " + bloomFilterSkips);
                return table.data.get(key);
            }
        }

        System.out.println("[Search Stats] Checked: " + tablesChecked + ", Bloom Skips: " + bloomFilterSkips);
        return null;
    }

    public static void main(String[] args) {
        advanced_problems lsm = new advanced_problems();

        // Fill multiple SSTables
        for (int i = 0; i < 20; i++) {
            lsm.put("key_" + i, "val_" + i);
        }

        System.out.println("--- Query existing key ---");
        System.out.println("Result: " + lsm.get("key_5"));

        System.out.println("\n--- Query non-existent key (Optimized by Bloom Filter) ---");
        System.out.println("Result: " + lsm.get("unknown_key"));
    }
}
