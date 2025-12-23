# HyperLogLog (HLL) Guide

## Overview
**HyperLogLog** is a probabilistic data structure used to estimate the **cardinality** (number of unique elements) of a set. Its main strength is using an incredibly small amount of memory to count billions of unique items with a typical error of ~2%.

## The "Magic" of HLL
Counting 1 billion unique 64-bit IDs exactly would require ~8GB of memory. HyperLogLog can provide a 98% accurate estimate using just **1.5KB** of memory.

## How it works (SDE2 Interview Intuition)
1. **Hashing**: Hash the items to binary strings.
2. **Probability**: If you see a binary string starting with `000...0` (say 10 zeros), the probability of that happening by chance is `1/(2^10)`. This suggests there are approximately `2^10 = 1024` items.
3. **Register Averaging**: HLL uses many registers (buckets) to store the maximum "count of leading zeros" seen and averages them using a **Harmonic Mean** to reduce variance.

## Senior Level Significance (SDE3)
- **Scalability**: It is the standard industry tool for "Daily Active Users" (DAU), unique visitors, or unique search terms in massive systems.
- **Mergeability**: HLLs are perfectly mergeable. You can count DAU in NY and London independently and merge them later to get the total unique DAU without any duplicate-counting bias.
- **Real-world adoption**: Used in **Redis** (`PFADD`), **Elasticsearch**, **BigQuery**, and **Presto**.

## Summary
HyperLogLog represents the peak of trade-offs in Big Data: sacrificing exactness for astronomical scale and constant-memory efficiency.
