import java.util.*;

/**
 * Basic Radix Tree (Compressed Trie) Operations in Java
 * Implements insertion and search with path compression.
 */
public class basic_operations {

    static class Node {
        Map<Character, Edge> children;
        boolean isEndOfWord;

        Node() {
            children = new HashMap<>();
            isEndOfWord = false;
        }
    }

    static class Edge {
        String label;
        Node target;

        Edge(String label, Node target) {
            this.label = label;
            this.target = target;
        }
    }

    private Node root;

    public basic_operations() {
        root = new Node();
    }

    public void insert(String word) {
        insert(root, word);
    }

    private void insert(Node node, String word) {
        if (word.isEmpty()) {
            node.isEndOfWord = true;
            return;
        }

        char firstChar = word.charAt(0);
        Edge edge = node.children.get(firstChar);

        if (edge == null) {
            // No edge exists, create a new one
            node.children.put(firstChar, new Edge(word, new Node() {
                {
                    isEndOfWord = true;
                }
            }));
            return;
        }

        // Shared prefix length
        int commonLen = 0;
        int maxLen = Math.min(word.length(), edge.label.length());
        while (commonLen < maxLen && word.charAt(commonLen) == edge.label.charAt(commonLen)) {
            commonLen++;
        }

        if (commonLen < edge.label.length()) {
            // Split existing edge
            String commonPart = edge.label.substring(0, commonLen);
            String remainingEdgePart = edge.label.substring(commonLen);

            Node splitNode = new Node();
            splitNode.children.put(remainingEdgePart.charAt(0), new Edge(remainingEdgePart, edge.target));

            edge.label = commonPart;
            edge.target = splitNode;
        }

        if (commonLen < word.length()) {
            // Continue insertion with remaining word
            insert(edge.target, word.substring(commonLen));
        } else {
            // Word exactly matches prefix path
            edge.target.isEndOfWord = true;
        }
    }

    public boolean search(String word) {
        return search(root, word);
    }

    private boolean search(Node node, String word) {
        if (word.isEmpty())
            return node.isEndOfWord;

        char firstChar = word.charAt(0);
        Edge edge = node.children.get(firstChar);

        if (edge == null)
            return false;

        if (word.startsWith(edge.label)) {
            return search(edge.target, word.substring(edge.label.length()));
        }

        return false;
    }

    public static void main(String[] args) {
        basic_operations radix = new basic_operations();
        String[] words = { "apple", "app", "apricot", "banana", "band" };

        System.out.println("Inserting: apple, app, apricot, banana, band");
        for (String w : words)
            radix.insert(w);

        System.out.println("Search 'apple': " + radix.search("apple"));
        System.out.println("Search 'app': " + radix.search("app"));
        System.out.println("Search 'apri': " + radix.search("apri"));
        System.out.println("Search 'apricot': " + radix.search("apricot"));
        System.out.println("Search 'band': " + radix.search("band"));
        System.out.println("Search 'balloon': " + radix.search("balloon"));
    }
}
