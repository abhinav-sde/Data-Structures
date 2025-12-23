#include <iostream>
#include <vector>
using namespace std;

/**
 * Basic Fenwick Tree Operations in C++
 */

class FenwickTree {
private:
    vector<int> tree;
    int n;
    
public:
    FenwickTree(int size) {
        n = size;
        tree.resize(n + 1, 0);
    }
    
    FenwickTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(n + 1, 0);
        
        for (int i = 0; i < n; i++) {
            update(i, arr[i]);
        }
    }
    
    void update(int i, int delta) {
        i++; // 1-indexed
        
        while (i <= n) {
            tree[i] += delta;
            i += (i & -i);
        }
    }
    
    int query(int i) {
        i++; // 1-indexed
        int sum = 0;
        
        while (i > 0) {
            sum += tree[i];
            i -= (i & -i);
        }
        
        return sum;
    }
    
    int rangeQuery(int left, int right) {
        if (left > right) return 0;
        if (left == 0) return query(right);
        return query(right) - query(left - 1);
    }
    
    void set(int i, int val) {
        int currentVal = rangeQuery(i, i);
        update(i, val - currentVal);
    }
    
    void display() {
        cout << "Fenwick Tree: ";
        for (int i = 1; i <= n; i++) {
            cout << tree[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    cout << "=== Fenwick Tree Basic Operations ===" << endl << endl;
    
    vector<int> arr = {3, 2, -1, 6, 5, 4, -3, 3, 7, 2};
    FenwickTree ft(arr);
    
    cout << "--- Prefix Sums ---" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Sum[0.." << i << "]: " << ft.query(i) << endl;
    }
    cout << endl;
    
    cout << "--- Range Queries ---" << endl;
    cout << "Sum[2..5]: " << ft.rangeQuery(2, 5) << endl;
    cout << "Sum[3..7]: " << ft.rangeQuery(3, 7) << endl;
    cout << endl;
    
    cout << "--- Update Operations ---" << endl;
    cout << "Adding 10 to index 3" << endl;
    ft.update(3, 10);
    cout << "New Sum[2..5]: " << ft.rangeQuery(2, 5) << endl;
    
    return 0;
}
