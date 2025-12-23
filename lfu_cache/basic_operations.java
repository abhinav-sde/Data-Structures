package lfu_cache;

import java.util.*;

/**
 * Basic LFU Cache Implementation
 * Uses three maps:
 * 1. Key to Value
 * 2. Key to Frequency
 * 3. Frequency to Ordered Set of Keys (LinkedHashSet)
 */
public class basic_operations {

    static class LFUCache {
        private int minFrequency;
        private final int capacity;
        private final Map<Integer, Integer> keyToVal;
        private final Map<Integer, Integer> keyToFreq;
        private final Map<Integer, LinkedHashSet<Integer>> freqToKeys;

        public LFUCache(int capacity) {
            this.capacity = capacity;
            this.minFrequency = 0;
            this.keyToVal = new HashMap<>();
            this.keyToFreq = new HashMap<>();
            this.freqToKeys = new HashMap<>();
        }

        public int get(int key) {
            if (!keyToVal.containsKey(key))
                return -1;
            updateFrequency(key);
            return keyToVal.get(key);
        }

        public void put(int key, int value) {
            if (capacity <= 0)
                return;
            if (keyToVal.containsKey(key)) {
                keyToVal.put(key, value);
                updateFrequency(key);
                return;
            }
            if (keyToVal.size() >= capacity) {
                evict();
            }
            keyToVal.put(key, value);
            keyToFreq.put(key, 1);
            minFrequency = 1;
            freqToKeys.computeIfAbsent(1, k -> new LinkedHashSet<>()).add(key);
        }

        private void updateFrequency(int key) {
            int freq = keyToFreq.get(key);
            keyToFreq.put(key, freq + 1);
            freqToKeys.get(freq).remove(key);
            if (freq == minFrequency && freqToKeys.get(freq).isEmpty()) {
                minFrequency++;
            }
            freqToKeys.computeIfAbsent(freq + 1, k -> new LinkedHashSet<>()).add(key);
        }

        private void evict() {
            int evictKey = freqToKeys.get(minFrequency).iterator().next();
            freqToKeys.get(minFrequency).remove(evictKey);
            keyToVal.remove(evictKey);
            keyToFreq.remove(evictKey);
        }

        public void display() {
            System.out.println("LFU State: " + keyToVal + " (MinFreq: " + minFrequency + ")");
        }
    }

    public static void main(String[] args) {
        LFUCache cache = new LFUCache(2);
        cache.put(1, 1);
        cache.put(2, 2);
        cache.display();
        cache.get(1); // freq of 1 becomes 2
        cache.put(3, 3); // evicts 2 (freq 1)
        cache.display();
    }
}
