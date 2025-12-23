#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ========================================
// 1. LARGEST RECTANGLE IN HISTOGRAM
// ========================================
// Concept: Stack for finding previous and next smaller elements
// Usage: area = largestRectangle(heights, n)
// Example: heights = {2, 1, 5, 6, 2, 3} returns 10
int largestRectangle(int heights[], int n) {
    stack<int> st;
    int maxArea = 0;
    int i = 0;
    
    while (i < n) {
        if (st.empty() || heights[st.top()] <= heights[i]) {
            st.push(i++);
        } else {
            int top = st.top();
            st.pop();
            int area = heights[top] * (st.empty() ? i : i - st.top() - 1);
            maxArea = max(maxArea, area);
        }
    }
    
    while (!st.empty()) {
        int top = st.top();
        st.pop();
        int area = heights[top] * (st.empty() ? i : i - st.top() - 1);
        maxArea = max(maxArea, area);
    }
    
    return maxArea;
}

// ========================================
// 2. CELEBRITY PROBLEM
// ========================================
// Concept: Stack elimination
// Usage: celebrity = findCelebrity(matrix, n)
// Example: Returns index of celebrity or -1
int findCelebrity(int matrix[][100], int n) {
    stack<int> st;
    
    // Push all people to stack
    for (int i = 0; i < n; i++) {
        st.push(i);
    }
    
    // Eliminate non-celebrities
    while (st.size() > 1) {
        int a = st.top(); st.pop();
        int b = st.top(); st.pop();
        
        if (matrix[a][b] == 1) {
            // a knows b, so a is not celebrity
            st.push(b);
        } else {
            // a doesn't know b, so b is not celebrity
            st.push(a);
        }
    }
    
    int candidate = st.top();
    
    // Verify candidate
    for (int i = 0; i < n; i++) {
        if (i != candidate) {
            if (matrix[candidate][i] == 1 || matrix[i][candidate] == 0) {
                return -1;
            }
        }
    }
    
    return candidate;
}

// ========================================
// 3. MAXIMAL RECTANGLE IN BINARY MATRIX
// ========================================
// Concept: Largest rectangle in histogram for each row
// Usage: area = maximalRectangle(matrix, rows, cols)
// Example: Returns largest rectangle area containing only 1s
int maximalRectangle(int matrix[][100], int rows, int cols) {
    int heights[100] = {0};
    int maxArea = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                heights[j]++;
            } else {
                heights[j] = 0;
            }
        }
        maxArea = max(maxArea, largestRectangle(heights, cols));
    }
    
    return maxArea;
}

// ========================================
// 4. IMPLEMENT STACK USING QUEUES
// ========================================
// Concept: Queue manipulation
#include <queue>

class StackUsingQueues {
private:
    queue<int> q1, q2;

public:
    void push(int value) {
        q2.push(value);
        
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        
        swap(q1, q2);
    }
    
    void pop() {
        if (q1.empty()) {
            cout << "Stack is empty!" << endl;
            return;
        }
        q1.pop();
    }
    
    int top() {
        if (q1.empty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

// ========================================
// 5. SLIDING WINDOW MAXIMUM
// ========================================
// Concept: Deque (can use stack approach)
// Usage: slidingWindowMax(arr, n, k, result)
// Example: arr = {1, 3, -1, -3, 5, 3, 6, 7}, k = 3 -> {3, 3, 5, 5, 6, 7}
void slidingWindowMax(int arr[], int n, int k, vector<int>& result) {
    stack<int> st;
    int nextGreater[n];
    
    // Find next greater for optimization
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            st.pop();
        }
        nextGreater[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    
    int maxIdx = 0;
    for (int i = 0; i <= n - k; i++) {
        // Find max in current window
        if (maxIdx < i) {
            maxIdx = i;
            for (int j = i; j < i + k; j++) {
                if (arr[j] > arr[maxIdx]) {
                    maxIdx = j;
                }
            }
        } else {
            if (arr[i + k - 1] >= arr[maxIdx]) {
                maxIdx = i + k - 1;
            }
        }
        
        result.push_back(arr[maxIdx]);
    }
}

// ========================================
// 6. REMOVE K DIGITS TO MAKE SMALLEST NUMBER
// ========================================
// Concept: Monotonic stack
// Usage: result = removeKdigits(num, k)
// Example: removeKdigits("1432219", 3) returns "1219"
string removeKdigits(string num, int k) {
    stack<char> st;
    
    for (char digit : num) {
        while (!st.empty() && k > 0 && st.top() > digit) {
            st.pop();
            k--;
        }
        st.push(digit);
    }
    
    // Remove remaining k digits
    while (k > 0 && !st.empty()) {
        st.pop();
        k--;
    }
    
    // Build result
    string result = "";
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    reverse(result.begin(), result.end());
    
    // Remove leading zeros
    int i = 0;
    while (i < result.length() && result[i] == '0') {
        i++;
    }
    result = result.substr(i);
    
    return result.empty() ? "0" : result;
}

// ========================================
// 7. DECODE STRING
// ========================================
// Concept: Stack for nested patterns
// Usage: decoded = decodeString(str)
// Example: decodeString("3[a2[c]]") returns "accaccacc"
string decodeString(string str) {
    stack<int> countStack;
    stack<string> stringStack;
    string currentString = "";
    int k = 0;
    
    for (char ch : str) {
        if (isdigit(ch)) {
            k = k * 10 + (ch - '0');
        } else if (ch == '[') {
            countStack.push(k);
            stringStack.push(currentString);
            currentString = "";
            k = 0;
        } else if (ch == ']') {
            string temp = currentString;
            currentString = stringStack.top();
            stringStack.pop();
            int count = countStack.top();
            countStack.pop();
            
            for (int i = 0; i < count; i++) {
                currentString += temp;
            }
        } else {
            currentString += ch;
        }
    }
    
    return currentString;
}

// ========================================
// 8. ASTEROID COLLISION
// ========================================
// Concept: Stack simulation
// Usage: asteroidCollision(asteroids, n)
// Example: {5, 10, -5} -> {5, 10}, {-2, -1, 1, 2} -> {-2, -1, 1, 2}
void asteroidCollision(int asteroids[], int n) {
    stack<int> st;
    
    for (int i = 0; i < n; i++) {
        bool destroyed = false;
        
        while (!st.empty() && asteroids[i] < 0 && st.top() > 0) {
            if (st.top() < -asteroids[i]) {
                st.pop();
                continue;
            } else if (st.top() == -asteroids[i]) {
                st.pop();
            }
            destroyed = true;
            break;
        }
        
        if (!destroyed) {
            st.push(asteroids[i]);
        }
    }
    
    vector<int> result;
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    reverse(result.begin(), result.end());
    
    cout << "Remaining asteroids: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
}

// ========================================
// 9. TRAPPING RAIN WATER USING STACK
// ========================================
// Concept: Stack-based approach
// Usage: water = trapRainWater(heights, n)
// Example: heights = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1} returns 6
int trapRainWater(int heights[], int n) {
    stack<int> st;
    int water = 0;
    
    for (int i = 0; i < n; i++) {
        while (!st.empty() && heights[i] > heights[st.top()]) {
            int top = st.top();
            st.pop();
            
            if (st.empty()) break;
            
            int distance = i - st.top() - 1;
            int boundedHeight = min(heights[i], heights[st.top()]) - heights[top];
            water += distance * boundedHeight;
        }
        st.push(i);
    }
    
    return water;
}

// ========================================
// 10. LONGEST VALID PARENTHESES
// ========================================
// Concept: Stack with indices
// Usage: length = longestValidParentheses(str)
// Example: longestValidParentheses("(()") returns 2
int longestValidParentheses(string str) {
    stack<int> st;
    st.push(-1);
    int maxLen = 0;
    
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            st.push(i);
        } else {
            st.pop();
            if (st.empty()) {
                st.push(i);
            } else {
                maxLen = max(maxLen, i - st.top());
            }
        }
    }
    
    return maxLen;
}

// ========================================
// 11. EVALUATE REVERSE POLISH NOTATION
// ========================================
// Concept: Stack evaluation
// Usage: result = evalRPN(tokens, n)
// Example: {"2", "1", "+", "3", "*"} returns 9
int evalRPN(string tokens[], int n) {
    stack<int> st;
    
    for (int i = 0; i < n; i++) {
        if (tokens[i] == "+" || tokens[i] == "-" || 
            tokens[i] == "*" || tokens[i] == "/") {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            
            if (tokens[i] == "+") st.push(a + b);
            else if (tokens[i] == "-") st.push(a - b);
            else if (tokens[i] == "*") st.push(a * b);
            else st.push(a / b);
        } else {
            st.push(stoi(tokens[i]));
        }
    }
    
    return st.top();
}

// ========================================
// 12. BASIC CALCULATOR
// ========================================
// Concept: Stack with operators
// Usage: result = calculate(str)
// Example: calculate("(1+(4+5+2)-3)+(6+8)") returns 23
int calculate(string str) {
    stack<int> st;
    int result = 0;
    int number = 0;
    int sign = 1;
    
    for (char ch : str) {
        if (isdigit(ch)) {
            number = number * 10 + (ch - '0');
        } else if (ch == '+') {
            result += sign * number;
            number = 0;
            sign = 1;
        } else if (ch == '-') {
            result += sign * number;
            number = 0;
            sign = -1;
        } else if (ch == '(') {
            st.push(result);
            st.push(sign);
            result = 0;
            sign = 1;
        } else if (ch == ')') {
            result += sign * number;
            number = 0;
            result *= st.top(); st.pop();
            result += st.top(); st.pop();
        }
    }
    
    result += sign * number;
    return result;
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    cout << "=== Stack Advanced Problems ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // 1. Largest Rectangle in Histogram
    // int heights[] = {2, 1, 5, 6, 2, 3};
    // int area = largestRectangle(heights, 6);
    // cout << "Largest rectangle area: " << area << endl;
    
    // 2. Celebrity Problem
    // int matrix[100][100] = {{0, 1, 0}, {0, 0, 0}, {0, 1, 0}};
    // int celebrity = findCelebrity(matrix, 3);
    // cout << "Celebrity: " << celebrity << endl;
    
    // 3. Maximal Rectangle
    // int matrix[100][100] = {{1, 0, 1, 0, 0}, {1, 0, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 0, 0, 1, 0}};
    // int area = maximalRectangle(matrix, 4, 5);
    // cout << "Maximal rectangle area: " << area << endl;
    
    // 4. Stack Using Queues
    // StackUsingQueues st;
    // st.push(1); st.push(2); st.push(3);
    // cout << "Top: " << st.top() << endl;
    // st.pop();
    // cout << "Top after pop: " << st.top() << endl;
    
    // 5. Sliding Window Maximum
    // int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
    // vector<int> result;
    // slidingWindowMax(arr, 8, 3, result);
    // cout << "Sliding window max: ";
    // for (int val : result) cout << val << " ";
    // cout << endl;
    
    // 6. Remove K Digits
    // string result = removeKdigits("1432219", 3);
    // cout << "Smallest number: " << result << endl;
    
    // 7. Decode String
    // string decoded = decodeString("3[a2[c]]");
    // cout << "Decoded: " << decoded << endl;
    
    // 8. Asteroid Collision
    // int asteroids[] = {5, 10, -5};
    // asteroidCollision(asteroids, 3);
    
    // 9. Trap Rain Water
    // int heights[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    // int water = trapRainWater(heights, 12);
    // cout << "Water trapped: " << water << endl;
    
    // 10. Longest Valid Parentheses
    // int len = longestValidParentheses("(()");
    // cout << "Longest valid parentheses: " << len << endl;
    
    // 11. Evaluate RPN
    // string tokens[] = {"2", "1", "+", "3", "*"};
    // int result = evalRPN(tokens, 5);
    // cout << "RPN result: " << result << endl;
    
    // 12. Basic Calculator
    // int result = calculate("(1+(4+5+2)-3)+(6+8)");
    // cout << "Calculator result: " << result << endl;
    
    return 0;
}
