#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<int> tree;
    int n;
    
public:
    FenwickTree(int size) : n(size), tree(size + 1, 0) {}
    
    void update(int i, int delta) {
        i++;
        while (i <= n) {
            tree[i] += delta;
            i += (i & -i);
        }
    }
    
    int query(int i) {
        i++;
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= (i & -i);
        }
        return sum;
    }
    
    int rangeQuery(int left, int right) {
        if (left == 0) return query(right);
        return query(right) - query(left - 1);
    }
};

class NumArray {
private:
    vector<int> nums;
    FenwickTree ft;
    
public:
    NumArray(vector<int>& nums) : nums(nums), ft(nums.size()) {
        for (int i = 0; i < nums.size(); i++) {
            ft.update(i, nums[i]);
        }
    }
    
    void update(int index, int val) {
        int delta = val - nums[index];
        nums[index] = val;
        ft.update(index, delta);
    }
    
    int sumRange(int left, int right) {
        return ft.rangeQuery(left, right);
    }
};

int main() {
    cout << "=== Core Fenwick Tree Problems ===" << endl << endl;
    
    cout << "Test: Range Sum Query - Mutable" << endl;
    vector<int> nums = {1, 3, 5, 7, 9, 11};
    NumArray numArray(nums);
    cout << "Sum[1..3]: " << numArray.sumRange(1, 3) << endl;
    numArray.update(1, 10);
    cout << "After update, Sum[1..3]: " << numArray.sumRange(1, 3) << endl;
    
    return 0;
}
