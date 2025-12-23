package bloom_filter;

import java.util.*;

public class basic_operations {

    static class BloomFilter {
        private BitSet bitSet;
        private int size;
        private int numHashFunctions;

        public BloomFilter(int size, int numHashFunctions) {
            this.size = size;
            this.numHashFunctions = numHashFunctions;
            this.bitSet = new BitSet(size);
        }

        private int hash(String item, int seed) {
            int hash = 0;
            for (char c : item.toCharArray()) {
                hash = (hash * seed + c) % size;
            }
            return Math.abs(hash);
        }

        public void add(String item) {
            for (int i = 0; i < numHashFunctions; i++) {
                int index = hash(item, i + 1);
                bitSet.set(index);
            }
        }

        public boolean mightContain(String item) {
            for (int i = 0; i < numHashFunctions; i++) {
                int index = hash(item, i + 1);
                if (!bitSet.get(index)) {
                    return false;
                }
            }
            return true;
        }

        public double getFalsePositiveRate() {
            int bitsSet = bitSet.cardinality();
            return Math.pow((double) bitsSet / size, numHashFunctions);
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Bloom Filter Demo ===\n");

        BloomFilter bf = new BloomFilter(100, 3);

        bf.add("apple");
        bf.add("banana");
        bf.add("orange");

        System.out.println("Contains 'apple': " + bf.mightContain("apple"));
        System.out.println("Contains 'grape': " + bf.mightContain("grape"));
        System.out.println("False positive rate: " + bf.getFalsePositiveRate());
    }
}
