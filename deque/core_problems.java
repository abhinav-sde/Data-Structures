package deque;

import java.util.*;

public class core_problems {

    // Problem 1: Sliding Window Maximum using Deque
    static int[] maxSlidingWindow(int[] nums, int k) {
        if (nums == null || k == 0)
            return new int[0];

        Deque<Integer> deque = new LinkedList<>();
        int[] result = new int[nums.length - k + 1];

        for (int i = 0; i < nums.length; i++) {
            // Remove elements outside window
            while (!deque.isEmpty() && deque.peekFirst() < i - k + 1) {
                deque.pollFirst();
            }

            // Remove smaller elements (they won't be max)
            while (!deque.isEmpty() && nums[deque.peekLast()] < nums[i]) {
                deque.pollLast();
            }

            deque.offerLast(i);

            if (i >= k - 1) {
                result[i - k + 1] = nums[deque.peekFirst()];
            }
        }

        return result;
    }

    // Problem 2: Implement Queue using Deque
    static class QueueUsingDeque {
        Deque<Integer> deque = new LinkedList<>();

        void enqueue(int val) {
            deque.offerLast(val);
        }

        int dequeue() {
            return deque.isEmpty() ? -1 : deque.pollFirst();
        }

        int front() {
            return deque.isEmpty() ? -1 : deque.peekFirst();
        }
    }

    // Problem 3: Implement Stack using Deque
    static class StackUsingDeque {
        Deque<Integer> deque = new LinkedList<>();

        void push(int val) {
            deque.offerLast(val);
        }

        int pop() {
            return deque.isEmpty() ? -1 : deque.pollLast();
        }

        int top() {
            return deque.isEmpty() ? -1 : deque.peekLast();
        }
    }

    // Problem 4: Check if Palindrome using Deque
    static boolean isPalindrome(String s) {
        Deque<Character> deque = new LinkedList<>();

        for (char c : s.toLowerCase().toCharArray()) {
            if (Character.isLetterOrDigit(c)) {
                deque.offerLast(c);
            }
        }

        while (deque.size() > 1) {
            if (deque.pollFirst() != deque.pollLast()) {
                return false;
            }
        }

        return true;
    }

    public static void main(String[] args) {
        System.out.println("=== Core Deque Problems ===\n");

        // Test 1: Sliding Window Maximum
        System.out.println("Test 1: Sliding Window Maximum");
        int[] nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
        int k = 3;
        int[] result = maxSlidingWindow(nums, k);
        System.out.println("Array: " + Arrays.toString(nums));
        System.out.println("k = " + k);
        System.out.println("Result: " + Arrays.toString(result));
        System.out.println();

        // Test 2: Queue using Deque
        System.out.println("Test 2: Queue using Deque");
        QueueUsingDeque queue = new QueueUsingDeque();
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);
        System.out.println("Dequeue: " + queue.dequeue());
        System.out.println("Front: " + queue.front());
        System.out.println();

        // Test 3: Palindrome Check
        System.out.println("Test 3: Palindrome Check");
        System.out.println("'racecar' is palindrome: " + isPalindrome("racecar"));
        System.out.println("'hello' is palindrome: " + isPalindrome("hello"));
    }
}
