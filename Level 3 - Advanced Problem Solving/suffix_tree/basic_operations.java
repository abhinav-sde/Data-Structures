import java.util.*;

/**
 * Basic Suffix Tree Operations in Java
 * Implements construction and substring search.
 * This is a simplified compressed trie implementation.
 */
public class basic_operations {

    static class Node {
        Map<Character, Edge> children = new HashMap<>();
        int start, end; // Indices in the original string for this edge's label

        Node(int start, int end) {
            this.start = start;
            this.end = end;
        }

        int length() {
            return end - start + 1;
        }
    }

    static class Edge {
        Node target;

        Edge(Node t) {
            target = t;
        }
    }

    private String text;
    private Node root;

    public basic_operations(String text) {
        this.text = text + "$"; // Unique terminator
        this.root = new Node(-1, -1);
        build();
    }

    private void build() {
        for (int i = 0; i < text.length(); i++) {
            insertSuffix(i);
        }
    }

    private void insertSuffix(int suffixStart) {
        Node curr = root;
        int i = suffixStart;

        while (i < text.length()) {
            char firstChar = text.charAt(i);
            Edge edge = curr.children.get(firstChar);

            if (edge == null) {
                // New branch
                curr.children.put(firstChar, new Edge(new Node(i, text.length() - 1)));
                return;
            }

            Node nextNode = edge.target;
            int labelLen = nextNode.length();
            int j = 0;

            // Match along the edge
            while (j < labelLen && i < text.length() && text.charAt(nextNode.start + j) == text.charAt(i)) {
                i++;
                j++;
            }

            if (j == labelLen) {
                // Fully matched edge, continue from next node
                curr = nextNode;
            } else {
                // Partial match, split the edge
                Node splitNode = new Node(nextNode.start, nextNode.start + j - 1);
                nextNode.start += j;

                curr.children.put(text.charAt(splitNode.start), new Edge(splitNode));
                splitNode.children.put(text.charAt(nextNode.start), new Edge(nextNode));

                // Add the remainder of the suffix
                splitNode.children.put(text.charAt(i), new Edge(new Node(i, text.length() - 1)));
                return;
            }
        }
    }

    public boolean contains(String pattern) {
        Node curr = root;
        int i = 0;

        while (i < pattern.length()) {
            char firstChar = pattern.charAt(i);
            Edge edge = curr.children.get(firstChar);

            if (edge == null)
                return false;

            Node nextNode = edge.target;
            int j = 0;
            while (j < nextNode.length() && i < pattern.length()) {
                if (text.charAt(nextNode.start + j) != pattern.charAt(i))
                    return false;
                i++;
                j++;
            }
            curr = nextNode;
        }
        return true;
    }

    public static void main(String[] args) {
        String text = "banana";
        basic_operations st = new basic_operations(text);

        System.out.println("Text: " + text);
        System.out.println("Contains 'nan': " + st.contains("nan"));
        System.out.println("Contains 'ana': " + st.contains("ana"));
        System.out.println("Contains 'ban': " + st.contains("ban"));
        System.out.println("Contains 'apple': " + st.contains("apple"));
    }
}
