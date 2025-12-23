# Fibonacci Heap

A **Fibonacci Heap** is a collection of min-heap-ordered trees. It is a highly efficient priority queue data structure that offers superior amortized running times for several operations.

## Core Properties
1.  **Amortized Efficiency**:
    - `Insert`, `Find-Min`, `Merge`, `Decrease-Key`: **O(1)**
    - `Delete`, `Extract-Min`: **O(log N)**
2.  **Structure**: It is a collection of trees (a forest) where each tree follows the min-heap property. The roots of these trees are maintained in a **Circular Doubly Linked List**.
3.  **Lazy Operations**: Key operations like `Merge` and `Insert` are performed "lazily"—simply linking new nodes/heaps to the root list without restructuring. Consolidation only happens during `Extract-Min`.

## Node Structure
Each node contains:
- `key`: The value/priority.
- `parent`: Pointer to the parent node.
- `child`: Pointer to one of its children.
- `left`, `right`: Pointers for the circular doubly linked list of siblings.
- `degree`: The number of children.
- `mark`: A boolean value used to keep the heap "compact" during `decrease-key`.

## Major Operations
### 1. Insert & Merge
- New nodes or separate heaps are simply added to the root list.
- The `min` pointer is updated if the new key is smaller.

### 2. Extract-Min
This is the most complex operation:
- The children of the min node are moved to the root list.
- The min node is removed.
- **Consolidation**: The root list is traversed, and trees of the same degree are merged until every root in the root list has a distinct degree.

### 3. Decrease-Key
- If the new key violates the heap property (smaller than parent), the node is **cut** from its parent and moved to the root list.
- **Cascading Cut**: If a parent has already lost a child (its `mark` was true), it is also cut and moved to the root list. This maintains the "Fibonacci" property of tree sizes.

## Advantages
- Fundamental for improving the performance of Dijkstra's algorithm from **O(E log V)** to **O(E + V log V)**.
- Highly efficient in scenarios with frequent `decrease-key` operations.

## Complexity Comparison
| Operation | Binary Heap | Fibonacci Heap (Amortized) |
|-----------|-------------|----------------------------|
| Insert    | O(log N)    | O(1)                       |
| Find-Min  | O(1)        | O(1)                       |
| Merge     | O(N)        | O(1)                       |
| Extract-Min| O(log N)   | O(log N)                   |
| Decrease-Key| O(log N)  | O(1)                       |
