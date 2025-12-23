package red_black_tree;

/**
 * Basic Red-Black Tree Implementation
 * Rules:
 * 1. Every node is red or black.
 * 2. Root is black.
 * 3. Every leaf (NIL) is black.
 * 4. If a node is red, both children are black.
 * 5. Every path from node to descendant NIL contains same number of black
 * nodes.
 */
public class basic_operations {

    enum Color {
        RED, BLACK
    }

    static class Node {
        int key;
        Node left, right, parent;
        Color color;

        Node(int key) {
            this.key = key;
            this.color = Color.RED;
        }
    }

    static class RedBlackTree {
        private final Node NIL;
        private Node root;

        public RedBlackTree() {
            NIL = new Node(0);
            NIL.color = Color.BLACK;
            root = NIL;
        }

        private void leftRotate(Node x) {
            Node y = x.right;
            x.right = y.left;
            if (y.left != NIL)
                y.left.parent = x;
            y.parent = x.parent;
            if (x.parent == null)
                root = y;
            else if (x == x.parent.left)
                x.parent.left = y;
            else
                x.parent.right = y;
            y.left = x;
            x.parent = y;
        }

        private void rightRotate(Node x) {
            Node y = x.left;
            x.left = y.right;
            if (y.right != NIL)
                y.right.parent = x;
            y.parent = x.parent;
            if (x.parent == null)
                root = y;
            else if (x == x.parent.right)
                x.parent.right = y;
            else
                x.parent.left = y;
            y.right = x;
            x.parent = y;
        }

        public void insert(int key) {
            Node node = new Node(key);
            node.left = node.right = NIL;
            Node y = null;
            Node x = root;
            while (x != NIL) {
                y = x;
                if (node.key < x.key)
                    x = x.left;
                else
                    x = x.right;
            }
            node.parent = y;
            if (y == null)
                root = node;
            else if (node.key < y.key)
                y.left = node;
            else
                y.right = node;
            fixInsert(node);
        }

        private void fixInsert(Node k) {
            while (k.parent != null && k.parent.color == Color.RED) {
                if (k.parent == k.parent.parent.left) {
                    Node u = k.parent.parent.right;
                    if (u.color == Color.RED) {
                        k.parent.color = Color.BLACK;
                        u.color = Color.BLACK;
                        k.parent.parent.color = Color.RED;
                        k = k.parent.parent;
                    } else {
                        if (k == k.parent.right) {
                            k = k.parent;
                            leftRotate(k);
                        }
                        k.parent.color = Color.BLACK;
                        k.parent.parent.color = Color.RED;
                        rightRotate(k.parent.parent);
                    }
                } else {
                    Node u = k.parent.parent.left;
                    if (u.color == Color.RED) {
                        k.parent.color = Color.BLACK;
                        u.color = Color.BLACK;
                        k.parent.parent.color = Color.RED;
                        k = k.parent.parent;
                    } else {
                        if (k == k.parent.left) {
                            k = k.parent;
                            rightRotate(k);
                        }
                        k.parent.color = Color.BLACK;
                        k.parent.parent.color = Color.RED;
                        leftRotate(k.parent.parent);
                    }
                }
            }
            root.color = Color.BLACK;
        }

        public void display() {
            printHelper(this.root, "", true);
        }

        private void printHelper(Node root, String indent, boolean last) {
            if (root != NIL) {
                System.out.print(indent);
                if (last) {
                    System.out.print("R----");
                    indent += "   ";
                } else {
                    System.out.print("L----");
                    indent += "|  ";
                }
                String sColor = root.color == Color.RED ? "RED" : "BLACK";
                System.out.println(root.key + "(" + sColor + ")");
                printHelper(root.left, indent, false);
                printHelper(root.right, indent, true);
            }
        }
    }

    public static void main(String[] args) {
        RedBlackTree rbt = new RedBlackTree();
        rbt.insert(10);
        rbt.insert(20);
        rbt.insert(30);
        rbt.insert(15);
        rbt.display();
    }
}
