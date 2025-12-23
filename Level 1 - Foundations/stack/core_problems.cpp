#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

// ========================================
// 1. REVERSE A STRING USING STACK
// ========================================
// Usage: reversed = reverseString(str)
// Example: reverseString("hello") returns "olleh"
string reverseString(string str) {
    stack<char> st;
    
    for (char ch : str) {
        st.push(ch);
    }
    
    string reversed = "";
    while (!st.empty()) {
        reversed += st.top();
        st.pop();
    }
    
    return reversed;
}

// ========================================
// 2. CHECK BALANCED PARENTHESES
// ========================================
// Usage: result = isBalanced(str)
// Example: isBalanced("({[]})") returns true
bool isBalanced(string str) {
    stack<char> st;
    
    for (char ch : str) {
        if (ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (st.empty()) return false;
            
            char top = st.top();
            if ((ch == ')' && top == '(') ||
                (ch == '}' && top == '{') ||
                (ch == ']' && top == '[')) {
                st.pop();
            } else {
                return false;
            }
        }
    }
    
    return st.empty();
}

// ========================================
// 3. INFIX TO POSTFIX CONVERSION
// ========================================
// Usage: postfix = infixToPostfix(infix)
// Example: infixToPostfix("a+b*c") returns "abc*+"
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

string infixToPostfix(string infix) {
    stack<char> st;
    string postfix = "";
    
    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            st.push(ch);
        } else if (ch == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop();  // Remove '('
        } else {
            while (!st.empty() && precedence(st.top()) >= precedence(ch)) {
                postfix += st.top();
                st.pop();
            }
            st.push(ch);
        }
    }
    
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }
    
    return postfix;
}

// ========================================
// 4. EVALUATE POSTFIX EXPRESSION
// ========================================
// Usage: result = evaluatePostfix(postfix)
// Example: evaluatePostfix("23*5+") returns 11
int evaluatePostfix(string postfix) {
    stack<int> st;
    
    for (char ch : postfix) {
        if (isdigit(ch)) {
            st.push(ch - '0');
        } else {
            int val2 = st.top(); st.pop();
            int val1 = st.top(); st.pop();
            
            switch (ch) {
                case '+': st.push(val1 + val2); break;
                case '-': st.push(val1 - val2); break;
                case '*': st.push(val1 * val2); break;
                case '/': st.push(val1 / val2); break;
            }
        }
    }
    
    return st.top();
}

// ========================================
// 5. NEXT GREATER ELEMENT
// ========================================
// Usage: nextGreater(arr, n, result)
// Example: arr = {4, 5, 2, 25} -> result = {5, 25, 25, -1}
void nextGreater(int arr[], int n, int result[]) {
    stack<int> st;
    
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= arr[i]) {
            st.pop();
        }
        
        result[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    
    cout << "Next greater elements: ";
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

// ========================================
// 6. STOCK SPAN PROBLEM
// ========================================
// Usage: stockSpan(prices, n, span)
// Example: prices = {100, 80, 60, 70, 60, 75, 85} -> span = {1, 1, 1, 2, 1, 4, 6}
void stockSpan(int prices[], int n, int span[]) {
    stack<int> st;
    st.push(0);
    span[0] = 1;
    
    for (int i = 1; i < n; i++) {
        while (!st.empty() && prices[st.top()] <= prices[i]) {
            st.pop();
        }
        
        span[i] = st.empty() ? (i + 1) : (i - st.top());
        st.push(i);
    }
    
    cout << "Stock span: ";
    for (int i = 0; i < n; i++) {
        cout << span[i] << " ";
    }
    cout << endl;
}

// ========================================
// 7. SORT A STACK
// ========================================
// Usage: sortStack(st)
// Example: Sorts stack in ascending order (smallest on top)
void sortedInsert(stack<int>& st, int element) {
    if (st.empty() || element < st.top()) {
        st.push(element);
        return;
    }
    
    int temp = st.top();
    st.pop();
    sortedInsert(st, element);
    st.push(temp);
}

void sortStack(stack<int>& st) {
    if (st.empty()) return;
    
    int temp = st.top();
    st.pop();
    sortStack(st);
    sortedInsert(st, temp);
}

// ========================================
// 8. GET MINIMUM ELEMENT IN O(1)
// ========================================
class MinStack {
private:
    stack<int> mainStack;
    stack<int> minStack;

public:
    void push(int value) {
        mainStack.push(value);
        if (minStack.empty() || value <= minStack.top()) {
            minStack.push(value);
        }
    }
    
    void pop() {
        if (mainStack.empty()) return;
        
        if (mainStack.top() == minStack.top()) {
            minStack.pop();
        }
        mainStack.pop();
    }
    
    int top() {
        return mainStack.top();
    }
    
    int getMin() {
        return minStack.top();
    }
};

// ========================================
// 9. REVERSE A STACK
// ========================================
// Usage: reverseStack(st)
// Example: Reverses the entire stack
void insertAtBottom(stack<int>& st, int element) {
    if (st.empty()) {
        st.push(element);
        return;
    }
    
    int temp = st.top();
    st.pop();
    insertAtBottom(st, element);
    st.push(temp);
}

void reverseStack(stack<int>& st) {
    if (st.empty()) return;
    
    int temp = st.top();
    st.pop();
    reverseStack(st);
    insertAtBottom(st, temp);
}

// ========================================
// 10. IMPLEMENT TWO STACKS IN ONE ARRAY
// ========================================
class TwoStacks {
private:
    int* arr;
    int size;
    int top1, top2;

public:
    TwoStacks(int n) {
        size = n;
        arr = new int[n];
        top1 = -1;
        top2 = size;
    }
    
    void push1(int value) {
        if (top1 < top2 - 1) {
            arr[++top1] = value;
            cout << "Pushed " << value << " to stack1." << endl;
        } else {
            cout << "Stack Overflow!" << endl;
        }
    }
    
    void push2(int value) {
        if (top1 < top2 - 1) {
            arr[--top2] = value;
            cout << "Pushed " << value << " to stack2." << endl;
        } else {
            cout << "Stack Overflow!" << endl;
        }
    }
    
    int pop1() {
        if (top1 >= 0) {
            return arr[top1--];
        } else {
            cout << "Stack1 Underflow!" << endl;
            return -1;
        }
    }
    
    int pop2() {
        if (top2 < size) {
            return arr[top2++];
        } else {
            cout << "Stack2 Underflow!" << endl;
            return -1;
        }
    }
    
    ~TwoStacks() {
        delete[] arr;
    }
};

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    cout << "=== Stack Core Problems ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // 1. Reverse string
    // string reversed = reverseString("hello");
    // cout << "Reversed: " << reversed << endl;
    
    // 2. Check balanced parentheses
    // if (isBalanced("({[]})")) {
    //     cout << "Balanced" << endl;
    // } else {
    //     cout << "Not balanced" << endl;
    // }
    
    // 3. Infix to Postfix
    // string postfix = infixToPostfix("a+b*c");
    // cout << "Postfix: " << postfix << endl;
    
    // 4. Evaluate Postfix
    // int result = evaluatePostfix("23*5+");
    // cout << "Result: " << result << endl;
    
    // 5. Next Greater Element
    // int arr[] = {4, 5, 2, 25};
    // int n = 4;
    // int result[n];
    // nextGreater(arr, n, result);
    
    // 6. Stock Span
    // int prices[] = {100, 80, 60, 70, 60, 75, 85};
    // int n = 7;
    // int span[n];
    // stockSpan(prices, n, span);
    
    // 7. Sort Stack
    // stack<int> st;
    // st.push(30); st.push(10); st.push(50); st.push(20);
    // sortStack(st);
    // cout << "Sorted stack (top to bottom): ";
    // while (!st.empty()) {
    //     cout << st.top() << " ";
    //     st.pop();
    // }
    // cout << endl;
    
    // 8. MinStack
    // MinStack minSt;
    // minSt.push(5);
    // minSt.push(3);
    // minSt.push(7);
    // minSt.push(2);
    // cout << "Minimum: " << minSt.getMin() << endl;
    
    // 9. Reverse Stack
    // stack<int> st;
    // st.push(1); st.push(2); st.push(3); st.push(4);
    // reverseStack(st);
    // cout << "Reversed stack: ";
    // while (!st.empty()) {
    //     cout << st.top() << " ";
    //     st.pop();
    // }
    // cout << endl;
    
    // 10. Two Stacks in One Array
    // TwoStacks ts(10);
    // ts.push1(5);
    // ts.push2(10);
    // ts.push1(15);
    // ts.push2(20);
    // cout << "Popped from stack1: " << ts.pop1() << endl;
    // cout << "Popped from stack2: " << ts.pop2() << endl;
    
    return 0;
}
