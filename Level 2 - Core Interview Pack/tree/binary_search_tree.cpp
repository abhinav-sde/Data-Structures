#include <iostream>
#include <climits>
using namespace std;

// ========================================
// BST NODE STRUCTURE
// ========================================

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// ========================================
// 1. INSERT IN BST
// ========================================
// Usage: root = insert(root, value)
// Example: root = insert(root, 50)
BSTNode* insert(BSTNode* root, int value) {
    if (root == nullptr) {
        cout << "Inserted " << value << endl;
        return new BSTNode(value);
    }
    
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    
    return root;
}

// ========================================
// 2. SEARCH IN BST
// ========================================
// Usage: found = search(root, value)
// Example: search(root, 30) returns node or nullptr
BSTNode* search(BSTNode* root, int value) {
    if (root == nullptr || root->data == value) {
        return root;
    }
    
    if (value < root->data) {
        return search(root->left, value);
    }
    
    return search(root->right, value);
}

// ========================================
// 3. FIND MINIMUM
// ========================================
// Usage: min = findMin(root)
// Example: findMin(root) returns leftmost node
BSTNode* findMin(BSTNode* root) {
    if (root == nullptr) return nullptr;
    
    while (root->left != nullptr) {
        root = root->left;
    }
    
    return root;
}

// ========================================
// 4. FIND MAXIMUM
// ========================================
// Usage: max = findMax(root)
// Example: findMax(root) returns rightmost node
BSTNode* findMax(BSTNode* root) {
    if (root == nullptr) return nullptr;
    
    while (root->right != nullptr) {
        root = root->right;
    }
    
    return root;
}

// ========================================
// 5. DELETE NODE IN BST
// ========================================
// Usage: root = deleteNode(root, value)
// Example: root = deleteNode(root, 30)
BSTNode* deleteNode(BSTNode* root, int value) {
    if (root == nullptr) return nullptr;
    
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // Node found
        
        // Case 1: Leaf node
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        
        // Case 2: One child
        if (root->left == nullptr) {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == nullptr) {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }
        
        // Case 3: Two children
        BSTNode* successor = findMin(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }
    
    return root;
}

// ========================================
// 6. INORDER SUCCESSOR
// ========================================
// Usage: successor = inorderSuccessor(root, node)
// Example: Next larger element in BST
BSTNode* inorderSuccessor(BSTNode* root, BSTNode* node) {
    if (node->right != nullptr) {
        return findMin(node->right);
    }
    
    BSTNode* successor = nullptr;
    while (root != nullptr) {
        if (node->data < root->data) {
            successor = root;
            root = root->left;
        } else if (node->data > root->data) {
            root = root->right;
        } else {
            break;
        }
    }
    
    return successor;
}

// ========================================
// 7. INORDER PREDECESSOR
// ========================================
// Usage: predecessor = inorderPredecessor(root, node)
// Example: Next smaller element in BST
BSTNode* inorderPredecessor(BSTNode* root, BSTNode* node) {
    if (node->left != nullptr) {
        return findMax(node->left);
    }
    
    BSTNode* predecessor = nullptr;
    while (root != nullptr) {
        if (node->data > root->data) {
            predecessor = root;
            root = root->right;
        } else if (node->data < root->data) {
            root = root->left;
        } else {
            break;
        }
    }
    
    return predecessor;
}

// ========================================
// 8. VALIDATE BST
// ========================================
// Usage: valid = isValidBST(root)
// Example: Checks if tree satisfies BST property
bool isValidBSTHelper(BSTNode* root, long min, long max) {
    if (root == nullptr) return true;
    
    if (root->data <= min || root->data >= max) {
        return false;
    }
    
    return isValidBSTHelper(root->left, min, root->data) &&
           isValidBSTHelper(root->right, root->data, max);
}

bool isValidBST(BSTNode* root) {
    return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
}

// ========================================
// 9. LOWEST COMMON ANCESTOR IN BST
// ========================================
// Usage: lca = lowestCommonAncestor(root, p, q)
// Example: LCA of two nodes in BST
BSTNode* lowestCommonAncestor(BSTNode* root, int p, int q) {
    if (root == nullptr) return nullptr;
    
    if (p < root->data && q < root->data) {
        return lowestCommonAncestor(root->left, p, q);
    }
    
    if (p > root->data && q > root->data) {
        return lowestCommonAncestor(root->right, p, q);
    }
    
    return root;
}

// ========================================
// 10. KTH SMALLEST ELEMENT
// ========================================
// Usage: kth = kthSmallest(root, k)
// Example: kthSmallest(root, 3) returns 3rd smallest
void kthSmallestHelper(BSTNode* root, int& k, int& result) {
    if (root == nullptr) return;
    
    kthSmallestHelper(root->left, k, result);
    
    k--;
    if (k == 0) {
        result = root->data;
        return;
    }
    
    kthSmallestHelper(root->right, k, result);
}

int kthSmallest(BSTNode* root, int k) {
    int result = -1;
    kthSmallestHelper(root, k, result);
    return result;
}

// ========================================
// 11. CONVERT SORTED ARRAY TO BST
// ========================================
// Usage: root = sortedArrayToBST(arr, start, end)
// Example: Creates balanced BST from sorted array
BSTNode* sortedArrayToBST(int arr[], int start, int end) {
    if (start > end) return nullptr;
    
    int mid = start + (end - start) / 2;
    BSTNode* root = new BSTNode(arr[mid]);
    
    root->left = sortedArrayToBST(arr, start, mid - 1);
    root->right = sortedArrayToBST(arr, mid + 1, end);
    
    return root;
}

// ========================================
// 12. RANGE SUM IN BST
// ========================================
// Usage: sum = rangeSumBST(root, low, high)
// Example: Sum of all nodes in range [low, high]
int rangeSumBST(BSTNode* root, int low, int high) {
    if (root == nullptr) return 0;
    
    if (root->data < low) {
        return rangeSumBST(root->right, low, high);
    }
    
    if (root->data > high) {
        return rangeSumBST(root->left, low, high);
    }
    
    return root->data + 
           rangeSumBST(root->left, low, high) + 
           rangeSumBST(root->right, low, high);
}

// ========================================
// 13. INORDER TRAVERSAL (SORTED ORDER)
// ========================================
// Usage: inorder(root)
// Example: Prints BST in sorted order
void inorder(BSTNode* root) {
    if (root == nullptr) return;
    
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    BSTNode* root = nullptr;
    
    cout << "=== Binary Search Tree Operations ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // Insert nodes
    // root = insert(root, 50);
    // root = insert(root, 30);
    // root = insert(root, 70);
    // root = insert(root, 20);
    // root = insert(root, 40);
    // root = insert(root, 60);
    // root = insert(root, 80);
    
    // Inorder (sorted)
    // cout << "Inorder: ";
    // inorder(root);
    // cout << endl;
    
    // Search
    // BSTNode* found = search(root, 40);
    // cout << "Search 40: " << (found ? "Found" : "Not found") << endl;
    
    // Min and Max
    // BSTNode* minNode = findMin(root);
    // BSTNode* maxNode = findMax(root);
    // cout << "Min: " << minNode->data << ", Max: " << maxNode->data << endl;
    
    // Delete
    // root = deleteNode(root, 30);
    // cout << "After deleting 30: ";
    // inorder(root);
    // cout << endl;
    
    // Validate BST
    // bool valid = isValidBST(root);
    // cout << "Is valid BST: " << (valid ? "Yes" : "No") << endl;
    
    // LCA
    // BSTNode* lca = lowestCommonAncestor(root, 20, 40);
    // cout << "LCA of 20 and 40: " << lca->data << endl;
    
    // Kth smallest
    // int kth = kthSmallest(root, 3);
    // cout << "3rd smallest: " << kth << endl;
    
    // Range sum
    // int sum = rangeSumBST(root, 30, 70);
    // cout << "Sum in range [30, 70]: " << sum << endl;
    
    // Convert sorted array to BST
    // int arr[] = {1, 2, 3, 4, 5, 6, 7};
    // BSTNode* balancedBST = sortedArrayToBST(arr, 0, 6);
    // cout << "Balanced BST created from sorted array" << endl;
    
    return 0;
}
