package heap;

/**
 * Advanced Heap Problems in Java
 * Contains complex heap-based algorithms and applications
 */

import java.util.*;

public class advanced_problems {

    // Problem 1: Task Scheduler
    // Given tasks and cooldown time, find minimum time to complete all tasks
    // Time Complexity: O(n log n)
    static int leastInterval(char[] tasks, int n) {
        // Count frequency of each task
        int[] freq = new int[26];
        for (char task : tasks) {
            freq[task - 'A']++;
        }

        // Max heap for frequencies
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> b - a);
        for (int f : freq) {
            if (f > 0)
                maxHeap.offer(f);
        }

        int time = 0;
        Queue<int[]> cooldown = new LinkedList<>(); // [frequency, available_time]

        while (!maxHeap.isEmpty() || !cooldown.isEmpty()) {
            time++;

            if (!maxHeap.isEmpty()) {
                int current = maxHeap.poll() - 1;
                if (current > 0) {
                    cooldown.offer(new int[] { current, time + n });
                }
            }

            if (!cooldown.isEmpty() && cooldown.peek()[1] == time) {
                maxHeap.offer(cooldown.poll()[0]);
            }
        }

        return time;
    }

    // Problem 2: Minimum Cost to Connect Ropes
    // Time Complexity: O(n log n)
    static int connectRopes(int[] ropes) {
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        for (int rope : ropes) {
            minHeap.offer(rope);
        }

        int totalCost = 0;

        while (minHeap.size() > 1) {
            int first = minHeap.poll();
            int second = minHeap.poll();
            int cost = first + second;
            totalCost += cost;
            minHeap.offer(cost);
        }

        return totalCost;
    }

    // Problem 3: Sliding Window Median
    // Time Complexity: O(n log k)
    static class SlidingWindowMedian {
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> b - a);
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        void addNum(int num) {
            maxHeap.offer(num);
            minHeap.offer(maxHeap.poll());

            if (maxHeap.size() < minHeap.size()) {
                maxHeap.offer(minHeap.poll());
            }
        }

        void removeNum(int num) {
            if (num <= maxHeap.peek()) {
                maxHeap.remove(num);
            } else {
                minHeap.remove(num);
            }

            // Rebalance
            if (maxHeap.size() < minHeap.size()) {
                maxHeap.offer(minHeap.poll());
            } else if (maxHeap.size() > minHeap.size() + 1) {
                minHeap.offer(maxHeap.poll());
            }
        }

        double findMedian() {
            if (maxHeap.size() == minHeap.size()) {
                return (maxHeap.peek() + minHeap.peek()) / 2.0;
            }
            return maxHeap.peek();
        }

        double[] medianSlidingWindow(int[] nums, int k) {
            double[] result = new double[nums.length - k + 1];

            for (int i = 0; i < nums.length; i++) {
                addNum(nums[i]);

                if (i >= k - 1) {
                    result[i - k + 1] = findMedian();
                    removeNum(nums[i - k + 1]);
                }
            }

            return result;
        }
    }

    // Problem 4: Find K Pairs with Smallest Sums
    // Time Complexity: O(k log k)
    static List<int[]> kSmallestPairs(int[] nums1, int[] nums2, int k) {
        List<int[]> result = new ArrayList<>();
        if (nums1.length == 0 || nums2.length == 0 || k == 0)
            return result;

        PriorityQueue<int[]> minHeap = new PriorityQueue<>(
                (a, b) -> (a[0] + a[1]) - (b[0] + b[1]));

        // Add first k pairs
        for (int i = 0; i < Math.min(nums1.length, k); i++) {
            minHeap.offer(new int[] { nums1[i], nums2[0], 0 }); // [num1, num2, index2]
        }

        while (k > 0 && !minHeap.isEmpty()) {
            int[] current = minHeap.poll();
            result.add(new int[] { current[0], current[1] });

            int index2 = current[2];
            if (index2 + 1 < nums2.length) {
                minHeap.offer(new int[] { current[0], nums2[index2 + 1], index2 + 1 });
            }
            k--;
        }

        return result;
    }

    // Problem 5: Merge K Sorted Linked Lists (simulated with arrays)
    static class ListNode {
        int val;
        ListNode next;

        ListNode(int val) {
            this.val = val;
        }
    }

    static ListNode mergeKLists(ListNode[] lists) {
        if (lists == null || lists.length == 0)
            return null;

        PriorityQueue<ListNode> minHeap = new PriorityQueue<>(
                (a, b) -> a.val - b.val);

        // Add first node from each list
        for (ListNode node : lists) {
            if (node != null) {
                minHeap.offer(node);
            }
        }

        ListNode dummy = new ListNode(0);
        ListNode current = dummy;

        while (!minHeap.isEmpty()) {
            ListNode node = minHeap.poll();
            current.next = node;
            current = current.next;

            if (node.next != null) {
                minHeap.offer(node.next);
            }
        }

        return dummy.next;
    }

    // Problem 6: Reorganize String (no two adjacent characters are same)
    // Time Complexity: O(n log k) where k is unique characters
    static String reorganizeString(String s) {
        // Count frequencies
        Map<Character, Integer> freqMap = new HashMap<>();
        for (char c : s.toCharArray()) {
            freqMap.put(c, freqMap.getOrDefault(c, 0) + 1);
        }

        // Max heap by frequency
        PriorityQueue<Character> maxHeap = new PriorityQueue<>(
                (a, b) -> freqMap.get(b) - freqMap.get(a));
        maxHeap.addAll(freqMap.keySet());

        StringBuilder result = new StringBuilder();
        Character prev = null;

        while (!maxHeap.isEmpty()) {
            char current = maxHeap.poll();
            result.append(current);

            // Add previous character back if it still has frequency
            if (prev != null && freqMap.get(prev) > 0) {
                maxHeap.offer(prev);
            }

            freqMap.put(current, freqMap.get(current) - 1);
            prev = freqMap.get(current) > 0 ? current : null;
        }

        return result.length() == s.length() ? result.toString() : "";
    }

    // Problem 7: IPO (maximize capital)
    // Time Complexity: O(n log n)
    static int findMaximizedCapital(int k, int w, int[] profits, int[] capital) {
        int n = profits.length;
        List<int[]> projects = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            projects.add(new int[] { capital[i], profits[i] });
        }

        // Sort by capital required
        projects.sort((a, b) -> a[0] - b[0]);

        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> b - a);
        int i = 0;

        for (int j = 0; j < k; j++) {
            // Add all projects we can afford
            while (i < n && projects.get(i)[0] <= w) {
                maxHeap.offer(projects.get(i)[1]);
                i++;
            }

            if (maxHeap.isEmpty())
                break;

            w += maxHeap.poll();
        }

        return w;
    }

    public static void main(String[] args) {
        System.out.println("=== Advanced Heap Problems ===\n");

        // Test 1: Task Scheduler
        System.out.println("Test 1: Task Scheduler");
        char[] tasks = { 'A', 'A', 'A', 'B', 'B', 'B' };
        int n = 2;
        System.out.println("Tasks: " + Arrays.toString(tasks) + ", cooldown: " + n);
        System.out.println("Minimum time: " + leastInterval(tasks, n));
        System.out.println();

        // Test 2: Connect Ropes
        System.out.println("Test 2: Minimum Cost to Connect Ropes");
        int[] ropes = { 4, 3, 2, 6 };
        System.out.println("Ropes: " + Arrays.toString(ropes));
        System.out.println("Minimum cost: " + connectRopes(ropes));
        System.out.println();

        // Test 3: Sliding Window Median
        System.out.println("Test 3: Sliding Window Median");
        int[] nums3 = { 1, 3, -1, -3, 5, 3, 6, 7 };
        int k3 = 3;
        SlidingWindowMedian swm = new SlidingWindowMedian();
        double[] medians = swm.medianSlidingWindow(nums3, k3);
        System.out.println("Array: " + Arrays.toString(nums3) + ", k: " + k3);
        System.out.println("Medians: " + Arrays.toString(medians));
        System.out.println();

        // Test 4: K Smallest Pairs
        System.out.println("Test 4: K Pairs with Smallest Sums");
        int[] nums1 = { 1, 7, 11 };
        int[] nums2 = { 2, 4, 6 };
        int k4 = 3;
        List<int[]> pairs = kSmallestPairs(nums1, nums2, k4);
        System.out.println("nums1: " + Arrays.toString(nums1));
        System.out.println("nums2: " + Arrays.toString(nums2));
        System.out.print("K smallest pairs: ");
        for (int[] pair : pairs) {
            System.out.print(Arrays.toString(pair) + " ");
        }
        System.out.println("\n");

        // Test 5: Reorganize String
        System.out.println("Test 5: Reorganize String");
        String s = "aab";
        System.out.println("Input: " + s);
        System.out.println("Reorganized: " + reorganizeString(s));
        System.out.println();

        // Test 6: IPO
        System.out.println("Test 6: IPO - Maximize Capital");
        int k6 = 2, w = 0;
        int[] profits = { 1, 2, 3 };
        int[] capital = { 0, 1, 1 };
        System.out.println("k: " + k6 + ", initial capital: " + w);
        System.out.println("Profits: " + Arrays.toString(profits));
        System.out.println("Capital required: " + Arrays.toString(capital));
        System.out.println("Maximum capital: " + findMaximizedCapital(k6, w, profits, capital));
    }
}
