package segment_tree;

// Segment Tree for Range Sum Query
public class SegmentTree {
    private int[] tree;
    private int n;

    public SegmentTree(int[] nums) {
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
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    private void update(int idx, int val, int node, int start, int end) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(idx, val, 2 * node, start, mid);
            } else {
                update(idx, val, 2 * node + 1, mid + 1, end);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    private int query(int L, int R, int node, int start, int end) {
        if (R < start || end < L)
            return 0;
        if (L <= start && end <= R)
            return tree[node];

        int mid = (start + end) / 2;
        int p1 = query(L, R, 2 * node, start, mid);
        int p2 = query(L, R, 2 * node + 1, mid + 1, end);
        return p1 + p2;
    }

    public void update(int idx, int val) {
        update(idx, val, 1, 0, n - 1);
    }

    public int query(int L, int R) {
        return query(L, R, 1, 0, n - 1);
    }

    public static void main(String[] args) {
        int[] nums = { 1, 3, 5, 7, 9, 11 };
        SegmentTree st = new SegmentTree(nums);

        System.out.println("Sum[1, 3]: " + st.query(1, 3)); // 15

        st.update(1, 10);
        System.out.println("Sum[1, 3] after update: " + st.query(1, 3)); // 22
    }
}
