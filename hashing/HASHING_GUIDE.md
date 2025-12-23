# Hashing Guide

## Introduction
**Hashing** is a technique used to map data of an arbitrary size to fixed-size values. It is primarily used to implement **Hash Tables**, which support efficient search, insertion, and deletion operations.

## Core Concepts

### 1. Hash Function
A function that converts a given key into an index in the hash table.
- **Goal**: Distribution keys uniformly across the table.
- **Properties**: Deterministic, fast to compute, minimizes collisions.

### 2. Collisions
Occur when two different keys hash to the same index.
**Resolution Techniques**:
- **Chaining**: Store multiple elements at the same index using a linked list or dynamic array.
- **Open Addressing**: Find the next available slot using probing (Linear, Quadratic, Double Hashing).

## Complexity
| Operation | Average Case | Worst Case |
|-----------|--------------|------------|
| Search    | O(1)         | O(n)       |
| Insert    | O(1)         | O(n)       |
| Delete    | O(1)         | O(n)       |

*Note: Worst case occurs when all keys hash to the same index (poor hash function).*

## Applications
- **Databases**: Indexing.
- **Caches**: Key-value storage.
- **Sets**: Testing membership.
- **Cryptography**: Digital signatures.
