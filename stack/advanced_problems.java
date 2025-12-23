/**
 * Stack Advanced Problems in Java
 * Contains complex Stack algorithms
 */

import java.util.*;

public class advanced_problems {
    
    // ========================================
    // 1. LARGEST RECTANGLE IN HISTOGRAM
    // ========================================
    static int largestRectangle(int[] heights, int n) {
        Stack<Integer> st = new Stack<>();
        int maxArea = 0;
        int i = 0;
        
        while (i < n) {
            if (st.isEmpty() || heights[st.peek()] <= heights[i]) {
                st.push(i++);
            } else {
                int top = st.pop();
                int area = heights[top] * (st.isEmpty() ? i : i - st.peek() - 1);
                maxArea = Math.max(maxArea, area);
            }
        }
        
        while (!st.isEmpty()) {
            int top = st.pop();
            int area = heights[top] * (st.isEmpty() ? i : i - st.peek() - 1);
            maxArea = Math.max(maxArea, area);
        }
        
        return maxArea;
    }
    
    // ========================================
    // 2. CELEBRITY PROBLEM
    // ========================================
    static int findCelebrity(int[][] matrix, int n) {
        Stack<Integer> st = new Stack<>();
        
        for (int i = 0; i < n; i++) {
            st.push(i);
        }
        
        while (st.size() > 1) {
            int a = st.pop();
            int b = st.pop();
            
            if (matrix[a][b] == 1) {
                // a knows b, so a is not celebrity
                st.push(b);
            } else {
                // a doesn't know b, so b is not celebrity
                st.push(a);
            }
        }
        
        if (st.isEmpty()) return -1;
        int candidate = st.pop();
        
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
    static int maximalRectangle(int[][] matrix, int rows, int cols) {
        int[] heights = new int[cols];
        int maxArea = 0;
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == 1) {
                    heights[j]++;
                } else {
                    heights[j] = 0;
                }
            }
            maxArea = Math.max(maxArea, largestRectangle(heights, cols));
        }
        
        return maxArea;
    }
    
    // ========================================
    // 4. IMPLEMENT STACK USING QUEUES
    // ========================================
    static class StackUsingQueues {
        private Queue<Integer> q1 = new LinkedList<>();
        private Queue<Integer> q2 = new LinkedList<>();
        
        public void push(int value) {
            q2.add(value);
            
            while (!q1.isEmpty()) {
                q2.add(q1.poll());
            }
            
            Queue<Integer> temp = q1;
            q1 = q2;
            q2 = temp;
        }
        
        public void pop() {
            if (q1.isEmpty()) {
                System.out.println("Stack is empty!");
                return;
            }
            q1.poll();
        }
        
        public int top() {
            if (q1.isEmpty()) {
                System.out.println("Stack is empty!");
                return -1;
            }
            return q1.peek();
        }
        
        public boolean empty() {
            return q1.isEmpty();
        }
    }
    
    // ========================================
    // 5. SLIDING WINDOW MAXIMUM
    // ========================================
    static void slidingWindowMax(int[] arr, int n, int k, List<Integer> result) {
        Stack<Integer> st = new Stack<>();
        int[] nextGreater = new int[n];
        
        // Find next greater for optimization
        for (int i = n - 1; i >= 0; i--) {
            while (!st.isEmpty() && arr[st.peek()] <= arr[i]) {
                st.pop();
            }
            nextGreater[i] = st.isEmpty() ? n : st.peek();
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
            
            result.add(arr[maxIdx]);
        }
    }
    
    // ========================================
    // 6. REMOVE K DIGITS TO MAKE SMALLEST NUMBER
    // ========================================
    static String removeKdigits(String num, int k) {
        Stack<Character> st = new Stack<>();
        
        for (char digit : num.toCharArray()) {
            while (!st.isEmpty() && k > 0 && st.peek() > digit) {
                st.pop();
                k--;
            }
            st.push(digit);
        }
        
        while (k > 0 && !st.isEmpty()) {
            st.pop();
            k--;
        }
        
        StringBuilder result = new StringBuilder();
        while (!st.isEmpty()) {
            result.append(st.pop());
        }
        result.reverse();
        
        // Remove leading zeros
        int i = 0;
        while (i < result.length() && result.charAt(i) == '0') {
            i++;
        }
        String ans = result.substring(i);
        
        return ans.isEmpty() ? "0" : ans;
    }
    
    // ========================================
    // 7. DECODE STRING
    // ========================================
    static String decodeString(String str) {
        Stack<Integer> countStack = new Stack<>();
        Stack<String> stringStack = new Stack<>();
        String currentString = "";
        int k = 0;
        
        for (char ch : str.toCharArray()) {
            if (Character.isDigit(ch)) {
                k = k * 10 + (ch - '0');
            } else if (ch == '[') {
                countStack.push(k);
                stringStack.push(currentString);
                currentString = "";
                k = 0;
            } else if (ch == ']') {
                String temp = currentString;
                currentString = stringStack.pop();
                int count = countStack.pop();
                
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
    static void asteroidCollision(int[] asteroids, int n) {
        Stack<Integer> st = new Stack<>();
        
        for (int i = 0; i < n; i++) {
            boolean destroyed = false;
            
            while (!st.isEmpty() && asteroids[i] < 0 && st.peek() > 0) {
                if (st.peek() < -asteroids[i]) {
                    st.pop();
                    continue;
                } else if (st.peek() == -asteroids[i]) {
                    st.pop();
                }
                destroyed = true;
                break;
            }
            
            if (!destroyed) {
                st.push(asteroids[i]);
            }
        }
        
        List<Integer> result = new ArrayList<>();
        while (!st.isEmpty()) {
            result.add(st.pop());
        }
        Collections.reverse(result);
        
        System.out.print("Remaining asteroids: ");
        for (int val : result) {
            System.out.print(val + " ");
        }
        System.out.println();
    }
    
    // ========================================
    // 9. TRAPPING RAIN WATER USING STACK
    // ========================================
    static int trapRainWater(int[] heights, int n) {
        Stack<Integer> st = new Stack<>();
        int water = 0;
        
        for (int i = 0; i < n; i++) {
            while (!st.isEmpty() && heights[i] > heights[st.peek()]) {
                int top = st.pop();
                
                if (st.isEmpty()) break;
                
                int distance = i - st.peek() - 1;
                int boundedHeight = Math.min(heights[i], heights[st.peek()]) - heights[top];
                water += distance * boundedHeight;
            }
            st.push(i);
        }
        
        return water;
    }
    
    // ========================================
    // 10. LONGEST VALID PARENTHESES
    // ========================================
    static int longestValidParentheses(String str) {
        Stack<Integer> st = new Stack<>();
        st.push(-1);
        int maxLen = 0;
        
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.isEmpty()) {
                    st.push(i);
                } else {
                    maxLen = Math.max(maxLen, i - st.peek());
                }
            }
        }
        
        return maxLen;
    }
    
    // ========================================
    // 11. EVALUATE REVERSE POLISH NOTATION
    // ========================================
    static int evalRPN(String[] tokens, int n) {
        Stack<Integer> st = new Stack<>();
        
        for (int i = 0; i < n; i++) {
            String t = tokens[i];
            if (t.equals("+") || t.equals("-") || t.equals("*") || t.equals("/")) {
                int b = st.pop();
                int a = st.pop();
                
                if (t.equals("+")) st.push(a + b);
                else if (t.equals("-")) st.push(a - b);
                else if (t.equals("*")) st.push(a * b);
                else st.push(a / b);
            } else {
                st.push(Integer.parseInt(t));
            }
        }
        
        return st.peek();
    }
    
    // ========================================
    // 12. BASIC CALCULATOR
    // ========================================
    static int calculate(String str) {
        Stack<Integer> st = new Stack<>();
        int result = 0;
        int number = 0;
        int sign = 1;
        
        for (char ch : str.toCharArray()) {
            if (Character.isDigit(ch)) {
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
                result *= st.pop(); // sign
                result += st.pop(); // previous result
            }
        }
        
        result += sign * number;
        return result;
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Stack Advanced Problems ===");
        
        // Example usage - uncomment to use
        
        // 1. Largest Rectangle
        // int[] heights = {2, 1, 5, 6, 2, 3};
        // System.out.println("Largest rectangle area: " + largestRectangle(heights, 6));
        
        // 5. Sliding Window Maximum
        // int[] arr = {1, 3, -1, -3, 5, 3, 6, 7};
        // List<Integer> result = new ArrayList<>();
        // slidingWindowMax(arr, 8, 3, result);
        // System.out.println("Sliding window max: " + result);
        
        // 6. Remove K Digits
        // System.out.println("Smallest number: " + removeKdigits("1432219", 3));
        
        // 7. Decode String
        // System.out.println("Decoded: " + decodeString("3[a2[c]]"));
        
        // 9. Trap Rain Water
        // int[] heights2 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        // System.out.println("Water trapped: " + trapRainWater(heights2, 12));
        
        // 12. Basic Calculator
        // System.out.println("Calculator result: " + calculate("(1+(4+5+2)-3)+(6+8)"));
    }
}
