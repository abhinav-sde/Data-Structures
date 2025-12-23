# Disjoint Set Union (DSU) Guide

## Introduction
The **Disjoint Set Union (DSU)** (also known as Union-Find) is a data structure that stores a collection of disjoint (non-overlapping) sets. It provides near-constant time operations to add new sets, merge existing sets, and determine whether elements are in the same set.

## Core Operations

### 1. Find
Determine which subset a particular element is in. This can be used for determining if two elements are in the same subset.
- **Path Compression**: Optimization where we make the found root the direct parent of all nodes on the path, flattening the tree.

### 2. Union
Join two subsets into a single subset.
- **Union by Rank/Size**: Optimization where we always attach the smaller/shorter tree to the larger/taller one to minimize tree height.

## Complexity
| Operation | Average Case | Worst Case |
|-----------|--------------|------------|
| Find      | O(α(n))      | O(n)       |
| Union     | O(α(n))      | O(n)       |

*α(n) is the Inverse Ackermann function, which is effectively constant (≤ 4) for all practical values of n.*

## Applications
- **Kruskal's Algorithm**: Finding Minimum Spanning Tree (MST).
- **Cycle Detection**: In undirected graphs.
- **Connected Components**: Finding connected regions in images or networks.
