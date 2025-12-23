import java.util.*;

/**
 * Basic Fibonacci Heap Operations in Java
 * Implements a min-priority queue with efficient amortized O(1) decrease-key.
 */
public class basic_operations {

    static class Node {
        int key;
        int degree;
        boolean mark;
        Node parent, child, left, right;

        Node(int key) {
            this.key = key;
            this.degree = 0;
            this.mark = false;
            this.left = this.right = this;
        }
    }

    private Node min;
    private int n;

    public basic_operations() {
        min = null;
        n = 0;
    }

    public void insert(int key) {
        Node node = new Node(key);
        if (min == null) {
            min = node;
        } else {
            addToRootList(node);
            if (key < min.key)
                min = node;
        }
        n++;
    }

    public int getMin() {
        if (min == null)
            throw new NoSuchElementException("Heap is empty");
        return min.key;
    }

    public int extractMin() {
        Node z = min;
        if (z != null) {
            if (z.child != null) {
                Node firstChild = z.child;
                Node x = firstChild;
                do {
                    Node next = x.right;
                    addToRootList(x);
                    x.parent = null;
                    x = next;
                } while (x != firstChild);
            }
            removeFromRootList(z);
            if (z == z.right) {
                min = null;
            } else {
                min = z.right;
                consolidate();
            }
            n--;
            return z.key;
        }
        throw new NoSuchElementException("Heap is empty");
    }

    private void consolidate() {
        int maxDegree = (int) (Math.log(n) / Math.log(1.618)) + 2;
        Node[] A = new Node[maxDegree];

        List<Node> rootList = new ArrayList<>();
        Node x = min;
        if (x != null) {
            Node start = x;
            do {
                rootList.add(x);
                x = x.right;
            } while (x != start);
        }

        for (Node w : rootList) {
            x = w;
            int d = x.degree;
            while (A[d] != null) {
                Node y = A[d];
                if (x.key > y.key) {
                    Node temp = x;
                    x = y;
                    y = temp;
                }
                link(y, x);
                A[d] = null;
                d++;
            }
            A[d] = x;
        }

        min = null;
        for (Node node : A) {
            if (node != null) {
                if (min == null) {
                    min = node;
                    node.left = node.right = node;
                } else {
                    addToRootList(node);
                    if (node.key < min.key)
                        min = node;
                }
            }
        }
    }

    private void link(Node y, Node x) {
        removeFromRootList(y);
        y.parent = x;
        if (x.child == null) {
            x.child = y;
            y.left = y.right = y;
        } else {
            y.right = x.child;
            y.left = x.child.left;
            x.child.left.right = y;
            x.child.left = y;
        }
        x.degree++;
        y.mark = false;
    }

    private void addToRootList(Node node) {
        node.right = min.right;
        node.left = min;
        min.right.left = node;
        min.right = node;
    }

    private void removeFromRootList(Node node) {
        node.left.right = node.right;
        node.right.left = node.left;
    }

    public static void main(String[] args) {
        basic_operations heap = new basic_operations();
        int[] keys = { 10, 20, 5, 15, 2, 30 };

        System.out.println("Inserting: 10, 20, 5, 15, 2, 30");
        for (int k : keys)
            heap.insert(k);

        System.out.println("Min: " + heap.getMin());
        System.out.println("Extracting Min: " + heap.extractMin());
        System.out.println("New Min: " + heap.getMin());
        System.out.println("Extracting Min: " + heap.extractMin());
        System.out.println("New Min: " + heap.getMin());
    }
}
