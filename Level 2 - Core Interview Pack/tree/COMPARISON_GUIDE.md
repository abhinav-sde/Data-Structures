# TREE DATA STRUCTURES - COMPLETE COMPARISON GUIDE
## Interview Preparation Reference

---

## 📋 TABLE OF CONTENTS
1. [Overview](#overview)
2. [Binary Tree](#binary-tree)
3. [Binary Search Tree (BST)](#binary-search-tree-bst)
4. [AVL Tree](#avl-tree)
5. [Red-Black Tree](#red-black-tree)
6. [B-Tree & B+ Tree](#b-tree--b-tree)
7. [Heap (Binary Heap)](#heap-binary-heap)
8. [Trie (Prefix Tree)](#trie-prefix-tree)
9. [Segment Tree](#segment-tree)
10. [Comparison Table](#comparison-table)
11. [When to Use What](#when-to-use-what)
12. [Interview Questions & Answers](#interview-questions--answers)
13. [Common Patterns](#common-patterns)

---

## 🎯 OVERVIEW

### What is a Tree?
A **tree** is a hierarchical data structure consisting of nodes connected by edges. Each tree has:
- **Root**: Top node
- **Parent**: Node with children
- **Child**: Node connected below parent
- **Leaf**: Node with no children
- **Height**: Longest path from root to leaf
- **Depth**: Distance from root to node

### Why Use Trees?
✅ **Hierarchical data** - Natural for file systems, org charts  
✅ **Fast search** - O(log n) in balanced trees  
✅ **Sorted data** - BST maintains order  
✅ **Range queries** - Efficient with segment trees  
✅ **Prefix matching** - Tries for autocomplete  

---

## 1️⃣ BINARY TREE

### Structure
```
       1
      / \
     2   3
    / \
   4   5
```

### Definition
- Each node has **at most 2 children** (left and right)
- No ordering constraint

### Types
1. **Full Binary Tree**: Every node has 0 or 2 children
2. **Complete Binary Tree**: All levels filled except possibly last (filled left to right)
3. **Perfect Binary Tree**: All internal nodes have 2 children, all leaves at same level
4. **Balanced Binary Tree**: Height difference between left and right subtrees ≤ 1

### Operations
| Operation | Time Complexity |
|-----------|----------------|
| Search | O(n) |
| Insert | O(n) |
| Delete | O(n) |
| Traversal | O(n) |

### Traversals
1. **Inorder** (Left-Root-Right): `4 2 5 1 3`
2. **Preorder** (Root-Left-Right): `1 2 4 5 3`
3. **Postorder** (Left-Right-Root): `4 5 2 3 1`
4. **Level Order** (BFS): `1 2 3 4 5`

### Real-World Examples
- **Expression Trees** (arithmetic expressions)
- **Huffman Coding** (compression)
- **Decision Trees** (ML algorithms)
- **DOM Tree** (HTML structure)

### Interview Code
```cpp
// Check if balanced
int height(TreeNode* root, bool& balanced) {
    if (!root) return 0;
    
    int left = height(root->left, balanced);
    int right = height(root->right, balanced);
    
    if (abs(left - right) > 1) balanced = false;
    
    return 1 + max(left, right);
}
```

---

## 2️⃣ BINARY SEARCH TREE (BST)

### Structure
```
       50
      /  \
    30    70
   / \   / \
  20 40 60 80
```

### Definition
- **Left subtree** < **Root** < **Right subtree**
- Inorder traversal gives **sorted order**

### Operations
| Operation | Average | Worst Case |
|-----------|---------|------------|
| Search | O(log n) | O(n) |
| Insert | O(log n) | O(n) |
| Delete | O(log n) | O(n) |
| Min/Max | O(log n) | O(n) |

*Worst case when tree becomes skewed (like linked list)*

### Key Properties
✅ Inorder traversal = Sorted order  
✅ Fast search, insert, delete (when balanced)  
✅ No duplicates (typically)  
❌ Can become unbalanced  

### Real-World Examples
- **Database Indexing** (with modifications)
- **Symbol Tables** (compilers)
- **Priority Queues** (with modifications)
- **Auto-complete** (with tries being better)

### Interview Code
```cpp
// Insert in BST
TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    
    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    
    return root;
}

// Delete in BST
TreeNode* deleteNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    
    if (val < root->data) {
        root->left = deleteNode(root->left, val);
    } else if (val > root->data) {
        root->right = deleteNode(root->right, val);
    } else {
        // Node found
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        
        // Two children: find inorder successor
        TreeNode* successor = findMin(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }
    
    return root;
}
```

---

## 3️⃣ AVL TREE

### Definition
- **Self-balancing BST**
- **Balance Factor** = height(left) - height(right) ∈ {-1, 0, 1}
- Maintains balance through **rotations**

### Rotations
1. **Left Rotation** (LL)
2. **Right Rotation** (RR)
3. **Left-Right Rotation** (LR)
4. **Right-Left Rotation** (RL)

### Operations
| Operation | Time Complexity |
|-----------|----------------|
| Search | O(log n) |
| Insert | O(log n) |
| Delete | O(log n) |

### Advantages
✅ **Guaranteed O(log n)** operations  
✅ **Strictly balanced** (height ≤ 1.44 log n)  
✅ **Faster lookups** than Red-Black trees  

### Disadvantages
❌ **More rotations** on insert/delete  
❌ **Complex implementation**  
❌ **Extra space** for balance factor  

### When to Use
- **Read-heavy** applications
- Need **guaranteed** O(log n) performance
- **Real-time** systems

### Real-World Examples
- **In-memory databases**
- **Real-time systems**
- **Graphics rendering** (spatial indexing)

---

## 4️⃣ RED-BLACK TREE

### Definition
- **Self-balancing BST**
- Each node has a **color** (red or black)

### Properties
1. Every node is red or black
2. Root is black
3. All leaves (NULL) are black
4. Red node cannot have red children
5. All paths from node to leaves have same number of black nodes

### Operations
| Operation | Time Complexity |
|-----------|----------------|
| Search | O(log n) |
| Insert | O(log n) |
| Delete | O(log n) |

### Advantages
✅ **Fewer rotations** than AVL (max 2 for insert)  
✅ **Faster insert/delete** than AVL  
✅ **Good balance** (height ≤ 2 log n)  

### Disadvantages
❌ **Slower lookups** than AVL  
❌ **Complex implementation**  
❌ **Extra space** for color  

### When to Use
- **Write-heavy** applications
- Need **good** (not perfect) balance
- **Standard library** implementations (map, set)

### Real-World Examples
- **C++ STL** (map, set, multimap, multiset)
- **Java TreeMap/TreeSet**
- **Linux kernel** (process scheduling)

---

## 5️⃣ B-TREE & B+ TREE

### B-Tree Definition
- **Multi-way search tree**
- Each node can have **multiple keys** and **children**
- All leaves at **same level**
- Order **m**: max m children, max m-1 keys

### B+ Tree Definition
- Variant of B-Tree
- **All data in leaves**
- Internal nodes only for navigation
- **Leaves linked** (like linked list)

### Operations
| Operation | Time Complexity |
|-----------|----------------|
| Search | O(log n) |
| Insert | O(log n) |
| Delete | O(log n) |
| Range Query | O(log n + k) |

### Advantages
✅ **Disk-friendly** (minimize disk I/O)  
✅ **High fanout** (shallow tree)  
✅ **Range queries** (B+ tree)  
✅ **Sequential access** (B+ tree)  

### When to Use
- **Databases** (indexing)
- **File systems**
- **Large datasets** on disk

### Real-World Examples
- **MySQL InnoDB** (B+ tree)
- **PostgreSQL** (B-tree)
- **File systems** (NTFS, ext4)

---

## 6️⃣ HEAP (BINARY HEAP)

### Definition
- **Complete binary tree**
- **Max Heap**: Parent ≥ children
- **Min Heap**: Parent ≤ children
- Usually implemented as **array**

### Array Representation
```
Index:  0  1  2  3  4  5  6
Array: [90,80,70,20,10,50,60]

       90
      /  \
    80    70
   / \   / \
  20 10 50 60

Parent(i) = (i-1)/2
Left(i) = 2i + 1
Right(i) = 2i + 2
```

### Operations
| Operation | Time Complexity |
|-----------|----------------|
| Insert | O(log n) |
| Delete Max/Min | O(log n) |
| Get Max/Min | O(1) |
| Heapify | O(n) |

### Advantages
✅ **Fast min/max** access  
✅ **Space efficient** (array)  
✅ **Priority queue** implementation  

### When to Use
- **Priority queues**
- **Heap sort**
- **Top K elements**
- **Median finding**

### Real-World Examples
- **Task scheduling** (OS)
- **Dijkstra's algorithm**
- **Huffman coding**
- **Event-driven simulation**

### Interview Code
```cpp
// Heapify down (max heap)
void heapifyDown(vector<int>& heap, int i, int n) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && heap[left] > heap[largest])
        largest = left;
    
    if (right < n && heap[right] > heap[largest])
        largest = right;
    
    if (largest != i) {
        swap(heap[i], heap[largest]);
        heapifyDown(heap, largest, n);
    }
}
```

---

## 7️⃣ TRIE (PREFIX TREE)

### Structure
```
       root
      / | \
     a  b  c
    /   |   \
   p    a    a
  /     |     \
 p      t      t
(app) (bat)  (cat)
```

### Definition
- **Tree for strings**
- Each node represents a **character**
- Path from root to node = **prefix**

### Operations
| Operation | Time Complexity |
|-----------|----------------|
| Insert | O(m) |
| Search | O(m) |
| Delete | O(m) |
| Prefix Search | O(m) |

*m = length of word*

### Advantages
✅ **Fast prefix search**  
✅ **Autocomplete**  
✅ **Spell checking**  
✅ **No hash collisions**  

### Disadvantages
❌ **Space intensive**  
❌ **Slower than hash** for exact match  

### When to Use
- **Autocomplete**
- **Spell checker**
- **IP routing**
- **Dictionary**

### Real-World Examples
- **Google search** (autocomplete)
- **Phone contacts** (T9 typing)
- **IP routing tables**
- **Spell checkers**

### Interview Code
```cpp
struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;
    
    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

void insert(TrieNode* root, string word) {
    TrieNode* curr = root;
    for (char c : word) {
        int index = c - 'a';
        if (!curr->children[index])
            curr->children[index] = new TrieNode();
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
}
```

---

## 8️⃣ SEGMENT TREE

### Definition
- **Binary tree** for range queries
- Each node stores **aggregate** of range
- Leaf nodes = array elements

### Operations
| Operation | Time Complexity |
|-----------|----------------|
| Build | O(n) |
| Query | O(log n) |
| Update | O(log n) |

### Advantages
✅ **Fast range queries** (sum, min, max)  
✅ **Fast updates**  
✅ **Flexible** (any associative operation)  

### When to Use
- **Range sum queries**
- **Range min/max queries**
- **Frequent updates**

### Real-World Examples
- **Stock market** (range queries)
- **Gaming** (collision detection)
- **Computational geometry**

---

## 📊 COMPARISON TABLE

| Tree Type | Search | Insert | Delete | Space | Balanced | Use Case |
|-----------|--------|--------|--------|-------|----------|----------|
| **Binary Tree** | O(n) | O(n) | O(n) | O(n) | ❌ | General hierarchy |
| **BST** | O(log n)* | O(log n)* | O(log n)* | O(n) | ❌ | Sorted data |
| **AVL** | O(log n) | O(log n) | O(log n) | O(n) | ✅ | Read-heavy |
| **Red-Black** | O(log n) | O(log n) | O(log n) | O(n) | ✅ | Write-heavy |
| **B-Tree** | O(log n) | O(log n) | O(log n) | O(n) | ✅ | Databases |
| **Heap** | O(n) | O(log n) | O(log n) | O(n) | ✅ | Priority queue |
| **Trie** | O(m) | O(m) | O(m) | O(ALPHABET*n*m) | N/A | Prefix search |
| **Segment Tree** | O(log n) | O(log n) | O(log n) | O(4n) | ✅ | Range queries |

*Average case; worst case O(n) for unbalanced BST

---

## 🎯 WHEN TO USE WHAT

### Use **Binary Tree** when:
- ✅ Representing hierarchical data
- ✅ Expression evaluation
- ✅ No specific ordering needed

### Use **BST** when:
- ✅ Need sorted data
- ✅ Frequent searches
- ✅ Simple implementation acceptable
- ❌ Don't need guaranteed performance

### Use **AVL Tree** when:
- ✅ **Read-heavy** workload
- ✅ Need **guaranteed** O(log n)
- ✅ Can afford rotation overhead

### Use **Red-Black Tree** when:
- ✅ **Write-heavy** workload
- ✅ Need good (not perfect) balance
- ✅ Standard library (STL map/set)

### Use **B-Tree/B+ Tree** when:
- ✅ **Database indexing**
- ✅ **File systems**
- ✅ Data on **disk**
- ✅ Range queries (B+ tree)

### Use **Heap** when:
- ✅ **Priority queue**
- ✅ Top K elements
- ✅ Median finding
- ✅ Heap sort

### Use **Trie** when:
- ✅ **Autocomplete**
- ✅ **Spell checking**
- ✅ Prefix matching
- ✅ Dictionary operations

### Use **Segment Tree** when:
- ✅ **Range queries** (sum, min, max)
- ✅ Frequent updates
- ✅ Competitive programming

---

## 💡 INTERVIEW QUESTIONS & ANSWERS

### Q1: Difference between Binary Tree and BST?
**Answer:**
- **Binary Tree**: No ordering, each node ≤ 2 children
- **BST**: Left < Root < Right, enables O(log n) search

### Q2: Why use AVL over BST?
**Answer:**
- **Guaranteed O(log n)** operations
- BST can degrade to O(n) if unbalanced
- AVL maintains strict balance

### Q3: AVL vs Red-Black Tree?
**Answer:**
| Feature | AVL | Red-Black |
|---------|-----|-----------|
| Balance | Stricter | Looser |
| Lookups | Faster | Slower |
| Insert/Delete | Slower (more rotations) | Faster |
| Use Case | Read-heavy | Write-heavy |

### Q4: How does B-Tree help databases?
**Answer:**
- **High fanout** → shallow tree → fewer disk I/O
- **Block-oriented** → matches disk block size
- **Range queries** efficient (B+ tree)

### Q5: Heap vs BST for priority queue?
**Answer:**
- **Heap**: O(1) get min/max, O(log n) insert/delete
- **BST**: O(log n) for all operations
- **Heap preferred**: Simpler, faster for priority queue

### Q6: When to use Trie over HashMap?
**Answer:**
- **Prefix search**: Trie O(m), HashMap can't do
- **Autocomplete**: Trie natural fit
- **Exact match**: HashMap O(1) vs Trie O(m)

### Q7: Inorder traversal of BST gives?
**Answer:** **Sorted order** (ascending)

### Q8: How to check if tree is balanced?
**Answer:**
```cpp
int height(TreeNode* root, bool& balanced) {
    if (!root) return 0;
    
    int left = height(root->left, balanced);
    int right = height(root->right, balanced);
    
    if (abs(left - right) > 1) balanced = false;
    
    return 1 + max(left, right);
}
```

### Q9: Lowest Common Ancestor in BST?
**Answer:**
```cpp
TreeNode* LCA(TreeNode* root, int p, int q) {
    if (p < root->data && q < root->data)
        return LCA(root->left, p, q);
    
    if (p > root->data && q > root->data)
        return LCA(root->right, p, q);
    
    return root;  // Split point
}
```

### Q10: Serialize and deserialize tree?
**Answer:**
```cpp
string serialize(TreeNode* root) {
    if (!root) return "#";
    return to_string(root->data) + "," + 
           serialize(root->left) + "," + 
           serialize(root->right);
}
```

---

## 🔄 COMMON PATTERNS

### 1. **Recursion**
Most tree problems use recursion naturally
```cpp
int height(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}
```

### 2. **DFS (Depth-First Search)**
- Preorder, Inorder, Postorder
- Use **stack** or recursion

### 3. **BFS (Breadth-First Search)**
- Level order traversal
- Use **queue**

### 4. **Two Pointers**
- Parent tracking
- Slow/fast pointers

### 5. **Divide and Conquer**
- Merge sort on trees
- Build tree from traversals

---

## ✅ SUMMARY

| Tree | Best For | Key Feature |
|------|----------|-------------|
| **Binary Tree** | Hierarchy | Simple structure |
| **BST** | Sorted data | Left < Root < Right |
| **AVL** | Read-heavy | Strict balance |
| **Red-Black** | Write-heavy | Fewer rotations |
| **B-Tree** | Databases | Disk-friendly |
| **Heap** | Priority queue | Fast min/max |
| **Trie** | Autocomplete | Prefix search |
| **Segment Tree** | Range queries | Fast updates |

---

*Master these trees for interview success! 🚀*
