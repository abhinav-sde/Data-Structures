# Count-Min Sketch Guide

## Overview
The **Count-Min Sketch** is a probabilistic data structure that serves as a frequency table of events in a stream of data. It uses hash functions to map events to frequencies, but unlike a hash table, it uses constant memory regardless of the number of unique elements.

## Key Properties
- **Space Complexity**: Fixed memory O(width * depth).
- **Time Complexity**: O(depth) for add/query (constant time).
- **Accuracy**: It will never *underestimate* a frequency. It may *overestimate* due to hash collisions.

## Industry Significance (SDE2-3)
- **Problem Solving**: "How do you find the Top 100 most frequent search queries in the last hour?" (Standard Heavy Hitters problem).
- **Infrastructure**: used in **Redis**, **Apache Spark**, and Network Router hardware to track frequent items without storing billions of keys.

## Error Configuration
- `epsilon (ε)`: Controls the error margin (Error ≤ ε * TotalStreamSize).
- `delta (δ)`: Controls the probability of exceeding the error margin (Confidence = 1 - δ).

## Summary
The Count-Min Sketch is a beautiful alternative to HashMaps when you have an infinite stream of data and don't need 100% exact counts, prioritizing low memory and high throughput.
