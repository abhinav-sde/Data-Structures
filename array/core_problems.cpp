#include <iostream>
#include <algorithm> // For swap and sort
using namespace std;

// Function to display the array
// Usage: display(arr, n) - displays all n elements
void display(int arr[], int n) {
    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Function for linear search
// Usage: index = linearSearch(arr, n, key)
// Example: index = linearSearch(arr, 5, 30) - searches for 30, returns index or -1
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

// Function for binary search (requires sorted array)
// Usage: index = binarySearch(arr, n, key)
// Example: index = binarySearch(arr, 5, 30) - searches for 30 in sorted array
int binarySearch(int arr[], int n, int key) {
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
// Usage: reverseArray(arr, n) - reverses the array in-place
// Example: reverseArray(arr, 5) - reverses array of 5 elements
void reverseArray(int arr[], int n) {
    int start = 0, end = n - 1;
    while (start < end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
    cout << "Array reversed." << endl;
}

// Function to find minimum and maximum
// Usage: findMinMax(arr, n) - prints min and max values
// Example: findMinMax(arr, 5) - finds min and max in array of 5 elements
void findMinMax(int arr[], int n) {
    if (n == 0) {
        cout << "Array is empty." << endl;
        return;
    }
    int minVal = arr[0];
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    cout << "Min: " << minVal << ", Max: " << maxVal << endl;
}

// Function to check if array is sorted
// Usage: result = checkSorted(arr, n)
// Example: result = checkSorted(arr, 5) - returns true if sorted, false otherwise
bool checkSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Function to sort the array
// Usage: sortArray(arr, n) - sorts the array in ascending order
// Example: sortArray(arr, 5) - sorts array of 5 elements
void sortArray(int arr[], int n) {
    sort(arr, arr + n);
    cout << "Array sorted." << endl;
}

// Function to find sum of all elements
// Usage: sum = sumArray(arr, n)
// Example: sum = sumArray(arr, 5) - returns sum of all 5 elements
int sumArray(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

// Function to find average of all elements
// Usage: avg = averageArray(arr, n)
// Example: avg = averageArray(arr, 5) - returns average of all 5 elements
double averageArray(int arr[], int n) {
    if (n == 0) return 0.0;
    return (double)sumArray(arr, n) / n;
}

// Function to count occurrences of a value
// Usage: count = countOccurrences(arr, n, value)
// Example: count = countOccurrences(arr, 5, 30) - counts how many times 30 appears
int countOccurrences(int arr[], int n, int value) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == value) {
            count++;
        }
    }
    return count;
}

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
    
    // Linear search for value 30
    // int index = linearSearch(arr, n, 30);
    // cout << "Index of 30: " << index << endl;
    
    // Sort and then binary search
    // sortArray(arr, n);
    // display(arr, n);
    // int index = binarySearch(arr, n, 30);
    // cout << "Index of 30: " << index << endl;
    
    // Reverse array
    // reverseArray(arr, n);
    // display(arr, n);
    
    // Find min and max
    // findMinMax(arr, n);
    
    // Check if sorted
    // if (checkSorted(arr, n)) {
    //     cout << "Array is sorted." << endl;
    // } else {
    //     cout << "Array is NOT sorted." << endl;
    // }
    
    // Find sum
    // int sum = sumArray(arr, n);
    // cout << "Sum: " << sum << endl;
    
    // Find average
    // double avg = averageArray(arr, n);
    // cout << "Average: " << avg << endl;
    
    // Count occurrences of 30
    // int count = countOccurrences(arr, n, 30);
    // cout << "Occurrences of 30: " << count << endl;
    
    delete[] arr;
    return 0;
}
