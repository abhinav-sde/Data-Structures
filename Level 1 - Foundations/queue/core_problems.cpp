#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// ========================================
// 1. REVERSE A QUEUE
// ========================================
// Usage: reverseQueue(q)
// Example: Reverses the entire queue
void reverseQueue(queue<int>& q) {
    stack<int> st;
    
    while (!q.empty()) {
        st.push(q.front());
        q.pop();
    }
    
    while (!st.empty()) {
        q.push(st.top());
        st.pop();
    }
    
    cout << "Queue reversed." << endl;
}

// ========================================
// 2. IMPLEMENT QUEUE USING STACKS
// ========================================
// Concept: Two stacks approach
class QueueUsingStacks {
private:
    stack<int> s1, s2;

public:
    void enqueue(int value) {
        s1.push(value);
        cout << "Enqueued " << value << endl;
    }
    
    int dequeue() {
        if (s1.empty() && s2.empty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        
        int value = s2.top();
        s2.pop();
        return value;
    }
    
    int peek() {
        if (s1.empty() && s2.empty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        
        return s2.top();
    }
    
    bool empty() {
        return s1.empty() && s2.empty();
    }
};

// ========================================
// 3. IMPLEMENT STACK USING QUEUES
// ========================================
// Concept: Single queue approach
class StackUsingQueue {
private:
    queue<int> q;

public:
    void push(int value) {
        int size = q.size();
        q.push(value);
        
        for (int i = 0; i < size; i++) {
            q.push(q.front());
            q.pop();
        }
        
        cout << "Pushed " << value << endl;
    }
    
    int pop() {
        if (q.empty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        int value = q.front();
        q.pop();
        return value;
    }
    
    int top() {
        if (q.empty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

// ========================================
// 4. GENERATE BINARY NUMBERS FROM 1 TO N
// ========================================
// Usage: generateBinary(n)
// Example: generateBinary(5) prints "1 10 11 100 101"
void generateBinary(int n) {
    queue<string> q;
    q.push("1");
    
    cout << "Binary numbers from 1 to " << n << ": ";
    for (int i = 0; i < n; i++) {
        string current = q.front();
        q.pop();
        cout << current << " ";
        
        q.push(current + "0");
        q.push(current + "1");
    }
    cout << endl;
}

// ========================================
// 5. FIRST NON-REPEATING CHARACTER IN STREAM
// ========================================
// Usage: firstNonRepeating(stream)
// Example: stream = "aabcc" prints "a -1 b b -1"
void firstNonRepeating(string stream) {
    queue<char> q;
    int freq[26] = {0};
    
    cout << "First non-repeating characters: ";
    for (char ch : stream) {
        q.push(ch);
        freq[ch - 'a']++;
        
        while (!q.empty() && freq[q.front() - 'a'] > 1) {
            q.pop();
        }
        
        if (q.empty()) {
            cout << "-1 ";
        } else {
            cout << q.front() << " ";
        }
    }
    cout << endl;
}

// ========================================
// 6. CIRCULAR TOUR (GAS STATION PROBLEM)
// ========================================
// Usage: start = circularTour(petrol, distance, n)
// Example: Returns starting point index or -1
int circularTour(int petrol[], int distance[], int n) {
    int start = 0;
    int deficit = 0;
    int balance = 0;
    
    for (int i = 0; i < n; i++) {
        balance += petrol[i] - distance[i];
        
        if (balance < 0) {
            deficit += balance;
            start = i + 1;
            balance = 0;
        }
    }
    
    return (balance + deficit >= 0) ? start : -1;
}

// ========================================
// 7. REVERSE FIRST K ELEMENTS OF QUEUE
// ========================================
// Usage: reverseFirstK(q, k)
// Example: Reverses first k elements of queue
void reverseFirstK(queue<int>& q, int k) {
    if (q.empty() || k > q.size()) {
        cout << "Invalid operation!" << endl;
        return;
    }
    
    stack<int> st;
    
    // Push first k elements to stack
    for (int i = 0; i < k; i++) {
        st.push(q.front());
        q.pop();
    }
    
    // Enqueue from stack
    while (!st.empty()) {
        q.push(st.top());
        st.pop();
    }
    
    // Move remaining elements to back
    int remaining = q.size() - k;
    for (int i = 0; i < remaining; i++) {
        q.push(q.front());
        q.pop();
    }
    
    cout << "First " << k << " elements reversed." << endl;
}

// ========================================
// 8. INTERLEAVE FIRST AND SECOND HALF OF QUEUE
// ========================================
// Usage: interleaveQueue(q)
// Example: {1,2,3,4,5,6} becomes {1,4,2,5,3,6}
void interleaveQueue(queue<int>& q) {
    if (q.size() % 2 != 0) {
        cout << "Queue size must be even!" << endl;
        return;
    }
    
    int halfSize = q.size() / 2;
    queue<int> firstHalf;
    
    // Store first half
    for (int i = 0; i < halfSize; i++) {
        firstHalf.push(q.front());
        q.pop();
    }
    
    // Interleave
    while (!firstHalf.empty()) {
        q.push(firstHalf.front());
        firstHalf.pop();
        q.push(q.front());
        q.pop();
    }
    
    cout << "Queue interleaved." << endl;
}

// ========================================
// 9. PRIORITY QUEUE OPERATIONS
// ========================================
// Usage: Demonstrates min and max heap
void priorityQueueDemo() {
    // Max heap (default)
    priority_queue<int> maxHeap;
    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);
    maxHeap.push(5);
    
    cout << "Max Heap (descending): ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;
    
    // Min heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(10);
    minHeap.push(30);
    minHeap.push(20);
    minHeap.push(5);
    
    cout << "Min Heap (ascending): ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;
}

// ========================================
// 10. DEQUE OPERATIONS
// ========================================
// Usage: Demonstrates double-ended queue
void dequeDemo() {
    deque<int> dq;
    
    // Insert at both ends
    dq.push_back(10);
    dq.push_back(20);
    dq.push_front(5);
    dq.push_front(1);
    
    cout << "Deque: ";
    for (int val : dq) {
        cout << val << " ";
    }
    cout << endl;
    
    // Remove from both ends
    dq.pop_front();
    dq.pop_back();
    
    cout << "After removing from both ends: ";
    for (int val : dq) {
        cout << val << " ";
    }
    cout << endl;
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    cout << "=== Queue Core Problems ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // 1. Reverse Queue
    // queue<int> q;
    // q.push(1); q.push(2); q.push(3); q.push(4); q.push(5);
    // reverseQueue(q);
    // cout << "Reversed queue: ";
    // while (!q.empty()) {
    //     cout << q.front() << " ";
    //     q.pop();
    // }
    // cout << endl;
    
    // 2. Queue Using Stacks
    // QueueUsingStacks qStack;
    // qStack.enqueue(1);
    // qStack.enqueue(2);
    // qStack.enqueue(3);
    // cout << "Dequeued: " << qStack.dequeue() << endl;
    // cout << "Peek: " << qStack.peek() << endl;
    
    // 3. Stack Using Queue
    // StackUsingQueue sQueue;
    // sQueue.push(1);
    // sQueue.push(2);
    // sQueue.push(3);
    // cout << "Popped: " << sQueue.pop() << endl;
    // cout << "Top: " << sQueue.top() << endl;
    
    // 4. Generate Binary Numbers
    // generateBinary(10);
    
    // 5. First Non-Repeating Character
    // firstNonRepeating("aabcc");
    
    // 6. Circular Tour
    // int petrol[] = {4, 6, 7, 4};
    // int distance[] = {6, 5, 3, 5};
    // int start = circularTour(petrol, distance, 4);
    // if (start != -1) {
    //     cout << "Start point: " << start << endl;
    // } else {
    //     cout << "No solution exists." << endl;
    // }
    
    // 7. Reverse First K Elements
    // queue<int> q;
    // q.push(1); q.push(2); q.push(3); q.push(4); q.push(5);
    // reverseFirstK(q, 3);
    // cout << "Queue after reversing first 3: ";
    // while (!q.empty()) {
    //     cout << q.front() << " ";
    //     q.pop();
    // }
    // cout << endl;
    
    // 8. Interleave Queue
    // queue<int> q;
    // q.push(1); q.push(2); q.push(3); q.push(4); q.push(5); q.push(6);
    // interleaveQueue(q);
    // cout << "Interleaved queue: ";
    // while (!q.empty()) {
    //     cout << q.front() << " ";
    //     q.pop();
    // }
    // cout << endl;
    
    // 9. Priority Queue Demo
    // priorityQueueDemo();
    
    // 10. Deque Demo
    // dequeDemo();
    
    return 0;
}
