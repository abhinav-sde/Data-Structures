#include <iostream>
#include <vector>
using namespace std;

// 2D Fenwick Tree
class FenwickTree2D {
private:
    vector<vector<int>> tree;
    int m, n;
    
public:
    FenwickTree2D(int rows, int cols) : m(rows), n(cols) {
        tree.resize(m + 1, vector<int>(n + 1, 0));
    }
    
    void update(int row, int col, int delta) {
        for (int i = row + 1; i <= m; i += (i & -i)) {
            for (int j = col + 1; j <= n; j += (j & -j)) {
                tree[i][j] += delta;
            }
        }
    }
    
    int query(int row, int col) {
        int sum = 0;
        for (int i = row + 1; i > 0; i -= (i & -i)) {
            for (int j = col + 1; j > 0; j -= (j & -j)) {
                sum += tree[i][j];
            }
        }
        return sum;
    }
    
    int rangeQuery(int row1, int col1, int row2, int col2) {
        int total = query(row2, col2);
        if (row1 > 0) total -= query(row1 - 1, col2);
        if (col1 > 0) total -= query(row2, col1 - 1);
        if (row1 > 0 && col1 > 0) total += query(row1 - 1, col1 - 1);
        return total;
    }
};

int main() {
    cout << "=== Advanced Fenwick Tree Problems ===" << endl << endl;
    
    cout << "Test: 2D Fenwick Tree" << endl;
    FenwickTree2D ft2d(3, 3);
    ft2d.update(0, 0, 1);
    ft2d.update(1, 1, 2);
    ft2d.update(2, 2, 3);
    cout << "Range sum [0,0] to [2,2]: " << ft2d.rangeQuery(0, 0, 2, 2) << endl;
    
    return 0;
}
