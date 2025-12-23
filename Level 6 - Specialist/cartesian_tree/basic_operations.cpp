#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int value;
    Node *left, *right;
    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

class CartesianTree {
public:
    Node* buildTree(vector<int>& arr, int start, int end) {
        if (start > end) return nullptr;
        
        int minIndex = start;
        for (int i = start + 1; i <= end; i++) {
            if (arr[i] < arr[minIndex]) {
                minIndex = i;
            }
        }
        
        Node* root = new Node(arr[minIndex]);
        root->left = buildTree(arr, start, minIndex - 1);
        root->right = buildTree(arr, minIndex + 1, end);
        
        return root;
    }
    
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->value << " ";
            inorder(node->right);
        }
    }
};

int main() {
    CartesianTree ct;
    vector<int> arr = {9, 3, 7, 1, 8, 12, 10};
    
    Node* root = ct.buildTree(arr, 0, arr.size() - 1);
    
    cout << "Inorder: ";
    ct.inorder(root);
    cout << endl;
    
    return 0;
}
