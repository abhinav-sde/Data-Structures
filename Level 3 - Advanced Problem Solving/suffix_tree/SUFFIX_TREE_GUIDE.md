# Suffix Tree

A **Suffix Tree** for a string $S$ is a compressed trie of all suffixes of $S$. It is one of the most powerful and versatile data structures in string processing.

## Core Properties
1.  **Structure**:
    - Each edge is labeled with a non-empty substring of $S$.
    - Each internal node (except the root) has at least two children.
    - Each leaf represents a unique suffix of $S$.
2.  **Termination**: To ensure every suffix ends at a leaf, a unique character (usually `$`) is often appended to the end of $S$.
3.  **Path Labels**: The concatenation of edge labels from the root to a leaf forming suffix $i$ is exactly $S[i..N]$.

## Key Features
- **Pattern Matching**: Find if $P$ is a substring of $S$ in **O(|P|)** time.
- **Occurrence Counting**: Find all $k$ occurrences of $P$ in **O(|P| + k)**.
- **Longest Repeated Substring**: Can be found in **O(N)** by looking for the deepest internal node.
- **Longest Common Substring**: Using a **Generalized Suffix Tree** (constructed from two or more strings), it can be found in **O(N1 + N2)**.

## Comparison with Suffix Array
| Feature       | Suffix Tree | Suffix Array |
|---------------|-------------|--------------|
| Construction  | O(N) (Ukkonen) | O(N) or O(N log N) |
| Space         | Higher (Nodes + Edges) | Low (Integers) |
| Implementation| High Complexity | Moderate |
| Best For      | Pattern Matching | LCP Queries, Space-constrained environments |

## Major Operations
### 1. Construction
- **Naive**: O(N^2) by inserting each suffix into a compressed trie.
- **Ukkonen's Algorithm**: A sophisticated O(N) online construction algorithm.

### 2. Search (Pattern Matching)
- Follow the path matching characters of $P$ against edge labels. If we run out of $P$ while matching, $P$ is a substring.

### 3. Longest Repeated Substring
- Find the internal node with the maximum path label length.

## Complexity
| Operation | Average/Worst Case |
|-----------|--------------------|
| Space     | O(N)               |
| Build     | O(N)               |
| Search    | O(m)               |

*(where N is length of string, m is length of pattern)*
