# Heap / Priority Queue Guide

## What is a Heap?

A **heap** is a specialized tree-based data structure that satisfies the **heap property**. It's commonly implemented as a binary heap using an array.

```
         1                    50
       /   \                /    \
      3     2              30    40
     / \   /              /  \   /
    5   4 6              10  20 35

   Min Heap             Max Heap
```

## Heap Properties

### Min Heap
- **Heap Property**: Parent ≤ Children
- **Root**: Contains the minimum element
- **Use Case**: Get minimum quickly, ascending priority

### Max Heap  
- **Heap Property**: Parent ≥ Children
- **Root**: Contains the maximum element
- **Use Case**: Get maximum quickly, descending priority

### Complete Binary Tree
- All levels are fully filled except possibly the last
- Last level is filled from left to right
- **Array Representation**:
  - Parent of index `i`: `(i-1)/2`
  - Left child of index `i`: `2*i + 1`
  - Right child of index `i`: `2*i + 2`

## Time Complexity

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| **Insert** | O(log n) | Add element and heapify up |
| **Extract Min/Max** | O(log n) | Remove root and heapify down |
| **Peek Min/Max** | O(1) | View root element |
| **Build Heap** | O(n) | Create heap from array |
| **Delete** | O(log n) | Remove arbitrary element |
| **Search** | O(n) | No guaranteed structure for search |

## Space Complexity

- **Space**: O(n) for storing n elements

## Core Operations

### 1. Insert (Heapify Up)
```
1. Add element at end of array
2. Compare with parent
3. If heap property violated, swap with parent
4. Repeat until heap property satisfied
```

### 2. Extract (Heapify Down)
```
1. Store root element (min/max)
2. Move last element to root
3. Compare with children
4. Swap with smallest/largest child if needed
5. Repeat until heap property satisfied
```

## When to Use Heap

### ✅ Use Heap When:
- Finding k-th largest/smallest elements
- Implementing priority queues
- Scheduling tasks by priority
- Finding median in a stream
- Merging k sorted arrays/lists
- Graph algorithms (Dijkstra, Prim)

### ❌ Avoid Heap When:
- Need to search for arbitrary elements (use hash table)
- Need sorted order of all elements (use sorting)
- Need FIFO order (use queue)
- Need to access elements by index (use array)

## Comparison with Other Data Structures

| Feature | Heap | Sorted Array | BST | Hash Table |
|---------|------|--------------|-----|------------|
| Get Min/Max | O(1) | O(1) | O(log n) | O(n) |
| Insert | O(log n) | O(n) | O(log n)* | O(1) |
| Delete Min/Max | O(log n) | O(n) | O(log n)* | - |
| Search | O(n) | O(log n) | O(log n)* | O(1) |
| Space | O(n) | O(n) | O(n) | O(n) |

*Assumes balanced BST (AVL/Red-Black)

## Common Problem Patterns

### Pattern 1: K-th Element Problems
**Examples**: K-th largest, K-th smallest, Top K frequent
**Approach**: Use heap of size K

```java
// K-th largest: Use min heap of size K
PriorityQueue<Integer> minHeap = new PriorityQueue<>();
for (int num : nums) {
    minHeap.offer(num);
    if (minHeap.size() > k) minHeap.poll();
}
return minHeap.peek();
```

### Pattern 2: Merge Problems
**Examples**: Merge K sorted lists/arrays
**Approach**: Use min heap with pointers

### Pattern 3: Two Heaps for Median
**Examples**: Find median in stream, sliding window median
**Approach**: Max heap (lower half) + Min heap (upper half)

```java
MaxHeap (lower) | MinHeap (upper)
    [1, 2, 3]   |   [5, 6, 7]
       median = (3 + 5) / 2 = 4
```

### Pattern 4: Scheduling/Greedy
**Examples**: Task scheduler, meeting rooms
**Approach**: Use heap to track earliest/latest times

## Real-World Applications

### 1. Operating Systems
- **Process Scheduling**: Priority-based task execution
- **Memory Management**: Best-fit allocation

### 2. Graph Algorithms
- **Dijkstra's Algorithm**: Shortest path (min heap)
- **Prim's Algorithm**: Minimum spanning tree (min heap)
- **A* Search**: Pathfinding with heuristics

### 3. Data Processing
- **Event-Driven Simulation**: Process events by timestamp
- **Load Balancing**: Assign tasks to least loaded server
- **Stream Processing**: Top K trending items

### 4. Compression
- **Huffman Coding**: Build optimal prefix codes

### 5. E-commerce
- **Recommendation Systems**: Top K products by score
- **Price Optimization**: Track price changes efficiently

## Common Pitfalls

> [!CAUTION]
> **Pitfall 1**: Using heap for searching
> Heaps are NOT optimized for searching arbitrary elements. Use hash tables or BSTs instead.

> [!WARNING]
> **Pitfall 2**: Forgetting to rebalance
> After any modification, always ensure heap property is maintained through heapify operations.

> [!CAUTION]
> **Pitfall 3**: Using wrong heap type
> Min heap for k-th largest (counterintuitive but correct), max heap for k-th smallest.

## Interview Tips

### Quick Recognition
If you see keywords like:
- "K-th largest/smallest"
- "Top K elements"
- "Merge K sorted"
- "Median from stream"
- "Priority-based scheduling"

→ **Think HEAP!**

### Complexity Analysis
- Building a heap from n elements: O(n), NOT O(n log n)
- K operations on heap of size n: O(k log n)
- Heap of size k for n elements: O(n log k)

### Min vs Max Heap Choice
| Problem | Heap Type | Reason |
|---------|-----------|--------|
| K-th largest | Min Heap | Keep largest K, remove smallest |
| K-th smallest | Max Heap | Keep smallest K, remove largest |
| Smallest range | Min Heap | Track minimum efficiently |
| Schedule by deadline | Min Heap | Process earliest deadline first |

## STL/Built-in Implementations

### Java
```java
// Min Heap
PriorityQueue<Integer> minHeap = new PriorityQueue<>();

// Max Heap
PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> b - a);

// Custom comparator
PriorityQueue<Task> pq = new PriorityQueue<>(
    (a, b) -> a.priority - b.priority
);
```

### C++
```cpp
// Min Heap
priority_queue<int, vector<int>, greater<int>> minHeap;

// Max Heap (default)
priority_queue<int> maxHeap;

// Custom comparator
auto comp = [](Task a, Task b) { return a.priority > b.priority; };
priority_queue<Task, vector<Task>, decltype(comp)> pq(comp);
```

## Practice Problems

### Basic
1. Implement min heap and max heap
2. Kth largest element in array
3. Last stone weight
4. Heap sort

### Intermediate
5. Top K frequent elements
6. Merge K sorted lists
7. Find median from data stream
8. Task scheduler

### Advanced
9. Sliding window median
10. IPO (maximize capital)
11. Minimize deviation in array
12. Find K pairs with smallest sums

---

## Summary

**Heap** is the go-to data structure when you need efficient access to minimum or maximum elements, especially in scenarios involving:
- Priority-based processing
- K-th element queries
- Merging sorted sequences
- Streaming data with dynamic updates

Master the two-heap technique for median problems and recognize the pattern of using a heap of size K for top-K queries.
