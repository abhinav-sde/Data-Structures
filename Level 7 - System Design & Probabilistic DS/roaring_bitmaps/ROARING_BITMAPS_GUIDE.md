# Roaring Bitmaps

**Roaring Bitmaps** are a compressed bitmap data structure that offers both better compression and better performance than standard bitsets or other compressed formats (like WAH or EWAH). They are widely used in high-performance search engines and databases like **Apache Lucene, Solr, and Spark**.

## The Problem
- **Standard BitSet**: Extremely space-inefficient for sparse data (e.g., storing just $\{1, 1000000\}$ uses a lot of memory).
- **Compressed Formats (WAH/EWAH)**: Slow for random access because they are run-length encoded (RLE), requiring decompression to check a bit.

## The Roaring Solution
Roaring Bitmaps partition the 32-bit integer range into chunks of $2^{16}$ (65,536) values. The high 16 bits identify the chunk, and the low 16 bits are stored in one of three container types:

1.  **Array Container**: Used when a chunk contains $\le 4096$ integers. It stores sorted 16-bit values.
2.  **Bitmap Container**: Used when a chunk contains $> 4096$ integers. It uses a bitset of 65,536 bits ($8$ KB).
3.  **Run Container**: Used for long sequences of contiguous integers (e.g., $100$ to $2000$). It stores pairs of (start, length).

## Transitions
Roaring Bitmaps are dynamic:
- If an Array Container grows beyond 4096 elements, it converts to a Bitmap Container.
- If a Bitmap Container shrinks below 4096 elements, it converts to an Array Container.
- Run containers are typically applied during a manual `run_optimize()` call.

## Performance Characteristics
- **Fast Random Access**: Checking `contains(x)` is O(log N) for Array containers and O(1) for Bitmap containers.
- **Fast Set Operations**: AND, OR, XOR operations are optimized for various container pair combinations.
- **Cache Friendly**: Containers fit well within CPU caches.

## Applications
- **Search Engines**: Storing "postings lists" (IDs of documents containing a word).
- **Databases**: Bitmapped indexes for low-cardinality columns.
- **Big Data**: Distributed join optimizations (Bloom Filters are often replaced by Roaring Bitmaps).

## Complexity (Average)
| Operation | Complexity |
|-----------|------------|
| contains  | O(1) to O(log k) |
| add       | O(1) to O(k)    |
| remove    | O(1) to O(k)    |
| AND / OR  | O(N + M)        |
