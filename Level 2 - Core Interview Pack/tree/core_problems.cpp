#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
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
// 1. MAXIMUM DEPTH / HEIGHT
// ========================================
// Concept: Recursion
// Usage: depth = maxDepth(root)
// Example: maxDepth(root) returns height of tree
int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// ========================================
// 2. MINIMUM DEPTH
// ========================================
// Concept: BFS or DFS
// Usage: depth = minDepth(root)
// Example: minDepth(root) returns shortest path to leaf
int minDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }
    
    if (root->left == nullptr) {
        return 1 + minDepth(root->right);
    }
    
    if (root->right == nullptr) {
        return 1 + minDepth(root->left);
    }
    
    return 1 + min(minDepth(root->left), minDepth(root->right));
}

// ========================================
// 3. DIAMETER OF TREE
// ========================================
// Concept: Longest path between any two nodes
// Usage: diam = diameter(root)
// Example: diameter(root) returns longest path
int diameterHelper(TreeNode* root, int& diameter) {
    if (root == nullptr) return 0;
    
    int leftHeight = diameterHelper(root->left, diameter);
    int rightHeight = diameterHelper(root->right, diameter);
    
    diameter = max(diameter, leftHeight + rightHeight);
    
    return 1 + max(leftHeight, rightHeight);
}

int diameter(TreeNode* root) {
    int diam = 0;
    diameterHelper(root, diam);
    return diam;
}

// ========================================
// 4. CHECK IF BALANCED
// ========================================
// Concept: Height difference <= 1 for all nodes
// Usage: balanced = isBalanced(root)
// Example: isBalanced(root) returns true/false
int checkHeight(TreeNode* root, bool& balanced) {
    if (root == nullptr) return 0;
    
    int leftHeight = checkHeight(root->left, balanced);
    int rightHeight = checkHeight(root->right, balanced);
    
    if (abs(leftHeight - rightHeight) > 1) {
        balanced = false;
    }
    
    return 1 + max(leftHeight, rightHeight);
}

bool isBalanced(TreeNode* root) {
    bool balanced = true;
    checkHeight(root, balanced);
    return balanced;
}

// ========================================
// 5. CHECK IF SYMMETRIC (MIRROR)
// ========================================
// Concept: Left subtree mirrors right subtree
// Usage: symmetric = isSymmetric(root)
// Example: isSymmetric(root) checks mirror property
bool isMirror(TreeNode* left, TreeNode* right) {
    if (left == nullptr && right == nullptr) return true;
    if (left == nullptr || right == nullptr) return false;
    
    return (left->data == right->data) &&
           isMirror(left->left, right->right) &&
           isMirror(left->right, right->left);
}

bool isSymmetric(TreeNode* root) {
    if (root == nullptr) return true;
    return isMirror(root->left, root->right);
}

// ========================================
// 6. INVERT/MIRROR TREE
// ========================================
// Concept: Swap left and right subtrees
// Usage: root = invertTree(root)
// Example: invertTree(root) mirrors the tree
TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) return nullptr;
    
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    invertTree(root->left);
    invertTree(root->right);
    
    return root;
}

// ========================================
// 7. LOWEST COMMON ANCESTOR (LCA)
// ========================================
// Concept: Deepest node that is ancestor of both
// Usage: lca = findLCA(root, p, q)
// Example: findLCA(root, 4, 5) finds common ancestor
TreeNode* findLCA(TreeNode* root, int p, int q) {
    if (root == nullptr) return nullptr;
    
    if (root->data == p || root->data == q) {
        return root;
    }
    
    TreeNode* left = findLCA(root->left, p, q);
    TreeNode* right = findLCA(root->right, p, q);
    
    if (left != nullptr && right != nullptr) {
        return root;
    }
    
    return (left != nullptr) ? left : right;
}

// ========================================
// 8. PATH SUM
// ========================================
// Concept: Check if root-to-leaf path sums to target
// Usage: exists = hasPathSum(root, sum)
// Example: hasPathSum(root, 22) checks if path exists
bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) return false;
    
    if (root->left == nullptr && root->right == nullptr) {
        return root->data == targetSum;
    }
    
    return hasPathSum(root->left, targetSum - root->data) ||
           hasPathSum(root->right, targetSum - root->data);
}

// ========================================
// 9. ALL ROOT-TO-LEAF PATHS
// ========================================
// Concept: DFS to collect all paths
// Usage: paths = allPaths(root)
// Example: Prints all root-to-leaf paths
void findPaths(TreeNode* root, vector<int>& path, vector<vector<int>>& paths) {
    if (root == nullptr) return;
    
    path.push_back(root->data);
    
    if (root->left == nullptr && root->right == nullptr) {
        paths.push_back(path);
    } else {
        findPaths(root->left, path, paths);
        findPaths(root->right, path, paths);
    }
    
    path.pop_back();
}

vector<vector<int>> allPaths(TreeNode* root) {
    vector<vector<int>> paths;
    vector<int> path;
    findPaths(root, path, paths);
    return paths;
}

// ========================================
// 10. LEVEL ORDER TRAVERSAL (BY LEVELS)
// ========================================
// Concept: BFS with level separation
// Usage: levels = levelOrderByLevels(root)
// Example: Returns vector of vectors (each level)
vector<vector<int>> levelOrderByLevels(TreeNode* root) {
    vector<vector<int>> result;
    if (root == nullptr) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->data);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(level);
    }
    
    return result;
}

// ========================================
// 11. ZIGZAG LEVEL ORDER
// ========================================
// Concept: Alternate left-to-right and right-to-left
// Usage: zigzag = zigzagLevelOrder(root)
// Example: Level 0: L->R, Level 1: R->L, etc.
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (root == nullptr) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;
    
    while (!q.empty()) {
        int size = q.size();
        vector<int> level(size);
        
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            int index = leftToRight ? i : (size - 1 - i);
            level[index] = node->data;
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(level);
        leftToRight = !leftToRight;
    }
    
    return result;
}

// ========================================
// 12. RIGHT SIDE VIEW
// ========================================
// Concept: Rightmost node at each level
// Usage: view = rightSideView(root)
// Example: Returns nodes visible from right side
vector<int> rightSideView(TreeNode* root) {
    vector<int> result;
    if (root == nullptr) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            if (i == size - 1) {
                result.push_back(node->data);
            }
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    
    return result;
}

// ========================================
// 13. LEFT SIDE VIEW
// ========================================
// Concept: Leftmost node at each level
// Usage: view = leftSideView(root)
// Example: Returns nodes visible from left side
vector<int> leftSideView(TreeNode* root) {
    vector<int> result;
    if (root == nullptr) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            if (i == 0) {
                result.push_back(node->data);
            }
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    
    return result;
}

// ========================================
// 14. VERTICAL ORDER TRAVERSAL
// ========================================
// Concept: Group nodes by vertical column
// Usage: verticalOrder(root)
// Example: Prints nodes column by column
void verticalOrderHelper(TreeNode* root, int col, map<int, vector<int>>& m) {
    if (root == nullptr) return;
    
    m[col].push_back(root->data);
    
    verticalOrderHelper(root->left, col - 1, m);
    verticalOrderHelper(root->right, col + 1, m);
}

void verticalOrder(TreeNode* root) {
    map<int, vector<int>> m;
    verticalOrderHelper(root, 0, m);
    
    cout << "Vertical Order: " << endl;
    for (auto& pair : m) {
        cout << "Column " << pair.first << ": ";
        for (int val : pair.second) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// ========================================
// 15. BOUNDARY TRAVERSAL
// ========================================
// Concept: Left boundary + leaves + right boundary
// Usage: boundaryTraversal(root)
// Example: Prints boundary nodes
void printLeftBoundary(TreeNode* root) {
    if (root == nullptr) return;
    if (root->left != nullptr || root->right != nullptr) {
        cout << root->data << " ";
    }
    if (root->left != nullptr) {
        printLeftBoundary(root->left);
    } else {
        printLeftBoundary(root->right);
    }
}

void printLeaves(TreeNode* root) {
    if (root == nullptr) return;
    
    printLeaves(root->left);
    
    if (root->left == nullptr && root->right == nullptr) {
        cout << root->data << " ";
    }
    
    printLeaves(root->right);
}

void printRightBoundary(TreeNode* root) {
    if (root == nullptr) return;
    
    if (root->right != nullptr) {
        printRightBoundary(root->right);
    } else {
        printRightBoundary(root->left);
    }
    
    if (root->left != nullptr || root->right != nullptr) {
        cout << root->data << " ";
    }
}

void boundaryTraversal(TreeNode* root) {
    if (root == nullptr) return;
    
    cout << "Boundary: ";
    cout << root->data << " ";
    
    printLeftBoundary(root->left);
    printLeaves(root->left);
    printLeaves(root->right);
    printRightBoundary(root->right);
    
    cout << endl;
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    cout << "=== Binary Tree Core Problems ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // Create sample tree
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    
    // TreeNode* root = new TreeNode(1);
    // root->left = new TreeNode(2);
    // root->right = new TreeNode(3);
    // root->left->left = new TreeNode(4);
    // root->left->right = new TreeNode(5);
    
    // 1. Max Depth
    // int depth = maxDepth(root);
    // cout << "Max Depth: " << depth << endl;
    
    // 2. Min Depth
    // int minDep = minDepth(root);
    // cout << "Min Depth: " << minDep << endl;
    
    // 3. Diameter
    // int diam = diameter(root);
    // cout << "Diameter: " << diam << endl;
    
    // 4. Is Balanced
    // bool balanced = isBalanced(root);
    // cout << "Is Balanced: " << (balanced ? "Yes" : "No") << endl;
    
    // 5. Is Symmetric
    // bool symmetric = isSymmetric(root);
    // cout << "Is Symmetric: " << (symmetric ? "Yes" : "No") << endl;
    
    // 6. Invert Tree
    // root = invertTree(root);
    // cout << "Tree inverted." << endl;
    
    // 7. LCA
    // TreeNode* lca = findLCA(root, 4, 5);
    // cout << "LCA of 4 and 5: " << lca->data << endl;
    
    // 8. Path Sum
    // bool hasPath = hasPathSum(root, 7);
    // cout << "Has path sum 7: " << (hasPath ? "Yes" : "No") << endl;
    
    // 9. All Paths
    // vector<vector<int>> paths = allPaths(root);
    // cout << "All paths:" << endl;
    // for (auto& path : paths) {
    //     for (int val : path) cout << val << " ";
    //     cout << endl;
    // }
    
    // 10. Level Order by Levels
    // vector<vector<int>> levels = levelOrderByLevels(root);
    // cout << "Level Order:" << endl;
    // for (auto& level : levels) {
    //     for (int val : level) cout << val << " ";
    //     cout << endl;
    // }
    
    // 11. Zigzag Level Order
    // vector<vector<int>> zigzag = zigzagLevelOrder(root);
    // cout << "Zigzag Order:" << endl;
    // for (auto& level : zigzag) {
    //     for (int val : level) cout << val << " ";
    //     cout << endl;
    // }
    
    // 12. Right Side View
    // vector<int> rightView = rightSideView(root);
    // cout << "Right View: ";
    // for (int val : rightView) cout << val << " ";
    // cout << endl;
    
    // 13. Left Side View
    // vector<int> leftView = leftSideView(root);
    // cout << "Left View: ";
    // for (int val : leftView) cout << val << " ";
    // cout << endl;
    
    // 14. Vertical Order
    // verticalOrder(root);
    
    // 15. Boundary Traversal
    // boundaryTraversal(root);
    
    return 0;
}
