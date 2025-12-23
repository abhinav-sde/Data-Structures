# B+ Tree Guide

## Overview
A **B+ Tree** is an N-ary tree that is the industry standard for database indexing and file systems. It is an evolution of the B-Tree optimized for block-based storage (Disk/SSD).

## Key Characteristics
1. **Internal Nodes**: Only store keys (routing information). This allows a very high "fan-out", reducing the height of the tree.
2. **Leaf Nodes**: Store both keys and data (or pointers to data).
3. **Leaf Links**: All leaf nodes are linked together in a linked-list fashion. This enables **O(log N) + K** range queries (where K is the number of results).

## B-Tree vs B+ Tree (SDE2-3 Interview Topic)
| Feature | B-Tree | B+ Tree |
|---------|--------|---------|
| Data Storage | Any node | Only in leaves |
| Pointer Fanout | Lower | Higher (internal nodes are smaller) |
| Range Queries | Requires tree traversal | Direct scan via leaf links |
| Tree Height | Slightly higher | Lower |

## Industrial Use
- **MySQL (InnoDB)**: Uses B+ Trees for primary (Clustered) and secondary indexes.
- **Postgres**: Standard B-Tree index is actually a High-Concurrency B+ variant.
- **Filesystems**: NTFS, XFS.

## Summary
The B+ Tree is better than the B-Tree for indexing because it maximizes the number of keys per disk block and provides exceptionally fast sequential access.
