#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Problem 1: Sliding Window Maximum
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;
    
    for (int i = 0; i < nums.size(); i++) {
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }
        
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}

// Problem 2: Palindrome Check
bool isPalindrome(string s) {
    deque<char> dq;
    
    for (char c : s) {
        if (isalnum(c)) {
            dq.push_back(tolower(c));
        }
    }
    
    while (dq.size() > 1) {
        if (dq.front() != dq.back()) {
            return false;
        }
        dq.pop_front();
        dq.pop_back();
    }
    
    return true;
}

int main() {
    cout << "=== Core Deque Problems ===" << endl << endl;
    
    // Test 1
    cout << "Test 1: Sliding Window Maximum" << endl;
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    vector<int> result = maxSlidingWindow(nums, k);
    cout << "Result: [ ";
    for (int r : result) cout << r << " ";
    cout << "]" << endl << endl;
    
    // Test 2
    cout << "Test 2: Palindrome Check" << endl;
    cout << "'racecar' is palindrome: " << (isPalindrome("racecar") ? "true" : "false") << endl;
    cout << "'hello' is palindrome: " << (isPalindrome("hello") ? "true" : "false") << endl;
    
    return 0;
}
