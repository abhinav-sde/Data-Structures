/**
 * Stack Core Problems in Java
 * Contains standard Stack algorithms
 */

import java.util.*;

public class core_problems {
    
    // ========================================
    // 1. REVERSE A STRING USING STACK
    // ========================================
    static String reverseString(String str) {
        Stack<Character> st = new Stack<>();
        
        for (char ch : str.toCharArray()) {
            st.push(ch);
        }
        
        StringBuilder reversed = new StringBuilder();
        while (!st.isEmpty()) {
            reversed.append(st.pop());
        }
        
        return reversed.toString();
    }
    
    // ========================================
    // 2. CHECK BALANCED PARENTHESES
    // ========================================
    static boolean isBalanced(String str) {
        Stack<Character> st = new Stack<>();
        
        for (char ch : str.toCharArray()) {
            if (ch == '(' || ch == '{' || ch == '[') {
                st.push(ch);
            } else if (ch == ')' || ch == '}' || ch == ']') {
                if (st.isEmpty()) return false;
                
                char top = st.pop();
                if ((ch == ')' && top != '(') ||
                    (ch == '}' && top != '{') ||
                    (ch == ']' && top != '[')) {
                    return false;
                }
            }
        }
        
        return st.isEmpty();
    }
    
    // ========================================
    // 3. INFIX TO POSTFIX CONVERSION
    // ========================================
    static int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    }
    
    static String infixToPostfix(String infix) {
        Stack<Character> st = new Stack<>();
        StringBuilder postfix = new StringBuilder();
        
        for (char ch : infix.toCharArray()) {
            if (Character.isLetterOrDigit(ch)) {
                postfix.append(ch);
            } else if (ch == '(') {
                st.push(ch);
            } else if (ch == ')') {
                while (!st.isEmpty() && st.peek() != '(') {
                    postfix.append(st.pop());
                }
                if (!st.isEmpty()) st.pop(); // Remove '('
            } else {
                while (!st.isEmpty() && precedence(st.peek()) >= precedence(ch)) {
                    postfix.append(st.pop());
                }
                st.push(ch);
            }
        }
        
        while (!st.isEmpty()) {
            postfix.append(st.pop());
        }
        
        return postfix.toString();
    }
    
    // ========================================
    // 4. EVALUATE POSTFIX EXPRESSION
    // ========================================
    static int evaluatePostfix(String postfix) {
        Stack<Integer> st = new Stack<>();
        
        for (char ch : postfix.toCharArray()) {
            if (Character.isDigit(ch)) {
                st.push(ch - '0');
            } else {
                int val2 = st.pop();
                int val1 = st.pop();
                
                switch (ch) {
                    case '+': st.push(val1 + val2); break;
                    case '-': st.push(val1 - val2); break;
                    case '*': st.push(val1 * val2); break;
                    case '/': st.push(val1 / val2); break;
                }
            }
        }
        
        return st.pop();
    }
    
    // ========================================
    // 5. NEXT GREATER ELEMENT
    // ========================================
    static void nextGreater(int[] arr, int n, int[] result) {
        Stack<Integer> st = new Stack<>();
        
        for (int i = n - 1; i >= 0; i--) {
            while (!st.isEmpty() && st.peek() <= arr[i]) {
                st.pop();
            }
            
            result[i] = st.isEmpty() ? -1 : st.peek();
            st.push(arr[i]);
        }
        
        System.out.print("Next greater elements: ");
        for (int i = 0; i < n; i++) {
            System.out.print(result[i] + " ");
        }
        System.out.println();
    }
    
    // ========================================
    // 6. STOCK SPAN PROBLEM
    // ========================================
    static void stockSpan(int[] prices, int n, int[] span) {
        Stack<Integer> st = new Stack<>();
        st.push(0);
        span[0] = 1;
        
        for (int i = 1; i < n; i++) {
            while (!st.isEmpty() && prices[st.peek()] <= prices[i]) {
                st.pop();
            }
            
            span[i] = st.isEmpty() ? (i + 1) : (i - st.peek());
            st.push(i);
        }
        
        System.out.print("Stock span: ");
        for (int i = 0; i < n; i++) {
            System.out.print(span[i] + " ");
        }
        System.out.println();
    }
    
    // ========================================
    // 7. SORT A STACK
    // ========================================
    static void sortedInsert(Stack<Integer> st, int element) {
        if (st.isEmpty() || element < st.peek()) {
            st.push(element);
            return;
        }
        
        int temp = st.pop();
        sortedInsert(st, element);
        st.push(temp);
    }
    
    static void sortStack(Stack<Integer> st) {
        if (st.isEmpty()) return;
        
        int temp = st.pop();
        sortStack(st);
        sortedInsert(st, temp);
    }
    
    // ========================================
    // 8. GET MINIMUM ELEMENT IN O(1)
    // ========================================
    static class MinStack {
        private Stack<Integer> mainStack;
        private Stack<Integer> minStack;
        
        public MinStack() {
            mainStack = new Stack<>();
            minStack = new Stack<>();
        }
        
        public void push(int value) {
            mainStack.push(value);
            if (minStack.isEmpty() || value <= minStack.peek()) {
                minStack.push(value);
            }
        }
        
        public void pop() {
            if (mainStack.isEmpty()) return;
            
            int value = mainStack.pop();
            if (value == minStack.peek()) {
                minStack.pop();
            }
        }
        
        public int top() {
            return mainStack.peek();
        }
        
        public int getMin() {
            return minStack.peek();
        }
    }
    
    // ========================================
    // 9. REVERSE A STACK
    // ========================================
    static void insertAtBottom(Stack<Integer> st, int element) {
        if (st.isEmpty()) {
            st.push(element);
            return;
        }
        
        int temp = st.pop();
        insertAtBottom(st, element);
        st.push(temp);
    }
    
    static void reverseStack(Stack<Integer> st) {
        if (st.isEmpty()) return;
        
        int temp = st.pop();
        reverseStack(st);
        insertAtBottom(st, temp);
    }
    
    // ========================================
    // 10. IMPLEMENT TWO STACKS IN ONE ARRAY
    // ========================================
    static class TwoStacks {
        private int[] arr;
        private int size;
        private int top1, top2;
        
        public TwoStacks(int n) {
            size = n;
            arr = new int[n];
            top1 = -1;
            top2 = size;
        }
        
        public void push1(int value) {
            if (top1 < top2 - 1) {
                arr[++top1] = value;
                System.out.println("Pushed " + value + " to stack1.");
            } else {
                System.out.println("Stack Overflow!");
            }
        }
        
        public void push2(int value) {
            if (top1 < top2 - 1) {
                arr[--top2] = value;
                System.out.println("Pushed " + value + " to stack2.");
            } else {
                System.out.println("Stack Overflow!");
            }
        }
        
        public int pop1() {
            if (top1 >= 0) {
                return arr[top1--];
            } else {
                System.out.println("Stack1 Underflow!");
                return -1;
            }
        }
        
        public int pop2() {
            if (top2 < size) {
                return arr[top2++];
            } else {
                System.out.println("Stack2 Underflow!");
                return -1;
            }
        }
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Stack Core Problems ===");
        
        // Example usage - uncomment to use
        
        // 1. Reverse string
        // System.out.println("Reversed: " + reverseString("hello"));
        
        // 2. Check balanced parentheses
        // if (isBalanced("({[]})")) {
        //     System.out.println("Balanced");
        // } else {
        //     System.out.println("Not balanced");
        // }
        
        // 3. Infix to Postfix
        // System.out.println("Postfix: " + infixToPostfix("a+b*c"));
        
        // 4. Evaluate Postfix
        // System.out.println("Result: " + evaluatePostfix("23*5+"));
        
        // 5. Next Greater Element
        // int[] arr = {4, 5, 2, 25};
        // int[] result = new int[4];
        // nextGreater(arr, 4, result);
        
        // 6. Stock Span
        // int[] prices = {100, 80, 60, 70, 60, 75, 85};
        // int[] span = new int[7];
        // stockSpan(prices, 7, span);
        
        // 7. Sort Stack
        // Stack<Integer> st = new Stack<>();
        // st.push(30); st.push(10); st.push(50); st.push(20);
        // sortStack(st);
        // System.out.println("Sorted stack: " + st);
        
        // 8. MinStack
        // MinStack minSt = new MinStack();
        // minSt.push(5);
        // minSt.push(3);
        // minSt.push(7);
        // minSt.push(2);
        // System.out.println("Minimum: " + minSt.getMin());
        
        // 9. Reverse Stack
        // Stack<Integer> st2 = new Stack<>();
        // st2.push(1); st2.push(2); st2.push(3); st2.push(4);
        // reverseStack(st2);
        // System.out.println("Reversed stack: " + st2);
        
        // 10. Two Stacks in One Array
        // TwoStacks ts = new TwoStacks(10);
        // ts.push1(5);
        // ts.push2(10);
        // System.out.println("Popped 1: " + ts.pop1());
        // System.out.println("Popped 2: " + ts.pop2());
    }
}
