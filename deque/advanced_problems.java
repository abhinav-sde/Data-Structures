package deque;

import java.util.*;

public class advanced_problems {

    // Problem 1: Longest Subarray with Absolute Diff <= Limit
    static int longestSubarray(int[] nums, int limit) {
        Deque<Integer> maxDeque = new LinkedList<>();
        Deque<Integer> minDeque = new LinkedList<>();
        int left = 0, result = 0;

        for (int right = 0; right < nums.length; right++) {
            while (!maxDeque.isEmpty() && nums[maxDeque.peekLast()] < nums[right]) {
                maxDeque.pollLast();
            }
            while (!minDeque.isEmpty() && nums[minDeque.peekLast()] > nums[right]) {
                minDeque.pollLast();
            }

            maxDeque.offerLast(right);
            minDeque.offerLast(right);

            while (nums[maxDeque.peekFirst()] - nums[minDeque.peekFirst()] > limit) {
                if (maxDeque.peekFirst() == left)
                    maxDeque.pollFirst();
                if (minDeque.peekFirst() == left)
                    minDeque.pollFirst();
                left++;
            }

            result = Math.max(result, right - left + 1);
        }

        return result;
    }

    // Problem 2: Shortest Subarray with Sum >= K
    static int shortestSubarray(int[] nums, int k) {
        int n = nums.length;
        long[] prefixSum = new long[n + 1];

        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        Deque<Integer> deque = new LinkedList<>();
        int result = n + 1;

        for (int i = 0; i <= n; i++) {
            while (!deque.isEmpty() && prefixSum[i] - prefixSum[deque.peekFirst()] >= k) {
                result = Math.min(result, i - deque.pollFirst());
            }

            while (!deque.isEmpty() && prefixSum[i] <= prefixSum[deque.peekLast()]) {
                deque.pollLast();
            }

            deque.offerLast(i);
        }

        return result == n + 1 ? -1 : result;
    }

    public static void main(String[] args) {
        System.out.println("=== Advanced Deque Problems ===\n");

        System.out.println("Test 1: Longest Subarray with Absolute Diff <= Limit");
        int[] nums1 = { 8, 2, 4, 7 };
        int limit = 4;
        System.out.println("Result: " + longestSubarray(nums1, limit));
        System.out.println();

        System.out.println("Test 2: Shortest Subarray with Sum >= K");
        int[] nums2 = { 2, -1, 2 };
        int k = 3;
        System.out.println("Result: " + shortestSubarray(nums2, k));
    }
}
