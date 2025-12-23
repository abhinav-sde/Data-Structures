/**
 * Advanced Array Problems in Java
 * Contains complex array algorithms
 */

import java.util.*;

public class advanced_problems {
    
    // ========================================
    // UTILITY FUNCTION
    // ========================================
    
    static void display(int[] arr, int n) {
        System.out.print("Array: ");
        for (int i = 0; i < n; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }
    
    // ========================================
    // 1. KADANE'S ALGORITHM - Maximum Subarray Sum
    // ========================================
    static int kadaneMaxSubarraySum(int[] arr, int n) {
        int maxSoFar = Integer.MIN_VALUE;
        int maxEndingHere = 0;
        
        for (int i = 0; i < n; i++) {
            maxEndingHere += arr[i];
            if (maxSoFar < maxEndingHere) {
                maxSoFar = maxEndingHere;
            }
            if (maxEndingHere < 0) {
                maxEndingHere = 0;
            }
        }
        return maxSoFar;
    }
    
    // ========================================
    // 2. TWO SUM PROBLEM
    // ========================================
    static void twoSum(int[] arr, int n, int target) {
        Map<Integer, Integer> map = new HashMap<>();
        boolean found = false;
        
        for (int i = 0; i < n; i++) {
            int complement = target - arr[i];
            if (map.containsKey(complement)) {
                System.out.println(complement + " + " + arr[i] + " = " + target);
                found = true;
            }
            map.put(arr[i], i);
        }
        
        if (!found) {
            System.out.println("No pair found with sum " + target);
        }
    }
    
    // ========================================
    // 3. DUTCH NATIONAL FLAG - Sort 0s, 1s, 2s
    // ========================================
    static void dutchNationalFlag(int[] arr, int n) {
        int low = 0, mid = 0, high = n - 1;
        
        while (mid <= high) {
            if (arr[mid] == 0) {
                int temp = arr[low];
                arr[low] = arr[mid];
                arr[mid] = temp;
                low++;
                mid++;
            } else if (arr[mid] == 1) {
                mid++;
            } else {
                int temp = arr[mid];
                arr[mid] = arr[high];
                arr[high] = temp;
                high--;
            }
        }
        System.out.println("Array sorted (0s, 1s, 2s).");
    }
    
    // ========================================
    // 4. MOVE ALL ZEROS TO END
    // ========================================
    static void moveZerosToEnd(int[] arr, int n) {
        int nonZeroIndex = 0;
        
        for (int i = 0; i < n; i++) {
            if (arr[i] != 0) {
                arr[nonZeroIndex] = arr[i];
                nonZeroIndex++;
            }
        }
        
        while (nonZeroIndex < n) {
            arr[nonZeroIndex] = 0;
            nonZeroIndex++;
        }
        System.out.println("Zeros moved to end.");
    }
    
    // ========================================
    // 5. FIND MISSING NUMBER (1 to N)
    // ========================================
    static int findMissingNumber(int[] arr, int n) {
        int totalSum = (n + 1) * (n + 2) / 2;
        int arraySum = 0;
        
        for (int i = 0; i < n; i++) {
            arraySum += arr[i];
        }
        
        return totalSum - arraySum;
    }
    
    // ========================================
    // 6. FIND DUPLICATE NUMBER
    // ========================================
    static int findDuplicate(int[] arr, int n) {
        int xorAll = 0;
        for (int i = 0; i < n; i++) {
            xorAll ^= arr[i];
        }
        for (int i = 1; i <= n - 1; i++) {
            xorAll ^= i;
        }
        return xorAll;
    }
    
    // ========================================
    // 7. ROTATE ARRAY BY K POSITIONS
    // ========================================
    static void reverse(int[] arr, int start, int end) {
        while (start < end) {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
    }
    
    static void rotateArray(int[] arr, int n, int k) {
        k = k % n;
        
        reverse(arr, 0, n - 1);
        reverse(arr, 0, k - 1);
        reverse(arr, k, n - 1);
        
        System.out.println("Array rotated by " + k + " positions.");
    }
    
    // ========================================
    // 8. LEADERS IN ARRAY
    // ========================================
    static void findLeaders(int[] arr, int n) {
        System.out.print("Leaders: ");
        int maxFromRight = arr[n - 1];
        System.out.print(maxFromRight + " ");
        
        for (int i = n - 2; i >= 0; i--) {
            if (arr[i] > maxFromRight) {
                maxFromRight = arr[i];
                System.out.print(maxFromRight + " ");
            }
        }
        System.out.println();
    }
    
    // ========================================
    // 9. STOCK BUY AND SELL (Single Transaction)
    // ========================================
    static int maxStockProfit(int[] arr, int n) {
        if (n < 2) return 0;
        
        int minPrice = arr[0];
        int maxProfit = 0;
        
        for (int i = 1; i < n; i++) {
            minPrice = Math.min(minPrice, arr[i]);
            maxProfit = Math.max(maxProfit, arr[i] - minPrice);
        }
        
        return maxProfit;
    }
    
    // ========================================
    // 10. MERGE TWO SORTED ARRAYS
    // ========================================
    static void mergeSortedArrays(int[] arr1, int n1, int[] arr2, int n2, int[] result) {
        int i = 0, j = 0, k = 0;
        
        while (i < n1 && j < n2) {
            if (arr1[i] <= arr2[j]) {
                result[k++] = arr1[i++];
            } else {
                result[k++] = arr2[j++];
            }
        }
        
        while (i < n1) {
            result[k++] = arr1[i++];
        }
        
        while (j < n2) {
            result[k++] = arr2[j++];
        }
        
        System.out.println("Arrays merged.");
    }
    
    // ========================================
    // 11. FIND SUBARRAY WITH GIVEN SUM
    // ========================================
    static void findSubarrayWithSum(int[] arr, int n, int targetSum) {
        int currentSum = arr[0];
        int start = 0;
        
        for (int end = 1; end <= n; end++) {
            while (currentSum > targetSum && start < end - 1) {
                currentSum -= arr[start];
                start++;
            }
            
            if (currentSum == targetSum) {
                System.out.println("Sum found between index " + start + " and " + (end - 1));
                return;
            }
            
            if (end < n) {
                currentSum += arr[end];
            }
        }
        
        System.out.println("No subarray found with sum " + targetSum);
    }
    
    // ========================================
    // 12. FIND MAJORITY ELEMENT (appears > n/2 times)
    // ========================================
    static int findMajorityElement(int[] arr, int n) {
        int candidate = -1;
        int count = 0;
        
        // Find candidate
        for (int i = 0; i < n; i++) {
            if (count == 0) {
                candidate = arr[i];
                count = 1;
            } else if (arr[i] == candidate) {
                count++;
            } else {
                count--;
            }
        }
        
        // Verify candidate
        count = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] == candidate) {
                count++;
            }
        }
        
        if (count > n / 2) {
            return candidate;
        }
        return -1;
    }
    
    // ========================================
    // 13. TRAPPING RAIN WATER
    // ========================================
    static int trappingRainWater(int[] arr, int n) {
        if (n <= 2) return 0;
        
        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int water = 0;
        
        while (left < right) {
            if (arr[left] < arr[right]) {
                if (arr[left] >= leftMax) {
                    leftMax = arr[left];
                } else {
                    water += leftMax - arr[left];
                }
                left++;
            } else {
                if (arr[right] >= rightMax) {
                    rightMax = arr[right];
                } else {
                    water += rightMax - arr[right];
                }
                right--;
            }
        }
        return water;
    }
    
    // ========================================
    // 14. LONGEST CONSECUTIVE SEQUENCE
    // ========================================
    static int longestConsecutive(int[] arr, int n) {
        Set<Integer> set = new HashSet<>();
        
        for (int i = 0; i < n; i++) {
            set.add(arr[i]);
        }
        
        int maxLength = 0;
        
        for (int i = 0; i < n; i++) {
            if (!set.contains(arr[i] - 1)) {
                int currentNum = arr[i];
                int currentLength = 1;
                
                while (set.contains(currentNum + 1)) {
                    currentNum++;
                    currentLength++;
                }
                
                maxLength = Math.max(maxLength, currentLength);
            }
        }
        return maxLength;
    }
    
    // ========================================
    // 15. PRODUCT OF ARRAY EXCEPT SELF
    // ========================================
    static void productExceptSelf(int[] arr, int n, int[] result) {
        result[0] = 1;
        for (int i = 1; i < n; i++) {
            result[i] = result[i - 1] * arr[i - 1];
        }
        
        int rightProduct = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= rightProduct;
            rightProduct *= arr[i];
        }
        
        System.out.println("Product array calculated.");
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
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
        
        // 1. Kadane's Algorithm
        // int maxSum = kadaneMaxSubarraySum(arr, n);
        // System.out.println("Maximum subarray sum: " + maxSum);
        
        // 2. Two Sum Problem
        // twoSum(arr, n, 9);
        
        // 3. Dutch National Flag
        // dutchNationalFlag(arr, n);
        // display(arr, n);
        
        // 4. Move Zeros to End
        // moveZerosToEnd(arr, n);
        // display(arr, n);
        
        // 5. Find Missing Number
        // int missing = findMissingNumber(arr, n);
        // System.out.println("Missing number: " + missing);
        
        // 6. Find Duplicate Number
        // int duplicate = findDuplicate(arr, n);
        // System.out.println("Duplicate number: " + duplicate);
        
        // 7. Rotate Array
        // rotateArray(arr, n, 2);
        // display(arr, n);
        
        // 8. Find Leaders
        // findLeaders(arr, n);
        
        // 9. Stock Buy and Sell
        // int profit = maxStockProfit(arr, n);
        // System.out.println("Maximum profit: " + profit);
        
        // 10. Merge Two Sorted Arrays
        // int[] arr2 = {2, 4, 6, 8};
        // int n2 = 4;
        // int[] result = new int[n + n2];
        // mergeSortedArrays(arr, n, arr2, n2, result);
        // display(result, n + n2);
        
        // 11. Find Subarray with Given Sum
        // findSubarrayWithSum(arr, n, 33);
        
        // 12. Find Majority Element
        // int majority = findMajorityElement(arr, n);
        // if (majority != -1) {
        //     System.out.println("Majority element: " + majority);
        // } else {
        //     System.out.println("No majority element found.");
        // }
        
        // 13. Trapping Rain Water
        // int water = trappingRainWater(arr, n);
        // System.out.println("Water trapped: " + water + " units");
        
        // 14. Longest Consecutive Sequence
        // int length = longestConsecutive(arr, n);
        // System.out.println("Longest consecutive sequence length: " + length);
        
        // 15. Product of Array Except Self
        // int[] productArr = new int[n];
        // productExceptSelf(arr, n, productArr);
        // display(productArr, n);
        
        scanner.close();
    }
}
