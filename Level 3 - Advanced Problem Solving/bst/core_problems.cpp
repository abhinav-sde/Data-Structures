#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/**
 * Core BST Problems in C++
 */

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Problem 1: Validate BST
bool isValidBSTHelper(TreeNode* node, long min, long max) {
    if (!node) return true;
    if (node->val <= min || node->val >= max) return false;
    return isValidBSTHelper(node->left, min, node->val) && 
           isValidBSTHelper(node->right, node->val, max);
}

bool isValidBST(TreeNode* root) {
    return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
}

// Problem 2: LCA
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;
    
    if (p->val < root->val && q->val < root->val) {
        return lowestCommonAncestor(root->left, p, q);
    }
    
    if (p->val > root->val && q->val > root->val) {
        return lowestCommonAncestor(root->right, p, q);
    }
    
    return root;
}

// Problem 3: Kth Smallest
void inorderK(TreeNode* node, int& k, int& result) {
    if (!node || k == 0) return;
    
    inorderK(node->left, k, result);
    
    k--;
    if (k == 0) {
        result = node->val;
        return;
    }
    
    inorderK(node->right, k, result);
}

int kthSmallest(TreeNode* root, int k) {
    int result = 0;
    inorderK(root, k, result);
    return result;
}

// Problem 4: Sorted Array to BST
TreeNode* sortedArrayToBST(vector<int>& nums, int left, int right) {
    if (left > right) return nullptr;
    
    int mid = left + (right - left) / 2;
    TreeNode* node = new TreeNode(nums[mid]);
    
    node->left = sortedArrayToBST(nums, left, mid - 1);
    node->right = sortedArrayToBST(nums, mid + 1, right);
    
    return node;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    return sortedArrayToBST(nums, 0, nums.size() - 1);
}

// Problem 5: Range Sum
int rangeSumBST(TreeNode* root, int low, int high) {
    if (!root) return 0;
    
    int sum = 0;
    if (root->val >= low && root->val <= high) {
        sum += root->val;
    }
    
    if (root->val > low) {
        sum += rangeSumBST(root->left, low, high);
    }
    
    if (root->val < high) {
        sum += rangeSumBST(root->right, low, high);
    }
    
    return sum;
}

// Helper functions
TreeNode* insert(TreeNode* node, int val) {
    if (!node) return new TreeNode(val);
    if (val < node->val) node->left = insert(node->left, val);
    else if (val > node->val) node->right = insert(node->right, val);
    return node;
}

void inorder(TreeNode* node) {
    if (!node) return;
    inorder(node->left);
    cout << node->val << " ";
    inorder(node->right);
}

int main() {
    cout << "=== Core BST Problems ===" << endl << endl;
    
    // Build BST
    TreeNode* bst = nullptr;
    vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    for (int v : values) {
        bst = insert(bst, v);
    }
    
    cout << "Test 1: Validate BST" << endl;
    cout << "Is valid BST: " << (isValidBST(bst) ? "true" : "false") << endl << endl;
    
    cout << "Test 2: Kth Smallest" << endl;
    cout << "3rd smallest: " << kthSmallest(bst, 3) << endl << endl;
    
    cout << "Test 3: Sorted Array to BST" << endl;
    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* balanced = sortedArrayToBST(sorted);
    cout << "Inorder of balanced BST: ";
    inorder(balanced);
    cout << endl << endl;
    
    cout << "Test 4: Range Sum" << endl;
    int sum = rangeSumBST(bst, 30, 70);
    cout << "Sum in range [30, 70]: " << sum << endl;
    
    return 0;
}
