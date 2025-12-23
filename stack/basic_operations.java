/**
 * Stack Basic Operations in Java
 * Contains Stack implementation using array
 */

import java.util.*;

public class basic_operations {
    
    // ========================================
    // STACK IMPLEMENTATION USING ARRAY
    // ========================================
    static class Stack {
        private static final int MAX_SIZE = 100;
        private int[] arr;
        private int topIndex;
        
        public Stack() {
            arr = new int[MAX_SIZE];
            topIndex = -1;
        }
        
        // Check if stack is empty
        public boolean isEmpty() {
            return topIndex == -1;
        }
        
        // Check if stack is full
        public boolean isFull() {
            return topIndex == MAX_SIZE - 1;
        }
        
        // Get current size
        public int size() {
            return topIndex + 1;
        }
        
        // Push element
        public void push(int value) {
            if (isFull()) {
                System.out.println("Stack Overflow! Cannot push " + value);
                return;
            }
            arr[++topIndex] = value;
            System.out.println("Pushed " + value + " to stack.");
        }
        
        // Pop element
        public int pop() {
            if (isEmpty()) {
                System.out.println("Stack Underflow! Cannot pop.");
                return -1;
            }
            int value = arr[topIndex--];
            System.out.println("Popped " + value + " from stack.");
            return value;
        }
        
        // Peek top element
        public int peek() {
            if (isEmpty()) {
                System.out.println("Stack is empty!");
                return -1;
            }
            return arr[topIndex];
        }
        
        // Display stack
        public void display() {
            if (isEmpty()) {
                System.out.println("Stack is empty.");
                return;
            }
            System.out.print("Stack (top to bottom): ");
            for (int i = topIndex; i >= 0; i--) {
                System.out.print(arr[i] + " ");
            }
            System.out.println();
        }
    }
    
    // ========================================
    // STANDALONE FUNCTIONS (Wrappers)
    // ========================================
    // Wrappers not strictly needed in Java as we use the class methods directly
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Stack Basic Operations ===");
        
        Stack stack = new Stack();
        
        // Push elements
        // stack.push(10);
        // stack.push(20);
        // stack.push(30);
        // stack.push(40);
        // stack.push(50);
        // stack.display();
        
        // Peek top element
        // System.out.println("Top element: " + stack.peek());
        
        // Get size
        // System.out.println("Stack size: " + stack.size());
        
        // Pop elements
        // stack.pop();
        // stack.pop();
        // stack.display();
    }
}
