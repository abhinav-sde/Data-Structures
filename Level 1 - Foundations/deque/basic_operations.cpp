#include <iostream>
using namespace std;

/**
 * Basic Deque Operations in C++
 */

class Deque {
private:
    int *arr;
    int front, rear, size, capacity;
    
public:
    Deque(int cap) {
        capacity = cap;
        arr = new int[capacity];
        front = -1;
        rear = 0;
        size = 0;
    }
    
    ~Deque() {
        delete[] arr;
    }
    
    void pushFront(int val) {
        if (isFull()) {
            cout << "Deque is full" << endl;
            return;
        }
        
        if (front == -1) {
            front = rear = 0;
        } else {
            front = (front - 1 + capacity) % capacity;
        }
        
        arr[front] = val;
        size++;
        cout << "Pushed " << val << " at front" << endl;
    }
    
    void pushRear(int val) {
        if (isFull()) {
            cout << "Deque is full" << endl;
            return;
        }
        
        if (front == -1) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }
        
        arr[rear] = val;
        size++;
        cout << "Pushed " << val << " at rear" << endl;
    }
    
    int popFront() {
        if (isEmpty()) {
            cout << "Deque is empty" << endl;
            return -1;
        }
        
        int val = arr[front];
        
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
        
        size--;
        return val;
    }
    
    int popRear() {
        if (isEmpty()) {
            cout << "Deque is empty" << endl;
            return -1;
        }
        
        int val = arr[rear];
        
        if (front == rear) {
            front = rear = -1;
        } else {
            rear = (rear - 1 + capacity) % capacity;
        }
        
        size--;
        return val;
    }
    
    int getFront() {
        if (isEmpty()) {
            cout << "Deque is empty" << endl;
            return -1;
        }
        return arr[front];
    }
    
    int getRear() {
        if (isEmpty()) {
            cout << "Deque is empty" << endl;
            return -1;
        }
        return arr[rear];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == capacity;
    }
    
    int getSize() {
        return size;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Deque is empty" << endl;
            return;
        }
        
        cout << "Deque: ";
        int i = front;
        for (int count = 0; count < size; count++) {
            cout << arr[i] << " ";
            i = (i + 1) % capacity;
        }
        cout << endl;
    }
};

int main() {
    cout << "=== Deque Basic Operations Demo ===" << endl << endl;
    
    Deque deque(5);
    
    cout << "--- Push Operations ---" << endl;
    deque.pushRear(10);
    deque.pushRear(20);
    deque.pushFront(5);
    deque.pushFront(1);
    deque.display();
    cout << endl;
    
    cout << "--- Peek Operations ---" << endl;
    cout << "Front: " << deque.getFront() << endl;
    cout << "Rear: " << deque.getRear() << endl;
    cout << "Size: " << deque.getSize() << endl << endl;
    
    cout << "--- Pop Operations ---" << endl;
    cout << "Popped from front: " << deque.popFront() << endl;
    deque.display();
    
    cout << "Popped from rear: " << deque.popRear() << endl;
    deque.display();
    
    return 0;
}
