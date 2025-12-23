# Skip List Guide

## Overview
Skip List is a probabilistic data structure that allows O(log n) search, insert, and delete operations.

## Time Complexity
- Search: O(log n) average
- Insert: O(log n) average
- Delete: O(log n) average

## Use Cases
- Alternative to balanced trees (simpler implementation)
- Concurrent data structures (easier to implement lock-free)
- Redis sorted sets
- LevelDB/RocksDB (LSM trees)

## Summary
Skip lists provide probabilistic balancing without rotations, making them simpler than AVL/Red-Black trees.
