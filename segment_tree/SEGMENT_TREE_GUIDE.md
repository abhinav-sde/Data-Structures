# Segment Tree Guide

## Introduction
A **Segment Tree** is a binary tree used for storing information about intervals or segments. It allows querying which of the stored segments contain a given point, but it's most often used for simple range queries.

## Core Operations

### 1. Build
Constructing the tree from an input array.
- **Time**: O(n)
- **Space**: O(4n)

### 2. Update (Point)
Changing the value of a single element in the input array and updating the tree path.
- **Time**: O(log n)

### 3. Query (Range)
Finding the sum/min/max/etc. for a range [L, R].
- **Time**: O(log n)

## Lazy Propagation
For range updates (updating all elements in [L, R]), standard updates take O(n). **Lazy Propagation** defers updates to children until they are needed, maintaining O(log n) efficiency.

## Applications
- **Range Sum Query**: Sum of elements from index L to R.
- **Range Minimum Query (RMQ)**: Minimum value in range [L, R].
- **Computational Geometry**: Solving problems with overlapping rectangles.
