# LFU Cache (Least Frequently Used) Guide

## Overview
LFU Cache evicts the items with the lowest access frequency. It is more complex than LRU because it needs to maintain frequency counts and handle ties using a secondary policy (usually LRU).

## Design Principle
- **Requirement**: O(1) for all operations.
- **Approach**: 
    - `HashMap<Key, Value>`: Same as LRU.
    - `HashMap<Key, Frequency>`: Tracking how many times a key was hit.
    - `HashMap<Frequency, LinkedList<Keys>>`: Grouping keys by their frequency.

## LRU vs LFU
- **LRU** is better at handling **temporal locality** (items used recently will be used again).
- **LFU** is better at handling **frequency locality** (items used many times are valuable).
- **Cons of LFU**: An item with a high frequency count from the past but never used again can "clog" the cache. This is solved by **Frequency Aging**.

## Industry Use (SDE3 Level)
Modern caches like **Caffeine** use **W-TinyLFU**. This uses a "frequency sketch" (similar to a Bloom filter) to estimate how many times something might be used, combined with a small "admission window" to filter out one-hit wonders.

## Summary
While LRU is the industry standard for general purposes, LFU (and its variants) is superior for high-concurrency systems where cache hit rate is critical.
