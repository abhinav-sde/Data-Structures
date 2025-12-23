# LRU Cache (Least Recently Used) Guide

## Overview
LRU Cache is the most common industry-standard for caching. It discards the least recently used items first.

## Design Principle
- **Time Complexity**: O(1) for both `get` and `put`.
- **Data Structures**: 
    - `HashMap`: For O(1) lookup.
    - `Doubly Linked List`: For O(1) reordering and eviction.

## Interview Significance (SDE2-3)
- Expected to be written from scratch without using `LinkedHashMap`.
- Discuss **Thread-Safety**: Use of `synchronized` vs `ReadWriteLock` vs `ConcurrentHashMap` with sampling.
- **Eviction Polices**: Explain why LRU might fail (One-hit wonders) and why **W-TinyLFU** or **LRU-K** might be better.

## Industrial Implementation
- **Redis**: Uses a sampling approximation of LRU to save memory and avoid locking overhead.
- **Guava/Caffeine**: Use Window-TinyLFU for high hit rates.

## Summary
The combination of a hash table and a doubly linked list provides the speed of a map with the temporal ordering of a list.
