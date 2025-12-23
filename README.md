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

## 📂 Implementation Inventory

### 🌟 Senior Level / Industry Standards
- **Cache**: [LRU Cache](lru_cache/), [LFU Cache](lfu_cache/)
- **Trees**: [Red-Black Tree](red_black_tree/), [B+ Tree](bplus_tree/)
- **Range & String**: [Sparse Table](sparse_table/), [Aho-Corasick](aho_corasick/), [Persistent Segment Tree](persistent_segment_tree/)
- **Big Data**: [Count-Min Sketch](count_min_sketch/), [HyperLogLog](hyperloglog/)

### 🛠️ Core Data Structures
- [Heap](heap/) (Min/Max, K-th Largest)
- [Trie](trie/) (Autocomplete, XOR)
- [BST](bst/) (Validate, AVL Tree)
- [Deque](deque/) (Sliding Window Max)
- [Fenwick Tree](fenwick_tree/) (Binary Indexed Tree)

### 📚 Specialized Structures
- [Skip List](skip_list/), [Suffix Array](suffix_array/), [Bloom Filter](bloom_filter/)
- [B-Tree](btree/), [Splay Tree](splay_tree/), [Cartesian Tree](cartesian_tree/)

### 🌐 Spatial Data Structures (`Advanced DS/`)
- [K-D Trees](Advanced%20DS/K-D%20Trees/), [R-Trees](Advanced%20DS/R-Trees/), [Quad Trees](Advanced%20DS/Quad%20Tree/)
- [Geohash+Trie](Advanced%20DS/Geohash+Trie/), [H3 Hex Grid](Advanced%20DS/H3%20Hex%20grid/)

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
javac -d bin structure_name/basic_operations.java
java -cp bin structure_name.basic_operations
```

### C++
```bash
g++ -std=c++17 structure_name/basic_operations.cpp -o app
./app
```

---

## License
Educational use only. Happy Coding! 🚀
