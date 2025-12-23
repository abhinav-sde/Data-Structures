# AVL Tree Guide

## Overview
An **AVL Tree** is a self-balancing Binary Search Tree where the heights of the two child subtrees of any node differ by at most one. It was the first such data structure to be invented (1962).

## The Balance Factor
**Balance Factor** = height(left subtree) - height(right subtree)

For an AVL tree, the balance factor of every node must be **-1, 0, or +1**.

## Four Rotation Cases

### 1. Left-Left (LL) Case
```
     z                         y
    /                         / \
   y        Right Rotate     x   z
  /         ---------->
 x
```

### 2. Right-Right (RR) Case
```
 x                            y
  \                          / \
   y       Left Rotate      x   z
    \      ---------->
     z
```

### 3. Left-Right (LR) Case
```
   z                       z                      y
  /                       /                      / \
 x        Left on x      y      Right on z      x   z
  \       -------->     /       --------->
   y                   x
```

### 4. Right-Left (RL) Case
```
 x                     x                        y
  \                     \                      / \
   z     Right on z      y      Left on x     x   z
  /      --------->       \     -------->
 y                         z
```

## AVL vs Red-Black (SDE2 Interview Topic)

| Feature | AVL | Red-Black |
|---------|-----|-----------|
| **Balance** | Stricter (height diff ≤ 1) | Looser (height ≤ 2 log N) |
| **Search** | **Faster** (lower height) | Slightly slower |
| **Insert/Delete** | More rotations | Fewer rotations |
| **Best for** | Read-heavy workloads | General purpose |

## Industry Use
- **SQLite** uses a variant of AVL for in-memory indexes
- **Teaching**: Standard for learning tree rotations
- **Databases**: Read-optimized lookup tables

## Interview Significance (SDE2)
- **Amazon/Microsoft**: Frequently ask to implement AVL insert with rotations
- **Meta/Google**: Less common (they prefer discussing Red-Black)
- **Key Skill**: Understanding when and how to rotate is the core competency

## Summary
AVL trees are the "strict parent" of balanced BSTs—more rigorously balanced than Red-Black trees. They're perfect for scenarios where lookups greatly outnumber modifications.
