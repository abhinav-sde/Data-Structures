import java.util.*;

/**
 * Monotonic Stack Patterns
 * A monotonic stack maintains elements in increasing or decreasing order.
 * Extremely powerful for optimizing O(N^2) nested loop problems to O(N).
 */
public class monotonic_patterns {

    /**
     * Pattern 1: Next Greater Element (NGE)
     * For each element, find the next element to the right that is greater.
     * Classic Use: Stock span, temperature rise days
     */
    static int[] nextGreaterElement(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        Arrays.fill(result, -1);
        Stack<Integer> stack = new Stack<>(); // Stores indices

        for (int i = 0; i < n; i++) {
            // Pop elements smaller than current
            while (!stack.isEmpty() && arr[stack.peek()] < arr[i]) {
                result[stack.pop()] = arr[i];
            }
            stack.push(i);
        }

        return result;
    }

    /**
     * Pattern 2: Largest Rectangle in Histogram
     * LeetCode 84 (Hard) - Google, Amazon favorite
     */
    static int largestRectangleArea(int[] heights) {
        Stack<Integer> stack = new Stack<>();
        int maxArea = 0;

        for (int i = 0; i <= heights.length; i++) {
            int h = (i == heights.length) ? 0 : heights[i];

            while (!stack.isEmpty() && h < heights[stack.peek()]) {
                int height = heights[stack.pop()];
                int width = stack.isEmpty() ? i : i - stack.peek() - 1;
                maxArea = Math.max(maxArea, height * width);
            }
            stack.push(i);
        }

        return maxArea;
    }

    /**
     * Pattern 3: Trapping Rain Water
     * LeetCode 42 (Hard) - Meta, Amazon common
     */
    static int trap(int[] height) {
        Stack<Integer> stack = new Stack<>();
        int water = 0;

        for (int i = 0; i < height.length; i++) {
            while (!stack.isEmpty() && height[i] > height[stack.peek()]) {
                int top = stack.pop();
                if (stack.isEmpty())
                    break;

                int distance = i - stack.peek() - 1;
                int boundedHeight = Math.min(height[i], height[stack.peek()]) - height[top];
                water += distance * boundedHeight;
            }
            stack.push(i);
        }

        return water;
    }

    /**
     * Pattern 4: Stock Span Problem
     * Calculate the span of stock prices (consecutive days with price <= current).
     */
    static int[] stockSpan(int[] prices) {
        int n = prices.length;
        int[] span = new int[n];
        Stack<Integer> stack = new Stack<>();

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && prices[stack.peek()] <= prices[i]) {
                stack.pop();
            }
            span[i] = stack.isEmpty() ? (i + 1) : (i - stack.peek());
            stack.push(i);
        }

        return span;
    }

    /**
     * Pattern 5: Sliding Window Maximum (using Monotonic Deque)
     * This is actually better done with Deque, but pattern is similar.
     */

    public static void main(String[] args) {
        int[] arr = { 4, 5, 2, 10, 8 };
        System.out.println("Next Greater Element:");
        int[] nge = nextGreaterElement(arr);
        System.out.println(Arrays.toString(nge));

        int[] histogram = { 2, 1, 5, 6, 2, 3 };
        System.out.println("\nLargest Rectangle: " + largestRectangleArea(histogram));

        int[] rain = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
        System.out.println("Rain Water Trapped: " + trap(rain));

        int[] prices = { 100, 80, 60, 70, 60, 75, 85 };
        System.out.println("Stock Span: " + Arrays.toString(stockSpan(prices)));
    }
}
