#include <iostream>
using namespace std;

struct BTreeNode {
    int* keys;
    int t;
    BTreeNode** children;
    int n;
    bool leaf;
    
    BTreeNode(int _t, bool _leaf) {
        t = _t;
        leaf = _leaf;
        keys = new int[2*t-1];
        children = new BTreeNode*[2*t];
        n = 0;
    }
};

class BTree {
private:
    BTreeNode* root;
    int t;
    
public:
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }
    
    bool search(int k) {
        return (root == nullptr) ? false : search(root, k);
    }
    
    bool search(BTreeNode* node, int k) {
        int i = 0;
        while (i < node->n && k > node->keys[i])
            i++;
        
        if (i < node->n && k == node->keys[i])
            return true;
        
        if (node->leaf)
            return false;
        
        return search(node->children[i], k);
    }
};

int main() {
    BTree t(3);
    cout << "B-Tree created with minimum degree 3" << endl;
    return 0;
}
