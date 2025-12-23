# Cartesian Tree Guide

## Overview
Cartesian Tree is a binary tree derived from a sequence of numbers, combining BST and heap properties.

## Properties
- **BST property**: Inorder traversal gives original sequence
- **Heap property**: Parent has smaller value than children (min-heap variant)

## Construction
- O(n) time using stack-based algorithm
- O(n log n) recursive approach

## Applications
1. **Range Minimum Query (RMQ)**: Reduce to LCA problem
2. **Suffix trees**: Used in construction
3. **Treaps**: Randomized Cartesian trees for BST operations

## Time Complexity
- Build: O(n) with stack, O(n log n) recursive
- RMQ: O(1) query after O(n) preprocessing

## Summary
Cartesian trees provide elegant solutions to RMQ and related problems by combining tree structures.
