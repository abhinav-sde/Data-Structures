# Splay Tree Guide

## Overview
Splay Tree is a self-adjusting binary search tree that moves recently accessed elements to the root.

## Properties
- No explicit balance factor
- Frequently accessed items near root
- Amortized O(log n) for all operations

## Operations
- **Splaying**: Move node to root through rotations
- Zig, Zig-Zig, Zig-Zag rotations

## Time Complexity
- Average: O(log n)
- Amortized: O(log n)
- Worst single operation: O(n)

## Use Cases
- Caching (frequently accessed items fast)
- Network routing
- Garbage collection

## Summary
Splay trees excel when there's locality of reference - recent accesses predict future accesses.
