package count_min_sketch;

import java.util.*;

/**
 * Basic Count-Min Sketch Implementation
 * A probabilistic data structure used for frequency estimation in data streams.
 * Trade-off: Uses very little memory but might slightly overestimate (no
 * underestimation).
 */
public class basic_operations {

    static class CountMinSketch {
        private final int width;
        private final int depth;
        private final long[][] table;
        private final long[] hashSeeds;
        private final Random random = new Random();

        public CountMinSketch(double epsilon, double delta) {
            // width = 2/epsilon, depth = ln(1/delta)
            this.width = (int) Math.ceil(2 / epsilon);
            this.depth = (int) Math.ceil(Math.log(1 / delta));
            this.table = new long[depth][width];
            this.hashSeeds = new long[depth];
            for (int i = 0; i < depth; i++) {
                hashSeeds[i] = random.nextLong();
            }
        }

        private int hash(String key, int i) {
            long hash = key.hashCode() ^ hashSeeds[i];
            int res = (int) (hash % width);
            return Math.abs(res);
        }

        public void add(String key) {
            for (int i = 0; i < depth; i++) {
                table[i][hash(key, i)]++;
            }
        }

        public long estimate(String key) {
            long min = Long.MAX_VALUE;
            for (int i = 0; i < depth; i++) {
                min = Math.min(min, table[i][hash(key, i)]);
            }
            return min;
        }
    }

    public static void main(String[] args) {
        CountMinSketch cms = new CountMinSketch(0.01, 0.01);
        cms.add("apple");
        cms.add("apple");
        cms.add("banana");
        System.out.println("Estimate 'apple': " + cms.estimate("apple"));
        System.out.println("Estimate 'banana': " + cms.estimate("banana"));
        System.out.println("Estimate 'orange': " + cms.estimate("orange"));
    }
}
