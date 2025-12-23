#include <iostream>
using namespace std;

// Function to display the array
// Usage: display(arr, n) - displays all n elements
void display(int arr[], int n) {
    if (n == 0) {
        cout << "Array is empty." << endl;
        return;
    }
    cout << "Array elements: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Function to insert at start
// Usage: newSize = insertAtStart(arr, n, capacity, value)
// Example: newSize = insertAtStart(arr, 5, 10, 99) - inserts 99 at start
int insertAtStart(int arr[], int n, int capacity, int val) {
    if (n == capacity) {
        cout << "Array is full. Cannot insert." << endl;
        return n;
    }
    for (int i = n; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = val;
    cout << "Inserted " << val << " at start." << endl;
    return n + 1;
}

// Function to insert at end
// Usage: newSize = insertAtEnd(arr, n, capacity, value)
// Example: newSize = insertAtEnd(arr, 5, 10, 99) - inserts 99 at end
int insertAtEnd(int arr[], int n, int capacity, int val) {
    if (n == capacity) {
        cout << "Array is full. Cannot insert." << endl;
        return n;
    }
    arr[n] = val;
    cout << "Inserted " << val << " at end." << endl;
    return n + 1;
}

// Function to insert at specific index
// Usage: newSize = insertAtIndex(arr, n, capacity, index, value)
// Example: newSize = insertAtIndex(arr, 5, 10, 2, 99) - inserts 99 at index 2
int insertAtIndex(int arr[], int n, int capacity, int index, int val) {
    if (n == capacity) {
        cout << "Array is full. Cannot insert." << endl;
        return n;
    }
    if (index < 0 || index > n) {
        cout << "Invalid index." << endl;
        return n;
    }
    for (int i = n; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = val;
    cout << "Inserted " << val << " at index " << index << "." << endl;
    return n + 1;
}

// Function to delete at specific index
// Usage: newSize = deleteAtIndex(arr, n, index)
// Example: newSize = deleteAtIndex(arr, 5, 2) - deletes element at index 2
int deleteAtIndex(int arr[], int n, int index) {
    if (n == 0) {
        cout << "Array is empty. Cannot delete." << endl;
        return n;
    }
    if (index < 0 || index >= n) {
        cout << "Invalid index." << endl;
        return n;
    }
    int deletedVal = arr[index];
    for (int i = index; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    cout << "Deleted " << deletedVal << " from index " << index << "." << endl;
    return n - 1;
}

// Function to delete by value (first occurrence)
// Usage: newSize = deleteValue(arr, n, value)
// Example: newSize = deleteValue(arr, 5, 30) - deletes first occurrence of 30
int deleteValue(int arr[], int n, int val) {
    if (n == 0) {
        cout << "Array is empty. Cannot delete." << endl;
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
        cout << "Value " << val << " not found." << endl;
        return n;
    }
    return deleteAtIndex(arr, n, index);
}

int main() {
    int n, capacity;
    
    cout << "Enter array capacity: ";
    cin >> capacity;
    
    int* arr = new int[capacity];
    
    cout << "Enter number of elements: ";
    cin >> n;
    
    if (n > capacity) {
        cout << "Size exceeds capacity. Setting size to capacity." << endl;
        n = capacity;
    }
    
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "\n=== Initial Array ===" << endl;
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
    
    delete[] arr;
    return 0;
}
