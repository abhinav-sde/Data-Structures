
/**
 * Basic Heap (Priority Queue) Operations in Java
 * Contains Min Heap and Max Heap implementations
 */

import java.util.Scanner;

public class basic_operations {

    // Min Heap Implementation
    static class MinHeap {
        private int[] heap;
        private int size;
        private int capacity;

        public MinHeap(int capacity) {
            this.capacity = capacity;
            this.size = 0;
            this.heap = new int[capacity];
        }

        // Get parent index
        private int parent(int i) {
            return (i - 1) / 2;
        }

        // Get left child index
        private int leftChild(int i) {
            return 2 * i + 1;
        }

        // Get right child index
        private int rightChild(int i) {
            return 2 * i + 2;
        }

        // Swap two elements
        private void swap(int i, int j) {
            int temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;
        }

        // Insert a new element
        // Time Complexity: O(log n)
        public void insert(int value) {
            if (size == capacity) {
                System.out.println("Heap is full. Cannot insert " + value);
                return;
            }

            // Insert at the end
            heap[size] = value;
            int current = size;
            size++;

            // Heapify up (bubble up)
            while (current > 0 && heap[current] < heap[parent(current)]) {
                swap(current, parent(current));
                current = parent(current);
            }

            System.out.println("Inserted " + value + " into min heap");
        }

        // Get minimum element (root)
        // Time Complexity: O(1)
        public int getMin() {
            if (size == 0) {
                System.out.println("Heap is empty");
                return -1;
            }
            return heap[0];
        }

        // Extract minimum element
        // Time Complexity: O(log n)
        public int extractMin() {
            if (size == 0) {
                System.out.println("Heap is empty");
                return -1;
            }

            if (size == 1) {
                size--;
                return heap[0];
            }

            // Store minimum and move last element to root
            int min = heap[0];
            heap[0] = heap[size - 1];
            size--;

            // Heapify down
            heapifyDown(0);

            return min;
        }

        // Heapify down (bubble down)
        private void heapifyDown(int i) {
            int smallest = i;
            int left = leftChild(i);
            int right = rightChild(i);

            if (left < size && heap[left] < heap[smallest]) {
                smallest = left;
            }

            if (right < size && heap[right] < heap[smallest]) {
                smallest = right;
            }

            if (smallest != i) {
                swap(i, smallest);
                heapifyDown(smallest);
            }
        }

        // Display heap
        public void display() {
            if (size == 0) {
                System.out.println("Heap is empty");
                return;
            }
            System.out.print("Min Heap: ");
            for (int i = 0; i < size; i++) {
                System.out.print(heap[i] + " ");
            }
            System.out.println();
        }
    }

    // Max Heap Implementation
    static class MaxHeap {
        private int[] heap;
        private int size;
        private int capacity;

        public MaxHeap(int capacity) {
            this.capacity = capacity;
            this.size = 0;
            this.heap = new int[capacity];
        }

        private int parent(int i) {
            return (i - 1) / 2;
        }

        private int leftChild(int i) {
            return 2 * i + 1;
        }

        private int rightChild(int i) {
            return 2 * i + 2;
        }

        private void swap(int i, int j) {
            int temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;
        }

        // Insert a new element
        // Time Complexity: O(log n)
        public void insert(int value) {
            if (size == capacity) {
                System.out.println("Heap is full. Cannot insert " + value);
                return;
            }

            heap[size] = value;
            int current = size;
            size++;

            // Heapify up (bubble up)
            while (current > 0 && heap[current] > heap[parent(current)]) {
                swap(current, parent(current));
                current = parent(current);
            }

            System.out.println("Inserted " + value + " into max heap");
        }

        // Get maximum element (root)
        // Time Complexity: O(1)
        public int getMax() {
            if (size == 0) {
                System.out.println("Heap is empty");
                return -1;
            }
            return heap[0];
        }

        // Extract maximum element
        // Time Complexity: O(log n)
        public int extractMax() {
            if (size == 0) {
                System.out.println("Heap is empty");
                return -1;
            }

            if (size == 1) {
                size--;
                return heap[0];
            }

            int max = heap[0];
            heap[0] = heap[size - 1];
            size--;

            heapifyDown(0);

            return max;
        }

        private void heapifyDown(int i) {
            int largest = i;
            int left = leftChild(i);
            int right = rightChild(i);

            if (left < size && heap[left] > heap[largest]) {
                largest = left;
            }

            if (right < size && heap[right] > heap[largest]) {
                largest = right;
            }

            if (largest != i) {
                swap(i, largest);
                heapifyDown(largest);
            }
        }

        public void display() {
            if (size == 0) {
                System.out.println("Heap is empty");
                return;
            }
            System.out.print("Max Heap: ");
            for (int i = 0; i < size; i++) {
                System.out.print(heap[i] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("=== Min Heap Demo ===");
        MinHeap minHeap = new MinHeap(10);

        // Insert elements
        minHeap.insert(10);
        minHeap.insert(5);
        minHeap.insert(20);
        minHeap.insert(1);
        minHeap.insert(15);
        minHeap.insert(30);

        minHeap.display();

        System.out.println("Minimum element: " + minHeap.getMin());
        System.out.println("Extracted min: " + minHeap.extractMin());

        minHeap.display();

        System.out.println("\n=== Max Heap Demo ===");
        MaxHeap maxHeap = new MaxHeap(10);

        // Insert elements
        maxHeap.insert(10);
        maxHeap.insert(5);
        maxHeap.insert(20);
        maxHeap.insert(1);
        maxHeap.insert(15);
        maxHeap.insert(30);

        maxHeap.display();

        System.out.println("Maximum element: " + maxHeap.getMax());
        System.out.println("Extracted max: " + maxHeap.extractMax());

        maxHeap.display();

        scanner.close();
    }
}
