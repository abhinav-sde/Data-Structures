import java.util.*;

/**
 * Core Radix Tree Problems in Java
 * Focuses on deletion and prefix completion.
 */
public class core_problems {

    static class Node {
        Map<Character, Edge> children = new HashMap<>();
        boolean isEndOfWord = false;
    }

    static class Edge {
        String label;
        Node target;

        Edge(String l, Node t) {
            label = l;
            target = t;
        }
    }

    private Node root = new Node();

    public void insert(String word) {
        insert(root, word);
    }

    private void insert(Node node, String word) {
        if (word.isEmpty()) {
            node.isEndOfWord = true;
            return;
        }
        char first = word.charAt(0);
        Edge edge = node.children.get(first);
        if (edge == null) {
            node.children.put(first, new Edge(word, new Node() {
                {
                    isEndOfWord = true;
                }
            }));
            return;
        }
        int commonLen = 0;
        while (commonLen < Math.min(word.length(), edge.label.length()) &&
                word.charAt(commonLen) == edge.label.charAt(commonLen))
            commonLen++;

        if (commonLen < edge.label.length()) {
            String common = edge.label.substring(0, commonLen);
            String remEdge = edge.label.substring(commonLen);
            Node split = new Node();
            split.children.put(remEdge.charAt(0), new Edge(remEdge, edge.target));
            edge.label = common;
            edge.target = split;
        }
        if (commonLen < word.length())
            insert(edge.target, word.substring(commonLen));
        else
            edge.target.isEndOfWord = true;
    }

    public boolean delete(String word) {
        return delete(root, word);
    }

    private boolean delete(Node node, String word) {
        if (word.isEmpty()) {
            if (!node.isEndOfWord)
                return false;
            node.isEndOfWord = false;
            return true;
        }

        char first = word.charAt(0);
        Edge edge = node.children.get(first);
        if (edge == null || !word.startsWith(edge.label))
            return false;

        boolean deleted = delete(edge.target, word.substring(edge.label.length()));
        if (deleted) {
            // Case 1: Target node has no children and is not end of word
            if (edge.target.children.isEmpty() && !edge.target.isEndOfWord) {
                node.children.remove(first);
            }
            // Case 2: Target node now has only one child and is not end of word
            else if (edge.target.children.size() == 1 && !edge.target.isEndOfWord) {
                Edge onlyChildEdge = edge.target.children.values().iterator().next();
                edge.label += onlyChildEdge.label;
                edge.target = onlyChildEdge.target;
            }

            // Case 3: Current node has only one child and is not end of word
            if (node != root && node.children.size() == 1 && !node.isEndOfWord) {
                // This requires parent context or return value to merge with parent
            }
        }
        return deleted;
    }

    public List<String> getWithPrefix(String prefix) {
        List<String> results = new ArrayList<>();
        Node curr = root;
        String match = "";
        String temp = prefix;

        while (!temp.isEmpty()) {
            Edge edge = curr.children.get(temp.charAt(0));
            if (edge == null || !temp.startsWith(edge.label) && !edge.label.startsWith(temp))
                return results;
            if (temp.length() < edge.label.length()) {
                // Prefix is inside edge.label
                match += edge.label;
                curr = edge.target;
                break;
            }
            match += edge.label;
            curr = edge.target;
            temp = temp.substring(edge.label.length());
        }

        collect(curr, match, results);
        return results;
    }

    private void collect(Node node, String current, List<String> results) {
        if (node.isEndOfWord)
            results.add(current);
        for (Edge edge : node.children.values()) {
            collect(edge.target, current + edge.label, results);
        }
    }

    public static void main(String[] args) {
        core_problems radix = new core_problems();
        radix.insert("romane");
        radix.insert("romanus");
        radix.insert("romulus");
        radix.insert("rubens");

        System.out.println("Prefix 'rom': " + radix.getWithPrefix("rom"));
        System.out.println("Prefix 'ru': " + radix.getWithPrefix("ru"));

        System.out.println("Deleting 'romanus'...");
        radix.delete("romanus");
        System.out.println("Prefix 'rom' after deletion: " + radix.getWithPrefix("rom"));
    }
}
