/**
 * Trie (Prefix Tree) Operations in Java
 * Contains Trie implementation and algorithms
 */

import java.util.*;

public class trie {
    
    // ========================================
    // TRIE NODE STRUCTURE
    // ========================================
    static class TrieNode {
        TrieNode[] children;
        boolean isEndOfWord;
        int wordCount;
        
        TrieNode() {
            children = new TrieNode[26];
            isEndOfWord = false;
            wordCount = 0;
            // Arrays in Java are initialized to null by default
        }
    }
    
    // ========================================
    // TRIE CLASS Implementation
    // ========================================
    static class TrieClass {
        private TrieNode root;
        
        public TrieClass() {
            root = new TrieNode();
        }
        
        // ========================================
        // 1. INSERT WORD
        // ========================================
        public void insert(String word) {
            TrieNode current = root;
            
            for (char ch : word.toCharArray()) {
                int index = ch - 'a';
                
                if (current.children[index] == null) {
                    current.children[index] = new TrieNode();
                }
                
                current = current.children[index];
            }
            
            current.isEndOfWord = true;
            current.wordCount++;
            System.out.println("Inserted: " + word);
        }
        
        // ========================================
        // 2. SEARCH WORD
        // ========================================
        public boolean search(String word) {
            TrieNode current = root;
            
            for (char ch : word.toCharArray()) {
                int index = ch - 'a';
                
                if (current.children[index] == null) {
                    return false;
                }
                
                current = current.children[index];
            }
            
            return current.isEndOfWord;
        }
        
        // ========================================
        // 3. STARTS WITH (PREFIX SEARCH)
        // ========================================
        public boolean startsWith(String prefix) {
            TrieNode current = root;
            
            for (char ch : prefix.toCharArray()) {
                int index = ch - 'a';
                
                if (current.children[index] == null) {
                    return false;
                }
                
                current = current.children[index];
            }
            
            return true;
        }
        
        // ========================================
        // 4. DELETE WORD
        // ========================================
        private boolean deleteWordHelper(TrieNode current, String word, int index) {
            if (index == word.length()) {
                if (!current.isEndOfWord) {
                    return false;
                }
                
                current.isEndOfWord = false;
                current.wordCount = 0;
                
                for (int i = 0; i < 26; i++) {
                    if (current.children[i] != null) {
                        return false;
                    }
                }
                
                return true;
            }
            
            int charIndex = word.charAt(index) - 'a';
            TrieNode node = current.children[charIndex];
            
            if (node == null) {
                return false;
            }
            
            boolean shouldDeleteChild = deleteWordHelper(node, word, index + 1);
            
            if (shouldDeleteChild) {
                current.children[charIndex] = null; // Delete reference
                
                if (!current.isEndOfWord) {
                    for (int i = 0; i < 26; i++) {
                        if (current.children[i] != null) {
                            return false;
                        }
                    }
                    return true;
                }
            }
            
            return false;
        }
        
        public void deleteWord(String word) {
            if (deleteWordHelper(root, word, 0)) {
                System.out.println("Deleted: " + word);
            } else {
                System.out.println("Word not found: " + word);
            }
        }
        
        // ========================================
        // 5. COUNT WORDS WITH PREFIX
        // ========================================
        private int countWordsHelper(TrieNode node) {
            if (node == null) return 0;
            
            int count = node.isEndOfWord ? 1 : 0;
            
            for (int i = 0; i < 26; i++) {
                count += countWordsHelper(node.children[i]);
            }
            
            return count;
        }
        
        public int countWordsWithPrefix(String prefix) {
            TrieNode current = root;
            
            for (char ch : prefix.toCharArray()) {
                int index = ch - 'a';
                
                if (current.children[index] == null) {
                    return 0;
                }
                
                current = current.children[index];
            }
            
            return countWordsHelper(current);
        }
        
        // ========================================
        // 6. GET ALL WORDS WITH PREFIX (AUTOCOMPLETE)
        // ========================================
        private void getAllWordsHelper(TrieNode node, String current, List<String> words) {
            if (node == null) return;
            
            if (node.isEndOfWord) {
                words.add(current);
            }
            
            for (int i = 0; i < 26; i++) {
                if (node.children[i] != null) {
                    getAllWordsHelper(node.children[i], current + (char)('a' + i), words);
                }
            }
        }
        
        public List<String> autocomplete(String prefix) {
            List<String> words = new ArrayList<>();
            TrieNode current = root;
            
            for (char ch : prefix.toCharArray()) {
                int index = ch - 'a';
                
                if (current.children[index] == null) {
                    return words;
                }
                
                current = current.children[index];
            }
            
            getAllWordsHelper(current, prefix, words);
            return words;
        }
        
        // ========================================
        // 7. LONGEST COMMON PREFIX
        // ========================================
        public String longestCommonPrefix() {
            StringBuilder prefix = new StringBuilder();
            TrieNode current = root;
            
            while (true) {
                int childCount = 0;
                int childIndex = -1;
                
                for (int i = 0; i < 26; i++) {
                    if (current.children[i] != null) {
                        childCount++;
                        childIndex = i;
                    }
                }
                
                if (childCount != 1 || current.isEndOfWord) {
                    break;
                }
                
                prefix.append((char)('a' + childIndex));
                current = current.children[childIndex];
            }
            
            return prefix.toString();
        }
        
        // ========================================
        // 8. PRINT ALL WORDS
        // ========================================
        private void printAllWordsHelper(TrieNode node, String current) {
            if (node == null) return;
            
            if (node.isEndOfWord) {
                System.out.print(current + " ");
            }
            
            for (int i = 0; i < 26; i++) {
                if (node.children[i] != null) {
                    printAllWordsHelper(node.children[i], current + (char)('a' + i));
                }
            }
        }
        
        public void printAllWords() {
            System.out.print("All words: ");
            printAllWordsHelper(root, "");
            System.out.println();
        }
        
        // ========================================
        // 9. COUNT TOTAL WORDS
        // ========================================
        public int countTotalWords() {
            return countWordsHelper(root);
        }
        
        // ========================================
        // 10. WORD FREQUENCY
        // ========================================
        public int getWordFrequency(String word) {
            TrieNode current = root;
            
            for (char ch : word.toCharArray()) {
                int index = ch - 'a';
                
                if (current.children[index] == null) {
                    return 0;
                }
                
                current = current.children[index];
            }
            
            return current.isEndOfWord ? current.wordCount : 0;
        }
    }
    
    // ========================================
    // ADDITIONAL TRIE PROBLEMS
    // ========================================
    
    // Word Break Problem
    static boolean wordBreakHelper(String s, int start, TrieClass trie, Boolean[] memo) {
        if (start == s.length()) return true;
        
        if (memo[start] != null) return memo[start];
        
        for (int end = start + 1; end <= s.length(); end++) {
            String word = s.substring(start, end);
            
            if (trie.search(word) && wordBreakHelper(s, end, trie, memo)) {
                return memo[start] = true;
            }
        }
        
        return memo[start] = false;
    }
    
    static boolean wordBreak(String s, List<String> wordDict) {
        TrieClass trie = new TrieClass();
        for (String word : wordDict) {
            trie.insert(word);
        }
        
        Boolean[] memo = new Boolean[s.length()];
        return wordBreakHelper(s, 0, trie, memo);
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        TrieClass trie = new TrieClass();
        
        System.out.println("=== Trie Operations ===");
        
        // Example usage - uncomment to use
        
        // Insert words
        // trie.insert("apple");
        // trie.insert("app");
        // trie.insert("application");
        // trie.insert("apply");
        // trie.insert("banana");
        // trie.insert("band");
        
        // Search
        // System.out.println("Search 'apple': " + (trie.search("apple") ? "Found" : "Not found"));
        // System.out.println("Search 'appl': " + (trie.search("appl") ? "Found" : "Not found"));
        
        // Starts with (prefix)
        // System.out.println("Starts with 'app': " + (trie.startsWith("app") ? "Yes" : "No"));
        // System.out.println("Starts with 'ban': " + (trie.startsWith("ban") ? "Yes" : "No"));
        
        // Count words with prefix
        // System.out.println("Words with prefix 'app': " + trie.countWordsWithPrefix("app"));
        
        // Autocomplete
        // List<String> suggestions = trie.autocomplete("app");
        // System.out.print("Autocomplete 'app': ");
        // for (String word : suggestions) {
        //     System.out.print(word + " ");
        // }
        // System.out.println();
        
        // Print all words
        // trie.printAllWords();
        
        // Count total words
        // System.out.println("Total words: " + trie.countTotalWords());
        
        // Longest common prefix
        // System.out.println("Longest common prefix: " + trie.longestCommonPrefix());
        
        // Delete word
        // trie.deleteWord("app");
        // trie.printAllWords();
        
        // Word frequency
        // trie.insert("apple");  // Insert again
        // System.out.println("Frequency of 'apple': " + trie.getWordFrequency("apple"));
    }
}
