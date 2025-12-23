package heap;

/**
 * Core Heap Problems in Java
 * Contains essential heap-based algorithms
 */

import java.util.*;

public class core_problems {

    // Problem 1: Find Kth Largest Element
    // Time Complexity: O(n log k)
    // Space Complexity: O(k)
    static int findKthLargest(int[] nums, int k) {
        // Use min heap of size k
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        for (int num : nums) {
            minHeap.offer(num);
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }

        return minHeap.peek();
    }

    // Problem 2: Heap Sort
    // Time Complexity: O(n log n)
    // Space Complexity: O(1)
    static void heapSort(int[] arr) {
        int n = arr.length;

        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        // Extract elements one by one
        for (int i = n - 1; i > 0; i--) {
            // Move current root to end
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // Heapify reduced heap
            heapify(arr, i, 0);
        }
    }

    private static void heapify(int[] arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;

            heapify(arr, n, largest);
        }
    }

    // Problem 3: Top K Frequent Elements
    // Time Complexity: O(n log k)
    // Space Complexity: O(n)
    static int[] topKFrequent(int[] nums, int k) {
        // Count frequencies
        Map<Integer, Integer> freqMap = new HashMap<>();
        for (int num : nums) {
            freqMap.put(num, freqMap.getOrDefault(num, 0) + 1);
        }

        // Min heap based on frequency
        PriorityQueue<Map.Entry<Integer, Integer>> minHeap = new PriorityQueue<>((a, b) -> a.getValue() - b.getValue());

        for (Map.Entry<Integer, Integer> entry : freqMap.entrySet()) {
            minHeap.offer(entry);
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }

        // Extract results
        int[] result = new int[k];
        int i = 0;
        while (!minHeap.isEmpty()) {
            result[i++] = minHeap.poll().getKey();
        }

        return result;
    }

    // Problem 4: Merge K Sorted Lists (using arrays)
    // Time Complexity: O(N log k) where N is total elements
    // Space Complexity: O(k)
    static class ArrayPointer {
        int arrayIndex;
        int elementIndex;
        int value;

        ArrayPointer(int arrayIndex, int elementIndex, int value) {
            this.arrayIndex = arrayIndex;
            this.elementIndex = elementIndex;
            this.value = value;
        }
    }

    static List<Integer> mergeKSortedArrays(int[][] arrays) {
        List<Integer> result = new ArrayList<>();
        PriorityQueue<ArrayPointer> minHeap = new PriorityQueue<>((a, b) -> a.value - b.value);

        // Add first element from each array
        for (int i = 0; i < arrays.length; i++) {
            if (arrays[i].length > 0) {
                minHeap.offer(new ArrayPointer(i, 0, arrays[i][0]));
            }
        }

        // Process heap
        while (!minHeap.isEmpty()) {
            ArrayPointer current = minHeap.poll();
            result.add(current.value);

            // Add next element from same array
            if (current.elementIndex + 1 < arrays[current.arrayIndex].length) {
                int nextIdx = current.elementIndex + 1;
                int nextVal = arrays[current.arrayIndex][nextIdx];
                minHeap.offer(new ArrayPointer(current.arrayIndex, nextIdx, nextVal));
            }
        }

        return result;
    }

    // Problem 5: Find Median from Data Stream
    static class MedianFinder {
        PriorityQueue<Integer> maxHeap; // Lower half
        PriorityQueue<Integer> minHeap; // Upper half

        public MedianFinder() {
            maxHeap = new PriorityQueue<>((a, b) -> b - a);
            minHeap = new PriorityQueue<>();
        }

        // Time Complexity: O(log n)
        public void addNum(int num) {
            // Add to max heap first
            maxHeap.offer(num);

            // Balance: move largest from max heap to min heap
            minHeap.offer(maxHeap.poll());

            // Ensure max heap has equal or one more element
            if (maxHeap.size() < minHeap.size()) {
                maxHeap.offer(minHeap.poll());
            }
        }

        // Time Complexity: O(1)
        public double findMedian() {
            if (maxHeap.size() == minHeap.size()) {
                return (maxHeap.peek() + minHeap.peek()) / 2.0;
            }
            return maxHeap.peek();
        }
    }

    // Problem 6: Last Stone Weight
    // Time Complexity: O(n log n)
    static int lastStoneWeight(int[] stones) {
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> b - a);

        for (int stone : stones) {
            maxHeap.offer(stone);
        }

        while (maxHeap.size() > 1) {
            int stone1 = maxHeap.poll();
            int stone2 = maxHeap.poll();

            if (stone1 != stone2) {
                maxHeap.offer(stone1 - stone2);
            }
        }

        return maxHeap.isEmpty() ? 0 : maxHeap.peek();
    }

    // Display array
    static void displayArray(int[] arr) {
        System.out.print("Array: ");
        for (int val : arr) {
            System.out.print(val + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        System.out.println("=== Core Heap Problems ===\n");

        // Test 1: Kth Largest Element
        System.out.println("Test 1: Kth Largest Element");
        int[] nums1 = { 3, 2, 1, 5, 6, 4 };
        int k1 = 2;
        System.out.println("Array: " + Arrays.toString(nums1));
        System.out.println(k1 + "th largest: " + findKthLargest(nums1, k1));
        System.out.println();

        // Test 2: Heap Sort
        System.out.println("Test 2: Heap Sort");
        int[] nums2 = { 12, 11, 13, 5, 6, 7 };
        System.out.println("Before: " + Arrays.toString(nums2));
        heapSort(nums2);
        System.out.println("After: " + Arrays.toString(nums2));
        System.out.println();

        // Test 3: Top K Frequent
        System.out.println("Test 3: Top K Frequent Elements");
        int[] nums3 = { 1, 1, 1, 2, 2, 3 };
        int k3 = 2;
        System.out.println("Array: " + Arrays.toString(nums3));
        System.out.println("Top " + k3 + " frequent: " + Arrays.toString(topKFrequent(nums3, k3)));
        System.out.println();

        // Test 4: Merge K Sorted Arrays
        System.out.println("Test 4: Merge K Sorted Arrays");
        int[][] arrays = {
                { 1, 4, 7 },
                { 2, 5, 8 },
                { 3, 6, 9 }
        };
        System.out.println("Merged: " + mergeKSortedArrays(arrays));
        System.out.println();

        // Test 5: Median Finder
        System.out.println("Test 5: Find Median from Data Stream");
        MedianFinder mf = new MedianFinder();
        mf.addNum(1);
        mf.addNum(2);
        System.out.println("Median after adding 1, 2: " + mf.findMedian());
        mf.addNum(3);
        System.out.println("Median after adding 3: " + mf.findMedian());
        System.out.println();

        // Test 6: Last Stone Weight
        System.out.println("Test 6: Last Stone Weight");
        int[] stones = { 2, 7, 4, 1, 8, 1 };
        System.out.println("Stones: " + Arrays.toString(stones));
        System.out.println("Last stone weight: " + lastStoneWeight(stones));
    }
}
