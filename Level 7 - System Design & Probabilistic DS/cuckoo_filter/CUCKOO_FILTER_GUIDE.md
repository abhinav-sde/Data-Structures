# Cuckoo Filter

A **Cuckoo Filter** is a compact, probabilistic data structure that supports membership queries on a set of items, much like a Bloom Filter. However, it offers several significant improvements over standard Bloom Filters.

## Key Advantages over Bloom Filter
1.  **Deletion Support**: You can remove items from a Cuckoo Filter without rebuilding the entire structure.
2.  **Higher Space Efficiency**: For low false-positive rates (FPR), Cuckoo Filters use less space than Bloom Filters.
3.  **Better Throughput**: Particularly for lookups, Cuckoo Filters can be faster due to better cache locality.

## How it Works: Partial-Key Cuckoo Hashing
Cuckoo Filters are based on **Cuckoo Hashing**, but instead of storing the actual items, they store small **fingerprints** (e.g., 8-bit or 12-bit hashes of the item).

1.  **Two Buckets**: Each item $x$ has two potential bucket locations:
    - $h_1(x) = hash(x)$
    - $h_2(x) = h_1(x) \oplus hash(fingerprint(x))$
2.  **Insertion**:
    - Try to put the fingerprint in an empty slot in $h_1(x)$ or $h_2(x)$.
    - If both are full, pick a random slot, "kick out" the existing fingerprint, and insert the new one.
    - The kicked-out fingerprint then moves to its own alternate location. This "cuckoo" behavior continues until a slot is found or a max number of kicks is reached.
3.  **Lookup**: Check both $h_1(x)$ and $h_2(x)$ for the fingerprint.
4.  **Deletion**: Find the fingerprint in $h_1(x)$ or $h_2(x)$ and remove one instance of it.

## Important Properties
- **False Positives**: Can occur if two different items produce the same fingerprint and hash to the same buckets.
- **Failures**: Insertion can fail if the filter becomes too full (usually > 90% load factor).
- **False Negatives**: None (as long as you only delete items that were previously inserted).

## Complexity
| Operation | Average   | Worst Case (Load < 95%) |
|-----------|-----------|------------------------|
| Insert    | O(1)      | O(Max Kicks)           |
| Lookup    | O(1)      | O(1)                   |
| Delete    | O(1)      | O(1)                   |
| Space     | O(N)      | O(N)                   |
