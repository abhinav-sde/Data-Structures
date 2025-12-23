
/**
 * Core Trie Problems in Java
 * Contains essential trie-based algorithms
 */

import java.util.*;

public class core_problems {

    // TrieNode class for problem solving
    static class TrieNode {
        Map<Character, TrieNode> children = new HashMap<>();
        boolean isEndOfWord = false;
        String word = null; // For some problems
    }

    // Problem 1: Implement Trie (Prefix Tree) - LeetCode 208
    static class ImplementTrie {
        private TrieNode root;

        public ImplementTrie() {
            root = new TrieNode();
        }

        public void insert(String word) {
            TrieNode current = root;
            for (char ch : word.toCharArray()) {
                current.children.putIfAbsent(ch, new TrieNode());
                current = current.children.get(ch);
            }
            current.isEndOfWord = true;
        }

        public boolean search(String word) {
            TrieNode current = root;
            for (char ch : word.toCharArray()) {
                if (!current.children.containsKey(ch))
                    return false;
                current = current.children.get(ch);
            }
            return current.isEndOfWord;
        }

        public boolean startsWith(String prefix) {
            TrieNode current = root;
            for (char ch : prefix.toCharArray()) {
                if (!current.children.containsKey(ch))
                    return false;
                current = current.children.get(ch);
            }
            return true;
        }
    }

    // Problem 2: Longest Common Prefix
    // Time Complexity: O(S) where S is sum of all characters
    static String longestCommonPrefix(String[] strs) {
        if (strs == null || strs.length == 0)
            return "";

        TrieNode root = new TrieNode();

        // Insert first string
        TrieNode current = root;
        for (char ch : strs[0].toCharArray()) {
            current.children.put(ch, new TrieNode());
            current = current.children.get(ch);
        }
        current.isEndOfWord = true;

        // Insert remaining strings
        for (int i = 1; i < strs.length; i++) {
            current = root;
            for (char ch : strs[i].toCharArray()) {
                if (!current.children.containsKey(ch)) {
                    current.children.put(ch, new TrieNode());
                }
                current = current.children.get(ch);
            }
            current.isEndOfWord = true;
        }

        // Find longest common prefix
        StringBuilder prefix = new StringBuilder();
        current = root;

        while (current.children.size() == 1 && !current.isEndOfWord) {
            Map.Entry<Character, TrieNode> entry = current.children.entrySet().iterator().next();
            prefix.append(entry.getKey());
            current = entry.getValue();
        }

        return prefix.toString();
    }

    // Problem 3: Word Break - Check if string can be segmented
    // Time Complexity: O(n^2)
    static boolean wordBreak(String s, List<String> wordDict) {
        TrieNode root = new TrieNode();

        // Build trie with dictionary words
        for (String word : wordDict) {
            TrieNode current = root;
            for (char ch : word.toCharArray()) {
                current.children.putIfAbsent(ch, new TrieNode());
                current = current.children.get(ch);
            }
            current.isEndOfWord = true;
        }

        // DP to check if string can be broken
        boolean[] dp = new boolean[s.length() + 1];
        dp[0] = true;

        for (int i = 0; i < s.length(); i++) {
            if (!dp[i])
                continue;

            TrieNode current = root;
            for (int j = i; j < s.length(); j++) {
                char ch = s.charAt(j);
                if (!current.children.containsKey(ch))
                    break;

                current = current.children.get(ch);
                if (current.isEndOfWord) {
                    dp[j + 1] = true;
                }
            }
        }

        return dp[s.length()];
    }

    // Problem 4: Add and Search Word (with wildcard '.')
    static class WordDictionary {
        private TrieNode root;

        public WordDictionary() {
            root = new TrieNode();
        }

        public void addWord(String word) {
            TrieNode current = root;
            for (char ch : word.toCharArray()) {
                current.children.putIfAbsent(ch, new TrieNode());
                current = current.children.get(ch);
            }
            current.isEndOfWord = true;
        }

        public boolean search(String word) {
            return searchHelper(word, 0, root);
        }

        private boolean searchHelper(String word, int index, TrieNode node) {
            if (index == word.length()) {
                return node.isEndOfWord;
            }

            char ch = word.charAt(index);

            if (ch == '.') {
                // Try all possible children
                for (TrieNode child : node.children.values()) {
                    if (searchHelper(word, index + 1, child)) {
                        return true;
                    }
                }
                return false;
            } else {
                if (!node.children.containsKey(ch)) {
                    return false;
                }
                return searchHelper(word, index + 1, node.children.get(ch));
            }
        }
    }

    // Problem 5: Max XOR of Two Numbers in Array
    // Time Complexity: O(n)
    static int findMaximumXOR(int[] nums) {
        TrieNode root = new TrieNode();

        // Build trie with binary representation
        for (int num : nums) {
            TrieNode current = root;
            for (int i = 31; i >= 0; i--) {
                int bit = (num >> i) & 1;
                char ch = (char) ('0' + bit);
                current.children.putIfAbsent(ch, new TrieNode());
                current = current.children.get(ch);
            }
        }

        int maxXor = 0;

        // For each number, try to find complement
        for (int num : nums) {
            TrieNode current = root;
            int currentXor = 0;

            for (int i = 31; i >= 0; i--) {
                int bit = (num >> i) & 1;
                char complement = (char) ('0' + (1 - bit));

                if (current.children.containsKey(complement)) {
                    currentXor |= (1 << i);
                    current = current.children.get(complement);
                } else {
                    current = current.children.get((char) ('0' + bit));
                }
            }

            maxXor = Math.max(maxXor, currentXor);
        }

        return maxXor;
    }

    // Problem 6: Top K Frequent Words
    // Time Complexity: O(n log k)
    static List<String> topKFrequent(String[] words, int k) {
        Map<String, Integer> freqMap = new HashMap<>();
        for (String word : words) {
            freqMap.put(word, freqMap.getOrDefault(word, 0) + 1);
        }

        PriorityQueue<Map.Entry<String, Integer>> minHeap = new PriorityQueue<>(
                (a, b) -> a.getValue().equals(b.getValue()) ? b.getKey().compareTo(a.getKey())
                        : a.getValue() - b.getValue());

        for (Map.Entry<String, Integer> entry : freqMap.entrySet()) {
            minHeap.offer(entry);
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }

        List<String> result = new ArrayList<>();
        while (!minHeap.isEmpty()) {
            result.add(0, minHeap.poll().getKey());
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println("=== Core Trie Problems ===\n");

        // Test 1: Implement Trie
        System.out.println("Test 1: Implement Trie");
        ImplementTrie trie = new ImplementTrie();
        trie.insert("apple");
        System.out.println("Search 'apple': " + trie.search("apple"));
        System.out.println("Search 'app': " + trie.search("app"));
        System.out.println("StartsWith 'app': " + trie.startsWith("app"));
        trie.insert("app");
        System.out.println("Search 'app': " + trie.search("app"));
        System.out.println();

        // Test 2: Longest Common Prefix
        System.out.println("Test 2: Longest Common Prefix");
        String[] strs = { "flower", "flow", "flight" };
        System.out.println("Strings: " + Arrays.toString(strs));
        System.out.println("LCP: " + longestCommonPrefix(strs));
        System.out.println();

        // Test 3: Word Break
        System.out.println("Test 3: Word Break");
        String s = "leetcode";
        List<String> wordDict = Arrays.asList("leet", "code");
        System.out.println("String: " + s);
        System.out.println("Dictionary: " + wordDict);
        System.out.println("Can break: " + wordBreak(s, wordDict));
        System.out.println();

        // Test 4: Add and Search Word
        System.out.println("Test 4: Add and Search Word (with wildcard)");
        WordDictionary wd = new WordDictionary();
        wd.addWord("bad");
        wd.addWord("dad");
        wd.addWord("mad");
        System.out.println("Search 'pad': " + wd.search("pad"));
        System.out.println("Search 'bad': " + wd.search("bad"));
        System.out.println("Search '.ad': " + wd.search(".ad"));
        System.out.println("Search 'b..': " + wd.search("b.."));
        System.out.println();

        // Test 5: Max XOR
        System.out.println("Test 5: Maximum XOR of Two Numbers");
        int[] nums = { 3, 10, 5, 25, 2, 8 };
        System.out.println("Array: " + Arrays.toString(nums));
        System.out.println("Max XOR: " + findMaximumXOR(nums));
        System.out.println();

        // Test 6: Top K Frequent Words
        System.out.println("Test 6: Top K Frequent Words");
        String[] words = { "i", "love", "leetcode", "i", "love", "coding" };
        int k = 2;
        System.out.println("Words: " + Arrays.toString(words));
        System.out.println("Top " + k + " frequent: " + topKFrequent(words, k));
    }
}
