
import java.util.*;

public class basic_operations {

    static class Node {
        int value;
        Node left, right;

        Node(int value) {
            this.value = value;
        }
    }

    static class CartesianTree {

        public Node buildTree(int[] arr) {
            if (arr == null || arr.length == 0)
                return null;
            return buildTreeHelper(arr, 0, arr.length - 1);
        }

        private Node buildTreeHelper(int[] arr, int start, int end) {
            if (start > end)
                return null;

            int minIndex = start;
            for (int i = start + 1; i <= end; i++) {
                if (arr[i] < arr[minIndex]) {
                    minIndex = i;
                }
            }

            Node root = new Node(arr[minIndex]);
            root.left = buildTreeHelper(arr, start, minIndex - 1);
            root.right = buildTreeHelper(arr, minIndex + 1, end);

            return root;
        }

        public void inorder(Node node) {
            if (node != null) {
                inorder(node.left);
                System.out.print(node.value + " ");
                inorder(node.right);
            }
        }

        public void display(Node root) {
            System.out.print("Inorder: ");
            inorder(root);
            System.out.println();
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Cartesian Tree Demo ===\n");

        CartesianTree ct = new CartesianTree();

        int[] arr = { 9, 3, 7, 1, 8, 12, 10, 20, 15, 18, 5 };

        System.out.println("Array: " + Arrays.toString(arr));

        Node root = ct.buildTree(arr);
        ct.display(root);

        System.out.println("\nCartesian tree built with min-heap property");
    }
}
