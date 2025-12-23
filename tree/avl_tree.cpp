#include <iostream>
#include <algorithm>
using namespace std;

// ========================================
// AVL TREE NODE STRUCTURE
// ========================================

struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

// ========================================
// UTILITY FUNCTIONS
// ========================================

// Get height of node
int height(AVLNode* node) {
    return node ? node->height : 0;
}

// Get balance factor
int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Update height of node
void updateHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }
}

// ========================================
// ROTATIONS
// ========================================

// Right Rotation (LL case)
//       y                    x
//      / \                  / \
//     x   T3    -->        T1  y
//    / \                      / \
//   T1  T2                   T2  T3
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    updateHeight(y);
    updateHeight(x);
    
    return x;
}

// Left Rotation (RR case)
//     x                      y
//    / \                    / \
//   T1  y       -->        x   T3
//      / \                / \
//     T2  T3             T1  T2
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    // Update heights
    updateHeight(x);
    updateHeight(y);
    
    return y;
}

// ========================================
// 1. INSERT IN AVL TREE
// ========================================
// Usage: root = insert(root, value)
// Example: root = insert(root, 10)
AVLNode* insert(AVLNode* root, int value) {
    // 1. Normal BST insertion
    if (root == nullptr) {
        cout << "Inserted " << value << endl;
        return new AVLNode(value);
    }
    
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        return root; // Duplicates not allowed
    }
    
    // 2. Update height
    updateHeight(root);
    
    // 3. Get balance factor
    int balance = getBalance(root);
    
    // 4. Balance the tree if needed
    
    // Left-Left Case
    if (balance > 1 && value < root->left->data) {
        cout << "LL Rotation at " << root->data << endl;
        return rightRotate(root);
    }
    
    // Right-Right Case
    if (balance < -1 && value > root->right->data) {
        cout << "RR Rotation at " << root->data << endl;
        return leftRotate(root);
    }
    
    // Left-Right Case
    if (balance > 1 && value > root->left->data) {
        cout << "LR Rotation at " << root->data << endl;
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right-Left Case
    if (balance < -1 && value < root->right->data) {
        cout << "RL Rotation at " << root->data << endl;
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

// ========================================
// 2. DELETE FROM AVL TREE
// ========================================
// Usage: root = deleteNode(root, value)
// Example: root = deleteNode(root, 10)
AVLNode* findMin(AVLNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

AVLNode* deleteNode(AVLNode* root, int value) {
    // 1. Normal BST deletion
    if (root == nullptr) return nullptr;
    
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // Node found
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode* temp = root->left ? root->left : root->right;
            
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            
            delete temp;
            cout << "Deleted " << value << endl;
        } else {
            AVLNode* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    
    if (root == nullptr) return root;
    
    // 2. Update height
    updateHeight(root);
    
    // 3. Get balance factor
    int balance = getBalance(root);
    
    // 4. Balance the tree
    
    // Left-Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    
    // Left-Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right-Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    
    // Right-Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

// ========================================
// 3. SEARCH IN AVL TREE
// ========================================
// Usage: found = search(root, value)
// Example: search(root, 30) returns node or nullptr
AVLNode* search(AVLNode* root, int value) {
    if (root == nullptr || root->data == value) {
        return root;
    }
    
    if (value < root->data) {
        return search(root->left, value);
    }
    
    return search(root->right, value);
}

// ========================================
// 4. CHECK IF BALANCED
// ========================================
// Usage: balanced = isBalanced(root)
// Example: isBalanced(root) returns true if AVL property maintained
bool isBalanced(AVLNode* root) {
    if (root == nullptr) return true;
    
    int balance = getBalance(root);
    
    if (abs(balance) > 1) return false;
    
    return isBalanced(root->left) && isBalanced(root->right);
}

// ========================================
// 5. INORDER TRAVERSAL
// ========================================
// Usage: inorder(root)
// Example: Prints tree in sorted order
void inorder(AVLNode* root) {
    if (root == nullptr) return;
    
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// ========================================
// 6. PREORDER TRAVERSAL
// ========================================
// Usage: preorder(root)
// Example: Prints tree in preorder
void preorder(AVLNode* root) {
    if (root == nullptr) return;
    
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// ========================================
// 7. PRINT TREE WITH HEIGHTS
// ========================================
// Usage: printTree(root, 0)
// Example: Prints tree structure with heights
void printTree(AVLNode* root, int space = 0, int indent = 4) {
    if (root == nullptr) return;
    
    space += indent;
    
    printTree(root->right, space);
    
    cout << endl;
    for (int i = indent; i < space; i++) {
        cout << " ";
    }
    cout << root->data << "(h=" << root->height << ",b=" << getBalance(root) << ")" << endl;
    
    printTree(root->left, space);
}

// ========================================
// 8. COUNT NODES
// ========================================
// Usage: count = countNodes(root)
// Example: countNodes(root) returns total nodes
int countNodes(AVLNode* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ========================================
// 9. FIND KTH SMALLEST
// ========================================
// Usage: kth = kthSmallest(root, k)
// Example: kthSmallest(root, 3) returns 3rd smallest
void kthSmallestHelper(AVLNode* root, int& k, int& result) {
    if (root == nullptr) return;
    
    kthSmallestHelper(root->left, k, result);
    
    k--;
    if (k == 0) {
        result = root->data;
        return;
    }
    
    kthSmallestHelper(root->right, k, result);
}

int kthSmallest(AVLNode* root, int k) {
    int result = -1;
    kthSmallestHelper(root, k, result);
    return result;
}

// ========================================
// 10. RANGE QUERY
// ========================================
// Usage: rangeQuery(root, low, high)
// Example: Prints all values in range [low, high]
void rangeQuery(AVLNode* root, int low, int high) {
    if (root == nullptr) return;
    
    if (root->data > low) {
        rangeQuery(root->left, low, high);
    }
    
    if (root->data >= low && root->data <= high) {
        cout << root->data << " ";
    }
    
    if (root->data < high) {
        rangeQuery(root->right, low, high);
    }
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    AVLNode* root = nullptr;
    
    cout << "=== AVL Tree Operations ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // Insert nodes
    // root = insert(root, 10);
    // root = insert(root, 20);
    // root = insert(root, 30);
    // root = insert(root, 40);
    // root = insert(root, 50);
    // root = insert(root, 25);
    
    // Print tree structure
    // cout << "\nTree Structure:" << endl;
    // printTree(root);
    
    // Inorder (sorted)
    // cout << "\nInorder: ";
    // inorder(root);
    // cout << endl;
    
    // Check if balanced
    // bool balanced = isBalanced(root);
    // cout << "Is balanced: " << (balanced ? "Yes" : "No") << endl;
    
    // Search
    // AVLNode* found = search(root, 25);
    // cout << "Search 25: " << (found ? "Found" : "Not found") << endl;
    
    // Count nodes
    // int count = countNodes(root);
    // cout << "Total nodes: " << count << endl;
    
    // Delete node
    // root = deleteNode(root, 20);
    // cout << "\nAfter deleting 20:" << endl;
    // printTree(root);
    
    // Kth smallest
    // int kth = kthSmallest(root, 3);
    // cout << "3rd smallest: " << kth << endl;
    
    // Range query
    // cout << "Range [20, 40]: ";
    // rangeQuery(root, 20, 40);
    // cout << endl;
    
    return 0;
}
