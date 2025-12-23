# Bloom Filter Guide

## Overview
Bloom Filter is a space-efficient probabilistic data structure for testing set membership.

## Properties
- **False positives**: Possible (says element exists when it doesn't)
- **False negatives**: Not possible (if it says no, it's definitely not there)
- **Space**: Much less than storing all elements

## Time Complexity
- Add: O(k) where k = number of hash functions
- Contains: O(k)

## Use Cases
- Spell checkers
- Database query optimization
- Web caching (check if URL visited)
- Network routers
- Blockchain (Bitcoin uses Bloom filters)

## Summary
Trade accuracy for space - use when false positives are acceptable but space is limited.
