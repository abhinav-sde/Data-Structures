package trie;

/**
 * Basic Trie (Prefix Tree) Operations in Java
 * Also known as Digital Tree or Prefix Tree
 */

import java.util.*;

public class basic_operations {

    // Trie Node class
    static class TrieNode {
        Map<Character, TrieNode> children;
        boolean isEndOfWord;

        public TrieNode() {
            children = new HashMap<>();
            isEndOfWord = false;
        }
    }

    // Trie class
    static class Trie {
        private TrieNode root;

        public Trie() {
            root = new TrieNode();
        }

        // Insert a word into the trie
        // Time Complexity: O(m) where m is length of word
        // Space Complexity: O(m) for new nodes
        public void insert(String word) {
            TrieNode current = root;

            for (char ch : word.toCharArray()) {
                current.children.putIfAbsent(ch, new TrieNode());
                current = current.children.get(ch);
            }

            current.isEndOfWord = true;
            System.out.println("Inserted: " + word);
        }

        // Search for a complete word
        // Time Complexity: O(m)
        // Space Complexity: O(1)
        public boolean search(String word) {
            TrieNode current = root;

            for (char ch : word.toCharArray()) {
                if (!current.children.containsKey(ch)) {
                    return false;
                }
                current = current.children.get(ch);
            }

            return current.isEndOfWord;
        }

        // Check if there's any word with given prefix
        // Time Complexity: O(m)
        // Space Complexity: O(1)
        public boolean startsWith(String prefix) {
            TrieNode current = root;

            for (char ch : prefix.toCharArray()) {
                if (!current.children.containsKey(ch)) {
                    return false;
                }
                current = current.children.get(ch);
            }

            return true;
        }

        // Delete a word from the trie
        // Time Complexity: O(m)
        public boolean delete(String word) {
            return deleteHelper(root, word, 0);
        }

        private boolean deleteHelper(TrieNode current, String word, int index) {
            if (index == word.length()) {
                // Word doesn't exist
                if (!current.isEndOfWord) {
                    return false;
                }
                current.isEndOfWord = false;
                // Return true if current node has no children
                return current.children.isEmpty();
            }

            char ch = word.charAt(index);
            TrieNode node = current.children.get(ch);

            if (node == null) {
                return false;
            }

            boolean shouldDeleteCurrentNode = deleteHelper(node, word, index + 1);

            if (shouldDeleteCurrentNode) {
                current.children.remove(ch);
                // Return true if no children and not end of another word
                return current.children.isEmpty() && !current.isEndOfWord;
            }

            return false;
        }

        // Get all words in the trie
        public List<String> getAllWords() {
            List<String> words = new ArrayList<>();
            collectWords(root, new StringBuilder(), words);
            return words;
        }

        private void collectWords(TrieNode node, StringBuilder prefix, List<String> words) {
            if (node.isEndOfWord) {
                words.add(prefix.toString());
            }

            for (Map.Entry<Character, TrieNode> entry : node.children.entrySet()) {
                prefix.append(entry.getKey());
                collectWords(entry.getValue(), prefix, words);
                prefix.deleteCharAt(prefix.length() - 1);
            }
        }

        // Get all words with given prefix (autocomplete)
        public List<String> getWordsWithPrefix(String prefix) {
            List<String> words = new ArrayList<>();
            TrieNode current = root;

            // Navigate to the prefix
            for (char ch : prefix.toCharArray()) {
                if (!current.children.containsKey(ch)) {
                    return words; // No words with this prefix
                }
                current = current.children.get(ch);
            }

            // Collect all words from this point
            collectWords(current, new StringBuilder(prefix), words);
            return words;
        }

        // Count total words in trie
        public int countWords() {
            return countWordsHelper(root);
        }

        private int countWordsHelper(TrieNode node) {
            int count = node.isEndOfWord ? 1 : 0;

            for (TrieNode child : node.children.values()) {
                count += countWordsHelper(child);
            }

            return count;
        }

        // Find longest common prefix
        public String longestCommonPrefix() {
            StringBuilder prefix = new StringBuilder();
            TrieNode current = root;

            while (current.children.size() == 1 && !current.isEndOfWord) {
                Map.Entry<Character, TrieNode> entry = current.children.entrySet().iterator().next();
                prefix.append(entry.getKey());
                current = entry.getValue();
            }

            return prefix.toString();
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Trie Basic Operations Demo ===\n");

        Trie trie = new Trie();

        // Insert words
        System.out.println("--- Inserting Words ---");
        trie.insert("apple");
        trie.insert("app");
        trie.insert("application");
        trie.insert("apply");
        trie.insert("bat");
        trie.insert("batch");
        trie.insert("batman");
        System.out.println();

        // Search for words
        System.out.println("--- Searching Words ---");
        System.out.println("Search 'apple': " + trie.search("apple"));
        System.out.println("Search 'app': " + trie.search("app"));
        System.out.println("Search 'appl': " + trie.search("appl"));
        System.out.println("Search 'bat': " + trie.search("bat"));
        System.out.println("Search 'ball': " + trie.search("ball"));
        System.out.println();

        // Check prefixes
        System.out.println("--- Checking Prefixes ---");
        System.out.println("Starts with 'app': " + trie.startsWith("app"));
        System.out.println("Starts with 'appl': " + trie.startsWith("appl"));
        System.out.println("Starts with 'bat': " + trie.startsWith("bat"));
        System.out.println("Starts with 'ball': " + trie.startsWith("ball"));
        System.out.println();

        // Autocomplete
        System.out.println("--- Autocomplete (words with prefix 'app') ---");
        List<String> suggestions = trie.getWordsWithPrefix("app");
        System.out.println(suggestions);
        System.out.println();

        System.out.println("--- Autocomplete (words with prefix 'bat') ---");
        suggestions = trie.getWordsWithPrefix("bat");
        System.out.println(suggestions);
        System.out.println();

        // Get all words
        System.out.println("--- All Words in Trie ---");
        List<String> allWords = trie.getAllWords();
        System.out.println(allWords);
        System.out.println();

        // Count words
        System.out.println("--- Count Words ---");
        System.out.println("Total words: " + trie.countWords());
        System.out.println();

        // Delete word
        System.out.println("--- Deleting 'app' ---");
        trie.delete("app");
        System.out.println("Search 'app' after delete: " + trie.search("app"));
        System.out.println("Search 'apple' after delete: " + trie.search("apple"));
        System.out.println("All words: " + trie.getAllWords());
    }
}
