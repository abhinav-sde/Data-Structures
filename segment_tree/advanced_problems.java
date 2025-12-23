package segment_tree;

public class advanced_problems {

    static class LazySegmentTree {
        int[] tree, lazy;
        int n;

        public LazySegmentTree(int[] nums) {
            n = nums.length;
            tree = new int[4 * n];
            lazy = new int[4 * n];
            build(nums, 1, 0, n - 1);
        }

        private void build(int[] nums, int node, int start, int end) {
            if (start == end) {
                tree[node] = nums[start];
            } else {
                int mid = (start + end) / 2;
                build(nums, 2 * node, start, mid);
                build(nums, 2 * node + 1, mid + 1, end);
                tree[node] = tree[2 * node] + tree[2 * node + 1];
            }
        }

        private void push(int node, int start, int end) {
            if (lazy[node] != 0) {
                tree[node] += (end - start + 1) * lazy[node];
                if (start != end) {
                    lazy[2 * node] += lazy[node];
                    lazy[2 * node + 1] += lazy[node];
                }
                lazy[node] = 0;
            }
        }

        private void updateRange(int node, int start, int end, int L, int R, int val) {
            push(node, start, end);
            if (start > end || start > R || end < L)
                return;

            if (start >= L && end <= R) {
                lazy[node] += val;
                push(node, start, end);
                return;
            }

            int mid = (start + end) / 2;
            updateRange(2 * node, start, mid, L, R, val);
            updateRange(2 * node + 1, mid + 1, end, L, R, val);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }

        private int queryRange(int node, int start, int end, int L, int R) {
            push(node, start, end);
            if (start > end || start > R || end < L)
                return 0;

            if (start >= L && end <= R)
                return tree[node];

            int mid = (start + end) / 2;
            return queryRange(2 * node, start, mid, L, R) +
                    queryRange(2 * node + 1, mid + 1, end, L, R);
        }

        public void update(int L, int R, int val) {
            updateRange(1, 0, n - 1, L, R, val);
        }

        public int query(int L, int R) {
            return queryRange(1, 0, n - 1, L, R);
        }
    }

    public static void main(String[] args) {
        int[] nums = { 1, 2, 3, 4, 5 };
        LazySegmentTree st = new LazySegmentTree(nums);

        System.out.println("Sum[0, 4]: " + st.query(0, 4)); // 15

        st.update(0, 2, 10);
        System.out.println("Sum[0, 4] after range update: " + st.query(0, 4)); // 45
    }
}
