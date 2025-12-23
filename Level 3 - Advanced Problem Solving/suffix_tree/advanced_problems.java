import java.util.*;

/**
 * Advanced Suffix Tree Problems in Java
 * Implements Longest Common Substring of two strings using a Generalized Suffix
 * Tree.
 */
public class advanced_problems {

    static class Node {
        Map<Character, Node> children = new HashMap<>();
        int start, end, depth;
        BitSet sources = new BitSet(2); // Tracks which strings have suffixes passing through this node

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

    public advanced_problems(String s1, String s2) {
        // Use distinct terminators for generalized suffix tree
        this.text = s1 + "#" + s2 + "$";
        this.root = new Node(-1, -1, 0);
        build(s1.length());
    }

    private void build(int s1Len) {
        for (int i = 0; i < text.length(); i++) {
            insertSuffix(i, i <= s1Len ? 0 : 1);
        }
    }

    private void insertSuffix(int suffixStart, int sourceIdx) {
        Node curr = root;
        curr.sources.set(sourceIdx);
        int i = suffixStart;
        while (i < text.length()) {
            char first = text.charAt(i);
            Node next = curr.children.get(first);
            if (next == null) {
                Node leaf = new Node(i, text.length() - 1, curr.depth + (text.length() - i));
                leaf.sources.set(sourceIdx);
                curr.children.put(first, leaf);
                return;
            }
            next.sources.set(sourceIdx);
            int j = 0, labelLen = next.length();
            while (j < labelLen && i < text.length() && text.charAt(next.start + j) == text.charAt(i)) {
                i++;
                j++;
            }
            if (j == labelLen) {
                curr = next;
            } else {
                Node split = new Node(next.start, next.start + j - 1, curr.depth + j);
                split.sources.set(0, 2); // Split node inherits source info later, simplified here
                next.start += j;
                curr.children.put(text.charAt(split.start), split);
                split.children.put(text.charAt(next.start), next);
                Node leaf = new Node(i, text.length() - 1, split.depth + (text.length() - i));
                leaf.sources.set(sourceIdx);
                split.children.put(text.charAt(i), leaf);
                propagateSources(split); // Ensure split node reflects its leaves
                return;
            }
        }
    }

    private void propagateSources(Node node) {
        for (Node child : node.children.values()) {
            node.sources.or(child.sources);
        }
    }

    private String lcs = "";

    public String findLongestCommonSubstring() {
        lcs = "";
        updateSources(root);
        dfsLCS(root, 0);
        return lcs;
    }

    private void updateSources(Node node) {
        for (Node child : node.children.values()) {
            updateSources(child);
            node.sources.or(child.sources);
        }
    }

    private void dfsLCS(Node node, int pathLen) {
        if (node.sources.cardinality() == 2) {
            if (pathLen > lcs.length()) {
                Node leaf = findAnyLeaf(node);
                int start = leaf.end - leaf.depth + 1;
                String candidate = text.substring(start, start + pathLen);
                if (!candidate.contains("#") && !candidate.contains("$"))
                    lcs = candidate;
            }
        }
        for (Node child : node.children.values()) {
            dfsLCS(child, pathLen + child.length());
        }
    }

    private Node findAnyLeaf(Node node) {
        if (node.children.isEmpty())
            return node;
        return findAnyLeaf(node.children.values().iterator().next());
    }

    public static void main(String[] args) {
        String s1 = "geeksforgeeks";
        String s2 = "quizgeeks";
        advanced_problems cp = new advanced_problems(s1, s2);
        System.out.println("S1: " + s1 + ", S2: " + s2);
        System.out.println("Longest Common Substring: " + cp.findLongestCommonSubstring());
    }
}
