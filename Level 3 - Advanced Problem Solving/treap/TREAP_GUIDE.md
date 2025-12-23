# Treap (Randomized Binary Search Tree)

A **Treap** is a randomized binary search tree that maintains its balance with high probability. The name "Treap" is a portmanteau of **Tree** and **Heap**.

## Core Concept
Each node in a Treap has two values:
1.  **Key**: Follows the **Binary Search Tree (BST)** property (left < parent < right).
2.  **Priority**: A randomly assigned value that follows the **Heap** property (parent > children or parent < children).

By maintaining both properties, the tree stays balanced on average, with operations having **O(log N)** complexity.

## Key Operations
Treaps are traditionally implemented using two primary low-level operations:
- **Split**: Divides a Treap into two separate Treaps based on a key $X$. One Treap contains all keys $\leq X$, and the other contains all keys $> X$.
- **Merge**: Combines two Treaps into one. This assumes that all keys in the first Treap are smaller than all keys in the second Treap.

### Basic Procedures
- **Search**: Exactly like a standard BST.
- **Insert**: Split the tree at the new key, create a new node, and merge them back.
- **Delete**: Split the tree to isolate the node to be deleted, merge the remaining parts.

## Advantages
- **Simplicity**: Easier to implement than Red-Black or AVL trees.
- **Flexivity**: Excellent for range operations (Reverse, Sum, etc.) in persistent or implicit forms.
- **Priority Control**: Can be used to implement weight-balanced trees by assigning specific priorities.

## Complexity
| Operation | Average   | Worst Case |
|-----------|-----------|------------|
| Space     | O(N)      | O(N)       |
| Search    | O(log N)  | O(N)       |
| Insert    | O(log N)  | O(N)       |
| Delete    | O(log N)  | O(N)       |
| Split     | O(log N)  | O(N)       |
| Merge     | O(log N)  | O(N)       |
