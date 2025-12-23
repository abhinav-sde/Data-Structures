# Aho-Corasick Algorithm Guide

## Overview
The **Aho-Corasick** algorithm is a multi-pattern string searching algorithm. It effectively combines a **Trie** structure with **KMP-style failure links**.

## Complexity
- **Preprocessing**: O(Sum of pattern lengths)
- **Searching**: O(TextLength + Number of matches)
- **Key Advantage**: Searching is independent of the number of patterns. Whether you are searching for 1 or 1,000,000 patterns, you only scan the text once.

## How it works
1. **Build a Trie** of all candidate patterns.
2. **Failure Links**: For each node, find the longest suffix that is also a prefix of some pattern (just like KMP).
3. **Search**: Traverse the Trie with text characters. If a character isn't a child of the current node, follow the failure link.

## Senior Level Interview Topics (SDE2-3)
- **DFA vs NFA**: Traditional Aho-Corasick with failure link loops is an NFA. Precomputing a `next[state][char]` table makes it a DFA.
- **Fail links in practice**: Used in building **grep**, high-speed firewalls (Snort IDS), and virus scanners.
- **Comparison**: Why use this over Rabin-Karp? Rabin-Karp is easier to implement but has higher complexity for very large pattern sets.

## Summary
When you need to find many needles in a haystack simultaneously, Aho-Corasick is the standard industry algorithm.
