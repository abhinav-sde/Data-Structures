
import java.util.*;

public class basic_operations {

    static class BTreeNode {
        int[] keys;
        BTreeNode[] children;
        int numKeys;
        boolean isLeaf;
        int t; // minimum degree

        BTreeNode(int t, boolean isLeaf) {
            this.t = t;
            this.isLeaf = isLeaf;
            this.keys = new int[2 * t - 1];
            this.children = new BTreeNode[2 * t];
            this.numKeys = 0;
        }
    }

    static class BTree {
        private BTreeNode root;
        private int t; // minimum degree

        public BTree(int t) {
            this.root = null;
            this.t = t;
        }

        public boolean search(int key) {
            return root == null ? false : search(root, key);
        }

        private boolean search(BTreeNode node, int key) {
            int i = 0;
            while (i < node.numKeys && key > node.keys[i]) {
                i++;
            }

            if (i < node.numKeys && key == node.keys[i]) {
                return true;
            }

            if (node.isLeaf) {
                return false;
            }

            return search(node.children[i], key);
        }

        public void insert(int key) {
            if (root == null) {
                root = new BTreeNode(t, true);
                root.keys[0] = key;
                root.numKeys = 1;
            } else {
                if (root.numKeys == 2 * t - 1) {
                    BTreeNode newRoot = new BTreeNode(t, false);
                    newRoot.children[0] = root;
                    splitChild(newRoot, 0);
                    root = newRoot;
                }
                insertNonFull(root, key);
            }
        }

        private void insertNonFull(BTreeNode node, int key) {
            int i = node.numKeys - 1;

            if (node.isLeaf) {
                while (i >= 0 && key < node.keys[i]) {
                    node.keys[i + 1] = node.keys[i];
                    i--;
                }
                node.keys[i + 1] = key;
                node.numKeys++;
            } else {
                while (i >= 0 && key < node.keys[i]) {
                    i--;
                }
                i++;

                if (node.children[i].numKeys == 2 * t - 1) {
                    splitChild(node, i);
                    if (key > node.keys[i]) {
                        i++;
                    }
                }
                insertNonFull(node.children[i], key);
            }
        }

        private void splitChild(BTreeNode parent, int i) {
            BTreeNode fullChild = parent.children[i];
            BTreeNode newChild = new BTreeNode(t, fullChild.isLeaf);

            newChild.numKeys = t - 1;

            for (int j = 0; j < t - 1; j++) {
                newChild.keys[j] = fullChild.keys[j + t];
            }

            if (!fullChild.isLeaf) {
                for (int j = 0; j < t; j++) {
                    newChild.children[j] = fullChild.children[j + t];
                }
            }

            fullChild.numKeys = t - 1;

            for (int j = parent.numKeys; j > i; j--) {
                parent.children[j + 1] = parent.children[j];
            }
            parent.children[i + 1] = newChild;

            for (int j = parent.numKeys - 1; j >= i; j--) {
                parent.keys[j + 1] = parent.keys[j];
            }
            parent.keys[i] = fullChild.keys[t - 1];
            parent.numKeys++;
        }
    }

    public static void main(String[] args) {
        System.out.println("=== B-Tree Demo ===\n");

        BTree bt = new BTree(3); // minimum degree = 3

        int[] values = { 10, 20, 5, 6, 12, 30, 7, 17 };
        for (int v : values) {
            bt.insert(v);
        }

        System.out.println("Search 6: " + bt.search(6));
        System.out.println("Search 15: " + bt.search(15));
    }
}
