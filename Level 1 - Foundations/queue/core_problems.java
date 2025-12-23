/**
 * Queue Core Problems in Java
 * Contains standard Queue algorithms
 */

import java.util.*;

public class core_problems {
    
    // ========================================
    // 1. REVERSE A QUEUE
    // ========================================
    static void reverseQueue(Queue<Integer> q) {
        Stack<Integer> st = new Stack<>();
        
        while (!q.isEmpty()) {
            st.push(q.poll());
        }
        
        while (!st.isEmpty()) {
            q.add(st.pop());
        }
        
        System.out.println("Queue reversed.");
    }
    
    // ========================================
    // 2. IMPLEMENT QUEUE USING STACKS
    // ========================================
    static class QueueUsingStacks {
        private Stack<Integer> s1 = new Stack<>();
        private Stack<Integer> s2 = new Stack<>();
        
        public void enqueue(int value) {
            s1.push(value);
            System.out.println("Enqueued " + value);
        }
        
        public int dequeue() {
            if (s1.isEmpty() && s2.isEmpty()) {
                System.out.println("Queue is empty!");
                return -1;
            }
            
            if (s2.isEmpty()) {
                while (!s1.isEmpty()) {
                    s2.push(s1.pop());
                }
            }
            
            return s2.pop();
        }
        
        public int peek() {
            if (s1.isEmpty() && s2.isEmpty()) {
                System.out.println("Queue is empty!");
                return -1;
            }
            
            if (s2.isEmpty()) {
                while (!s1.isEmpty()) {
                    s2.push(s1.pop());
                }
            }
            
            return s2.peek();
        }
        
        public boolean empty() {
            return s1.isEmpty() && s2.isEmpty();
        }
    }
    
    // ========================================
    // 3. IMPLEMENT STACK USING QUEUES
    // ========================================
    static class StackUsingQueue {
        private Queue<Integer> q = new LinkedList<>();
        
        public void push(int value) {
            int size = q.size();
            q.add(value);
            
            for (int i = 0; i < size; i++) {
                q.add(q.poll());
            }
            
            System.out.println("Pushed " + value);
        }
        
        public int pop() {
            if (q.isEmpty()) {
                System.out.println("Stack is empty!");
                return -1;
            }
            return q.poll();
        }
        
        public int top() {
            if (q.isEmpty()) {
                System.out.println("Stack is empty!");
                return -1;
            }
            return q.peek();
        }
        
        public boolean empty() {
            return q.isEmpty();
        }
    }
    
    // ========================================
    // 4. GENERATE BINARY NUMBERS FROM 1 TO N
    // ========================================
    static void generateBinary(int n) {
        Queue<String> q = new LinkedList<>();
        q.add("1");
        
        System.out.print("Binary numbers from 1 to " + n + ": ");
        for (int i = 0; i < n; i++) {
            String current = q.poll();
            System.out.print(current + " ");
            
            q.add(current + "0");
            q.add(current + "1");
        }
        System.out.println();
    }
    
    // ========================================
    // 5. FIRST NON-REPEATING CHARACTER IN STREAM
    // ========================================
    static void firstNonRepeating(String stream) {
        Queue<Character> q = new LinkedList<>();
        int[] freq = new int[26];
        
        System.out.print("First non-repeating characters: ");
        for (char ch : stream.toCharArray()) {
            q.add(ch);
            freq[ch - 'a']++;
            
            while (!q.isEmpty() && freq[q.peek() - 'a'] > 1) {
                q.poll();
            }
            
            if (q.isEmpty()) {
                System.out.print("-1 ");
            } else {
                System.out.print(q.peek() + " ");
            }
        }
        System.out.println();
    }
    
    // ========================================
    // 6. CIRCULAR TOUR (GAS STATION PROBLEM)
    // ========================================
    static int circularTour(int[] petrol, int[] distance, int n) {
        int start = 0;
        int deficit = 0;
        int balance = 0;
        
        for (int i = 0; i < n; i++) {
            balance += petrol[i] - distance[i];
            
            if (balance < 0) {
                deficit += balance;
                start = i + 1;
                balance = 0;
            }
        }
        
        return (balance + deficit >= 0) ? start : -1;
    }
    
    // ========================================
    // 7. REVERSE FIRST K ELEMENTS OF QUEUE
    // ========================================
    static void reverseFirstK(Queue<Integer> q, int k) {
        if (q.isEmpty() || k > q.size()) {
            System.out.println("Invalid operation!");
            return;
        }
        
        Stack<Integer> st = new Stack<>();
        
        // Push first k elements to stack
        for (int i = 0; i < k; i++) {
            st.push(q.poll());
        }
        
        // Enqueue from stack
        while (!st.isEmpty()) {
            q.add(st.pop());
        }
        
        // Move remaining elements to back
        int remaining = q.size() - k;
        for (int i = 0; i < remaining; i++) {
            q.add(q.poll());
        }
        
        System.out.println("First " + k + " elements reversed.");
    }
    
    // ========================================
    // 8. INTERLEAVE FIRST AND SECOND HALF OF QUEUE
    // ========================================
    static void interleaveQueue(Queue<Integer> q) {
        if (q.size() % 2 != 0) {
            System.out.println("Queue size must be even!");
            return;
        }
        
        int halfSize = q.size() / 2;
        Queue<Integer> firstHalf = new LinkedList<>();
        
        // Store first half
        for (int i = 0; i < halfSize; i++) {
            firstHalf.add(q.poll());
        }
        
        // Interleave
        while (!firstHalf.isEmpty()) {
            q.add(firstHalf.poll());
            q.add(q.poll());
        }
        
        System.out.println("Queue interleaved.");
    }
    
    // ========================================
    // 9. PRIORITY QUEUE OPERATIONS
    // ========================================
    static void priorityQueueDemo() {
        // Max heap (default in C++ is max, in Java is min, so we revert comparison)
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        maxHeap.add(10);
        maxHeap.add(30);
        maxHeap.add(20);
        maxHeap.add(5);
        
        System.out.print("Max Heap (descending): ");
        while (!maxHeap.isEmpty()) {
            System.out.print(maxHeap.poll() + " ");
        }
        System.out.println();
        
        // Min heap
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        minHeap.add(10);
        minHeap.add(30);
        minHeap.add(20);
        minHeap.add(5);
        
        System.out.print("Min Heap (ascending): ");
        while (!minHeap.isEmpty()) {
            System.out.print(minHeap.poll() + " ");
        }
        System.out.println();
    }
    
    // ========================================
    // 10. DEQUE OPERATIONS
    // ========================================
    static void dequeDemo() {
        Deque<Integer> dq = new ArrayDeque<>();
        
        // Insert at both ends
        dq.addLast(10);
        dq.addLast(20);
        dq.addFirst(5);
        dq.addFirst(1);
        
        System.out.print("Deque: ");
        for (int val : dq) {
            System.out.print(val + " ");
        }
        System.out.println();
        
        // Remove from both ends
        dq.removeFirst();
        dq.removeLast();
        
        System.out.print("After removing from both ends: ");
        for (int val : dq) {
            System.out.print(val + " ");
        }
        System.out.println();
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Queue Core Problems ===");
        
        // Example usage - uncomment to use
        
        // 1. Reverse Queue
        // Queue<Integer> q = new LinkedList<>();
        // q.add(1); q.add(2); q.add(3); q.add(4); q.add(5);
        // reverseQueue(q);
        // System.out.println("Reversed queue: " + q);
        
        // 4. Generate Binary Numbers
        // generateBinary(10);
        
        // 5. First Non-Repeating Character
        // firstNonRepeating("aabcc");
        
        // 7. Reverse First K Elements
        // Queue<Integer> q2 = new LinkedList<>();
        // q2.add(1); q2.add(2); q2.add(3); q2.add(4); q2.add(5);
        // reverseFirstK(q2, 3);
        // System.out.println("Queue: " + q2);
        
        // 9. Priority Queue Demo
        // priorityQueueDemo();
        
        // 10. Deque Demo
        // dequeDemo();
    }
}
