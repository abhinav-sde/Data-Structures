/**
 * Core Array Problems in Java
 * Contains essential array algorithms
 */

import java.util.Scanner;
import java.util.Arrays;

public class core_problems {
    
    // Function to display the array
    static void display(int[] arr, int n) {
        System.out.print("Array: ");
        for (int i = 0; i < n; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }
    
    // Function for linear search
    static int linearSearch(int[] arr, int n, int key) {
        for (int i = 0; i < n; i++) {
            if (arr[i] == key) {
                return i;
            }
        }
        return -1;
    }
    
    // Function for binary search (requires sorted array)
    static int binarySearch(int[] arr, int n, int key) {
        int low = 0, high = n - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] == key) {
                return mid;
            } else if (arr[mid] < key) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }
    
    // Function to reverse the array
    static void reverseArray(int[] arr, int n) {
        int start = 0, end = n - 1;
        while (start < end) {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
        System.out.println("Array reversed.");
    }
    
    // Function to find minimum and maximum
    static void findMinMax(int[] arr, int n) {
        if (n == 0) {
            System.out.println("Array is empty.");
            return;
        }
        int minVal = arr[0];
        int maxVal = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] < minVal) minVal = arr[i];
            if (arr[i] > maxVal) maxVal = arr[i];
        }
        System.out.println("Min: " + minVal + ", Max: " + maxVal);
    }
    
    // Function to check if array is sorted
    static boolean checkSorted(int[] arr, int n) {
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
        }
        return true;
    }
    
    // Function to sort the array
    static void sortArray(int[] arr, int n) {
        Arrays.sort(arr, 0, n);
        System.out.println("Array sorted.");
    }
    
    // Function to find sum of all elements
    static int sumArray(int[] arr, int n) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
        }
        return sum;
    }
    
    // Function to find average of all elements
    static double averageArray(int[] arr, int n) {
        if (n == 0) return 0.0;
        return (double)sumArray(arr, n) / n;
    }
    
    // Function to count occurrences of a value
    static int countOccurrences(int[] arr, int n, int value) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] == value) {
                count++;
            }
        }
        return count;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter number of elements: ");
        int n = scanner.nextInt();
        
        int[] arr = new int[n];
        
        System.out.print("Enter " + n + " elements: ");
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
        }
        
        System.out.println("\n=== Initial Array ===");
        display(arr, n);
        
        // ========================================
        // Example function calls - uncomment to use
        // ========================================
        
        // Linear search for value 30
        // int index = linearSearch(arr, n, 30);
        // System.out.println("Index of 30: " + index);
        
        // Sort and then binary search
        // sortArray(arr, n);
        // display(arr, n);
        // int index = binarySearch(arr, n, 30);
        // System.out.println("Index of 30: " + index);
        
        // Reverse array
        // reverseArray(arr, n);
        // display(arr, n);
        
        // Find min and max
        // findMinMax(arr, n);
        
        // Check if sorted
        // if (checkSorted(arr, n)) {
        //     System.out.println("Array is sorted.");
        // } else {
        //     System.out.println("Array is NOT sorted.");
        // }
        
        // Find sum
        // int sum = sumArray(arr, n);
        // System.out.println("Sum: " + sum);
        
        // Find average
        // double avg = averageArray(arr, n);
        // System.out.println("Average: " + avg);
        
        // Count occurrences of 30
        // int count = countOccurrences(arr, n, 30);
        // System.out.println("Occurrences of 30: " + count);
        
        scanner.close();
    }
}
