
import java.util.*;

/**
 * Basic B+ Tree Implementation
 * Key differences from B-Tree:
 * 1. Internal nodes only store keys (for routing).
 * 2. Leaves store all keys (and values).
 * 3. Leaves are linked for range queries.
 */
public class basic_operations {

    static class BPlusNode {
        boolean isLeaf;
        List<Integer> keys;
        List<BPlusNode> children;
        BPlusNode next; // Link for leaves

        BPlusNode(boolean isLeaf) {
            this.isLeaf = isLeaf;
            this.keys = new ArrayList<>();
            this.children = new ArrayList<>();
            this.next = null;
        }
    }

    static class BPlusTree {
        private final int degree; // max children
        private BPlusNode root;

        public BPlusTree(int degree) {
            this.degree = degree;
            this.root = new BPlusNode(true);
        }

        public void insert(int key) {
            BPlusNode r = root;
            if (r.keys.size() == degree - 1) {
                BPlusNode s = new BPlusNode(false);
                root = s;
                s.children.add(r);
                split(s, 0, r);
                insertNonFull(s, key);
            } else {
                insertNonFull(r, key);
            }
        }

        private void split(BPlusNode parent, int i, BPlusNode child) {
            int mid = (degree - 1) / 2;
            BPlusNode newNode = new BPlusNode(child.isLeaf);

            if (child.isLeaf) {
                // Leaf split: Copy mid key up but also keep it in leaf
                for (int j = mid; j < child.keys.size(); j++) {
                    newNode.keys.add(child.keys.get(j));
                }
                child.keys.subList(mid, child.keys.size()).clear();
                parent.keys.add(i, newNode.keys.get(0));
                newNode.next = child.next;
                child.next = newNode;
            } else {
                // Internal split: Mid key goes up, not kept in children
                for (int j = mid + 1; j < child.keys.size(); j++) {
                    newNode.keys.add(child.keys.get(j));
                }
                for (int j = mid + 1; j < child.children.size(); j++) {
                    newNode.children.add(child.children.get(j));
                }
                parent.keys.add(i, child.keys.get(mid));
                child.keys.subList(mid, child.keys.size()).clear();
                child.children.subList(mid + 1, child.children.size()).clear();
            }
            parent.children.add(i + 1, newNode);
        }

        private void insertNonFull(BPlusNode node, int key) {
            int i = node.keys.size() - 1;
            if (node.isLeaf) {
                while (i >= 0 && key < node.keys.get(i))
                    i--;
                node.keys.add(i + 1, key);
            } else {
                while (i >= 0 && key < node.keys.get(i))
                    i--;
                i++;
                if (node.children.get(i).keys.size() == degree - 1) {
                    split(node, i, node.children.get(i));
                    if (key > node.keys.get(i))
                        i++;
                }
                insertNonFull(node.children.get(i), key);
            }
        }

        public void display() {
            // Traverse leaves using next pointer (Sequential access)
            BPlusNode curr = root;
            while (!curr.isLeaf)
                curr = curr.children.get(0);
            while (curr != null) {
                System.out.print(curr.keys + " -> ");
                curr = curr.next;
            }
            System.out.println("null");
        }
    }

    public static void main(String[] args) {
        BPlusTree tree = new BPlusTree(4);
        tree.insert(10);
        tree.insert(20);
        tree.insert(5);
        tree.insert(15);
        tree.insert(25);
        tree.insert(30);
        tree.display();
    }
}
