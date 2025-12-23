# Persistent Segment Tree Guide

## Overview
A **Persistent Segment Tree** is a segment tree that preserves its previous versions after each update. It is a **Functional Data Structure**, where updates do not modify the tree in-place.

## Key Technique: Path Copying
Since each update in a segment tree only modifies **O(log N)** nodes (the path from leaf to root), a persistent tree creates new versions by only copying those O(log N) changed nodes. The rest of the tree is shared between versions.

## Complexity
- **Time (Update)**: O(log N)
- **Time (Query)**: O(log N)
- **Space**: O(log N) per update

## SDE2-3 Interview Significance
- **Advanced Problem Solving**: It is the standard solution for the "K-th Smallest Number in an Array Range" problem.
- **System Design Concepts**: Highlighting that you understand how **Git**, **Cow (Copy-on-write)** file systems, or **BigTable** snapshots work.

## Comparison
- **Standard SegTree**: Memory O(N), Time O(log N), No history.
- **Persistent SegTree**: Memory O(N + Q log N), Time O(log N), Full history.

## Summary
While rarely used in common application code, the mastery of Persistent Segment Trees marks the shift from a "problem solver" to an "architect" who understands immutable state management across versions.
