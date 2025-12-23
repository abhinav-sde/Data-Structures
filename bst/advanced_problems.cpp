#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
using namespace std;

/**
 * Advanced BST Problems in C++
 * Including AVL Tree
 */

struct TreeNode {
    int val;
    TreeNode *left, *right;
    int height;
    
    TreeNode(int v) : val(v), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    TreeNode* root;
    
    int height(TreeNode* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(TreeNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        
        return x;
    }
    
    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        
        return y;
    }
    
    TreeNode* insertHelper(TreeNode* node, int val) {
        if (!node) return new TreeNode(val);
        
        if (val < node->val) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->val) {
            node->right = insertHelper(node->right, val);
        } else {
            return node;
        }
        
        node->height = 1 + max(height(node->left), height(node->right));
        
        int balance = getBalance(node);
        
        // Left Left
        if (balance > 1 && val < node->left->val) {
            return rightRotate(node);
        }
        
        // Right Right
        if (balance < -1 && val > node->right->val) {
            return leftRotate(node);
        }
        
        // Left Right
        if (balance > 1 && val > node->left->val) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Left
        if (balance < -1 && val < node->right->val) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    void inorderHelper(TreeNode* node) {
        if (!node) return;
        inorderHelper(node->left);
        cout << node->val << " ";
        inorderHelper(node->right);
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(int val) {
        root = insertHelper(root, val);
    }
    
    void inorder() {
        inorderHelper(root);
        cout << endl;
    }
    
    int getHeight() {
        return height(root);
    }
};

// Balance BST
void inorderToVector(TreeNode* node, vector<int>& vec) {
    if (!node) return;
    inorderToVector(node->left, vec);
    vec.push_back(node->val);
    inorderToVector(node->right, vec);
}

TreeNode* sortedVectorToBST(vector<int>& vec, int left, int right) {
    if (left > right) return nullptr;
    
    int mid = left + (right - left) / 2;
    TreeNode* node = new TreeNode(vec[mid]);
    
    node->left = sortedVectorToBST(vec, left, mid - 1);
    node->right = sortedVectorToBST(vec, mid + 1, right);
    
    return node;
}

TreeNode* balanceBST(TreeNode* root) {
    vector<int> sorted;
    inorderToVector(root, sorted);
    return sortedVectorToBST(sorted, 0, sorted.size() - 1);
}

int main() {
    cout << "=== Advanced BST Problems ===" << endl << endl;
    
    cout << "Test 1: AVL Tree" << endl;
    AVLTree avl;
    vector<int> values = {10, 20, 30, 40, 50, 25};
    
    for (int v : values) {
        avl.insert(v);
    }
    
    cout << "AVL Inorder: ";
    avl.inorder();
    cout << "AVL Height: " << avl.getHeight() << endl << endl;
    
    cout << "Test 2: Balance BST" << endl;
    TreeNode* unbalanced = new TreeNode(1);
    unbalanced->right = new TreeNode(2);
    unbalanced->right->right = new TreeNode(3);
    unbalanced->right->right->right = new TreeNode(4);
    
    TreeNode* balanced = balanceBST(unbalanced);
    cout << "BST balanced successfully" << endl;
    
    return 0;
}
