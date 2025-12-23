# Data Structure Repository

A comprehensive collection of fundamental and advanced data structures implemented in Java and C++.

## 📚 Table of Contents

- [Overview](#overview)
- [Implemented Data Structures](#implemented-data-structures)
- [Repository Structure](#repository-structure)
- [Quick Start](#quick-start)
- [Complexity Cheat Sheet](#complexity-cheat-sheet)

## Overview

This repository contains educational implementations of essential data structures with:
- **Dual Language Support**: Java and C++ implementations
- **Three Difficulty Levels**: Basic operations, core problems, and advanced problems
- **Comprehensive Guides**: Markdown guides for each structure
- **Real-world Applications**: Practical use cases and interview tips

## Implemented Data Structures

### ✅ High Priority (Interview Essentials)

| Data Structure | Description | Key Operations | Guide |
|----------------|-------------|----------------|-------|
| **Heap** | Priority queue with min/max | Insert, Extract: O(log n) | [Guide](heap/HEAP_GUIDE.md) |
| **Trie** | Prefix tree for strings | Insert, Search: O(m) | [Guide](trie/TRIE_GUIDE.md) |
| **BST** | Binary search tree | Search, Insert: O(log n)* | [Guide](bst/BST_GUIDE.md) |

### ✅ Medium Priority (Advanced Techniques)

| Data Structure | Description | Key Operations | Guide |
|----------------|-------------|----------------|-------|
| **Deque** | Double-ended queue | Push/Pop both ends: O(1) | [Guide](deque/DEQUE_GUIDE.md) |
| **Fenwick Tree** | Binary indexed tree | Update, Query: O(log n) | [Guide](fenwick_tree/FENWICK_TREE_GUIDE.md) |

### 🔄 Advanced Structures (Specialized)

| Data Structure | Description | Use Case |
|----------------|-------------|----------|
| **Skip List** | Probabilistic balanced structure | Alternative to balanced trees |
| **Suffix Array** | Sorted suffixes | Pattern matching |
| **Bloom Filter** | Probabilistic set membership | Space-efficient existence checks |
| **B-Tree** | Multi-way search tree | Databases, file systems |
| **Splay Tree** | Self-adjusting BST | Frequently accessed items |
| **Cartesian Tree** | Min-heap + BST hybrid | Range minimum query |

### 🌐 Spatial Data Structures

Located in `Advanced DS/`:
- **K-D Trees**: k-dimensional search
- **Quad Tree**: 2D spatial partitioning
- **R-Trees**: Spatial indexing
- **Geohash + Trie**: Location encoding
- **H3 Hex Grid**: Hexagonal grid system

### 📊 Additional Structures

- **Array**: Basic operations and algorithms
- **Linked List**: Singly/doubly linked lists
- **Stack**: LIFO operations
- **Queue**: FIFO operations
- **String**: String algorithms
- **Tree**: General tree operations
- **Graph**: Graph algorithms
- **Hashing**: Hash tables and maps
- **Segment Tree**: Range queries with updates
- **Disjoint Set** (Union-Find/DSU): Set operations

## Repository Structure

Each data structure folder follows this consistent pattern:

```
data_structure_name/
├── basic_operations.java      # Fundamental operations
├── basic_operations.cpp        # C++ implementation
├── core_problems.java          # Essential algorithms
├── core_problems.cpp           # C++ solutions
├── advanced_problems.java      # Complex applications
├── advanced_problems.cpp       # Advanced C++ problems
└── GUIDE.md                    # Comprehensive guide
```

## Quick Start

### Java
```bash
cd Data-Structure/heap
javac basic_operations.java
java basic_operations
```

### C++
```bash
cd Data-Structure/heap
g++ -std=c++17 basic_operations.cpp -o basic_operations
./basic_operations
```

## Complexity Cheat Sheet

### Search/Access Operations

| Structure | Average | Worst | Notes |
|-----------|---------|-------|-------|
| Array | O(1) index, O(n) search | O(n) | Direct access by index |
| Linked List | O(n) | O(n) | Sequential access only |
| Stack/Queue | O(1) peek | O(1) | Access only top/front |
| Hash Table | O(1) | O(n) | With good hash function |
| BST | O(log n) | O(n) | Balanced: O(log n) guaranteed |
| Heap | O(1) peek | O(1) | Only min/max accessible |
| Trie | O(m) | O(m) | m = string length |

### Insert/Delete Operations

| Structure | Average | Worst | Notes |
|-----------|---------|-------|-------|
| Array (end) | O(1) amortized | O(n) | Insertion at arbitrary position: O(n) |
| Linked List | O(1) at head | O(n) | O(n) to find position |
| Stack/Queue | O(1) | O(1) | Push/pop from ends |
| Hash Table | O(1) | O(n) | Amortized with resizing |
| BST | O(log n) | O(n) | Balanced: O(log n) guaranteed |
| Heap | O(log n) | O(log n) | Insert and extract |
| Trie | O(m) | O(m) | m = string length |
| Fenwick Tree | O(log n) | O(log n) | Update and query |
| Segment Tree | O(log n) | O(log n) | Range operations |

### Special Operations

| Structure | Operation | Complexity | Notes |
|-----------|-----------|------------|-------|
| Heap | Extract min/max | O(log n) | Priority queue |
| Trie | Prefix search | O(p) | p = prefix length |
| Trie | Autocomplete | O(p + n) | n = results |
| BST | Range query | O(log n + k) | k = results |
| Fenwick Tree | Range sum | O(log n) | Prefix sums |
| Segment Tree | Range query | O(log n) | Any associative operation |
| Disjoint Set | Union/Find | O(α(n)) | α = inverse Ackermann |

### Space Complexity

| Structure | Space | Notes |
|-----------|-------|-------|
| Array | O(n) | Contiguous memory |
| Linked List | O(n) | Extra pointer overhead |
| Hash Table | O(n) | Load factor overhead |
| BST | O(n) | Pointer overhead |
| Heap | O(n) | Array-based implementation |
| Trie | O(ALPHABET * N * M) | Can be optimized with HashMap |
| Fenwick/Segment Tree | O(n) / O(4n) | Linearspace |

---

## Interview Preparation Tips

### Quick Pattern Recognition

**Heap** → "k-th largest", "top k elements", "merge k sorted", "median stream"

**Trie** → "autocomplete", "prefix matching", "word dictionary", "XOR maximum"

**BST** → "sorted order", "k-th smallest", "range query", "validate BST"

**Deque** → "sliding window", "monotonic queue", "palindrome"

**Fenwick** → "range sum", "prefix sum with updates", "inversion count"

**Segment Tree** → "range min/max/sum", "lazy propagation"

---

## Contributing

This is an educational repository. Each implementation follows best practices and includes:
- Clear, commented code
- Multiple test cases
- Time/space complexity analysis
- Real-world applications

---

## License

Educational use - feel free to learn and share!

---

## Quick Links

- [Array Operations](array/)
- [Linked List](linked_list/)
- [Stack](stack/)
- [Queue](queue/)
- [Tree](tree/)
- [Graph](graph/)
- [Hashing](hashing/)
- [String Algorithms](string/)

**Happy Learning! 🚀**
