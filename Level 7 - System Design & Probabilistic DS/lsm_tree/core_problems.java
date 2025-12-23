import java.util.*;

/**
 * Core LSM-Tree Problems in Java
 * Focuses on Compaction (Merging SSTables) and Tombstone-based Deletions.
 */
public class core_problems {

    static class SSTable {
        TreeMap<String, String> data;
        long id;

        SSTable(TreeMap<String, String> data, long id) {
            this.data = new TreeMap<>(data);
            this.id = id;
        }
    }

    private TreeMap<String, String> memTable = new TreeMap<>();
    private final List<SSTable> level0 = new ArrayList<>();
    private final List<SSTable> level1 = new ArrayList<>();
    private int nextId = 1;
    private final String TOMBSTONE = "__DELETED__";

    public void put(String key, String value) {
        memTable.put(key, value);
    }

    public void delete(String key) {
        memTable.put(key, TOMBSTONE);
    }

    public void flush() {
        if (memTable.isEmpty())
            return;
        System.out.println("Flushing MemTable to Level 0...");
        level0.add(0, new SSTable(memTable, nextId++));
        memTable.clear();

        if (level0.size() >= 3) {
            compact();
        }
    }

    /**
     * Simulation of Compaction: Merges all Level 0 SSTables into Level 1.
     * Keeps only the latest value for each key and removes tombstones.
     */
    private void compact() {
        System.out.println("Triggering Compaction (L0 -> L1)...");
        TreeMap<String, String> merged = new TreeMap<>();

        // Merge from oldest L0 to newest L0 to ensure newest overwrites
        for (int i = level0.size() - 1; i >= 0; i--) {
            merged.putAll(level0.get(i).data);
        }

        // Remove tombstones in final level (simplification)
        merged.entrySet().removeIf(entry -> entry.getValue().equals(TOMBSTONE));

        level1.add(new SSTable(merged, nextId++));
        level0.clear();
        System.out.println("Compaction complete. New Level 1 SSTable size: " + merged.size());
    }

    public String get(String key) {
        if (memTable.containsKey(key)) {
            String val = memTable.get(key);
            return val.equals(TOMBSTONE) ? null : val;
        }

        for (SSTable table : level0) {
            if (table.data.containsKey(key)) {
                String val = table.data.get(key);
                return val.equals(TOMBSTONE) ? null : val;
            }
        }

        for (SSTable table : level1) {
            if (table.data.containsKey(key)) {
                String val = table.data.get(key);
                return val.equals(TOMBSTONE) ? null : val;
            }
        }

        return null;
    }

    public static void main(String[] args) {
        core_problems lsm = new core_problems();

        lsm.put("k1", "v1");
        lsm.put("k2", "v2");
        lsm.flush();

        lsm.put("k1", "v1_new");
        lsm.put("k3", "v3");
        lsm.flush();

        lsm.delete("k2");
        lsm.put("k4", "v4");
        lsm.flush(); // This should trigger compaction

        System.out.println("\nQuerying after compaction:");
        System.out.println("k1: " + lsm.get("k1")); // v1_new
        System.out.println("k2: " + lsm.get("k2")); // null (deleted)
        System.out.println("k3: " + lsm.get("k3")); // v3
        System.out.println("k4: " + lsm.get("k4")); // v4
    }
}
