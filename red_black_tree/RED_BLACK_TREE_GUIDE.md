# Red-Black Tree Guide

## Overview
A **Red-Black Tree** is a self-balancing binary search tree. It is complex to implement but provides O(log n) guarantees for search, insert, and delete with very efficient real-world performance.

## The 5 Rules
1. Every node is **Red** or **Black**.
2. The **Root** is always **Black**.
3. Every **Leaf (NIL)** is **Black**.
4. If a node is **Red**, both its children must be **Black** (No consecutive Reds).
5. For each node, all paths from the node to descendant leaves contain the same number of **Black** nodes.

## AVL vs Red-Black (SDE2 Interview Topic)
- **AVL**: More balanced (Max height ~1.44 log n). Better for **Search-heavy** workloads.
- **Red-Black**: Less balanced (Max height ~2 log n). Better for **Insert/Delete-heavy** workloads because it performs fewer rotations.
- **Industry Standard**: Red-Black is used in `HashMap` (Java 8+), `TreeMap`, `std::map`, and Linux Kernel Task Scheduler.

## Implementation Tip
Always implement the `leftRotate` and `rightRotate` helper functions first. The logic for fixing violation depends entirely on these.

## Summary
Red-Black trees are the "workhorse" of industrial balanced trees due to their balanced trade-off between search speed and update complexity.
