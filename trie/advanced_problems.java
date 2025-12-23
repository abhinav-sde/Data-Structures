package trie;

/**
 * Advanced Trie Problems in Java
 * Contains complex trie-based algorithms
 */

import java.util.*;

public class advanced_problems {

    static class TrieNode {
        Map<Character, TrieNode> children = new HashMap<>();
        boolean isEndOfWord = false;
        String word = null;
    }

    // Problem 1: Word Search II - Find all words from a board
    // Time Complexity: O(m*n*4^L) where L is max word length
    static List<String> findWords(char[][] board, String[] words) {
        TrieNode root = new TrieNode();

        // Build trie with all words
        for (String word : words) {
            TrieNode current = root;
            for (char ch : word.toCharArray()) {
                current.children.putIfAbsent(ch, new TrieNode());
                current = current.children.get(ch);
            }
            current.isEndOfWord = true;
            current.word = word;
        }

        Set<String> result = new HashSet<>();

        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[0].length; j++) {
                dfs(board, i, j, root, result);
            }
        }

        return new ArrayList<>(result);
    }

    private static void dfs(char[][] board, int i, int j, TrieNode node, Set<String> result) {
        if (i < 0 || i >= board.length || j < 0 || j >= board[0].length)
            return;

        char ch = board[i][j];
        if (ch == '#' || !node.children.containsKey(ch))
            return;

        TrieNode next = node.children.get(ch);
        if (next.isEndOfWord) {
            result.add(next.word);
        }

        board[i][j] = '#'; // Mark visited
        dfs(board, i + 1, j, next, result);
        dfs(board, i - 1, j, next, result);
        dfs(board, i, j + 1, next, result);
        dfs(board, i, j - 1, next, result);
        board[i][j] = ch; // Restore
    }

    // Problem 2: Replace Words (dictionary compression)
    // Time Complexity: O(N) where N is total characters
    static String replaceWords(List<String> dictionary, String sentence) {
        TrieNode root = new TrieNode();

        // Build trie
        for (String word : dictionary) {
            TrieNode current = root;
            for (char ch : word.toCharArray()) {
                current.children.putIfAbsent(ch, new TrieNode());
                current = current.children.get(ch);
            }
            current.isEndOfWord = true;
        }

        StringBuilder result = new StringBuilder();
        String[] words = sentence.split(" ");

        for (String word : words) {
            if (result.length() > 0)
                result.append(" ");

            TrieNode current = root;
            StringBuilder prefix = new StringBuilder();

            for (char ch : word.toCharArray()) {
                if (current.isEndOfWord)
                    break;
                if (!current.children.containsKey(ch)) {
                    prefix = new StringBuilder(word);
                    break;
                }
                prefix.append(ch);
                current = current.children.get(ch);
            }

            result.append(prefix.length() > 0 ? prefix.toString() : word);
        }

        return result.toString();
    }

    // Problem 3: Stream of Characters
    static class StreamChecker {
        private TrieNode root;
        private StringBuilder stream;

        public StreamChecker(String[] words) {
            root = new TrieNode();
            stream = new StringBuilder();

            // Insert words in reverse
            for (String word : words) {
                TrieNode current = root;
                for (int i = word.length() - 1; i >= 0; i--) {
                    char ch = word.charAt(i);
                    current.children.putIfAbsent(ch, new TrieNode());
                    current = current.children.get(ch);
                }
                current.isEndOfWord = true;
            }
        }

        public boolean query(char letter) {
            stream.append(letter);

            TrieNode current = root;
            for (int i = stream.length() - 1; i >= 0; i--) {
                char ch = stream.charAt(i);
                if (!current.children.containsKey(ch)) {
                    return false;
                }
                current = current.children.get(ch);
                if (current.isEndOfWord) {
                    return true;
                }
            }

            return false;
        }
    }

    // Problem 4: Palindrome Pairs
    // Time Complexity: O(n * k^2) where k is max word length
    static List<List<Integer>> palindromePairs(String[] words) {
        List<List<Integer>> result = new ArrayList<>();
        if (words == null || words.length == 0)
            return result;

        Map<String, Integer> wordMap = new HashMap<>();
        for (int i = 0; i < words.length; i++) {
            wordMap.put(words[i], i);
        }

        for (int i = 0; i < words.length; i++) {
            String word = words[i];

            for (int j = 0; j <= word.length(); j++) {
                String left = word.substring(0, j);
                String right = word.substring(j);

                if (isPalindrome(left)) {
                    String rightRev = new StringBuilder(right).reverse().toString();
                    if (wordMap.containsKey(rightRev) && wordMap.get(rightRev) != i) {
                        result.add(Arrays.asList(wordMap.get(rightRev), i));
                    }
                }

                if (right.length() > 0 && isPalindrome(right)) {
                    String leftRev = new StringBuilder(left).reverse().toString();
                    if (wordMap.containsKey(leftRev) && wordMap.get(leftRev) != i) {
                        result.add(Arrays.asList(i, wordMap.get(leftRev)));
                    }
                }
            }
        }

        return result;
    }

    private static boolean isPalindrome(String s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (s.charAt(left++) != s.charAt(right--))
                return false;
        }
        return true;
    }

    // Problem 5: Design Search Autocomplete System
    static class AutocompleteSystem {
        private TrieNode root;
        private TrieNode current;
        private StringBuilder currentInput;

        class TrieNode {
            Map<Character, TrieNode> children = new HashMap<>();
            Map<String, Integer> sentences = new HashMap<>();
        }

        public AutocompleteSystem(String[] sentences, int[] times) {
            root = new TrieNode();
            current = root;
            currentInput = new StringBuilder();

            for (int i = 0; i < sentences.length; i++) {
                insert(sentences[i], times[i]);
            }
        }

        private void insert(String sentence, int count) {
            TrieNode node = root;
            for (char ch : sentence.toCharArray()) {
                node.children.putIfAbsent(ch, new TrieNode());
                node = node.children.get(ch);
                node.sentences.put(sentence, node.sentences.getOrDefault(sentence, 0) + count);
            }
        }

        public List<String> input(char c) {
            if (c == '#') {
                insert(currentInput.toString(), 1);
                currentInput = new StringBuilder();
                current = root;
                return new ArrayList<>();
            }

            currentInput.append(c);

            if (current != null) {
                current = current.children.get(c);
            }

            if (current == null) {
                return new ArrayList<>();
            }

            // Get top 3
            PriorityQueue<Map.Entry<String, Integer>> pq = new PriorityQueue<>(
                    (a, b) -> a.getValue().equals(b.getValue()) ? a.getKey().compareTo(b.getKey())
                            : b.getValue() - a.getValue());

            pq.addAll(current.sentences.entrySet());

            List<String> result = new ArrayList<>();
            for (int i = 0; i < 3 && !pq.isEmpty(); i++) {
                result.add(pq.poll().getKey());
            }

            return result;
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Advanced Trie Problems ===\n");

        // Test 1: Word Search II
        System.out.println("Test 1: Word Search II");
        char[][] board = {
                { 'o', 'a', 'a', 'n' },
                { 'e', 't', 'a', 'e' },
                { 'i', 'h', 'k', 'r' },
                { 'i', 'f', 'l', 'v' }
        };
        String[] words = { "oath", "pea", "eat", "rain" };
        System.out.println("Found words: " + findWords(board, words));
        System.out.println();

        // Test 2: Replace Words
        System.out.println("Test 2: Replace Words");
        List<String> dictionary = Arrays.asList("cat", "bat", "rat");
        String sentence = "the cattle was rattled by the battery";
        System.out.println("Original: " + sentence);
        System.out.println("Replaced: " + replaceWords(dictionary, sentence));
        System.out.println();

        // Test 3: Stream Checker
        System.out.println("Test 3: Stream of Characters");
        StreamChecker sc = new StreamChecker(new String[] { "cd", "f", "kl" });
        System.out.println("Query 'a': " + sc.query('a'));
        System.out.println("Query 'b': " + sc.query('b'));
        System.out.println("Query 'c': " + sc.query('c'));
        System.out.println("Query 'd': " + sc.query('d'));
        System.out.println();

        // Test 4: Palindrome Pairs
        System.out.println("Test 4: Palindrome Pairs");
        String[] palindromeWords = { "abcd", "dcba", "lls", "s", "sssll" };
        System.out.println("Words: " + Arrays.toString(palindromeWords));
        System.out.println("Pairs: " + palindromePairs(palindromeWords));
        System.out.println();

        // Test 5: Autocomplete
        System.out.println("Test 5: Search Autocomplete System");
        AutocompleteSystem ac = new AutocompleteSystem(
                new String[] { "i love you", "island", "iroman", "i love leetcode" },
                new int[] { 5, 3, 2, 2 });
        System.out.println("Input 'i': " + ac.input('i'));
        System.out.println("Input ' ': " + ac.input(' '));
        System.out.println("Input 'a': " + ac.input('a'));
        System.out.println("Input '#': " + ac.input('#'));
    }
}
