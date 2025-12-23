import java.util.*;

/**
 * Core Fibonacci Heap Problems in Java
 * Focuses on Decrease-Key and Delete operations.
 */
public class core_problems {

    static class Node {
        int key;
        int degree;
        boolean mark;
        Node parent, child, left, right;

        Node(int key) {
            this.key = key;
            this.left = this.right = this;
        }
    }

    private Node min;
    private int n;

    public void insert(Node node) {
        if (min == null) {
            min = node;
            node.left = node.right = node;
        } else {
            node.right = min.right;
            node.left = min;
            min.right.left = node;
            min.right = node;
            if (node.key < min.key)
                min = node;
        }
        n++;
    }

    public void decreaseKey(Node x, int k) {
        if (k > x.key)
            throw new IllegalArgumentException("New key is greater than current key");
        x.key = k;
        Node y = x.parent;
        if (y != null && x.key < y.key) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x.key < min.key)
            min = x;
    }

    private void cut(Node x, Node y) {
        // Remove x from child list of y
        if (x.right == x) {
            y.child = null;
        } else {
            x.left.right = x.right;
            x.right.left = x.left;
            if (y.child == x)
                y.child = x.right;
        }
        y.degree--;
        // Add x to root list
        x.parent = null;
        x.mark = false;
        x.right = min.right;
        x.left = min;
        min.right.left = x;
        min.right = x;
    }

    private void cascadingCut(Node y) {
        Node z = y.parent;
        if (z != null) {
            if (!y.mark) {
                y.mark = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

    public void delete(Node x) {
        decreaseKey(x, Integer.MIN_VALUE);
        extractMin();
    }

    public Node extractMin() {
        Node z = min;
        if (z != null) {
            if (z.child != null) {
                Node curr = z.child;
                do {
                    Node next = curr.right;
                    curr.parent = null;
                    // Add curr to root list
                    curr.right = min.right;
                    curr.left = min;
                    min.right.left = curr;
                    min.right = curr;
                    curr = next;
                } while (curr != z.child);
            }
            z.left.right = z.right;
            z.right.left = z.left;
            if (z == z.right)
                min = null;
            else {
                min = z.right;
                consolidate();
            }
            n--;
        }
        return z;
    }

    private void consolidate() {
        int maxDegree = (int) (Math.log(n + 1) / Math.log(1.618)) + 2;
        Node[] A = new Node[maxDegree];
        List<Node> rootList = new ArrayList<>();
        Node curr = min;
        if (curr != null) {
            Node start = curr;
            do {
                rootList.add(curr);
                curr = curr.right;
            } while (curr != start);
        }
        for (Node x : rootList) {
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
                    node.right = min.right;
                    node.left = min;
                    min.right.left = node;
                    min.right = node;
                    if (node.key < min.key)
                        min = node;
                }
            }
        }
    }

    private void link(Node y, Node x) {
        y.left.right = y.right;
        y.right.left = y.left;
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

    public static void main(String[] args) {
        core_problems heap = new core_problems();
        Node n1 = new Node(10);
        Node n2 = new Node(20);
        Node n3 = new Node(5);
        Node n4 = new Node(15);

        heap.insert(n1);
        heap.insert(n2);
        heap.insert(n3);
        heap.insert(n4);
        System.out.println("Inserted nodes: 10, 20, 5, 15. Min is: " + heap.min.key);

        System.out.println("Decreasing key of node 20 to 2...");
        heap.decreaseKey(n2, 2);
        System.out.println("New Min is: " + heap.min.key);

        System.out.println("Deleting node 5...");
        heap.delete(n3);
        System.out.println("Min after deletion is: " + (heap.min != null ? heap.min.key : "null"));
    }
}
