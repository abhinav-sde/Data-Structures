import java.util.*;

/**
 * Basic Cuckoo Filter Operations in Java
 * Implements a simple Cuckoo Filter with 4 slots per bucket and 8-bit
 * fingerprints.
 */
public class basic_operations {

    private static final int SLOTS_PER_BUCKET = 4;
    private static final int MAX_KICKS = 500;

    private final byte[][] buckets;
    private final int numBuckets;
    private final Random random = new Random();

    public basic_operations(int capacity) {
        // Capacity should be power of 2 for efficiency in a real impl
        this.numBuckets = (int) Math.ceil((double) capacity / SLOTS_PER_BUCKET);
        this.buckets = new byte[numBuckets][SLOTS_PER_BUCKET];
    }

    public boolean insert(String item) {
        byte fingerprint = getFingerprint(item);
        int i1 = getHash(item);
        int i2 = getAltIndex(i1, fingerprint);

        if (insertToBucket(i1, fingerprint) || insertToBucket(i2, fingerprint)) {
            return true;
        }

        // Must kick
        int currIndex = random.nextBoolean() ? i1 : i2;
        for (int n = 0; n < MAX_KICKS; n++) {
            int slot = random.nextInt(SLOTS_PER_BUCKET);
            byte kickedFingerprint = buckets[currIndex][slot];
            buckets[currIndex][slot] = fingerprint;

            fingerprint = kickedFingerprint;
            currIndex = getAltIndex(currIndex, fingerprint);

            if (insertToBucket(currIndex, fingerprint)) {
                return true;
            }
        }

        return false; // Filter is full
    }

    public boolean lookup(String item) {
        byte fingerprint = getFingerprint(item);
        int i1 = getHash(item);
        int i2 = getAltIndex(i1, fingerprint);

        return bucketContains(i1, fingerprint) || bucketContains(i2, fingerprint);
    }

    public boolean delete(String item) {
        byte fingerprint = getFingerprint(item);
        int i1 = getHash(item);
        int i2 = getAltIndex(i1, fingerprint);

        return deleteFromBucket(i1, fingerprint) || deleteFromBucket(i2, fingerprint);
    }

    private boolean insertToBucket(int idx, byte fp) {
        for (int i = 0; i < SLOTS_PER_BUCKET; i++) {
            if (buckets[idx][i] == 0) {
                buckets[idx][i] = fp;
                return true;
            }
        }
        return false;
    }

    private boolean bucketContains(int idx, byte fp) {
        for (int i = 0; i < SLOTS_PER_BUCKET; i++) {
            if (buckets[idx][i] == fp)
                return true;
        }
        return false;
    }

    private boolean deleteFromBucket(int idx, byte fp) {
        for (int i = 0; i < SLOTS_PER_BUCKET; i++) {
            if (buckets[idx][i] == fp) {
                buckets[idx][i] = 0;
                return true;
            }
        }
        return false;
    }

    private int getHash(String item) {
        return Math.abs(item.hashCode()) % numBuckets;
    }

    private byte getFingerprint(String item) {
        int hash = item.hashCode();
        byte fp = (byte) ((hash ^ (hash >>> 16)) & 0xFF);
        return fp == 0 ? (byte) 1 : fp; // 0 is reserved for empty
    }

    private int getAltIndex(int index, byte fp) {
        int hashFp = Math.abs(Byte.toString(fp).hashCode());
        return (index ^ hashFp) % numBuckets;
    }

    public static void main(String[] args) {
        basic_operations filter = new basic_operations(100);

        System.out.println("Inserting: apple, banana, cherry");
        filter.insert("apple");
        filter.insert("banana");
        filter.insert("cherry");

        System.out.println("Lookup apple: " + filter.lookup("apple"));
        System.out.println("Lookup durian: " + filter.lookup("durian"));

        System.out.println("Deleting banana...");
        filter.delete("banana");
        System.out.println("Lookup banana: " + filter.lookup("banana"));
    }
}
