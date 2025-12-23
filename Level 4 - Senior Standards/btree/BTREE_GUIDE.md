# B-Tree Guide

## Overview
B-Tree is a self-balancing multi-way search tree optimized for systems that read/write large blocks of data.

## Properties
- All leaves at same level
- Minimum degree t (except root)
- Each node has at most 2t-1 keys
- Each node has at least t-1 keys (except root)

## Time Complexity
- Search/Insert/Delete: O(log n)
- Height: O(log n)

## Use Cases
- **Databases**: MySQL, PostgreSQL use B+ trees for indexing
- **File Systems**: NTFS, ext4, HFS+ use B-trees
- **Key-Value Stores**: MongoDB, CouchDB

## Summary
B-Trees minimize disk I/O by keeping tree height low with multiple keys per node.
