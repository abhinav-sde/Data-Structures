import java.util.*;

/**
 * Core Suffix Tree Problems in Java
 * Focuses on Longest Repeated Substring and Pattern Counting.
 */
public class core_problems {

    static class Node {
        Map<Character, Node> children = new HashMap<>();
        int start, end;
        int depth; // Path length from root to this node

        Node(int start, int end, int depth) {
            this.start = start;
            this.end = end;
            this.depth = depth;
        }

        int length() {
            return end - start + 1;
        }
    }

    private String text;
    private Node root;

    public core_problems(String text) {
        this.text = text + "$";
        this.root = new Node(-1, -1, 0);
        build();
    }

    private void build() {
        for (int i = 0; i < text.length(); i++)
            insertSuffix(i);
    }

    private void insertSuffix(int suffixStart) {
        Node curr = root;
        int i = suffixStart;
        while (i < text.length()) {
            char first = text.charAt(i);
            Node next = curr.children.get(first);
            if (next == null) {
                curr.children.put(first, new Node(i, text.length() - 1, curr.depth + (text.length() - i)));
                return;
            }
            int j = 0, labelLen = next.length();
            while (j < labelLen && i < text.length() && text.charAt(next.start + j) == text.charAt(i)) {
                i++;
                j++;
            }
            if (j == labelLen) {
                curr = next;
            } else {
                Node split = new Node(next.start, next.start + j - 1, curr.depth + j);
                next.start += j;
                curr.children.put(text.charAt(split.start), split);
                split.children.put(text.charAt(next.start), next);
                split.children.put(text.charAt(i), new Node(i, text.length() - 1, split.depth + (text.length() - i)));
                return;
            }
        }
    }

    // Problem 1: Longest Repeated Substring
    private String maxRepeated = "";

    public String findLongestRepeatedSubstring() {
        maxRepeated = "";
        dfs(root, 0);
        return maxRepeated;
    }

    private void dfs(Node node, int pathLen) {
        if (node.children.size() >= 2) {
            // Internal node representing a repeated substring
            if (pathLen > maxRepeated.length()) {
                // Find any leaf to get original string index
                Node anyLeaf = findAnyLeaf(node);
                int start = anyLeaf.end - anyLeaf.depth + 1;
                String candidate = text.substring(start, start + pathLen);
                if (!candidate.contains("$"))
                    maxRepeated = candidate;
            }
        }
        for (Node child : node.children.values()) {
            dfs(child, pathLen + child.length());
        }
    }

    private Node findAnyLeaf(Node node) {
        if (node.children.isEmpty())
            return node;
        return findAnyLeaf(node.children.values().iterator().next());
    }

    // Problem 2: Count Occurrences
    public int countOccurrences(String pattern) {
        Node curr = root;
        int i = 0;
        while (i < pattern.length()) {
            char first = pattern.charAt(i);
            Node next = curr.children.get(first);
            if (next == null)
                return 0;
            int j = 0;
            while (j < next.length() && i < pattern.length()) {
                if (text.charAt(next.start + j) != pattern.charAt(i))
                    return 0;
                i++;
                j++;
            }
            curr = next;
        }
        return countLeaves(curr);
    }

    private int countLeaves(Node node) {
        if (node.children.isEmpty())
            return 1;
        int count = 0;
        for (Node child : node.children.values())
            count += countLeaves(child);
        return count;
    }

    public static void main(String[] args) {
        String text = "banana";
        core_problems cp = new core_problems(text);
        System.out.println("Longest Repeated Substring in 'banana': " + cp.findLongestRepeatedSubstring());
        System.out.println("Occurrences of 'ana': " + cp.countOccurrences("ana"));
        System.out.println("Occurrences of 'a': " + cp.countOccurrences("a"));
    }
}
