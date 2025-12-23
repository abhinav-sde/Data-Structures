# Data Structure Repository

A world-class collection of fundamental and industrial-grade data structures implemented in Java and C++. 

## 🚀 The Complete SDE Survival Kit

This repository has been upgraded from a basic collection to a **FAANG-ready resource**, covering everything from Arrays to Big-Data probabilistic structures (HyperLogLog).

---

## 📊 Complexity Cheat Sheet

### Essential Data Structures

| Structure | Search/Access | Insert/Delete | Notes |
|-----------|---------------|---------------|-------|
| **LRU Cache** | O(1) | O(1) | Industry standard for caching |
| **LFU Cache** | O(1) | O(1) | Better for high-frequency patterns |
| **Red-Black Tree** | O(log N) | O(log N) | Workhorse for standard map libraries |
| **B+ Tree** | O(log N) | O(log N) | The standard for Database Indexing |
| **Trie** | O(M) | O(M) | M = String length. Fast prefix search |

### High-Performance Queries

| Structure | Query Complexity | Update Complexity | Notes |
|-----------|------------------|-------------------|-------|
| **Sparse Table** | **O(1)** | N/A (Static) | Fastest for RMQ/GCD queries |
| **Fenwick Tree** | O(log N) | O(log N) | Lower memory range sums |
| **Segment Tree** | O(log N) | O(log N) | General purpose range queries |
| **Persistent SegTree**| O(log N) | O(log N) | Version control for your data |

### Scalable & Big Data (Probabilistic)

| Structure | Memory | Error Type | Use Case |
|-----------|--------|------------|----------|
| **Bloom Filter**| Fixed Small | False Positive | Membership existence checks |
| **Count-Min Sketch**| Fixed Small | Overestimation | Frequency counting in streams |
| **HyperLogLog**| **KB (Fixed)** | Estimation (~2%) | Unique visitor/user count |

---

## 📂 Master Roadmap

### 🟢 Level 1: The Foundations (SDE1/New Grad)
*Goal: Understand memory layout and linear ordering.*
- [Array](Level%201%20-%20Foundations/array/)
- [Linked List](Level%201%20-%20Foundations/linked_list/)
- [Stack](Level%201%20-%20Foundations/stack/)
- [Queue](Level%201%20-%20Foundations/queue/)
- [Deque](Level%201%20-%20Foundations/deque/)
- [String](Level%201%20-%20Foundations/string/)

### 🟡 Level 2: Core Interview Pack (SDE1/SDE2)
*Goal: Efficient lookup and hierarchical storage.*
- [Hashing (Map/Set)](Level%202%20-%20Core%20Interview%20Pack/hashing/)
- [Tree (Basic)](Level%202%20-%20Core%20Interview%20Pack/tree/)
- [Heaps / Priority Queues](Level%202%20-%20Core%20Interview%20Pack/heap/)

### 🟠 Level 3: Advanced Problem Solving (SDE2)
*Goal: Specialized range queries and set management.*
- [BST (Binary Search Tree)](Level%203%20-%20Advanced%20Problem%20Solving/bst/)
- [Trie (Prefix Tree)](Level%203%20-%20Advanced%20Problem%20Solving/trie/)
- [Disjoint Set (DSU)](Level%203%20-%20Advanced%20Problem%20Solving/disjoint_set/)
- [Segment Tree](Level%203%20-%20Advanced%20Problem%20Solving/segment_tree/)
- [Fenwick Tree (BIT)](Level%203%20-%20Advanced%20Problem%20Solving/fenwick_tree/)
- [Graph (Basic)](Level%203%20-%20Advanced%20Problem%20Solving/graph/)

### 🔴 Level 4: Senior/Industrial Standards (SDE2/Senior SDE3)
*Goal: Real-world system components and optimized trees.*
- [LRU Cache](Level%204%20-%20Senior%20Standards/lru_cache/)
- [LFU Cache](Level%204%20-%20Senior%20Standards/lfu_cache/)
- [Red-Black Tree](Level%204%20-%20Senior%20Standards/red_black_tree/)
- [B+ Tree](Level%204%20-%20Senior%20Standards/bplus_tree/)
- [B-Tree](Level%204%20-%20Senior%20Standards/btree/)
- [Sparse Table](Level%204%20-%20Senior%20Standards/sparse_table/)

### 🟣 Level 5: Big Data & Professional Scale (SDE3/Staff)
*Goal: Approximations and massively distributed logic.*
- [Bloom Filter](Level%205%20-%20Big%20Data/bloom_filter/)
- [Count-Min Sketch](Level%205%20-%20Big%20Data/count_min_sketch/)
- [HyperLogLog](Level%205%20-%20Big%20Data/hyperloglog/)
- [Aho-Corasick](Level%205%20-%20Big%20Data/aho_corasick/)
- [Suffix Array](Level%205%20-%20Big%20Data/suffix_array/)
- [Persistent Segment Tree](Level%205%20-%20Big%20Data/persistent_segment_tree/)

### ⚪ Level 6: Specialist & Niche Architectures
*Goal: Extreme corner-case optimization.*
- [Skip List](Level%206%20-%20Specialist/skip_list/)
- [Splay Tree](Level%206%20-%20Specialist/splay_tree/)
- [Cartesian Tree](Level%206%20-%20Specialist/cartesian_tree/)
- [Spatial DS (Advanced)](Level%206%20-%20Specialist/Advanced%20DS/)

---

## 💡 Interview Pattern Matching

| "If you see this keyword..." | "...Think of this DS" |
|-----------------------------|-----------------------|
| "Range Minimum Query + Static" | **Sparse Table** |
| "Frequency of strings in a stream" | **Count-Min Sketch** |
| "Database Index / Range Scans" | **B+ Tree** |
| "History / Previous Versions" | **Persistent Segment Tree** |
| "Unique Count / Cardinality" | **HyperLogLog** |
| "Multi-keyword scanning" | **Aho-Corasick** |

---

## 🛠️ Usage

### Java
```bash
# Example for LRU Cache
javac -d bin "Level 4 - Senior Standards/lru_cache/basic_operations.java"
java -cp bin lru_cache.basic_operations
```

### C++
```bash
# Example for LRU Cache
g++ -std=c++17 "Level 4 - Senior Standards/lru_cache/basic_operations.cpp" -o app
./app
```

---

## License
Educational use only. Happy Coding! 🚀
