#include <iostream>
#include <queue>
using namespace std;

// ========================================
// QUEUE IMPLEMENTATION USING ARRAY
// ========================================

const int MAX_SIZE = 100;

class Queue {
private:
    int arr[MAX_SIZE];
    int front, rear, count;

public:
    Queue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    // Check if queue is empty
    bool isEmpty() {
        return count == 0;
    }

    // Check if queue is full
    bool isFull() {
        return count == MAX_SIZE;
    }

    // Get current size
    int size() {
        return count;
    }

    // Enqueue element
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow! Cannot enqueue " << value << endl;
            return;
        }
        rear = (rear + 1) % MAX_SIZE;
        arr[rear] = value;
        count++;
        cout << "Enqueued " << value << " to queue." << endl;
    }

    // Dequeue element
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow! Cannot dequeue." << endl;
            return -1;
        }
        int value = arr[front];
        front = (front + 1) % MAX_SIZE;
        count--;
        cout << "Dequeued " << value << " from queue." << endl;
        return value;
    }

    // Peek front element
    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return arr[front];
    }

    // Display queue
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue (front to rear): ";
        int idx = front;
        for (int i = 0; i < count; i++) {
            cout << arr[idx] << " ";
            idx = (idx + 1) % MAX_SIZE;
        }
        cout << endl;
    }
};

// ========================================
// CIRCULAR QUEUE IMPLEMENTATION
// ========================================

class CircularQueue {
private:
    int arr[MAX_SIZE];
    int front, rear;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return (rear + 1) % MAX_SIZE == front;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Circular Queue is full!" << endl;
            return;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % MAX_SIZE;
        }
        arr[rear] = value;
        cout << "Enqueued " << value << " to circular queue." << endl;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Circular Queue is empty!" << endl;
            return -1;
        }
        int value = arr[front];
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % MAX_SIZE;
        }
        cout << "Dequeued " << value << " from circular queue." << endl;
        return value;
    }

    void display() {
        if (isEmpty()) {
            cout << "Circular Queue is empty." << endl;
            return;
        }
        cout << "Circular Queue: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % MAX_SIZE;
        }
        cout << endl;
    }
};

// ========================================
// STANDALONE FUNCTIONS
// ========================================

// Usage: enqueue(queue, value) - adds value to queue
void enqueueElement(Queue& queue, int value) {
    queue.enqueue(value);
}

// Usage: value = dequeue(queue) - removes and returns front element
int dequeueElement(Queue& queue) {
    return queue.dequeue();
}

// Usage: value = peek(queue) - returns front element without removing
int peekElement(Queue& queue) {
    return queue.peek();
}

// Usage: empty = isEmpty(queue) - checks if queue is empty
bool isQueueEmpty(Queue& queue) {
    return queue.isEmpty();
}

// Usage: full = isFull(queue) - checks if queue is full
bool isQueueFull(Queue& queue) {
    return queue.isFull();
}

// Usage: size = getSize(queue) - returns number of elements
int getSize(Queue& queue) {
    return queue.size();
}

// Usage: display(queue) - displays all elements
void displayQueue(Queue& queue) {
    queue.display();
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    Queue queue;
    
    cout << "=== Queue Basic Operations ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // Enqueue elements
    // enqueueElement(queue, 10);
    // enqueueElement(queue, 20);
    // enqueueElement(queue, 30);
    // enqueueElement(queue, 40);
    // enqueueElement(queue, 50);
    // displayQueue(queue);
    
    // Peek front element
    // int front = peekElement(queue);
    // cout << "Front element: " << front << endl;
    
    // Get size
    // int size = getSize(queue);
    // cout << "Queue size: " << size << endl;
    
    // Dequeue elements
    // dequeueElement(queue);
    // dequeueElement(queue);
    // displayQueue(queue);
    
    // Check if empty
    // if (isQueueEmpty(queue)) {
    //     cout << "Queue is empty." << endl;
    // } else {
    //     cout << "Queue is not empty." << endl;
    // }
    
    // Check if full
    // if (isQueueFull(queue)) {
    //     cout << "Queue is full." << endl;
    // } else {
    //     cout << "Queue is not full." << endl;
    // }
    
    // Circular Queue Example
    // cout << "\n=== Circular Queue ===" << endl;
    // CircularQueue cq;
    // cq.enqueue(1);
    // cq.enqueue(2);
    // cq.enqueue(3);
    // cq.display();
    // cq.dequeue();
    // cq.enqueue(4);
    // cq.display();
    
    return 0;
}
