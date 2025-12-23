import java.util.LinkedList;

// Simple Hash Table using Chaining
class HashTable {
    private static class Entry {
        String key;
        String value;

        Entry(String key, String value) {
            this.key = key;
            this.value = value;
        }
    }

    private int buckets;
    private LinkedList<Entry>[] table;

    public HashTable(int size) {
        buckets = size;
        table = new LinkedList[size];
        for (int i = 0; i < size; i++) {
            table[i] = new LinkedList<>();
        }
    }

    private int hashFunction(String key) {
        int hash = 0;
        for (int i = 0; i < key.length(); i++) {
            hash = (hash * 31 + key.charAt(i)) % buckets;
        }
        return Math.abs(hash);
    }

    public void insert(String key, String value) {
        int index = hashFunction(key);
        for (Entry e : table[index]) {
            if (e.key.equals(key)) {
                e.value = value;
                return;
            }
        }
        table[index].add(new Entry(key, value));
    }

    public String search(String key) {
        int index = hashFunction(key);
        for (Entry e : table[index]) {
            if (e.key.equals(key)) {
                return e.value;
            }
        }
        return "Not Found";
    }

    public void remove(String key) {
        int index = hashFunction(key);
        table[index].removeIf(e -> e.key.equals(key));
    }

    public void printTable() {
        for (int i = 0; i < buckets; i++) {
            System.out.print(i + ": ");
            for (Entry e : table[i]) {
                System.out.print("[" + e.key + ":" + e.value + "] -> ");
            }
            System.out.println("NULL");
        }
    }

    public static void main(String[] args) {
        HashTable ht = new HashTable(10);
        ht.insert("name", "Bob");
        ht.insert("role", "Developer");
        ht.insert("lang", "Java");

        System.out.println("Search 'role': " + ht.search("role"));
        ht.printTable();

        ht.remove("lang");
        System.out.println("After removing 'lang':");
        ht.printTable();
    }
}
