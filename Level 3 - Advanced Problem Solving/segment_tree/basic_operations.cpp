#include <iostream>
#include <vector>

using namespace std;

// Segment Tree for Range Sum Query
class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);
        build(nums, 1, 0, n - 1);
    }

    void build(vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
        } else {
            int mid = (start + end) / 2;
            build(nums, 2 * node, start, mid);
            build(nums, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    // Point update
    void update(int idx, int val, int node, int start, int end) {
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

    int query(int L, int R, int node, int start, int end) {
        // Range completely outside
        if (R < start || end < L) {
            return 0;
        }
        // Range completely inside
        if (L <= start && end <= R) {
            return tree[node];
        }
        // Partial overlap
        int mid = (start + end) / 2;
        int p1 = query(L, R, 2 * node, start, mid);
        int p2 = query(L, R, 2 * node + 1, mid + 1, end);
        return p1 + p2;
    }

    // Helper wrappers
    void update(int idx, int val) {
        update(idx, val, 1, 0, n - 1);
    }

    int query(int L, int R) {
        return query(L, R, 1, 0, n - 1);
    }
};

int main() {
    vector<int> nums = {1, 3, 5, 7, 9, 11};
    SegmentTree st(nums);

    cout << "Sum[1, 3] (3+5+7): " << st.query(1, 3) << endl; // 15
    
    st.update(1, 10); // nums[1] becomes 10
    cout << "Sum[1, 3] after update (10+5+7): " << st.query(1, 3) << endl; // 22

    return 0;
}
