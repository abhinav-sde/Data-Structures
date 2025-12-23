
import java.util.*;

public class core_problems {

    // Problem 1: Range Sum Query - Mutable
    static class NumArray {
        FenwickTree ft;
        int[] nums;

        public NumArray(int[] nums) {
            this.nums = nums;
            this.ft = new FenwickTree(nums.length);
            for (int i = 0; i < nums.length; i++) {
                ft.update(i, nums[i]);
            }
        }

        public void update(int index, int val) {
            int delta = val - nums[index];
            nums[index] = val;
            ft.update(index, delta);
        }

        public int sumRange(int left, int right) {
            return ft.rangeQuery(left, right);
        }
    }

    static class FenwickTree {
        private int[] tree;
        private int n;

        public FenwickTree(int size) {
            n = size;
            tree = new int[n + 1];
        }

        public void update(int i, int delta) {
            i++;
            while (i <= n) {
                tree[i] += delta;
                i += (i & -i);
            }
        }

        public int query(int i) {
            i++;
            int sum = 0;
            while (i > 0) {
                sum += tree[i];
                i -= (i & -i);
            }
            return sum;
        }

        public int rangeQuery(int left, int right) {
            if (left == 0)
                return query(right);
            return query(right) - query(left - 1);
        }
    }

    // Problem 2: Count of Smaller Numbers After Self
    static List<Integer> countSmaller(int[] nums) {
        int offset = 10000; // Handle negative numbers
        int size = 2 * 10000 + 1;
        FenwickTree ft = new FenwickTree(size);

        List<Integer> result = new ArrayList<>();

        for (int i = nums.length - 1; i >= 0; i--) {
            int val = nums[i] + offset;
            int smaller = val > 0 ? ft.query(val - 1) : 0;
            result.add(0, smaller);
            ft.update(val, 1);
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println("=== Core Fenwick Tree Problems ===\n");

        // Test 1: Range Sum Query
        System.out.println("Test 1: Range Sum Query - Mutable");
        int[] nums = { 1, 3, 5, 7, 9, 11 };
        NumArray numArray = new NumArray(nums);
        System.out.println("Sum[1..3]: " + numArray.sumRange(1, 3));
        numArray.update(1, 10);
        System.out.println("After update(1, 10), Sum[1..3]: " + numArray.sumRange(1, 3));
        System.out.println();

        // Test 2: Count Smaller
        System.out.println("Test 2: Count of Smaller Numbers After Self");
        int[] arr = { 5, 2, 6, 1 };
        System.out.println("Array: " + Arrays.toString(arr));
        System.out.println("Result: " + countSmaller(arr));
    }
}
