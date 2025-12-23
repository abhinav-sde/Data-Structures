# Sparse Table Guide

## Overview
A **Sparse Table** is a data structure designed for **Range Queries** on a static array. It is particularly famous for its ability to answer **Range Minimum Queries (RMQ)** in constant time **O(1)**.

## Key Properties
- **Preprocessing**: O(N log N) using Dynamic Programming.
- **Query**: O(1) for idempotent functions, O(log N) for non-idempotent.
- **Static**: Does not support updates. If updates are needed, use a **Segment Tree**.

## Idempotent Functions
A function `f(x, y)` is idempotent if `f(x, x) = x`. Sparse Table gives O(1) for:
- `min(a, b)`
- `max(a, b)`
- `gcd(a, b)`
- bitwise `AND`, `OR`

## Interview Applications (SDE2-3)
1. **LCA (Lowest Common Ancestor)**: By converting a tree into an Euler Tour, LCA can be solved as an RMQ problem on the tour array. Using a Sparse Table allows for **O(1)** LCA queries.
2. **Longest Common Prefix (LCP)**: Used in conjunction with Suffix Arrays to find the LCP of any two suffixes in O(1).

## Summary
The Sparse Table is the "speed king" of range queries. When your data is static and query latency is critical (e.g., HFT, Real-time systems), Sparse Table is the weapon of choice.
