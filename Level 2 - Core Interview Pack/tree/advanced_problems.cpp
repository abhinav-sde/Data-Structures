#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <stack>
#include <climits>
using namespace std;

// ========================================
// NODE STRUCTURES
// ========================================

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

struct NodeWithParent {
    int data;
    NodeWithParent* left;
    NodeWithParent* right;
    NodeWithParent* parent;
    
    NodeWithParent(int val) : data(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

// ========================================
// 1. SERIALIZE AND DESERIALIZE TREE
// ========================================
// Concept: Convert tree to string and back
// Usage: str = serialize(root), root = deserialize(str)
string serialize(TreeNode* root) {
    if (root == nullptr) return "#";
    
    return to_string(root->data) + "," + 
           serialize(root->left) + "," + 
           serialize(root->right);
}

TreeNode* deserializeHelper(queue<string>& nodes) {
    string val = nodes.front();
    nodes.pop();
    
    if (val == "#") return nullptr;
    
    TreeNode* root = new TreeNode(stoi(val));
    root->left = deserializeHelper(nodes);
    root->right = deserializeHelper(nodes);
    
    return root;
}

TreeNode* deserialize(string data) {
    queue<string> nodes;
    string token = "";
    
    for (char c : data) {
        if (c == ',') {
            nodes.push(token);
            token = "";
        } else {
            token += c;
        }
    }
    if (!token.empty()) nodes.push(token);
    
    return deserializeHelper(nodes);
}

// ========================================
// 2. CONSTRUCT TREE FROM INORDER AND PREORDER
// ========================================
// Concept: Use preorder for root, inorder for left/right split
TreeNode* buildTreeHelper(vector<int>& preorder, int& preIdx, 
                          vector<int>& inorder, int inStart, int inEnd,
                          unordered_map<int, int>& inMap) {
    if (inStart > inEnd) return nullptr;
    
    int rootVal = preorder[preIdx++];
    TreeNode* root = new TreeNode(rootVal);
    
    int inIdx = inMap[rootVal];
    
    root->left = buildTreeHelper(preorder, preIdx, inorder, inStart, inIdx - 1, inMap);
    root->right = buildTreeHelper(preorder, preIdx, inorder, inIdx + 1, inEnd, inMap);
    
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int, int> inMap;
    for (int i = 0; i < inorder.size(); i++) {
        inMap[inorder[i]] = i;
    }
    
    int preIdx = 0;
    return buildTreeHelper(preorder, preIdx, inorder, 0, inorder.size() - 1, inMap);
}

// ========================================
// 3. MAXIMUM PATH SUM
// ========================================
// Concept: Path can start and end at any node
int maxPathSumHelper(TreeNode* root, int& maxSum) {
    if (root == nullptr) return 0;
    
    int left = max(0, maxPathSumHelper(root->left, maxSum));
    int right = max(0, maxPathSumHelper(root->right, maxSum));
    
    maxSum = max(maxSum, left + right + root->data);
    
    return root->data + max(left, right);
}

int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    maxPathSumHelper(root, maxSum);
    return maxSum;
}

// ========================================
// 4. FLATTEN TREE TO LINKED LIST
// ========================================
// Concept: Flatten to right-skewed tree (preorder)
void flatten(TreeNode* root) {
    if (root == nullptr) return;
    
    flatten(root->left);
    flatten(root->right);
    
    TreeNode* rightSubtree = root->right;
    root->right = root->left;
    root->left = nullptr;
    
    TreeNode* current = root;
    while (current->right != nullptr) {
        current = current->right;
    }
    current->right = rightSubtree;
}

// ========================================
// 5. POPULATE NEXT RIGHT POINTERS
// ========================================
// Concept: Connect nodes at same level
struct NodeWithNext {
    int data;
    NodeWithNext* left;
    NodeWithNext* right;
    NodeWithNext* next;
    
    NodeWithNext(int val) : data(val), left(nullptr), right(nullptr), next(nullptr) {}
};

NodeWithNext* connect(NodeWithNext* root) {
    if (root == nullptr) return nullptr;
    
    queue<NodeWithNext*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            NodeWithNext* node = q.front();
            q.pop();
            
            if (i < size - 1) {
                node->next = q.front();
            }
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    
    return root;
}

// ========================================
// 6. KTHSMALLEST ELEMENT IN BST
// ========================================
// Concept: Inorder traversal of BST gives sorted order
void kthSmallestHelper(TreeNode* root, int& k, int& result) {
    if (root == nullptr) return;
    
    kthSmallestHelper(root->left, k, result);
    
    k--;
    if (k == 0) {
        result = root->data;
        return;
    }
    
    kthSmallestHelper(root->right, k, result);
}

int kthSmallest(TreeNode* root, int k) {
    int result = -1;
    kthSmallestHelper(root, k, result);
    return result;
}

// ========================================
// 7. VALIDATE BST
// ========================================
// Concept: Check if tree satisfies BST property
bool isValidBSTHelper(TreeNode* root, long minVal, long maxVal) {
    if (root == nullptr) return true;
    
    if (root->data <= minVal || root->data >= maxVal) {
        return false;
    }
    
    return isValidBSTHelper(root->left, minVal, root->data) &&
           isValidBSTHelper(root->right, root->data, maxVal);
}

bool isValidBST(TreeNode* root) {
    return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
}

// ========================================
// 8. RECOVER BST (TWO SWAPPED NODES)
// ========================================
// Concept: Find two swapped nodes and fix
void recoverBSTHelper(TreeNode* root, TreeNode*& first, TreeNode*& second, TreeNode*& prev) {
    if (root == nullptr) return;
    
    recoverBSTHelper(root->left, first, second, prev);
    
    if (prev != nullptr && prev->data > root->data) {
        if (first == nullptr) {
            first = prev;
        }
        second = root;
    }
    prev = root;
    
    recoverBSTHelper(root->right, first, second, prev);
}

void recoverBST(TreeNode* root) {
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;
    TreeNode* prev = nullptr;
    
    recoverBSTHelper(root, first, second, prev);
    
    if (first != nullptr && second != nullptr) {
        swap(first->data, second->data);
    }
}

// ========================================
// 9. BINARY TREE CAMERAS
// ========================================
// Concept: Minimum cameras to monitor all nodes
enum CameraState { NOT_MONITORED = 0, MONITORED = 1, HAS_CAMERA = 2 };

int minCamerasHelper(TreeNode* root, int& cameras) {
    if (root == nullptr) return MONITORED;
    
    int left = minCamerasHelper(root->left, cameras);
    int right = minCamerasHelper(root->right, cameras);
    
    if (left == NOT_MONITORED || right == NOT_MONITORED) {
        cameras++;
        return HAS_CAMERA;
    }
    
    if (left == HAS_CAMERA || right == HAS_CAMERA) {
        return MONITORED;
    }
    
    return NOT_MONITORED;
}

int minCameraCover(TreeNode* root) {
    int cameras = 0;
    if (minCamerasHelper(root, cameras) == NOT_MONITORED) {
        cameras++;
    }
    return cameras;
}

// ========================================
// 10. MORRIS TRAVERSAL (INORDER)
// ========================================
// Concept: O(1) space traversal using threading
vector<int> morrisInorder(TreeNode* root) {
    vector<int> result;
    TreeNode* current = root;
    
    while (current != nullptr) {
        if (current->left == nullptr) {
            result.push_back(current->data);
            current = current->right;
        } else {
            TreeNode* predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current) {
                predecessor = predecessor->right;
            }
            
            if (predecessor->right == nullptr) {
                predecessor->right = current;
                current = current->left;
            } else {
                predecessor->right = nullptr;
                result.push_back(current->data);
                current = current->right;
            }
        }
    }
    
    return result;
}

// ========================================
// 11. VERTICAL SUM
// ========================================
// Concept: Sum of nodes at each vertical column
void verticalSumHelper(TreeNode* root, int col, map<int, int>& sumMap) {
    if (root == nullptr) return;
    
    sumMap[col] += root->data;
    
    verticalSumHelper(root->left, col - 1, sumMap);
    verticalSumHelper(root->right, col + 1, sumMap);
}

void verticalSum(TreeNode* root) {
    map<int, int> sumMap;
    verticalSumHelper(root, 0, sumMap);
    
    cout << "Vertical Sums:" << endl;
    for (auto& pair : sumMap) {
        cout << "Column " << pair.first << ": " << pair.second << endl;
    }
}

// ========================================
// 12. DISTANCE BETWEEN TWO NODES
// ========================================
// Concept: Use LCA and find distances
TreeNode* findLCA(TreeNode* root, int p, int q) {
    if (root == nullptr || root->data == p || root->data == q) {
        return root;
    }
    
    TreeNode* left = findLCA(root->left, p, q);
    TreeNode* right = findLCA(root->right, p, q);
    
    if (left && right) return root;
    return left ? left : right;
}

int findLevel(TreeNode* root, int val, int level) {
    if (root == nullptr) return -1;
    if (root->data == val) return level;
    
    int left = findLevel(root->left, val, level + 1);
    if (left != -1) return left;
    
    return findLevel(root->right, val, level + 1);
}

int findDistance(TreeNode* root, int p, int q) {
    TreeNode* lca = findLCA(root, p, q);
    
    int d1 = findLevel(lca, p, 0);
    int d2 = findLevel(lca, q, 0);
    
    return d1 + d2;
}

// ========================================
// 13. PRINT ALL K-SUM PATHS
// ========================================
// Concept: Find all paths with sum k
void kSumPathsHelper(TreeNode* root, int k, vector<int>& path, int& count) {
    if (root == nullptr) return;
    
    path.push_back(root->data);
    
    int sum = 0;
    for (int i = path.size() - 1; i >= 0; i--) {
        sum += path[i];
        if (sum == k) {
            count++;
        }
    }
    
    kSumPathsHelper(root->left, k, path, count);
    kSumPathsHelper(root->right, k, path, count);
    
    path.pop_back();
}

int kSumPaths(TreeNode* root, int k) {
    vector<int> path;
    int count = 0;
    kSumPathsHelper(root, k, path, count);
    return count;
}

// ========================================
// 14. CONVERT BST TO GREATER TREE
// ========================================
// Concept: Replace each node with sum of all greater nodes
void convertBSTHelper(TreeNode* root, int& sum) {
    if (root == nullptr) return;
    
    convertBSTHelper(root->right, sum);
    
    sum += root->data;
    root->data = sum;
    
    convertBSTHelper(root->left, sum);
}

TreeNode* convertBST(TreeNode* root) {
    int sum = 0;
    convertBSTHelper(root, sum);
    return root;
}

// ========================================
// 15. HOUSE ROBBER III
// ========================================
// Concept: Max money without robbing adjacent nodes
pair<int, int> robHelper(TreeNode* root) {
    if (root == nullptr) return {0, 0};
    
    auto left = robHelper(root->left);
    auto right = robHelper(root->right);
    
    int robCurrent = root->data + left.second + right.second;
    int skipCurrent = max(left.first, left.second) + max(right.first, right.second);
    
    return {robCurrent, skipCurrent};
}

int rob(TreeNode* root) {
    auto result = robHelper(root);
    return max(result.first, result.second);
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    cout << "=== Binary Tree Advanced Problems ===" << endl;
    
    // Create sample tree for testing
    // TreeNode* root = new TreeNode(1);
    // root->left = new TreeNode(2);
    // root->right = new TreeNode(3);
    // root->left->left = new TreeNode(4);
    // root->left->right = new TreeNode(5);
    
    // Test functions here (uncomment as needed)
    
    return 0;
}
