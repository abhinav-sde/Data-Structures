#include <iostream>
#include <vector>

using namespace std;

// Lazy Propagation Segment Tree for Range Sum with Range Updates
class LazySegmentTree {
    vector<int> tree, lazy;
    int n;

public:
    LazySegmentTree(vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
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

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void updateRange(int node, int start, int end, int L, int R, int val) {
        push(node, start, end);
        if (start > end || start > R || end < L) return;

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

    int queryRange(int node, int start, int end, int L, int R) {
        push(node, start, end);
        if (start > end || start > R || end < L) return 0;

        if (start >= L && end <= R) return tree[node];

        int mid = (start + end) / 2;
        return queryRange(2 * node, start, mid, L, R) + 
               queryRange(2 * node + 1, mid + 1, end, L, R);
    }

    void update(int L, int R, int val) {
        updateRange(1, 0, n - 1, L, R, val);
    }

    int query(int L, int R) {
        return queryRange(1, 0, n - 1, L, R);
    }
};

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    LazySegmentTree st(nums);
    
    // Sum [0, 4] = 15
    cout << "Sum[0, 4]: " << st.query(0, 4) << endl;

    // Add 10 to range [0, 2] -> {11, 12, 13, 4, 5} -> Sum = 45
    st.update(0, 2, 10);
    cout << "Sum[0, 4] after range update: " << st.query(0, 4) << endl;

    return 0;
}
