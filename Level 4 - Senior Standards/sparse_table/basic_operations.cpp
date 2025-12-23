#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

/**
 * Sparse Table for O(1) Range Minimum Query
 */
class SparseTable {
    vector<vector<int>> st;
    vector<int> logs;
    int N, K;

public:
    SparseTable(const vector<int>& arr) {
        N = arr.size();
        K = log2(N) + 1;
        st.assign(N, vector<int>(K));
        logs.assign(N + 1, 0);

        for (int i = 2; i <= N; i++) logs[i] = logs[i / 2] + 1;

        for (int i = 0; i < N; i++) st[i][0] = arr[i];

        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) <= N; i++) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int L, int R) {
        int j = logs[R - L + 1];
        return min(st[L][j], st[R - (1 << j) + 1][j]);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 2, 8, 1};
    SparseTable st(arr);
    cout << "Min [0, 5]: " << st.query(0, 5) << endl;
    cout << "Min [1, 3]: " << st.query(1, 3) << endl;
    return 0;
}
