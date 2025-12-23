# LSM-Tree (Log-Structured Merge-Tree)

An **LSM-Tree** is a data structure designed to provide high write throughput by transforming random writes into sequential writes. It is the core storage architecture behind databases like **Cassandra, RocksDB, and LevelDB**.

## The Problem
Standard B-Trees require random disk I/O to update nodes, which is slow. As datasets grow larger than RAM, write performance drops significantly due to disk seek latency.

## The LSM-Tree Solution
LSM-Trees use a multi-tiered approach:
1.  **MemTable (Memory)**: All writes (and updates/deletes) are first stored in a sorted in-memory structure (like a Skip List or Red-Black Tree).
2.  **WAL (Write-Ahead Log)**: To prevent data loss, writes are also appended to an on-disk log before being added to the MemTable.
3.  **Flushing**: When the MemTable reaching a certain size, it is frozen and flushed to disk as an immutable **SSTable** (Sorted String Table).
4.  **SSTables (Disk)**: These are sorted files. Because they are sorted, searching is efficient, but you may have to check multiple files (starting from the newest).
5.  **Compaction**: In the background, the system merges multiple SSTables into a single larger SSTable, removing duplicates and "tombstones" (deleted markers).

## Operations
- **Write**: O(1) amortized (append to WAL + insert into MemTable).
- **Read**: Check MemTable, then check SSTables from newest to oldest. Potential O(L * log N) where L is the number of SSTables.
- **Delete**: A special value called a **Tombstone** is written for the key. The actual data is removed during the next compaction.

## Advantages
- **Extreme Write Performance**: Orders of magnitude faster than B-Trees for high-frequency writes.
- **Compression**: Immutable SSTables are easy to compress.

## Complexity
| Operation | LSM-Tree (Amortized) | B-Tree       |
|-----------|--------------------|--------------|
| Insert    | **O(1)**           | O(log N)     |
| Update    | **O(1)**           | O(log N)     |
| Search    | O(log N)           | **O(log N)** |

*(Note: Read performance in LSM-trees is often optimized using Bloom Filters and Indexing)*
