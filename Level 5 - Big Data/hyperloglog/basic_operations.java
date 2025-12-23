
import java.util.*;

/**
 * Basic HyperLogLog Implementation
 * A probabilistic data structure used for estimating the number of unique
 * elements (cardinality).
 * Memory complexity: O(log log N) - hence the name.
 */
public class basic_operations {

    static class HyperLogLog {
        private final int p; // precision bits
        private final int m; // number of registers
        private final double alpha;
        private final int[] registers;

        public HyperLogLog(int p) {
            this.p = p;
            this.m = 1 << p;
            this.registers = new int[m];

            // Determine alpha constant
            if (m == 16)
                alpha = 0.673;
            else if (m == 32)
                alpha = 0.697;
            else if (m == 64)
                alpha = 0.709;
            else
                alpha = 0.7213 / (1 + 1.079 / m);
        }

        public void add(String item) {
            int hash = item.hashCode();
            int index = (hash >>> (32 - p)); // Use first p bits for index
            int w = (hash << p) | (1 << (p - 1)); // Remaining bits and ensure non-zero
            int rho = Integer.numberOfLeadingZeros(w) + 1;
            registers[index] = Math.max(registers[index], rho);
        }

        public long count() {
            double Z = 0;
            for (int r : registers) {
                Z += Math.pow(2, -r);
            }
            double estimate = alpha * m * m / Z;

            // Small range correction (if estimate <= 2.5 * m)
            if (estimate <= 2.5 * m) {
                int V = 0; // count zero registers
                for (int r : registers)
                    if (r == 0)
                        V++;
                if (V > 0)
                    estimate = m * Math.log((double) m / V);
            }

            return Math.round(estimate);
        }
    }

    public static void main(String[] args) {
        HyperLogLog hll = new HyperLogLog(10); // 2^10 = 1024 registers
        for (int i = 0; i < 5000; i++) {
            hll.add("User_" + i);
        }
        // Duplicate adds shouldn't change count significantly
        for (int i = 0; i < 1000; i++)
            hll.add("User_" + i);

        System.out.println("Estimated unique users: " + hll.count());
        System.out.println("Actual unique users: 5000");
    }
}
