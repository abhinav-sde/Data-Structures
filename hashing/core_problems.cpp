#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Problem 1: Two Sum
// Given an array of integers and a target, return indices of the two numbers such that they add up to target.
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> map; // Value -> Index
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (map.count(complement)) {
            return {map[complement], i};
        }
        map[nums[i]] = i;
    }
    return {};
}

// Problem 2: First Repeated Character
// Find the first character that repeats in a string.
char firstRepeatedChar(string s) {
    unordered_set<char> seen;
    for (char c : s) {
        if (seen.count(c)) return c;
        seen.insert(c);
    }
    return '\0';
}

int main() {
    // Test Two Sum
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = twoSum(nums, target);
    if (!result.empty()) {
        cout << "Two Sum Indices: " << result[0] << ", " << result[1] << endl;
    } else {
        cout << "Two Sum not found" << endl;
    }

    // Test First Repeated
    string s = "abacaba";
    cout << "First Repeated: " << firstRepeatedChar(s) << endl;

    return 0;
}
