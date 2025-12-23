
import java.util.*;

/**
 * Interval Tree Implementation
 * Efficiently finds all intervals that overlap with a given query interval.
 * Used in scheduling, calendar systems, and genomics.
 */
public class basic_operations {

    static class Interval {
        int low, high;

        Interval(int low, int high) {
            this.low = low;
            this.high = high;
        }

        boolean overlaps(Interval other) {
            return this.low <= other.high && other.low <= this.high;
        }

        @Override
        public String toString() {
            return "[" + low + ", " + high + "]";
        }
    }

    static class Node {
        Interval interval;
        int max; // Maximum high value in subtree
        Node left, right;

        Node(Interval interval) {
            this.interval = interval;
            this.max = interval.high;
        }
    }

    static class IntervalTree {
        private Node root;

        public void insert(Interval interval) {
            root = insert(root, interval);
        }

        private Node insert(Node node, Interval interval) {
            if (node == null)
                return new Node(interval);

            int low = node.interval.low;
            if (interval.low < low) {
                node.left = insert(node.left, interval);
            } else {
                node.right = insert(node.right, interval);
            }

            // Update max
            if (node.max < interval.high) {
                node.max = interval.high;
            }

            return node;
        }

        public List<Interval> searchOverlap(Interval query) {
            List<Interval> result = new ArrayList<>();
            searchOverlap(root, query, result);
            return result;
        }

        private void searchOverlap(Node node, Interval query, List<Interval> result) {
            if (node == null)
                return;

            // Check current interval
            if (node.interval.overlaps(query)) {
                result.add(node.interval);
            }

            // If left subtree can have overlaps, search it
            if (node.left != null && node.left.max >= query.low) {
                searchOverlap(node.left, query, result);
            }

            // Search right subtree
            searchOverlap(node.right, query, result);
        }

        public void display() {
            display(root, "", true);
        }

        private void display(Node node, String indent, boolean last) {
            if (node != null) {
                System.out.print(indent);
                if (last) {
                    System.out.print("R----");
                    indent += "   ";
                } else {
                    System.out.print("L----");
                    indent += "|  ";
                }
                System.out.println(node.interval + " (max=" + node.max + ")");
                display(node.left, indent, false);
                display(node.right, indent, true);
            }
        }
    }

    public static void main(String[] args) {
        IntervalTree tree = new IntervalTree();
        tree.insert(new Interval(15, 20));
        tree.insert(new Interval(10, 30));
        tree.insert(new Interval(17, 19));
        tree.insert(new Interval(5, 20));
        tree.insert(new Interval(12, 15));
        tree.insert(new Interval(30, 40));

        System.out.println("Interval Tree:");
        tree.display();

        Interval query = new Interval(14, 16);
        System.out.println("\nSearching for overlaps with " + query + ":");
        List<Interval> overlaps = tree.searchOverlap(query);
        for (Interval i : overlaps) {
            System.out.println(i);
        }
    }
}
