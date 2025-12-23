/**
 * Heap Operations in Java
 * Contains MinHeap, MaxHeap and Heap Sort implementations
 */

import java.util.*;

public class heap {
    
    // ========================================
    // MIN HEAP IMPLEMENTATION
    // ========================================
    
    static class MinHeap {
        private List<Integer> heap;
        
        public MinHeap() {
            heap = new ArrayList<>();
        }
        
        private int parent(int i) { return (i - 1) / 2; }
        private int leftChild(int i) { return 2 * i + 1; }
        private int rightChild(int i) { return 2 * i + 2; }
        
        private void heapifyUp(int i) {
            while (i > 0 && heap.get(parent(i)) > heap.get(i)) {
                Collections.swap(heap, i, parent(i));
                i = parent(i);
            }
        }
        
        private void heapifyDown(int i) {
            int minIndex = i;
            int left = leftChild(i);
            int right = rightChild(i);
            
            if (left < heap.size() && heap.get(left) < heap.get(minIndex)) {
                minIndex = left;
            }
            
            if (right < heap.size() && heap.get(right) < heap.get(minIndex)) {
                minIndex = right;
            }
            
            if (i != minIndex) {
                Collections.swap(heap, i, minIndex);
                heapifyDown(minIndex);
            }
        }
        
        // Insert element
        public void insert(int value) {
            heap.add(value);
            heapifyUp(heap.size() - 1);
            System.out.println("Inserted " + value + " into min heap.");
        }
        
        // Extract minimum
        public int extractMin() {
            if (heap.isEmpty()) {
                System.out.println("Heap is empty!");
                return Integer.MAX_VALUE;
            }
            
            int minVal = heap.get(0);
            heap.set(0, heap.get(heap.size() - 1));
            heap.remove(heap.size() - 1);
            
            if (!heap.isEmpty()) {
                heapifyDown(0);
            }
            
            return minVal;
        }
        
        // Get minimum without removing
        public int getMin() {
            if (heap.isEmpty()) {
                System.out.println("Heap is empty!");
                return Integer.MAX_VALUE;
            }
            return heap.get(0);
        }
        
        // Check if empty
        public boolean isEmpty() {
            return heap.isEmpty();
        }
        
        // Get size
        public int size() {
            return heap.size();
        }
        
        // Display heap
        public void display() {
            System.out.print("Min Heap: ");
            for (int val : heap) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
        
        // Build heap from array
        public void buildHeap(List<Integer> arr) {
            heap = new ArrayList<>(arr);
            for (int i = heap.size() / 2 - 1; i >= 0; i--) {
                heapifyDown(i);
            }
            System.out.println("Min heap built from array.");
        }
    }
    
    // ========================================
    // MAX HEAP IMPLEMENTATION
    // ========================================
    
    static class MaxHeap {
        private List<Integer> heap;
        
        public MaxHeap() {
            heap = new ArrayList<>();
        }
        
        private int parent(int i) { return (i - 1) / 2; }
        private int leftChild(int i) { return 2 * i + 1; }
        private int rightChild(int i) { return 2 * i + 2; }
        
        private void heapifyUp(int i) {
            while (i > 0 && heap.get(parent(i)) < heap.get(i)) {
                Collections.swap(heap, i, parent(i));
                i = parent(i);
            }
        }
        
        private void heapifyDown(int i) {
            int maxIndex = i;
            int left = leftChild(i);
            int right = rightChild(i);
            
            if (left < heap.size() && heap.get(left) > heap.get(maxIndex)) {
                maxIndex = left;
            }
            
            if (right < heap.size() && heap.get(right) > heap.get(maxIndex)) {
                maxIndex = right;
            }
            
            if (i != maxIndex) {
                Collections.swap(heap, i, maxIndex);
                heapifyDown(maxIndex);
            }
        }
        
        // Insert element
        public void insert(int value) {
            heap.add(value);
            heapifyUp(heap.size() - 1);
            System.out.println("Inserted " + value + " into max heap.");
        }
        
        // Extract maximum
        public int extractMax() {
            if (heap.isEmpty()) {
                System.out.println("Heap is empty!");
                return Integer.MIN_VALUE;
            }
            
            int maxVal = heap.get(0);
            heap.set(0, heap.get(heap.size() - 1));
            heap.remove(heap.size() - 1);
            
            if (!heap.isEmpty()) {
                heapifyDown(0);
            }
            
            return maxVal;
        }
        
        // Get maximum without removing
        public int getMax() {
            if (heap.isEmpty()) {
                System.out.println("Heap is empty!");
                return Integer.MIN_VALUE;
            }
            return heap.get(0);
        }
        
        // Check if empty
        public boolean isEmpty() {
            return heap.isEmpty();
        }
        
        // Get size
        public int size() {
            return heap.size();
        }
        
        // Display heap
        public void display() {
            System.out.print("Max Heap: ");
            for (int val : heap) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
        
        // Build heap from array
        public void buildHeap(List<Integer> arr) {
            heap = new ArrayList<>(arr);
            for (int i = heap.size() / 2 - 1; i >= 0; i--) {
                heapifyDown(i);
            }
            System.out.println("Max heap built from array.");
        }
    }
    
    // ========================================
    // HEAP SORT
    // ========================================
    static void heapSort(List<Integer> arr) {
        int n = arr.size();
        
        // Build max heap manually (in-place)
        // Note: Implementing standard heap sort logic directly on list
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        
        // Extract elements one by one
        for (int i = n - 1; i > 0; i--) {
            Collections.swap(arr, 0, i);
            heapify(arr, i, 0);
        }
        
        System.out.println("Array sorted using heap sort.");
    }
    
    static void heapify(List<Integer> arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr.get(left) > arr.get(largest)) {
            largest = left;
        }
        
        if (right < n && arr.get(right) > arr.get(largest)) {
            largest = right;
        }
        
        if (largest != i) {
            Collections.swap(arr, i, largest);
            heapify(arr, n, largest);
        }
    }
    
    // ========================================
    // FIND KTH LARGEST ELEMENT
    // ========================================
    static int findKthLargest(List<Integer> arr, int k) {
        MinHeap minHeap = new MinHeap(); // Using our custom MinHeap
        
        for (int num : arr) {
            minHeap.insert(num);
            if (minHeap.size() > k) {
                minHeap.extractMin();
            }
        }
        
        return minHeap.getMin();
    }
    
    // ========================================
    // FIND KTH SMALLEST ELEMENT
    // ========================================
    static int findKthSmallest(List<Integer> arr, int k) {
        MaxHeap maxHeap = new MaxHeap(); // Using our custom MaxHeap
        
        for (int num : arr) {
            maxHeap.insert(num);
            if (maxHeap.size() > k) {
                maxHeap.extractMax();
            }
        }
        
        return maxHeap.getMax();
    }
    
    // ========================================
    // MEDIAN FINDER (USING TWO HEAPS)
    // ========================================
    static class MedianFinder {
        PriorityQueue<Integer> minHeap; // Upper half
        PriorityQueue<Integer> maxHeap; // Lower half
        
        public MedianFinder() {
            minHeap = new PriorityQueue<>();
            maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        }
        
        public void addNum(int num) {
            if (maxHeap.isEmpty() || num <= maxHeap.peek()) {
                maxHeap.add(num);
            } else {
                minHeap.add(num);
            }
            
            // Balance heaps
            if (maxHeap.size() > minHeap.size() + 1) {
                minHeap.add(maxHeap.poll());
            } else if (minHeap.size() > maxHeap.size()) {
                maxHeap.add(minHeap.poll());
            }
        }
        
        public double findMedian() {
            if (maxHeap.size() == minHeap.size()) {
                return (maxHeap.peek() + minHeap.peek()) / 2.0;
            }
            return maxHeap.peek();
        }
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Heap Operations ===");
        
        // Example usage - uncomment to use
        
        // Min Heap
        // MinHeap minHeap = new MinHeap();
        // minHeap.insert(5);
        // minHeap.insert(3);
        // minHeap.insert(7);
        // minHeap.insert(1);
        // minHeap.display();
        
        // System.out.println("Min: " + minHeap.getMin());
        // System.out.println("Extracted min: " + minHeap.extractMin());
        // minHeap.display();
        
        // Max Heap
        // MaxHeap maxHeap = new MaxHeap();
        // maxHeap.insert(5);
        // maxHeap.insert(3);
        // maxHeap.insert(7);
        // maxHeap.insert(1);
        // maxHeap.display();
        
        // System.out.println("Max: " + maxHeap.getMax());
        // System.out.println("Extracted max: " + maxHeap.extractMax());
        // maxHeap.display();
        
        // Build heap from array
        // List<Integer> arr = Arrays.asList(4, 10, 3, 5, 1);
        // MinHeap heap = new MinHeap();
        // heap.buildHeap(arr);
        // heap.display();
        
        // Heap Sort
        // List<Integer> sortArr = new ArrayList<>(Arrays.asList(12, 11, 13, 5, 6, 7));
        // System.out.print("Before sort: ");
        // System.out.println(sortArr);
        
        // heapSort(sortArr);
        
        // System.out.print("After sort: ");
        // System.out.println(sortArr);
        
        // Kth Largest
        // List<Integer> kArr = Arrays.asList(3, 2, 1, 5, 6, 4);
        // int kthLargest = findKthLargest(kArr, 2);
        // System.out.println("2nd largest: " + kthLargest);
        
        // Kth Smallest
        // int kthSmallest = findKthSmallest(kArr, 2);
        // System.out.println("2nd smallest: " + kthSmallest);
        
        // Median Finder
        // MedianFinder mf = new MedianFinder();
        // mf.addNum(1);
        // mf.addNum(2);
        // System.out.println("Median: " + mf.findMedian());
        // mf.addNum(3);
        // System.out.println("Median: " + mf.findMedian());
    }
}
