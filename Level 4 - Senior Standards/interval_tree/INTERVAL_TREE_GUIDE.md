# Interval Tree Guide

## Overview
An **Interval Tree** is a specialized binary search tree designed to efficiently answer **interval overlap queries**. It answers: "Given a query interval [a, b], find all intervals in the tree that overlap with it."

## Key Properties
- **Structure**: BST ordered by interval start points (`low` value).
- **Augmentation**: Each node stores the **maximum high value** in its subtree.
- **Complexity**: 
  - Insert: O(log N) average, O(N) worst (unbalanced)
  - Query: O(log N + K) where K = number of overlapping intervals

## The "max" Augmentation
The key insight is storing `max = maximum endpoint in subtree` at each node. This allows pruning: if `left.max < query.low`, no overlaps exist in left subtree.

## SDE2-3 Interview Significance
- **Frequency**: 10-15% of Google/Meta senior rounds
- **Classic Problems**:
  - Meeting room scheduling with conflict detection
  - Calendar applications (Google Calendar uses a variant)
  - Range overlap in genomics/DNA sequencing
  - Video streaming buffer management

## Real-World Applications
1. **Google Calendar**: Detecting meeting conflicts
2. **Operating Systems**: Memory segment management
3. **Databases**: Index range locks
4. **Genomics**: Finding overlapping DNA sequences

## Interview Tip
If asked to implement from scratch, start with the basic BST insert. Then add the `max` field update. Finally, implement the overlap search with the pruning logic.

## Balanced Variant (SDE3)
For guaranteed O(log N), combine with Red-Black Tree properties. This is the "Augmented Red-Black Tree" pattern used in production systems.

## Summary
Interval Trees are the go-to structure when you need to efficiently query "what overlaps with X?" in a dynamic set of intervals.
