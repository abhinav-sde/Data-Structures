# Trie (Prefix Tree) Guide

## What is a Trie?

A **Trie** (pronounced "try") is a tree-like data structure used to store and retrieve strings efficiently. Also known as a **prefix tree** or **digital tree**, it excels at prefix-based operations.

```
         root
        /  |  \
       a   b   c
      /    |    \
     p    at    ar
    /      |     |
   p      ch     t
  /        |
 le       ell
(apple)  (bat, batch, bell)
```

## Trie Properties

- **Nodes**: Each node represents a character
- **Root**: Empty node representing the start
- **Edges**: Connect parent to child nodes
- **End Marker**: Flag indicating a complete word
- **Children**: Typically stored in HashMap or array

## Time Complexity

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| **Insert** | O(m) | m = length of word |
| **Search** | O(m) | Search for exact word |
| **StartsWith** | O(m) | Check prefix existence |
| **Delete** | O(m) | Remove word from trie |
| **Autocomplete** | O(p + n) | p = prefix length, n = results |

## Space Complexity

- **Space**: O(ALPHABET_SIZE * N * M)
  - N = number of words
  - M = average word length
  - ALPHABET_SIZE = typically 26 for lowercase

**Optimization**: Use HashMap instead of fixed arrays to save space when alphabet is large or sparse.

## Core Operations

### 1. Insert
```java
void insert(String word) {
    TrieNode current = root;
    for (char ch : word.toCharArray()) {
        current.children.putIfAbsent(ch, new TrieNode());
        current = current.children.get(ch);
    }
    current.isEndOfWord = true;
}
```

### 2. Search
```java
boolean search(String word) {
    TrieNode current = root;
    for (char ch : word.toCharArray()) {
        if (!current.children.containsKey(ch)) return false;
        current = current.children.get(ch);
    }
    return current.isEndOfWord;
}
```

### 3. StartsWith (Prefix Check)
```java
boolean startsWith(String prefix) {
    TrieNode current = root;
    for (char ch : prefix.toCharArray()) {
        if (!current.children.containsKey(ch)) return false;
        current = current.children.get(ch);
    }
    return true; // Don't need isEndOfWord check
}
```

## When to Use Trie

### ✅ Use Trie When:
- Autocomplete/type-ahead suggestions
- Spell checkers and dictionaries
- IP routing (longest prefix matching)
- Pattern matching with prefixes
- Word games (boggle, scrabble)
- String prefix queries

### ❌ Avoid Trie When:
- Simple membership testing (use HashSet)
- Exact string matching only (use HashMap)
- Memory is severely constrained
- Strings have no common prefixes

## Comparison with Other Data Structures

| Feature | Trie | Hash Table | BST |
|---------|------|------------|-----|
| Search | O(m) | O(1) avg | O(log n) |
| Prefix Search | O(m) | O(n*m) | O(log n + m) |
| Autocomplete | O(p+n) | O(n*m) | O(log n + n) |
| Space | High | Medium | Medium |
| Ordered | Yes | No | Yes |

**m** = word length, **n** = number of words/keys, **p** = prefix length

## Common Problem Patterns

### Pattern 1: Word Dictionary
**Examples**: Insert/search words, wildcard search
**Approach**: Standard trie with recursion for wildcards

```java
// Wildcard search with '.'
boolean search(String word, TrieNode node, int index) {
    if (index == word.length()) return node.isEndOfWord;
    
    char ch = word.charAt(index);
    if (ch == '.') {
        for (TrieNode child : node.children.values()) {
            if (search(word, child, index + 1)) return true;
        }
        return false;
    }
    // ... standard search
}
```

### Pattern 2: Prefix-Based Problems
**Examples**: Autocomplete, longest common prefix
**Approach**: Traverse trie until prefix, collect results

### Pattern 3: Grid/Matrix Word Search
**Examples**: Word Search II, Boggle
**Approach**: Build trie from word list, DFS on grid

```java
// DFS + Trie for Word Search II
void dfs(board, i, j, trieNode, results) {
    if (trieNode.isEndOfWord) {
        results.add(trieNode.word);
    }
    // Explore 4 directions with trie pruning
}
```

### Pattern 4: Binary Trie (XOR Problems)
**Examples**: Maximum XOR, XOR queries
**Approach**: Store numbers in binary, find complement path

## Real-World Applications

### 1. Search Engines
- **Autocomplete**: Google search suggestions
- **Spell Check**: "Did you mean...?"
- **Query Suggestions**: Related searches

### 2. Network Routing
- **IP Routing Tables**: Longest prefix matching
- **DNS Resolution**: Domain name lookups
- **URL Shorteners**: Efficient path matching

### 3. Text Editors & IDEs
- **Code Completion**: Variable/function suggestions
- **Syntax Highlighting**: Keyword matching
- **Find/Replace**: Pattern matching

### 4. Mobile Keyboards
- **T9 Predictive Text**: Word predictions
- **Swipe Typing**: Gesture recognition
- **Emoji Search**: By name or keyword

### 5. Gaming
- **Word Games**: Scrabble, Boggle validators
- **Command Parsers**: Game console commands
- **Chat Filters**: Profanity detection

## Common Pitfalls

> [!CAUTION]
> **Pitfall 1**: Forgetting `isEndOfWord` marker
> Not marking end of word leads to false positives (e.g., "app" found when only "apple" was inserted).

> [!WARNING]
> **Pitfall 2**: Memory overhead
> Tries can consume significant memory. Use HashMap children for sparse alphabets, or compress with techniques like:
> - Radix trees (PATRICIA tries)
> - Ternary search trees

> [!CAUTION]
> **Pitfall 3**: Incorrect deletion
> Deleting a word should only remove nodes that aren't part of other words. Requires recursive cleanup.

## Interview Tips

### Quick Recognition
If you see keywords like:
- "Autocomplete"
- "Prefix matching"
- "Dictionary of words"
- "Word search in grid"
- "Longest common prefix"

→ **Think TRIE!**

### Common Tricks

**1. Reverse Insertion**: For suffix matching problems
```java
// Insert "hello" as "olleh" to check suffixes
```

**2. Store Frequency**: At each node for top-K problems
```java
class TrieNode {
    Map<Character, TrieNode> children;
    int frequency; // How many words pass through
}
```

**3. Store Complete Word**: At leaf nodes for easy retrieval
```java
class TrieNode {
    String word; // Store at isEndOfWord = true
}
```

### Space Optimization

**Array vs HashMap Children:**
- **Array**: `TrieNode[26]` for fixed alphabet
  - Faster access: O(1)
  - Higher memory: Always 26 pointers
  
- **HashMap**: `Map<Character, TrieNode>`
  - Lower memory: Only used characters
  - Slightly slower: O(1) average

## Variations

### 1. Compressed Trie (Radix Tree)
- Merge nodes with single child
- Used in: Git, routing tables

### 2. Ternary Search Tree
- Each node has 3 children: less, equal, greater
- More space-efficient than standard trie

### 3. Suffix Trie
- Insert all suffixes of a string
- Used for: Pattern matching, longest repeated substring

## Practice Problems

### Basic
1. Implement Trie (insert, search, startsWith)
2. Longest common prefix
3. Word break

### Intermediate
4. Add and search word (with wildcard)
5. Replace words (dictionary compression)
6. Top K frequent words

### Advanced
7. Word Search II (find words in grid)
8. Palindrome pairs
9. Stream of characters
10. Design search autocomplete system
11. Maximum XOR of two numbers

---

## Summary

**Trie** is the optimal data structure for prefix-based string operations. It trades space for time, providing O(m) operations where m is the word length, independent of the number of words stored.

**Key Advantage**: Efficient prefix matching and autocomplete functionality that would be O(n*m) with hash tables.

**Best Use Cases**: Search suggestions, spell checkers, IP routing, word games.

Master the standard trie implementation first, then explore variations like binary tries for XOR problems and compressed tries for memory efficiency.
