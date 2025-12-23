
public class core_problems {

    // Problem: Range Minimum Query
    static class MinSegmentTree {
        int[] tree;
        int n;

        public MinSegmentTree(int[] nums) {
            n = nums.length;
            tree = new int[4 * n];
            build(nums, 1, 0, n - 1);
        }

        private void build(int[] nums, int node, int start, int end) {
            if (start == end) {
                tree[node] = nums[start];
            } else {
                int mid = (start + end) / 2;
                build(nums, 2 * node, start, mid);
                build(nums, 2 * node + 1, mid + 1, end);
                tree[node] = Math.min(tree[2 * node], tree[2 * node + 1]);
            }
        }

        public int query(int L, int R, int node, int start, int end) {
            if (R < start || end < L)
                return Integer.MAX_VALUE;
            if (L <= start && end <= R)
                return tree[node];

            int mid = (start + end) / 2;
            return Math.min(query(L, R, 2 * node, start, mid),
                    query(L, R, 2 * node + 1, mid + 1, end));
        }

        public int query(int L, int R) {
            return query(L, R, 1, 0, n - 1);
        }
    }

    public static void main(String[] args) {
        int[] nums = { 5, 2, 8, 1, 9, 3 };
        MinSegmentTree st = new MinSegmentTree(nums);
        System.out.println("Min in range [0, 2]: " + st.query(0, 2)); // 2
        System.out.println("Min in range [0, 5]: " + st.query(0, 5)); // 1
    }
}
