#include <iostream>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <vector>
using namespace std;

// ========================================
// UTILITY FUNCTION
// ========================================

void display(int arr[], int n) {
    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// ========================================
// 1. KADANE'S ALGORITHM - Maximum Subarray Sum
// ========================================
// Concept: Dynamic Programming
// Usage: maxSum = kadaneMaxSubarraySum(arr, n)
// Example: arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4} returns 6 (subarray: {4, -1, 2, 1})
int kadaneMaxSubarraySum(int arr[], int n) {
    int maxSoFar = INT_MIN;
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
// Concept: Hashing
// Usage: twoSum(arr, n, target) - prints pairs that sum to target
// Example: arr = {2, 7, 11, 15}, target = 9 prints "2 + 7 = 9"
void twoSum(int arr[], int n, int target) {
    unordered_map<int, int> map;
    bool found = false;
    
    for (int i = 0; i < n; i++) {
        int complement = target - arr[i];
        if (map.find(complement) != map.end()) {
            cout << complement << " + " << arr[i] << " = " << target << endl;
            found = true;
        }
        map[arr[i]] = i;
    }
    
    if (!found) {
        cout << "No pair found with sum " << target << endl;
    }
}

// ========================================
// 3. DUTCH NATIONAL FLAG - Sort 0s, 1s, 2s
// ========================================
// Concept: Three-way partitioning
// Usage: dutchNationalFlag(arr, n) - sorts array of 0s, 1s, 2s in O(n)
// Example: arr = {0, 1, 2, 0, 1, 2} becomes {0, 0, 1, 1, 2, 2}
void dutchNationalFlag(int arr[], int n) {
    int low = 0, mid = 0, high = n - 1;
    
    while (mid <= high) {
        if (arr[mid] == 0) {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] == 1) {
            mid++;
        } else {
            swap(arr[mid], arr[high]);
            high--;
        }
    }
    cout << "Array sorted (0s, 1s, 2s)." << endl;
}

// ========================================
// 4. MOVE ALL ZEROS TO END
// ========================================
// Concept: Two-pointer technique
// Usage: moveZerosToEnd(arr, n) - moves all zeros to end while maintaining order
// Example: arr = {1, 0, 2, 0, 3} becomes {1, 2, 3, 0, 0}
void moveZerosToEnd(int arr[], int n) {
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
    cout << "Zeros moved to end." << endl;
}

// ========================================
// 5. FIND MISSING NUMBER (1 to N)
// ========================================
// Concept: Mathematical formula (Sum of N natural numbers)
// Usage: missing = findMissingNumber(arr, n)
// Example: arr = {1, 2, 4, 5} (n=4, should have 1-5) returns 3
int findMissingNumber(int arr[], int n) {
    int totalSum = (n + 1) * (n + 2) / 2;  // Sum of 1 to n+1
    int arraySum = 0;
    
    for (int i = 0; i < n; i++) {
        arraySum += arr[i];
    }
    
    return totalSum - arraySum;
}

// ========================================
// 6. FIND DUPLICATE NUMBER
// ========================================
// Concept: Floyd's Cycle Detection (Tortoise and Hare)
// Usage: duplicate = findDuplicate(arr, n)
// Example: arr = {1, 3, 4, 2, 2} returns 2
int findDuplicate(int arr[], int n) {
    // Using XOR approach for simplicity
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
// Concept: Reversal algorithm
// Usage: rotateArray(arr, n, k) - rotates array right by k positions
// Example: arr = {1, 2, 3, 4, 5}, k = 2 becomes {4, 5, 1, 2, 3}
void rotateArray(int arr[], int n, int k) {
    k = k % n;  // Handle k > n
    
    // Reverse entire array
    reverse(arr, arr + n);
    // Reverse first k elements
    reverse(arr, arr + k);
    // Reverse remaining elements
    reverse(arr + k, arr + n);
    
    cout << "Array rotated by " << k << " positions." << endl;
}

// ========================================
// 8. LEADERS IN ARRAY
// ========================================
// Concept: Traverse from right
// Usage: findLeaders(arr, n) - prints all leaders (elements greater than all to right)
// Example: arr = {16, 17, 4, 3, 5, 2} prints "17 5 2"
void findLeaders(int arr[], int n) {
    cout << "Leaders: ";
    int maxFromRight = arr[n - 1];
    cout << maxFromRight << " ";
    
    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] > maxFromRight) {
            maxFromRight = arr[i];
            cout << maxFromRight << " ";
        }
    }
    cout << endl;
}

// ========================================
// 9. STOCK BUY AND SELL (Single Transaction)
// ========================================
// Concept: Track minimum and maximum profit
// Usage: maxProfit = maxStockProfit(arr, n)
// Example: arr = {7, 1, 5, 3, 6, 4} returns 5 (buy at 1, sell at 6)
int maxStockProfit(int arr[], int n) {
    if (n < 2) return 0;
    
    int minPrice = arr[0];
    int maxProfit = 0;
    
    for (int i = 1; i < n; i++) {
        minPrice = min(minPrice, arr[i]);
        maxProfit = max(maxProfit, arr[i] - minPrice);
    }
    
    return maxProfit;
}

// ========================================
// 10. MERGE TWO SORTED ARRAYS
// ========================================
// Concept: Two-pointer technique
// Usage: mergeSortedArrays(arr1, n1, arr2, n2, result)
// Example: arr1 = {1, 3, 5}, arr2 = {2, 4, 6} -> result = {1, 2, 3, 4, 5, 6}
void mergeSortedArrays(int arr1[], int n1, int arr2[], int n2, int result[]) {
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
    
    cout << "Arrays merged." << endl;
}

// ========================================
// 11. FIND SUBARRAY WITH GIVEN SUM
// ========================================
// Concept: Sliding window
// Usage: findSubarrayWithSum(arr, n, targetSum) - prints subarray indices
// Example: arr = {1, 4, 20, 3, 10, 5}, sum = 33 prints "Sum found between index 2 and 4"
void findSubarrayWithSum(int arr[], int n, int targetSum) {
    int currentSum = arr[0];
    int start = 0;
    
    for (int end = 1; end <= n; end++) {
        while (currentSum > targetSum && start < end - 1) {
            currentSum -= arr[start];
            start++;
        }
        
        if (currentSum == targetSum) {
            cout << "Sum found between index " << start << " and " << end - 1 << endl;
            return;
        }
        
        if (end < n) {
            currentSum += arr[end];
        }
    }
    
    cout << "No subarray found with sum " << targetSum << endl;
}

// ========================================
// 12. FIND MAJORITY ELEMENT (appears > n/2 times)
// ========================================
// Concept: Boyer-Moore Voting Algorithm
// Usage: majority = findMajorityElement(arr, n)
// Example: arr = {2, 2, 1, 1, 2, 2, 2} returns 2
int findMajorityElement(int arr[], int n) {
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
    return -1;  // No majority element
}

// ========================================
// 13. TRAPPING RAIN WATER
// ========================================
// Concept: Two-pointer / Prefix-Suffix max
// Usage: water = trappingRainWater(arr, n)
// Example: arr = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1} returns 6
int trappingRainWater(int arr[], int n) {
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
// Concept: Hashing
// Usage: length = longestConsecutive(arr, n)
// Example: arr = {100, 4, 200, 1, 3, 2} returns 4 (sequence: 1, 2, 3, 4)
int longestConsecutive(int arr[], int n) {
    unordered_map<int, bool> map;
    
    for (int i = 0; i < n; i++) {
        map[arr[i]] = true;
    }
    
    int maxLength = 0;
    
    for (int i = 0; i < n; i++) {
        if (map.find(arr[i] - 1) == map.end()) {
            int currentNum = arr[i];
            int currentLength = 1;
            
            while (map.find(currentNum + 1) != map.end()) {
                currentNum++;
                currentLength++;
            }
            
            maxLength = max(maxLength, currentLength);
        }
    }
    
    return maxLength;
}

// ========================================
// 15. PRODUCT OF ARRAY EXCEPT SELF
// ========================================
// Concept: Prefix and Suffix products
// Usage: productExceptSelf(arr, n, result)
// Example: arr = {1, 2, 3, 4} -> result = {24, 12, 8, 6}
void productExceptSelf(int arr[], int n, int result[]) {
    // Left products
    result[0] = 1;
    for (int i = 1; i < n; i++) {
        result[i] = result[i - 1] * arr[i - 1];
    }
    
    // Right products
    int rightProduct = 1;
    for (int i = n - 1; i >= 0; i--) {
        result[i] *= rightProduct;
        rightProduct *= arr[i];
    }
    
    cout << "Product array calculated." << endl;
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    int n;
    
    cout << "Enter number of elements: ";
    cin >> n;
    
    int* arr = new int[n];
    
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "\n=== Initial Array ===" << endl;
    display(arr, n);
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // 1. Kadane's Algorithm - Maximum Subarray Sum
    // int maxSum = kadaneMaxSubarraySum(arr, n);
    // cout << "Maximum subarray sum: " << maxSum << endl;
    
    // 2. Two Sum Problem
    // twoSum(arr, n, 9);  // Find pairs that sum to 9
    
    // 3. Dutch National Flag (for array with 0s, 1s, 2s)
    // dutchNationalFlag(arr, n);
    // display(arr, n);
    
    // 4. Move Zeros to End
    // moveZerosToEnd(arr, n);
    // display(arr, n);
    
    // 5. Find Missing Number
    // int missing = findMissingNumber(arr, n);
    // cout << "Missing number: " << missing << endl;
    
    // 6. Find Duplicate Number
    // int duplicate = findDuplicate(arr, n);
    // cout << "Duplicate number: " << duplicate << endl;
    
    // 7. Rotate Array by k positions
    // rotateArray(arr, n, 2);  // Rotate by 2 positions
    // display(arr, n);
    
    // 8. Find Leaders
    // findLeaders(arr, n);
    
    // 9. Stock Buy and Sell
    // int profit = maxStockProfit(arr, n);
    // cout << "Maximum profit: " << profit << endl;
    
    // 10. Merge Two Sorted Arrays
    // int arr2[] = {2, 4, 6, 8};
    // int n2 = 4;
    // int* result = new int[n + n2];
    // mergeSortedArrays(arr, n, arr2, n2, result);
    // display(result, n + n2);
    // delete[] result;
    
    // 11. Find Subarray with Given Sum
    // findSubarrayWithSum(arr, n, 33);
    
    // 12. Find Majority Element
    // int majority = findMajorityElement(arr, n);
    // if (majority != -1) {
    //     cout << "Majority element: " << majority << endl;
    // } else {
    //     cout << "No majority element found." << endl;
    // }
    
    // 13. Trapping Rain Water
    // int water = trappingRainWater(arr, n);
    // cout << "Water trapped: " << water << " units" << endl;
    
    // 14. Longest Consecutive Sequence
    // int length = longestConsecutive(arr, n);
    // cout << "Longest consecutive sequence length: " << length << endl;
    
    // 15. Product of Array Except Self
    // int* productArr = new int[n];
    // productExceptSelf(arr, n, productArr);
    // display(productArr, n);
    // delete[] productArr;
    
    delete[] arr;
    return 0;
}
