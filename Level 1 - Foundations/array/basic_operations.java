/**
 * Basic Array Operations in Java
 * Contains fundamental array manipulation functions
 */

import java.util.Scanner;

public class basic_operations {
    
    // Function to display the array
    // Usage: display(arr, n) - displays all n elements
    static void display(int[] arr, int n) {
        if (n == 0) {
            System.out.println("Array is empty.");
            return;
        }
        System.out.print("Array elements: ");
        for (int i = 0; i < n; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }
    
    // Function to insert at start
    // Usage: newSize = insertAtStart(arr, n, capacity, value)
    // Example: newSize = insertAtStart(arr, 5, 10, 99) - inserts 99 at start
    static int insertAtStart(int[] arr, int n, int capacity, int val) {
        if (n == capacity) {
            System.out.println("Array is full. Cannot insert.");
            return n;
        }
        for (int i = n; i > 0; i--) {
            arr[i] = arr[i - 1];
        }
        arr[0] = val;
        System.out.println("Inserted " + val + " at start.");
        return n + 1;
    }
    
    // Function to insert at end
    // Usage: newSize = insertAtEnd(arr, n, capacity, value)
    // Example: newSize = insertAtEnd(arr, 5, 10, 99) - inserts 99 at end
    static int insertAtEnd(int[] arr, int n, int capacity, int val) {
        if (n == capacity) {
            System.out.println("Array is full. Cannot insert.");
            return n;
        }
        arr[n] = val;
        System.out.println("Inserted " + val + " at end.");
        return n + 1;
    }
    
    // Function to insert at specific index
    // Usage: newSize = insertAtIndex(arr, n, capacity, index, value)
    // Example: newSize = insertAtIndex(arr, 5, 10, 2, 99) - inserts 99 at index 2
    static int insertAtIndex(int[] arr, int n, int capacity, int index, int val) {
        if (n == capacity) {
            System.out.println("Array is full. Cannot insert.");
            return n;
        }
        if (index < 0 || index > n) {
            System.out.println("Invalid index.");
            return n;
        }
        for (int i = n; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = val;
        System.out.println("Inserted " + val + " at index " + index + ".");
        return n + 1;
    }
    
    // Function to delete at specific index
    // Usage: newSize = deleteAtIndex(arr, n, index)
    // Example: newSize = deleteAtIndex(arr, 5, 2) - deletes element at index 2
    static int deleteAtIndex(int[] arr, int n, int index) {
        if (n == 0) {
            System.out.println("Array is empty. Cannot delete.");
            return n;
        }
        if (index < 0 || index >= n) {
            System.out.println("Invalid index.");
            return n;
        }
        int deletedVal = arr[index];
        for (int i = index; i < n - 1; i++) {
            arr[i] = arr[i + 1];
        }
        System.out.println("Deleted " + deletedVal + " from index " + index + ".");
        return n - 1;
    }
    
    // Function to delete by value (first occurrence)
    // Usage: newSize = deleteValue(arr, n, value)
    // Example: newSize = deleteValue(arr, 5, 30) - deletes first occurrence of 30
    static int deleteValue(int[] arr, int n, int val) {
        if (n == 0) {
            System.out.println("Array is empty. Cannot delete.");
            return n;
        }
        int index = -1;
        for (int i = 0; i < n; i++) {
            if (arr[i] == val) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            System.out.println("Value " + val + " not found.");
            return n;
        }
        return deleteAtIndex(arr, n, index);
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter array capacity: ");
        int capacity = scanner.nextInt();
        
        int[] arr = new int[capacity];
        
        System.out.print("Enter number of elements: ");
        int n = scanner.nextInt();
        
        if (n > capacity) {
            System.out.println("Size exceeds capacity. Setting size to capacity.");
            n = capacity;
        }
        
        System.out.print("Enter " + n + " elements: ");
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
        }
        
        System.out.println("\n=== Initial Array ===");
        display(arr, n);
        
        // ========================================
        // Example function calls - uncomment to use
        // ========================================
        
        // Insert at start
        // n = insertAtStart(arr, n, capacity, 5);
        // display(arr, n);
        
        // Insert at end
        // n = insertAtEnd(arr, n, capacity, 60);
        // display(arr, n);
        
        // Insert at index 2
        // n = insertAtIndex(arr, n, capacity, 2, 25);
        // display(arr, n);
        
        // Delete at index 1
        // n = deleteAtIndex(arr, n, 1);
        // display(arr, n);
        
        // Delete value 30
        // n = deleteValue(arr, n, 30);
        // display(arr, n);
        
        scanner.close();
    }
}
