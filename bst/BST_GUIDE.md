# Binary Search Tree (BST) Guide

## What is a BST?

A **Binary Search Tree** is a binary tree data structure where each node follows the BST property:
- All values in the **left subtree** < node value
- All values in the **right subtree** > node value

```
        50
       /  \
      30   70
     / \   / \
    20 40 60 80

BST Property maintained at every node
```

## BST Properties

### Core Invariant
**For every node N:**
- `left.val < N.val < right.val`
- This property holds recursively for all subtrees

### Inorder Traversal = Sorted Order
Inorder traversal of a BST always produces elements in sorted order.

## Time Complexity

| Operation | Average | Worst Case | Balanced (AVL/RB) |
|-----------|---------|-----------|-------------------|
| **Search** | O(log n) | O(n) | O(log n) |
| **Insert** | O(log n) | O(n) | O(log n) |
| **Delete** | O(log n) | O(n) | O(log n) |
| **Min/Max** | O(log n) | O(n) | O(log n) |
| **Successor** | O(log n) | O(n) | O(log n) |

**Note**: Worst case O(n) occurs when tree degenerates into a linked list (inserting sorted data).

## Space Complexity

- **Space**: O(n) for storing n nodes
- **Recursion depth**: O(h) where h is height

## Core Operations

### 1. Search
```java
boolean search(TreeNode node, int val) {
    if (node == null) return false;
    if (node.val == val) return true;
    if (val < node.val) return search(node.left, val);
    return search(node.right, val);
}
```

### 2. Insert
```java
TreeNode insert(TreeNode node, int val) {
    if (node == null) return new TreeNode(val);
    
    if (val < node.val) {
        node.left = insert(node.left, val);
    } else if (val > node.val) {
        node.right = insert(node.right, val);
    }
    
    return node;
}
```

### 3. Delete (3 Cases)
```java
// Case 1: Leaf node - simply remove
// Case 2: One child - replace with child
// Case 3: Two children - replace with inorder successor
```

## When to Use BST

### ✅ Use BST When:
- Need sorted/ordered data
- Range queries (find all in range [a, b])
- Finding kth smallest/largest
- Floor/ceiling operations
- Dynamic dataset with frequent inserts/deletes

### ❌ Avoid BST When:
- Only need membership testing (use HashSet)
- Data doesn't need ordering
- Expect sorted input (use balanced BST or build from middle)
- Need O(1) operations (use HashMap)

## Comparison with Other Structures

| Feature | BST | AVL/RB Tree | Hash Table | Array (sorted) |
|---------|-----|-------------|------------|----------------|
| Search | O(log n)* | O(log n) | O(1) | O(log n) |
| Insert | O(log n)* | O(log n) | O(1) | O(n) |
| Delete | O(log n)* | O(log n) | O(1) | O(n) |
| Ordered | Yes | Yes | No | Yes |
| Range Query | O(log n + k) | O(log n + k) | O(n) | O(log n + k) |
| Memory | Medium | Medium | High | Low |

*Average case, worst case O(n) for unbalanced BST

## Self-Balancing BSTs

### AVL Tree
- **Balance Factor**: |height(left) - height(right)| ≤ 1
- **Rotations**: 4 types (LL, RR, LR, RL)
- **Use**: Read-heavy workloads
- **Guarantee**: Strictlybalanced, O(log n) guaranteed

### Red-Black Tree
- **Properties**: Color properties + black height
- **Rotations**: Fewer than AVL
- **Use**: Insert/delete-heavy workloads
- **Example**: Java TreeMap, C++ std::map

### Comparison
| Property | AVL | Red-Black |
|----------|-----|-----------|
| Balance | Stricter | Looser |
| Height | ~1.44 log n | ~2 log n |
| Rotations (Insert) | More | Fewer |
| Rotations (Delete) | More | Fewer |
| Lookup | Faster | Slower |
| Insert/Delete | Slower | Faster |

## Common Problem Patterns

### Pattern 1: Validate BST
**Key**: Pass min/max bounds recursively

```java
boolean isValidBST(TreeNode node, Integer min, Integer max) {
    if (node == null) return true;
    if ((min != null && node.val <= min) || 
        (max != null && node.val >= max)) return false;
    
    return isValidBST(node.left, min, node.val) &&
           isValidBST(node.right, node.val, max);
}
```

### Pattern 2: BST Iterator (Controlled Inorder)
**Approach**: Use stack to simulate inorder traversal

### Pattern 3: Lowest Common Ancestor
**Key**: Use BST property to navigate

```java
TreeNode LCA(TreeNode root, TreeNode p, TreeNode q) {
    if (p.val < root.val && q.val < root.val)
        return LCA(root.left, p, q);
    if (p.val > root.val && q.val > root.val)
        return LCA(root.right, p, q);
    return root; // Split point
}
```

### Pattern 4: Kth Smallest/Largest
**Approach**: Inorder traversal (k-th smallest) or reverse inorder (k-th largest)

## Real-World Applications

### 1. Databases
- **Index Structures**: B-trees (generalized BST)
- **Range Queries**: Find all records in range

### 2. File Systems
- **Directory Trees**: Organize files hierarchically
- **Symbol Tables**: Compiler symbol management

### 3. Networking
- **Routing Tables**: IP address lookup
- **Priority Scheduling**: Process management

### 4. Language Libraries
- **Java TreeMap/TreeSet**: Sorted map/set
- **C++ std::map/std::set**: Red-black trees
- **Python sortedcontainers**: Balanced trees

### 5. Gaming
- **Leaderboards**: Maintain sorted scores
- **Spatial Partitioning**: Quad-trees, k-d trees

## Common Pitfalls

> [!CAUTION]
> **Pitfall 1**: Inserting sorted data
> Inserting already-sorted data creates a skewed tree (linked list). Always use balanced BST or randomize insertion order.

> [!WARNING]
> **Pitfall 2**: Incorrect validation
> Don't just check node.left < node < node.right. Must check against min/max bounds.

> [!CAUTION]
> **Pitfall 3**: Forgetting BST property during delete
> When deleting a node with two children, must maintain BST property by using successor/predecessor.

## Interview Tips

### Quick Recognition
If you see:
- "Sorted order"
- "K-th smallest/largest"
- "Range query"
- "Floor/ceiling"
- "Inorder traversal"

→ **Think BST!**

### Common Tricks

**1. Inorder = Sorted**: Many problems become trivial with this insight

**2. BST to Sorted Array**: For balancing or analysis

**3. Two Pointers on Sorted Array**: Convert BST to array, use two pointers

**4. Morris Traversal**: O(1) space inorder traversal

### Complexity Analysis Tips
- **Height-dependent**: Most operations are O(h)
- **Balanced**: h = O(log n)
- **Skewed**: h = O(n)
- **Always specify**: "O(log n) if balanced, O(n) worst case"

## Practice Problems

### Basic
1. Implement BST (insert, delete, search)
2. Validate BST
3. Inorder/preorder/postorder traversal

### Intermediate
4. Lowest common ancestor
5. Kth smallest element
6. Convert sorted array to BST
7. Range sum query

### Advanced
8. Serialize and deserialize BST
9. Recover BST (two nodes swapped)
10. Balance a BST
11. AVL tree implementation
12. BST iterator

---

## Summary

**BST** provides O(log n) search, insert, and delete when balanced, while maintaining sorted order. The key advantage over hash tables is support for range queries and ordered operations.

**Critical**: Always consider balance. For production use, prefer self-balancing variants (AVL, Red-Black) or use language built-ins (TreeMap, std::map).

**Best Use Cases**: When you need both fast access AND sorted order - leaderboards, priority queues with updates, range queries.

Master the BST property and inorder traversal - these are the foundations for solving most BST problems.
