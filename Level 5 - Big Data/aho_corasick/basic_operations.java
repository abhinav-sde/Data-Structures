package aho_corasick;

import java.util.*;

/**
 * Basic Aho-Corasick Implementation
 * Efficiently finds all occurrences of multiple patterns in a text.
 */
public class basic_operations {

    static class Node {
        Map<Character, Node> children = new HashMap<>();
        Node fail;
        List<Integer> patternIndices = new ArrayList<>();
    }

    static class AhoCorasick {
        private Node root;

        public AhoCorasick(String[] patterns) {
            root = new Node();
            buildTrie(patterns);
            buildFailLinks();
        }

        private void buildTrie(String[] patterns) {
            for (int i = 0; i < patterns.length; i++) {
                Node curr = root;
                for (char c : patterns[i].toCharArray()) {
                    curr = curr.children.computeIfAbsent(c, k -> new Node());
                }
                curr.patternIndices.add(i);
            }
        }

        private void buildFailLinks() {
            Queue<Node> queue = new LinkedList<>();
            for (Node child : root.children.values()) {
                child.fail = root;
                queue.add(child);
            }

            while (!queue.isEmpty()) {
                Node u = queue.poll();
                for (Map.Entry<Character, Node> entry : u.children.entrySet()) {
                    char c = entry.getKey();
                    Node v = entry.getValue();
                    Node f = u.fail;
                    while (f != null && !f.children.containsKey(c)) {
                        f = f.fail;
                    }
                    v.fail = (f == null) ? root : f.children.get(c);
                    v.patternIndices.addAll(v.fail.patternIndices);
                    queue.add(v);
                }
            }
        }

        public void search(String text, String[] patterns) {
            Node curr = root;
            for (int i = 0; i < text.length(); i++) {
                char c = text.charAt(i);
                while (curr != root && !curr.children.containsKey(c)) {
                    curr = curr.fail;
                }
                curr = curr.children.getOrDefault(c, root);
                for (int idx : curr.patternIndices) {
                    System.out.println(
                            "Pattern \"" + patterns[idx] + "\" found at index " + (i - patterns[idx].length() + 1));
                }
            }
        }
    }

    public static void main(String[] args) {
        String[] patterns = { "he", "she", "hers", "his" };
        String text = "ahishers";
        AhoCorasick ac = new AhoCorasick(patterns);
        ac.search(text, patterns);
    }
}
