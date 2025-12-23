#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Basic Heap (Priority Queue) Operations in C++
 * Contains Min Heap and Max Heap implementations
 */

// Min Heap Implementation
class MinHeap {
private:
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[i] < heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void heapifyDown(int i) {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] < heap[smallest])
            smallest = left;
        
        if (right < heap.size() && heap[right] < heap[smallest])
            smallest = right;
        
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }
    
public:
    // Insert element
    // Time Complexity: O(log n)
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
        cout << "Inserted " << value << " into min heap" << endl;
    }
    
    // Get minimum element
    // Time Complexity: O(1)
    int getMin() {
        if (heap.empty()) {
            cout << "Heap is empty" << endl;
            return -1;
        }
        return heap[0];
    }
    
    // Extract minimum element
    // Time Complexity: O(log n)
    int extractMin() {
        if (heap.empty()) {
            cout << "Heap is empty" << endl;
            return -1;
        }
        
        if (heap.size() == 1) {
            int min = heap[0];
            heap.pop_back();
            return min;
        }
        
        int min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        
        return min;
    }
    
    // Check if heap is empty
    bool isEmpty() {
        return heap.empty();
    }
    
    // Get size
    int size() {
        return heap.size();
    }
    
    // Display heap
    void display() {
        if (heap.empty()) {
            cout << "Heap is empty" << endl;
            return;
        }
        cout << "Min Heap: ";
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
};

// Max Heap Implementation
class MaxHeap {
private:
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[i] > heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void heapifyDown(int i) {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] > heap[largest])
            largest = left;
        
        if (right < heap.size() && heap[right] > heap[largest])
            largest = right;
        
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }
    
public:
    // Insert element
    // Time Complexity: O(log n)
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
        cout << "Inserted " << value << " into max heap" << endl;
    }
    
    // Get maximum element
    // Time Complexity: O(1)
    int getMax() {
        if (heap.empty()) {
            cout << "Heap is empty" << endl;
            return -1;
        }
        return heap[0];
    }
    
    // Extract maximum element
    // Time Complexity: O(log n)
    int extractMax() {
        if (heap.empty()) {
            cout << "Heap is empty" << endl;
            return -1;
        }
        
        if (heap.size() == 1) {
            int max = heap[0];
            heap.pop_back();
            return max;
        }
        
        int max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        
        return max;
    }
    
    bool isEmpty() {
        return heap.empty();
    }
    
    int size() {
        return heap.size();
    }
    
    void display() {
        if (heap.empty()) {
            cout << "Heap is empty" << endl;
            return;
        }
        cout << "Max Heap: ";
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
};

int main() {
    cout << "=== Min Heap Demo ===" << endl;
    MinHeap minHeap;
    
    // Insert elements
    minHeap.insert(10);
    minHeap.insert(5);
    minHeap.insert(20);
    minHeap.insert(1);
    minHeap.insert(15);
    minHeap.insert(30);
    
    minHeap.display();
    
    cout << "Minimum element: " << minHeap.getMin() << endl;
    cout << "Extracted min: " << minHeap.extractMin() << endl;
    
    minHeap.display();
    
    cout << "\n=== Max Heap Demo ===" << endl;
    MaxHeap maxHeap;
    
    // Insert elements
    maxHeap.insert(10);
    maxHeap.insert(5);
    maxHeap.insert(20);
    maxHeap.insert(1);
    maxHeap.insert(15);
    maxHeap.insert(30);
    
    maxHeap.display();
    
    cout << "Maximum element: " << maxHeap.getMax() << endl;
    cout << "Extracted max: " << maxHeap.extractMax() << endl;
    
    maxHeap.display();
    
    return 0;
}
