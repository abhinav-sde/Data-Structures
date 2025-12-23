#include <iostream>
#include <queue>
using namespace std;

// ========================================
// BINARY TREE NODE STRUCTURE
// ========================================

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// ========================================
// 1. CREATE A NEW NODE
// ========================================
// Usage: node = createNode(value)
// Example: node = createNode(10)
TreeNode* createNode(int value) {
    return new TreeNode(value);
}

// ========================================
// 2. INSERT NODE (LEVEL ORDER)
// ========================================
// Usage: root = insert(root, value)
// Example: root = insert(root, 20)
TreeNode* insert(TreeNode* root, int value) {
    if (root == nullptr) {
        cout << "Inserted " << value << " as root." << endl;
        return createNode(value);
    }
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* temp = q.front();
        q.pop();
        
        if (temp->left == nullptr) {
            temp->left = createNode(value);
            cout << "Inserted " << value << " as left child of " << temp->data << endl;
            return root;
        } else {
            q.push(temp->left);
        }
        
        if (temp->right == nullptr) {
            temp->right = createNode(value);
            cout << "Inserted " << value << " as right child of " << temp->data << endl;
            return root;
        } else {
            q.push(temp->right);
        }
    }
    
    return root;
}

// ========================================
// 3. INORDER TRAVERSAL (Left-Root-Right)
// ========================================
// Usage: inorder(root)
// Example: For tree with root 1, left 2, right 3 -> prints "2 1 3"
void inorder(TreeNode* root) {
    if (root == nullptr) return;
    
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// ========================================
// 4. PREORDER TRAVERSAL (Root-Left-Right)
// ========================================
// Usage: preorder(root)
// Example: For tree with root 1, left 2, right 3 -> prints "1 2 3"
void preorder(TreeNode* root) {
    if (root == nullptr) return;
    
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// ========================================
// 5. POSTORDER TRAVERSAL (Left-Right-Root)
// ========================================
// Usage: postorder(root)
// Example: For tree with root 1, left 2, right 3 -> prints "2 3 1"
void postorder(TreeNode* root) {
    if (root == nullptr) return;
    
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// ========================================
// 6. LEVEL ORDER TRAVERSAL (BFS)
// ========================================
// Usage: levelOrder(root)
// Example: Prints nodes level by level
void levelOrder(TreeNode* root) {
    if (root == nullptr) return;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* temp = q.front();
        q.pop();
        
        cout << temp->data << " ";
        
        if (temp->left != nullptr) {
            q.push(temp->left);
        }
        if (temp->right != nullptr) {
            q.push(temp->right);
        }
    }
}

// ========================================
// 7. HEIGHT OF TREE
// ========================================
// Usage: h = height(root)
// Example: height(root) returns maximum depth
int height(TreeNode* root) {
    if (root == nullptr) return 0;
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    return max(leftHeight, rightHeight) + 1;
}

// ========================================
// 8. COUNT NODES
// ========================================
// Usage: count = countNodes(root)
// Example: countNodes(root) returns total number of nodes
int countNodes(TreeNode* root) {
    if (root == nullptr) return 0;
    
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ========================================
// 9. COUNT LEAF NODES
// ========================================
// Usage: leaves = countLeaves(root)
// Example: countLeaves(root) returns number of leaf nodes
int countLeaves(TreeNode* root) {
    if (root == nullptr) return 0;
    
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }
    
    return countLeaves(root->left) + countLeaves(root->right);
}

// ========================================
// 10. SEARCH FOR A VALUE
// ========================================
// Usage: found = search(root, value)
// Example: search(root, 5) returns true if 5 exists
bool search(TreeNode* root, int value) {
    if (root == nullptr) return false;
    
    if (root->data == value) return true;
    
    return search(root->left, value) || search(root->right, value);
}

// ========================================
// 11. FIND MINIMUM VALUE
// ========================================
// Usage: min = findMin(root)
// Example: findMin(root) returns smallest value in tree
int findMin(TreeNode* root) {
    if (root == nullptr) {
        cout << "Tree is empty!" << endl;
        return -1;
    }
    
    int minVal = root->data;
    
    if (root->left != nullptr) {
        minVal = min(minVal, findMin(root->left));
    }
    
    if (root->right != nullptr) {
        minVal = min(minVal, findMin(root->right));
    }
    
    return minVal;
}

// ========================================
// 12. FIND MAXIMUM VALUE
// ========================================
// Usage: max = findMax(root)
// Example: findMax(root) returns largest value in tree
int findMax(TreeNode* root) {
    if (root == nullptr) {
        cout << "Tree is empty!" << endl;
        return -1;
    }
    
    int maxVal = root->data;
    
    if (root->left != nullptr) {
        maxVal = max(maxVal, findMax(root->left));
    }
    
    if (root->right != nullptr) {
        maxVal = max(maxVal, findMax(root->right));
    }
    
    return maxVal;
}

// ========================================
// 13. DELETE TREE
// ========================================
// Usage: root = deleteTree(root)
// Example: Deletes all nodes and frees memory
TreeNode* deleteTree(TreeNode* root) {
    if (root == nullptr) return nullptr;
    
    deleteTree(root->left);
    deleteTree(root->right);
    
    delete root;
    return nullptr;
}

// ========================================
// 14. PRINT TREE STRUCTURE
// ========================================
// Usage: printTree(root, 0)
// Example: Prints tree in a visual format
void printTree(TreeNode* root, int space = 0, int indent = 4) {
    if (root == nullptr) return;
    
    space += indent;
    
    printTree(root->right, space);
    
    cout << endl;
    for (int i = indent; i < space; i++) {
        cout << " ";
    }
    cout << root->data << endl;
    
    printTree(root->left, space);
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    TreeNode* root = nullptr;
    
    cout << "=== Binary Tree Basic Operations ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // Create a sample tree
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    
    // root = insert(root, 1);
    // root = insert(root, 2);
    // root = insert(root, 3);
    // root = insert(root, 4);
    // root = insert(root, 5);
    
    // Print tree structure
    // cout << "\nTree Structure:" << endl;
    // printTree(root);
    
    // Traversals
    // cout << "\nInorder: ";
    // inorder(root);
    // cout << endl;
    
    // cout << "Preorder: ";
    // preorder(root);
    // cout << endl;
    
    // cout << "Postorder: ";
    // postorder(root);
    // cout << endl;
    
    // cout << "Level Order: ";
    // levelOrder(root);
    // cout << endl;
    
    // Height
    // int h = height(root);
    // cout << "\nHeight: " << h << endl;
    
    // Count nodes
    // int total = countNodes(root);
    // cout << "Total nodes: " << total << endl;
    
    // Count leaves
    // int leaves = countLeaves(root);
    // cout << "Leaf nodes: " << leaves << endl;
    
    // Search
    // bool found = search(root, 4);
    // cout << "Search 4: " << (found ? "Found" : "Not found") << endl;
    
    // Min and Max
    // int minVal = findMin(root);
    // int maxVal = findMax(root);
    // cout << "Min: " << minVal << ", Max: " << maxVal << endl;
    
    // Delete tree
    // root = deleteTree(root);
    // cout << "\nTree deleted." << endl;
    
    return 0;
}
