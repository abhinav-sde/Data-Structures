#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

/**
 * Core Heap Problems in C++
 * Contains essential heap-based algorithms
 */

// Problem 1: Find Kth Largest Element
// Time Complexity: O(n log k)
int findKthLargest(vector<int>& nums, int k) {
    // Min heap of size k
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    return minHeap.top();
}

// Problem 2: Heap Sort
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Problem 3: Top K Frequent Elements
vector<int> topKFrequent(vector<int>& nums, int k) {
    // Count frequencies
    unordered_map<int, int> freqMap;
    for (int num : nums) {
        freqMap[num]++;
    }
    
    // Min heap based on frequency
    auto comp = [](pair<int, int> a, pair<int, int> b) {
        return a.second > b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> minHeap(comp);
    
    for (auto& entry : freqMap) {
        minHeap.push(entry);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    // Extract results
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().first);
        minHeap.pop();
    }
    
    return result;
}

// Problem 4: Merge K Sorted Arrays
struct ArrayPointer {
    int arrayIndex;
    int elementIndex;
    int value;
    
    ArrayPointer(int ai, int ei, int v) : arrayIndex(ai), elementIndex(ei), value(v) {}
    
    bool operator>(const ArrayPointer& other) const {
        return value > other.value;
    }
};

vector<int> mergeKSortedArrays(vector<vector<int>>& arrays) {
    vector<int> result;
    priority_queue<ArrayPointer, vector<ArrayPointer>, greater<ArrayPointer>> minHeap;
    
    // Add first element from each array
    for (int i = 0; i < arrays.size(); i++) {
        if (!arrays[i].empty()) {
            minHeap.push(ArrayPointer(i, 0, arrays[i][0]));
        }
    }
    
    // Process heap
    while (!minHeap.empty()) {
        ArrayPointer current = minHeap.top();
        minHeap.pop();
        result.push_back(current.value);
        
        // Add next element from same array
        if (current.elementIndex + 1 < arrays[current.arrayIndex].size()) {
            int nextIdx = current.elementIndex + 1;
            int nextVal = arrays[current.arrayIndex][nextIdx];
            minHeap.push(ArrayPointer(current.arrayIndex, nextIdx, nextVal));
        }
    }
    
    return result;
}

// Problem 5: Find Median from Data Stream
class MedianFinder {
private:
    priority_queue<int> maxHeap; // Lower half
    priority_queue<int, vector<int>, greater<int>> minHeap; // Upper half
    
public:
    MedianFinder() {}
    
    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        
        if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
        return maxHeap.top();
    }
};

// Problem 6: Last Stone Weight
int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> maxHeap;
    
    for (int stone : stones) {
        maxHeap.push(stone);
    }
    
    while (maxHeap.size() > 1) {
        int stone1 = maxHeap.top(); maxHeap.pop();
        int stone2 = maxHeap.top(); maxHeap.pop();
        
        if (stone1 != stone2) {
            maxHeap.push(stone1 - stone2);
        }
    }
    
    return maxHeap.empty() ? 0 : maxHeap.top();
}

// Helper function to display vector
void displayVector(const vector<int>& vec) {
    cout << "[ ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << "]" << endl;
}

int main() {
    cout << "=== Core Heap Problems ===" << endl << endl;
    
    // Test 1: Kth Largest Element
    cout << "Test 1: Kth Largest Element" << endl;
    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    cout << "Array: "; displayVector(nums1);
    cout << k1 << "th largest: " << findKthLargest(nums1, k1) << endl << endl;
    
    // Test 2: Heap Sort
    cout << "Test 2: Heap Sort" << endl;
    vector<int> nums2 = {12, 11, 13, 5, 6, 7};
    cout << "Before: "; displayVector(nums2);
    heapSort(nums2);
    cout << "After: "; displayVector(nums2);
    cout << endl;
    
    // Test 3: Top K Frequent
    cout << "Test 3: Top K Frequent Elements" << endl;
    vector<int> nums3 = {1, 1, 1, 2, 2, 3};
    int k3 = 2;
    cout << "Array: "; displayVector(nums3);
    vector<int> topK = topKFrequent(nums3, k3);
    cout << "Top " << k3 << " frequent: "; displayVector(topK);
    cout << endl;
    
    // Test 4: Merge K Sorted Arrays
    cout << "Test 4: Merge K Sorted Arrays" << endl;
    vector<vector<int>> arrays = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };
    vector<int> merged = mergeKSortedArrays(arrays);
    cout << "Merged: "; displayVector(merged);
    cout << endl;
    
    // Test 5: Median Finder
    cout << "Test 5: Find Median from Data Stream" << endl;
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    cout << "Median after adding 1, 2: " << mf.findMedian() << endl;
    mf.addNum(3);
    cout << "Median after adding 3: " << mf.findMedian() << endl << endl;
    
    // Test 6: Last Stone Weight
    cout << "Test 6: Last Stone Weight" << endl;
    vector<int> stones = {2, 7, 4, 1, 8, 1};
    cout << "Stones: "; displayVector(stones);
    cout << "Last stone weight: " << lastStoneWeight(stones) << endl;
    
    return 0;
}
