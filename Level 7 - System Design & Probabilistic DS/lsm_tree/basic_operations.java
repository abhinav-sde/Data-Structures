import java.util.*;

/**
 * Basic LSM-Tree Operations in Java
 * Implements MemTable (TreeMap) and mock SSTable flushing.
 */
public class basic_operations {

    static class SSTable {
        TreeMap<String, String> data;
        long timestamp;

        SSTable(TreeMap<String, String> data) {
            this.data = new TreeMap<>(data);
            this.timestamp = System.currentTimeMillis();
        }
    }

    private TreeMap<String, String> memTable = new TreeMap<>();
    private final List<SSTable> ssTables = new ArrayList<>();
    private final int threshold;

    public basic_operations(int threshold) {
        this.threshold = threshold;
    }

    public void put(String key, String value) {
        memTable.put(key, value);
        if (memTable.size() >= threshold) {
            flush();
        }
    }

    private void flush() {
        System.out.println("Flushing MemTable to SSTable...");
        ssTables.add(0, new SSTable(memTable)); // Add newest to front
        memTable.clear();
    }

    public String get(String key) {
        // 1. Check MemTable
        if (memTable.containsKey(key)) {
            return memTable.get(key);
        }

        // 2. Check SSTables from newest to oldest
        for (SSTable table : ssTables) {
            if (table.data.containsKey(key)) {
                return table.data.get(key);
            }
        }

        return null;
    }

    public static void main(String[] args) {
        basic_operations lsm = new basic_operations(3);

        System.out.println("Writing and flushing simulation...");
        lsm.put("user:1", "Alice");
        lsm.put("user:2", "Bob");
        lsm.put("user:3", "Charlie"); // Triggers flush
        lsm.put("user:4", "David");
        lsm.put("user:1", "Alice_Updated"); // Overwrite in current memTable

        System.out.println("Key 'user:1': " + lsm.get("user:1"));
        System.out.println("Key 'user:3': " + lsm.get("user:3"));
        System.out.println("Key 'non_existent': " + lsm.get("non_existent"));

        System.out.println("Total SSTables: " + lsm.ssTables.size());
    }
}
