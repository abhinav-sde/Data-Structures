
/**
 * Basic Deque (Double-Ended Queue) Operations in Java
 * Supports insertion and deletion from both ends
 */

import java.util.*;

public class basic_operations {

    // Deque implementation using circular array
    static class Deque {
        private int[] arr;
        private int front, rear, size, capacity;

        public Deque(int capacity) {
            this.capacity = capacity;
            this.arr = new int[capacity];
            this.front = -1;
            this.rear = 0;
            this.size = 0;
        }

        // Insert at front
        // Time Complexity: O(1)
        public void pushFront(int val) {
            if (isFull()) {
                System.out.println("Deque is full. Cannot push " + val + " at front");
                return;
            }

            if (front == -1) {
                front = rear = 0;
            } else {
                front = (front - 1 + capacity) % capacity;
            }

            arr[front] = val;
            size++;
            System.out.println("Pushed " + val + " at front");
        }

        // Insert at rear
        // Time Complexity: O(1)
        public void pushRear(int val) {
            if (isFull()) {
                System.out.println("Deque is full. Cannot push " + val + " at rear");
                return;
            }

            if (front == -1) {
                front = rear = 0;
            } else {
                rear = (rear + 1) % capacity;
            }

            arr[rear] = val;
            size++;
            System.out.println("Pushed " + val + " at rear");
        }

        // Delete from front
        // Time Complexity: O(1)
        public int popFront() {
            if (isEmpty()) {
                System.out.println("Deque is empty");
                return -1;
            }

            int val = arr[front];

            if (front == rear) {
                front = rear = -1;
            } else {
                front = (front + 1) % capacity;
            }

            size--;
            return val;
        }

        // Delete from rear
        // Time Complexity: O(1)
        public int popRear() {
            if (isEmpty()) {
                System.out.println("Deque is empty");
                return -1;
            }

            int val = arr[rear];

            if (front == rear) {
                front = rear = -1;
            } else {
                rear = (rear - 1 + capacity) % capacity;
            }

            size--;
            return val;
        }

        // Get front element
        public int getFront() {
            if (isEmpty()) {
                System.out.println("Deque is empty");
                return -1;
            }
            return arr[front];
        }

        // Get rear element
        public int getRear() {
            if (isEmpty()) {
                System.out.println("Deque is empty");
                return -1;
            }
            return arr[rear];
        }

        // Check if empty
        public boolean isEmpty() {
            return size == 0;
        }

        // Check if full
        public boolean isFull() {
            return size == capacity;
        }

        // Get size
        public int size() {
            return size;
        }

        // Display deque
        public void display() {
            if (isEmpty()) {
                System.out.println("Deque is empty");
                return;
            }

            System.out.print("Deque: ");
            int i = front;
            for (int count = 0; count < size; count++) {
                System.out.print(arr[i] + " ");
                i = (i + 1) % capacity;
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Deque Basic Operations Demo ===\n");

        Deque deque = new Deque(5);

        // Test push operations
        System.out.println("--- Push Operations ---");
        deque.pushRear(10);
        deque.pushRear(20);
        deque.pushFront(5);
        deque.pushFront(1);
        deque.display();
        System.out.println();

        // Test peek operations
        System.out.println("--- Peek Operations ---");
        System.out.println("Front: " + deque.getFront());
        System.out.println("Rear: " + deque.getRear());
        System.out.println("Size: " + deque.size());
        System.out.println();

        // Test pop operations
        System.out.println("--- Pop Operations ---");
        System.out.println("Popped from front: " + deque.popFront());
        deque.display();

        System.out.println("Popped from rear: " + deque.popRear());
        deque.display();
        System.out.println();

        // Test full capacity
        System.out.println("--- Testing Capacity ---");
        deque.pushRear(30);
        deque.pushRear(40);
        deque.pushRear(50);
        deque.display();

        deque.pushRear(60); // Should fail - full
        System.out.println();

        // Empty the deque
        System.out.println("--- Emptying Deque ---");
        while (!deque.isEmpty()) {
            System.out.println("Popped: " + deque.popFront());
        }
        deque.display();
    }
}
