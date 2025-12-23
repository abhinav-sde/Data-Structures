#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Problem: Longest Consecutive Sequence
// Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
// Algorithm should run in O(n) time.
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> numSet(nums.begin(), nums.end());
    int longestStreak = 0;

    for (int num : numSet) {
        // Only start counting if 'num' is the start of a sequence
        if (!numSet.count(num - 1)) {
            int currentNum = num;
            int currentStreak = 1;

            while (numSet.count(currentNum + 1)) {
                currentNum += 1;
                currentStreak += 1;
            }

            longestStreak = max(longestStreak, currentStreak);
        }
    }

    return longestStreak;
}

int main() {
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout << "Longest Consecutive Sequence Length: " << longestConsecutive(nums) << endl; 
    // Expected: 4 (1, 2, 3, 4)
    return 0;
}
