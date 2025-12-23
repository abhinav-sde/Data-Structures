# Fenwick Tree (Binary Indexed Tree) Guide

## What is a Fenwick Tree?

A **Fenwick Tree** is a data structure for efficiently calculating prefix sums and handling range queries with updates.

## Time Complexity

| Operation | Time |
|-----------|------|
| **Update** | O(log n) |
| **Prefix Sum** | O(log n) |
| **Range Sum** | O(log n) |
| **Build** | O(n log n) |

## Key Operations

```java
// Update: Add delta to index i
void update(int i, int delta) {
    i++; // 1-indexed
    while (i <= n) {
        tree[i] += delta;
        i += (i & -i); // Add last set bit
    }
}

// Query: Prefix sum [0..i]
int query(int i) {
    i++; // 1-indexed
    int sum = 0;
    while (i > 0) {
        sum += tree[i];
        i -= (i & -i); // Remove last set bit
    }
    return sum;
}
```

## When to Use

✅ **Use when:**
- Need range sum with updates
- Coordinate compression problems
- Inversion count
- 2D range queries

❌ **Avoid when:**
- Only need static queries (use prefix sum array)
- Need non-commutative operations

## Fenwick vs Segment Tree

| Feature | Fenwick | Segment |
|---------|---------|----------|
| Code Complexity | Simpler | More complex |
| Memory | 2x less | 4x array |
| Range Update | Harder | Easier |
| Use Case | Sum queries | General purpose |

## Practice Problems

1. Range sum query - mutable
2. Count of smaller numbers after self
3. 2D range sum
4. Inversion count

---

## Summary

Fenwick Tree provides O(log n) prefix sums and updates with minimal memory and code. Ideal for cumulative sum problems.
