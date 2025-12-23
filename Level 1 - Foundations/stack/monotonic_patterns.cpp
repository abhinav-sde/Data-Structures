#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/**
 * Monotonic Stack Patterns in C++
 */

// Pattern 1: Next Greater Element
vector<int> nextGreaterElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> st;
    
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            result[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }
    
    return result;
}

// Pattern 2: Largest Rectangle in Histogram
int largestRectangleArea(vector<int>& heights) {
    stack<int> st;
    int maxArea = 0;
    
    for (int i = 0; i <= heights.size(); i++) {
        int h = (i == heights.size()) ? 0 : heights[i];
        
        while (!st.empty() && h < heights[st.top()]) {
            int height = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        st.push(i);
    }
    
    return maxArea;
}

// Pattern 3: Trapping Rain Water
int trap(vector<int>& height) {
    stack<int> st;
    int water = 0;
    
    for (int i = 0; i < height.size(); i++) {
        while (!st.empty() && height[i] > height[st.top()]) {
            int top = st.top();
            st.pop();
            if (st.empty()) break;
            
            int distance = i - st.top() - 1;
            int boundedHeight = min(height[i], height[st.top()]) - height[top];
            water += distance * boundedHeight;
        }
        st.push(i);
    }
    
    return water;
}

int main() {
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> nge = nextGreaterElement(arr);
    
    cout << "Next Greater Element: ";
    for (int x : nge) cout << x << " ";
    cout << endl;
    
    vector<int> histogram = {2, 1, 5, 6, 2, 3};
    cout << "Largest Rectangle: " << largestRectangleArea(histogram) << endl;
    
    vector<int> rain = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Rain Water: " << trap(rain) << endl;
    
    return 0;
}
