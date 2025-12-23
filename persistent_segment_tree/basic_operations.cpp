#include <iostream>
#include <vector>

using namespace std;

/**
 * Persistent Segment Tree for Range Sums
 */
struct Node {
    int sum;
    Node *l, *r;
    Node(int v) : sum(v), l(nullptr), r(nullptr) {}
    Node(Node* _l, Node* _r) : l(_l), r(_r) {
        sum = (l ? l->sum : 0) + (r ? r->sum : 0);
    }
};

class PersistentSegTree {
    vector<Node*> roots;
    int n;

    Node* build(const vector<int>& arr, int L, int R) {
        if (L == R) return new Node(arr[L]);
        int mid = (L + R) / 2;
        return new Node(build(arr, L, mid), build(arr, mid + 1, R));
    }

    Node* update(Node* prev, int L, int R, int idx, int val) {
        if (L == R) return new Node(val);
        int mid = (L + R) / 2;
        if (idx <= mid) return new Node(update(prev->l, L, mid, idx, val), prev->r);
        else return new Node(prev->l, update(prev->r, mid + 1, R, idx, val));
    }

    int query(Node* node, int L, int R, int qL, int qR) {
        if (!node || qL > R || qR < L) return 0;
        if (qL <= L && R <= qR) return node->sum;
        int mid = (L + R) / 2;
        return query(node->l, L, mid, qL, qR) + query(node->r, mid + 1, R, qL, qR);
    }

public:
    PersistentSegTree(const vector<int>& arr) {
        n = arr.size();
        roots.push_back(build(arr, 0, n - 1));
    }

    void update(int v, int idx, int val) {
        roots.push_back(update(roots[v], 0, n - 1, idx, val));
    }

    int query(int v, int qL, int qR) {
        return query(roots[v], 0, n - 1, qL, qR);
    }
};

int main() {
    vector<int> arr = {1, 2, 3};
    PersistentSegTree pst(arr);
    cout << "V0 Sum [0,2]: " << pst.query(0, 0, 2) << endl;
    pst.update(0, 1, 10);
    cout << "V1 Sum [0,2]: " << pst.query(1, 0, 2) << endl;
    return 0;
}
