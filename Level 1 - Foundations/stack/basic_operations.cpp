#include <iostream>
#include <stack>
using namespace std;

// ========================================
// STACK IMPLEMENTATION USING ARRAY
// ========================================

const int MAX_SIZE = 100;

class Stack {
private:
    int arr[MAX_SIZE];
    int topIndex;

public:
    Stack() {
        topIndex = -1;
    }

    // Check if stack is empty
    bool isEmpty() {
        return topIndex == -1;
    }

    // Check if stack is full
    bool isFull() {
        return topIndex == MAX_SIZE - 1;
    }

    // Get current size
    int size() {
        return topIndex + 1;
    }

    // Push element
    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow! Cannot push " << value << endl;
            return;
        }
        arr[++topIndex] = value;
        cout << "Pushed " << value << " to stack." << endl;
    }

    // Pop element
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! Cannot pop." << endl;
            return -1;
        }
        int value = arr[topIndex--];
        cout << "Popped " << value << " from stack." << endl;
        return value;
    }

    // Peek top element
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return arr[topIndex];
    }

    // Display stack
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }
        cout << "Stack (top to bottom): ";
        for (int i = topIndex; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// ========================================
// STANDALONE FUNCTIONS
// ========================================

// Usage: push(stack, value) - pushes value to stack
void pushElement(Stack& stack, int value) {
    stack.push(value);
}

// Usage: value = pop(stack) - pops and returns top element
int popElement(Stack& stack) {
    return stack.pop();
}

// Usage: value = peek(stack) - returns top element without removing
int peekElement(Stack& stack) {
    return stack.peek();
}

// Usage: empty = isEmpty(stack) - checks if stack is empty
bool isStackEmpty(Stack& stack) {
    return stack.isEmpty();
}

// Usage: full = isFull(stack) - checks if stack is full
bool isStackFull(Stack& stack) {
    return stack.isFull();
}

// Usage: size = getSize(stack) - returns number of elements
int getSize(Stack& stack) {
    return stack.size();
}

// Usage: display(stack) - displays all elements
void displayStack(Stack& stack) {
    stack.display();
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    Stack stack;
    
    cout << "=== Stack Basic Operations ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // Push elements
    // pushElement(stack, 10);
    // pushElement(stack, 20);
    // pushElement(stack, 30);
    // pushElement(stack, 40);
    // pushElement(stack, 50);
    // displayStack(stack);
    
    // Peek top element
    // int top = peekElement(stack);
    // cout << "Top element: " << top << endl;
    
    // Get size
    // int size = getSize(stack);
    // cout << "Stack size: " << size << endl;
    
    // Pop elements
    // popElement(stack);
    // popElement(stack);
    // displayStack(stack);
    
    // Check if empty
    // if (isStackEmpty(stack)) {
    //     cout << "Stack is empty." << endl;
    // } else {
    //     cout << "Stack is not empty." << endl;
    // }
    
    // Check if full
    // if (isStackFull(stack)) {
    //     cout << "Stack is full." << endl;
    // } else {
    //     cout << "Stack is not full." << endl;
    // }
    
    return 0;
}
