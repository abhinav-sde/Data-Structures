# Radix Tree (Compressed Trie)

A **Radix Tree** (also known as a **Compressed Trie** or **Patricia Tree**) is a space-optimized version of a Trie. In a standard Trie, each edge represents a single character. In a Radix Tree, any node that is the only child is merged with its parent, and the edge stores the multi-character prefix string.

## Core Concepts
1.  **Node Merging**: If a node has only one child, it is merged with that child to form a single edge with multiple characters.
2.  **Edge Labels**: Edges store strings (prefixes) rather than single characters.
3.  **Lookup Depth**: Reduced lookup depth compared to a standard Trie for datasets with long common prefixes.

## Major Operations
### 1. Search
- Traverse the tree by matching the search string against edge labels.
- If an edge label is a prefix of the remaining search string, proceed to the child.
- If the search string exactly matches the concatenated path to a terminal node, it is found.

### 2. Insert
- Similar to search, but when a mismatch occurs:
  - If the mismatch happens in the middle of an edge label, the edge is **split** into two parts.
  - A new child node is added for the new string.
  - If the mismatch happens at a node, a new child is simply added.

### 3. Delete
- Locate the node and mark it as non-terminal.
- **Node Merging**: If the node now has only one child, merge it with the child.
- If the parent of the deleted node now has only one child, merge them as well. This maintains the "Radix" property.

## Advantages
- **Space Efficiency**: Significantly less space used for datasets with many unique but long strings (like URLs or file paths).
- **Lookup Speed**: Fewer node traversals than a standard Trie.

## Applications
- **IP Routing**: Longest prefix matching for CIDR blocks.
- **Inverted Indices**: Efficiently storing terms in search engines.
- **File Systems**: Representing directory structures.

## Complexity
| Operation | Average/Worst Case |
|-----------|--------------------|
| Space     | O(Total String Length)|
| Search    | O(k)               |
| Insert    | O(k)               |
| Delete    | O(k)               |

*(where k is the length of the string)*
