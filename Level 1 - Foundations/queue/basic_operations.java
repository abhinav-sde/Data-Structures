/**
 * Queue Basic Operations in Java
 * Contains Queue implementation using array and Circular Queue
 */

import java.util.*;

public class basic_operations {
    
    // ========================================
    // QUEUE IMPLEMENTATION USING ARRAY
    // ========================================
    static class Queue {
        private static final int MAX_SIZE = 100;
        private int[] arr;
        private int front, rear, count;
        
        public Queue() {
            arr = new int[MAX_SIZE];
            front = 0;
            rear = -1;
            count = 0;
        }
        
        // Check if queue is empty
        public boolean isEmpty() {
            return count == 0;
        }
        
        // Check if queue is full
        public boolean isFull() {
            return count == MAX_SIZE;
        }
        
        // Get current size
        public int size() {
            return count;
        }
        
        // Enqueue element
        public void enqueue(int value) {
            if (isFull()) {
                System.out.println("Queue Overflow! Cannot enqueue " + value);
                return;
            }
            rear = (rear + 1) % MAX_SIZE;
            arr[rear] = value;
            count++;
            System.out.println("Enqueued " + value + " to queue.");
        }
        
        // Dequeue element
        public int dequeue() {
            if (isEmpty()) {
                System.out.println("Queue Underflow! Cannot dequeue.");
                return -1;
            }
            int value = arr[front];
            front = (front + 1) % MAX_SIZE;
            count--;
            System.out.println("Dequeued " + value + " from queue.");
            return value;
        }
        
        // Peek front element
        public int peek() {
            if (isEmpty()) {
                System.out.println("Queue is empty!");
                return -1;
            }
            return arr[front];
        }
        
        // Display queue
        public void display() {
            if (isEmpty()) {
                System.out.println("Queue is empty.");
                return;
            }
            System.out.print("Queue (front to rear): ");
            int idx = front;
            for (int i = 0; i < count; i++) {
                System.out.print(arr[idx] + " ");
                idx = (idx + 1) % MAX_SIZE;
            }
            System.out.println();
        }
    }
    
    // ========================================
    // CIRCULAR QUEUE IMPLEMENTATION
    // ========================================
    static class CircularQueue {
        private static final int MAX_SIZE = 100;
        private int[] arr;
        private int front, rear;
        
        public CircularQueue() {
            arr = new int[MAX_SIZE];
            front = -1;
            rear = -1;
        }
        
        public boolean isEmpty() {
            return front == -1;
        }
        
        public boolean isFull() {
            return (rear + 1) % MAX_SIZE == front;
        }
        
        public void enqueue(int value) {
            if (isFull()) {
                System.out.println("Circular Queue is full!");
                return;
            }
            if (isEmpty()) {
                front = rear = 0;
            } else {
                rear = (rear + 1) % MAX_SIZE;
            }
            arr[rear] = value;
            System.out.println("Enqueued " + value + " to circular queue.");
        }
        
        public int dequeue() {
            if (isEmpty()) {
                System.out.println("Circular Queue is empty!");
                return -1;
            }
            int value = arr[front];
            if (front == rear) {
                front = rear = -1;
            } else {
                front = (front + 1) % MAX_SIZE;
            }
            System.out.println("Dequeued " + value + " from circular queue.");
            return value;
        }
        
        public void display() {
            if (isEmpty()) {
                System.out.println("Circular Queue is empty.");
                return;
            }
            System.out.print("Circular Queue: ");
            int i = front;
            while (true) {
                System.out.print(arr[i] + " ");
                if (i == rear) break;
                i = (i + 1) % MAX_SIZE;
            }
            System.out.println();
        }
    }
    
    // ========================================
    // STANDALONE FUNCTIONS (Wrappers)
    // ========================================
    
    // Wrappers not strictly needed in Java as we use the class methods directly
    // but kept for structure similarity.
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Queue Basic Operations ===");
        
        Queue queue = new Queue();
        
        // Enqueue elements
        // queue.enqueue(10);
        // queue.enqueue(20);
        // queue.enqueue(30);
        // queue.enqueue(40);
        // queue.enqueue(50);
        // queue.display();
        
        // Peek front element
        // System.out.println("Front element: " + queue.peek());
        
        // Get size
        // System.out.println("Queue size: " + queue.size());
        
        // Dequeue elements
        // queue.dequeue();
        // queue.dequeue();
        // queue.display();
        
        // Circular Queue Example
        // System.out.println("\n=== Circular Queue ===");
        // CircularQueue cq = new CircularQueue();
        // cq.enqueue(1);
        // cq.enqueue(2);
        // cq.enqueue(3);
        // cq.display();
    }
}
