package skip_list;

/**
 * Basic Skip List Operations
 * Probabilistic data structure for fast search
 */

import java.util.*;

public class basic_operations {

    static class Node {
        int value;
        Node[] forward;

        Node(int value, int level) {
            this.value = value;
            this.forward = new Node[level + 1];
        }
    }

    static class SkipList {
        private static final int MAX_LEVEL = 16;
        private static final double P = 0.5;
        private Node header;
        private int level;
        private Random random;

        public SkipList() {
            header = new Node(Integer.MIN_VALUE, MAX_LEVEL);
            level = 0;
            random = new Random();
        }

        private int randomLevel() {
            int lvl = 0;
            while (lvl < MAX_LEVEL && random.nextDouble() < P) {
                lvl++;
            }
            return lvl;
        }

        public boolean search(int target) {
            Node current = header;

            for (int i = level; i >= 0; i--) {
                while (current.forward[i] != null && current.forward[i].value < target) {
                    current = current.forward[i];
                }
            }

            current = current.forward[0];
            return current != null && current.value == target;
        }

        public void insert(int value) {
            Node[] update = new Node[MAX_LEVEL + 1];
            Node current = header;

            for (int i = level; i >= 0; i--) {
                while (current.forward[i] != null && current.forward[i].value < value) {
                    current = current.forward[i];
                }
                update[i] = current;
            }

            current = current.forward[0];

            if (current == null || current.value != value) {
                int newLevel = randomLevel();

                if (newLevel > level) {
                    for (int i = level + 1; i <= newLevel; i++) {
                        update[i] = header;
                    }
                    level = newLevel;
                }

                Node newNode = new Node(value, newLevel);

                for (int i = 0; i <= newLevel; i++) {
                    newNode.forward[i] = update[i].forward[i];
                    update[i].forward[i] = newNode;
                }

                System.out.println("Inserted: " + value);
            }
        }

        public void display() {
            System.out.println("Skip List:");
            for (int i = 0; i <= level; i++) {
                Node node = header.forward[i];
                System.out.print("Level " + i + ": ");
                while (node != null) {
                    System.out.print(node.value + " ");
                    node = node.forward[i];
                }
                System.out.println();
            }
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Skip List Demo ===\n");

        SkipList sl = new SkipList();

        int[] values = { 3, 6, 7, 9, 12, 19, 17, 26, 21, 25 };
        for (int v : values) {
            sl.insert(v);
        }

        sl.display();

        System.out.println("\nSearch 19: " + sl.search(19));
        System.out.println("Search 15: " + sl.search(15));
    }
}
