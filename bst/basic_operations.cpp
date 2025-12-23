#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

/**
 * Basic Binary Search Tree Operations in C++
 */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;
    
    TreeNode* insertHelper(TreeNode* node, int val) {
        if (!node) return new TreeNode(val);
        
        if (val < node->val) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->val) {
            node->right = insertHelper(node->right, val);
        }
        
        return node;
    }
    
    bool searchHelper(TreeNode* node, int val) {
        if (!node) return false;
        if (node->val == val) return true;
        if (val < node->val) return searchHelper(node->left, val);
        return searchHelper(node->right, val);
    }
    
    TreeNode* deleteHelper(TreeNode* node, int val) {
        if (!node) return nullptr;
        
        if (val < node->val) {
            node->left = deleteHelper(node->left, val);
        } else if (val > node->val) {
            node->right = deleteHelper(node->right, val);
        } else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            
            TreeNode* successor = findMin(node->right);
            node->val = successor->val;
            node->right = deleteHelper(node->right, successor->val);
        }
        
        return node;
    }
    
    TreeNode* findMin(TreeNode* node) {
        while (node->left) node = node->left;
        return node;
    }
    
    void inorderHelper(TreeNode* node) {
        if (!node) return;
        inorderHelper(node->left);
        cout << node->val << " ";
        inorderHelper(node->right);
    }
    
    void preorderHelper(TreeNode* node) {
        if (!node) return;
        cout << node->val << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }
    
    void postorderHelper(TreeNode* node) {
        if (!node) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->val << " ";
    }
    
    int heightHelper(TreeNode* node) {
        if (!node) return -1;
        return 1 + max(heightHelper(node->left), heightHelper(node->right));
    }
    
    int sizeHelper(TreeNode* node) {
        if (!node) return 0;
        return 1 + sizeHelper(node->left) + sizeHelper(node->right);
    }
    
    bool isBSTHelper(TreeNode* node, TreeNode* minNode, TreeNode* maxNode) {
        if (!node) return true;
        
        if ((minNode && node->val <= minNode->val) || 
            (maxNode && node->val >= maxNode->val)) {
            return false;
        }
        
        return isBSTHelper(node->left, minNode, node) && 
               isBSTHelper(node->right, node, maxNode);
    }
    
public:
    BST() : root(nullptr) {}
    
    void insert(int val) {
        root = insertHelper(root, val);
        cout << "Inserted: " << val << endl;
    }
    
    bool search(int val) {
        return searchHelper(root, val);
    }
    
    void remove(int val) {
        root = deleteHelper(root, val);
        cout << "Deleted: " << val << endl;
    }
    
    void inorder() {
        cout << "Inorder: ";
        inorderHelper(root);
        cout << endl;
    }
    
    void preorder() {
        cout << "Preorder: ";
        preorderHelper(root);
        cout << endl;
    }
    
    void postorder() {
        cout << "Postorder: ";
        postorderHelper(root);
        cout << endl;
    }
    
    void levelOrder() {
        if (!root) return;
        
        cout << "Level Order: ";
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            cout << current->val << " ";
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        cout << endl;
    }
    
    int height() {
        return heightHelper(root);
    }
    
    int size() {
        return sizeHelper(root);
    }
    
    bool isBST() {
        return isBSTHelper(root, nullptr, nullptr);
    }
};

int main() {
    cout << "=== BST Basic Operations Demo ===" << endl << endl;
    
    BST bst;
    
    cout << "--- Inserting Values ---" << endl;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    cout << endl;
    
    cout << "--- Traversals ---" << endl;
    bst.inorder();
    bst.preorder();
    bst.postorder();
    bst.levelOrder();
    cout << endl;
    
    cout << "--- Search Operations ---" << endl;
    cout << "Search 40: " << (bst.search(40) ? "true" : "false") << endl;
    cout << "Search 25: " << (bst.search(25) ? "true" : "false") << endl;
    cout << endl;
    
    cout << "--- Tree Properties ---" << endl;
    cout << "Height: " << bst.height() << endl;
    cout << "Size: " << bst.size() << endl;
    cout << "Is BST: " << (bst.isBST() ? "true" : "false") << endl;
    cout << endl;
    
    cout << "--- Delete Operations ---" << endl;
    bst.remove(20);
    bst.inorder();
    bst.remove(30);
    bst.inorder();
    bst.remove(50);
    bst.inorder();
    
    return 0;
}
