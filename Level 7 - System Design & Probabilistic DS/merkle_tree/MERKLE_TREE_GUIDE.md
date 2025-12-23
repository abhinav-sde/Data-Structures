# Merkle Tree (Hash Tree)

A **Merkle Tree** is a tree in which every leaf node is labeled with the cryptographic hash of a data block, and every non-leaf node is labeled with the cryptographic hash of the labels of its child nodes.

## Core Concepts
1.  **Data Integrity**: Any change to a data block at the leaf level will propagate up the tree, causing the root hash to change. This allows for efficient verification of large datasets.
2.  **Binary Tree Structure**: Most commonly implemented as a binary tree, where each internal node has exactly two children.
3.  **Odd Leaves**: If the number of data blocks is odd, the last block is duplicated (or handled specially) to maintain the tree structure.

## Merkle Proof (Audit Path)
A key feature of Merkle Trees is the ability to prove that a specific data block is part of the tree without sharing the entire tree.
- To prove block $B$, you only need the hashes of its siblings up to the root.
- **Complexity**: O(log N) hashes are required for a proof.

## Root Hash
The root hash is a concise summary of the entire dataset. It is often shared (e.g., in a block header) to provide a single point of truth for data integrity.

## Applications
- **Git**: Each commit represents a root of a Merkle Tree of files.
- **Blockchain (Bitcoin/Ethereum)**: Transactions are hashed into a Merkle Tree to allow light nodes to verify transaction inclusion.
- **Distributed Databases (Cassandra/Dynamo)**: Merkle trees are used during "anti-entropy" (data repair) to efficiently find differences between data replicas.

## Complexity
| Operation | Average/Worst Case |
|-----------|--------------------|
| Build     | O(N)               |
| Proof Size| O(log N)           |
| Verify    | O(log N)           |
