#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Problem: Range Minimum Query
// Given an array, find the minimum element in range [L, R]
class MinSegmentTree {
    vector<int> tree;
    int n;

public:
    MinSegmentTree(vector<int>& nums) {
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
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    }

    int query(int L, int R, int node, int start, int end) {
        if (R < start || end < L) return INT_MAX;
        if (L <= start && end <= R) return tree[node];
        
        int mid = (start + end) / 2;
        return min(query(L, R, 2 * node, start, mid),
                   query(L, R, 2 * node + 1, mid + 1, end));
    }

    int query(int L, int R) {
        return query(L, R, 1, 0, n - 1);
    }
};

int main() {
    vector<int> nums = {5, 2, 8, 1, 9, 3};
    MinSegmentTree st(nums);
    cout << "Min in range [0, 2]: " << st.query(0, 2) << endl; // 2
    cout << "Min in range [0, 5]: " << st.query(0, 5) << endl; // 1
    return 0;
}
