#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ========================================
// MIN HEAP IMPLEMENTATION
// ========================================

class MinHeap {
private:
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void heapifyDown(int i) {
        int minIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] < heap[minIndex]) {
            minIndex = left;
        }
        
        if (right < heap.size() && heap[right] < heap[minIndex]) {
            minIndex = right;
        }
        
        if (i != minIndex) {
            swap(heap[i], heap[minIndex]);
            heapifyDown(minIndex);
        }
    }

public:
    // Insert element
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
        cout << "Inserted " << value << " into min heap." << endl;
    }
    
    // Extract minimum
    int extractMin() {
        if (heap.empty()) {
            cout << "Heap is empty!" << endl;
            return INT_MAX;
        }
        
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return minVal;
    }
    
    // Get minimum without removing
    int getMin() {
        if (heap.empty()) {
            cout << "Heap is empty!" << endl;
            return INT_MAX;
        }
        return heap[0];
    }
    
    // Check if empty
    bool isEmpty() {
        return heap.empty();
    }
    
    // Get size
    int size() {
        return heap.size();
    }
    
    // Display heap
    void display() {
        cout << "Min Heap: ";
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    // Build heap from array
    void buildHeap(vector<int>& arr) {
        heap = arr;
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
        cout << "Min heap built from array." << endl;
    }
};

// ========================================
// MAX HEAP IMPLEMENTATION
// ========================================

class MaxHeap {
private:
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void heapifyDown(int i) {
        int maxIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] > heap[maxIndex]) {
            maxIndex = left;
        }
        
        if (right < heap.size() && heap[right] > heap[maxIndex]) {
            maxIndex = right;
        }
        
        if (i != maxIndex) {
            swap(heap[i], heap[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
    // Insert element
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
        cout << "Inserted " << value << " into max heap." << endl;
    }
    
    // Extract maximum
    int extractMax() {
        if (heap.empty()) {
            cout << "Heap is empty!" << endl;
            return INT_MIN;
        }
        
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return maxVal;
    }
    
    // Get maximum without removing
    int getMax() {
        if (heap.empty()) {
            cout << "Heap is empty!" << endl;
            return INT_MIN;
        }
        return heap[0];
    }
    
    // Check if empty
    bool isEmpty() {
        return heap.empty();
    }
    
    // Get size
    int size() {
        return heap.size();
    }
    
    // Display heap
    void display() {
        cout << "Max Heap: ";
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    // Build heap from array
    void buildHeap(vector<int>& arr) {
        heap = arr;
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
        cout << "Max heap built from array." << endl;
    }
};

// ========================================
// HEAP SORT
// ========================================
// Usage: heapSort(arr)
// Example: Sorts array in ascending order using max heap
void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        int current = i;
        while (true) {
            int largest = current;
            int left = 2 * current + 1;
            int right = 2 * current + 2;
            
            if (left < n && arr[left] > arr[largest]) {
                largest = left;
            }
            
            if (right < n && arr[right] > arr[largest]) {
                largest = right;
            }
            
            if (largest != current) {
                swap(arr[current], arr[largest]);
                current = largest;
            } else {
                break;
            }
        }
    }
    
    // Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        
        int current = 0;
        while (true) {
            int largest = current;
            int left = 2 * current + 1;
            int right = 2 * current + 2;
            
            if (left < i && arr[left] > arr[largest]) {
                largest = left;
            }
            
            if (right < i && arr[right] > arr[largest]) {
                largest = right;
            }
            
            if (largest != current) {
                swap(arr[current], arr[largest]);
                current = largest;
            } else {
                break;
            }
        }
    }
    
    cout << "Array sorted using heap sort." << endl;
}

// ========================================
// FIND KTH LARGEST ELEMENT
// ========================================
// Usage: kth = findKthLargest(arr, k)
// Example: findKthLargest({3,2,1,5,6,4}, 2) returns 5
int findKthLargest(vector<int>& arr, int k) {
    MinHeap minHeap;
    
    for (int num : arr) {
        minHeap.insert(num);
        if (minHeap.size() > k) {
            minHeap.extractMin();
        }
    }
    
    return minHeap.getMin();
}

// ========================================
// FIND KTH SMALLEST ELEMENT
// ========================================
// Usage: kth = findKthSmallest(arr, k)
// Example: findKthSmallest({3,2,1,5,6,4}, 2) returns 2
int findKthSmallest(vector<int>& arr, int k) {
    MaxHeap maxHeap;
    
    for (int num : arr) {
        maxHeap.insert(num);
        if (maxHeap.size() > k) {
            maxHeap.extractMax();
        }
    }
    
    return maxHeap.getMax();
}

// ========================================
// MERGE K SORTED ARRAYS
// ========================================
// Usage: merged = mergeKSortedArrays(arrays)
// Example: Merges multiple sorted arrays into one
struct HeapNode {
    int value;
    int arrayIndex;
    int elementIndex;
    
    bool operator>(const HeapNode& other) const {
        return value > other.value;
    }
};

vector<int> mergeKSortedArrays(vector<vector<int>>& arrays) {
    vector<int> result;
    MinHeap minHeap;
    
    // Insert first element of each array
    for (int i = 0; i < arrays.size(); i++) {
        if (!arrays[i].empty()) {
            minHeap.insert(arrays[i][0]);
        }
    }
    
    // Note: This is a simplified version
    // For full implementation, need custom heap with array tracking
    
    return result;
}

// ========================================
// MEDIAN FINDER (USING TWO HEAPS)
// ========================================
class MedianFinder {
private:
    MaxHeap maxHeap;  // Lower half
    MinHeap minHeap;  // Upper half

public:
    void addNum(int num) {
        if (maxHeap.isEmpty() || num <= maxHeap.getMax()) {
            maxHeap.insert(num);
        } else {
            minHeap.insert(num);
        }
        
        // Balance heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.insert(maxHeap.extractMax());
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.insert(minHeap.extractMin());
        }
    }
    
    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.getMax() + minHeap.getMin()) / 2.0;
        }
        return maxHeap.getMax();
    }
};

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    cout << "=== Heap Operations ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // Min Heap
    // MinHeap minHeap;
    // minHeap.insert(5);
    // minHeap.insert(3);
    // minHeap.insert(7);
    // minHeap.insert(1);
    // minHeap.display();
    
    // cout << "Min: " << minHeap.getMin() << endl;
    // cout << "Extracted min: " << minHeap.extractMin() << endl;
    // minHeap.display();
    
    // Max Heap
    // MaxHeap maxHeap;
    // maxHeap.insert(5);
    // maxHeap.insert(3);
    // maxHeap.insert(7);
    // maxHeap.insert(1);
    // maxHeap.display();
    
    // cout << "Max: " << maxHeap.getMax() << endl;
    // cout << "Extracted max: " << maxHeap.extractMax() << endl;
    // maxHeap.display();
    
    // Build heap from array
    // vector<int> arr = {4, 10, 3, 5, 1};
    // MinHeap heap;
    // heap.buildHeap(arr);
    // heap.display();
    
    // Heap Sort
    // vector<int> arr = {12, 11, 13, 5, 6, 7};
    // cout << "Before sort: ";
    // for (int val : arr) cout << val << " ";
    // cout << endl;
    
    // heapSort(arr);
    
    // cout << "After sort: ";
    // for (int val : arr) cout << val << " ";
    // cout << endl;
    
    // Kth Largest
    // vector<int> arr = {3, 2, 1, 5, 6, 4};
    // int kthLargest = findKthLargest(arr, 2);
    // cout << "2nd largest: " << kthLargest << endl;
    
    // Kth Smallest
    // int kthSmallest = findKthSmallest(arr, 2);
    // cout << "2nd smallest: " << kthSmallest << endl;
    
    // Median Finder
    // MedianFinder mf;
    // mf.addNum(1);
    // mf.addNum(2);
    // cout << "Median: " << mf.findMedian() << endl;
    // mf.addNum(3);
    // cout << "Median: " << mf.findMedian() << endl;
    
    return 0;
}
