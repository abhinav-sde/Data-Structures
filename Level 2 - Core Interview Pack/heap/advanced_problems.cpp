#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;

/**
 * Advanced Heap Problems in C++
 * Contains complex heap-based algorithms and applications
 */

// Problem 1: Task Scheduler
int leastInterval(vector<char>& tasks, int n) {
    vector<int> freq(26, 0);
    for (char task : tasks) {
        freq[task - 'A']++;
    }
    
    priority_queue<int> maxHeap;
    for (int f : freq) {
        if (f > 0) maxHeap.push(f);
    }
    
    int time = 0;
    queue<pair<int, int>> cooldown; // {frequency, available_time}
    
    while (!maxHeap.empty() || !cooldown.empty()) {
        time++;
        
        if (!maxHeap.empty()) {
            int current = maxHeap.top() - 1;
            maxHeap.pop();
            if (current > 0) {
                cooldown.push({current, time + n});
            }
        }
        
        if (!cooldown.empty() && cooldown.front().second == time) {
            maxHeap.push(cooldown.front().first);
            cooldown.pop();
        }
    }
    
    return time;
}

// Problem 2: Minimum Cost to Connect Ropes
int connectRopes(vector<int>& ropes) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (int rope : ropes) {
        minHeap.push(rope);
    }
    
    int totalCost = 0;
    
    while (minHeap.size() > 1) {
        int first = minHeap.top(); minHeap.pop();
        int second = minHeap.top(); minHeap.pop();
        int cost = first + second;
        totalCost += cost;
        minHeap.push(cost);
    }
    
    return totalCost;
}

// Problem 3: Find K Pairs with Smallest Sums
vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    vector<pair<int, int>> result;
    if (nums1.empty() || nums2.empty() || k == 0) return result;
    
    auto comp = [&](pair<int, int> a, pair<int, int> b) {
        return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> minHeap(comp);
    
    for (int i = 0; i < min((int)nums1.size(), k); i++) {
        minHeap.push({i, 0});
    }
    
    while (k > 0 && !minHeap.empty()) {
        auto [i, j] = minHeap.top();
        minHeap.pop();
        result.push_back({nums1[i], nums2[j]});
        
        if (j + 1 < nums2.size()) {
            minHeap.push({i, j + 1});
        }
        k--;
    }
    
    return result;
}

// Problem 4: Reorganize String
string reorganizeString(string s) {
    unordered_map<char, int> freqMap;
    for (char c : s) {
        freqMap[c]++;
    }
    
    auto comp = [&](char a, char b) {
        return freqMap[a] < freqMap[b];
    };
    priority_queue<char, vector<char>, decltype(comp)> maxHeap(comp);
    
    for (auto& [ch, freq] : freqMap) {
        maxHeap.push(ch);
    }
    
    string result;
    char prev = '\0';
    
    while (!maxHeap.empty()) {
        char current = maxHeap.top();
        maxHeap.pop();
        result += current;
        
        if (prev != '\0' && freqMap[prev] > 0) {
            maxHeap.push(prev);
        }
        
        freqMap[current]--;
        prev = freqMap[current] > 0 ? current : '\0';
    }
    
    return result.length() == s.length() ? result : "";
}

// Problem 5: IPO (maximize capital)
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    int n = profits.size();
    vector<pair<int, int>> projects;
    
    for (int i = 0; i < n; i++) {
        projects.push_back({capital[i], profits[i]});
    }
    
    sort(projects.begin(), projects.end());
    
    priority_queue<int> maxHeap;
    int i = 0;
    
    for (int j = 0; j < k; j++) {
        while (i < n && projects[i].first <= w) {
            maxHeap.push(projects[i].second);
            i++;
        }
        
        if (maxHeap.empty()) break;
        
        w += maxHeap.top();
        maxHeap.pop();
    }
    
    return w;
}

// Problem 6: Ugly Number II
int nthUglyNumber(int n) {
    priority_queue<long, vector<long>, greater<long>> minHeap;
    unordered_map<long, bool> seen;
    
    minHeap.push(1);
    seen[1] = true;
    
    vector<int> primes = {2, 3, 5};
    long ugly = 1;
    
    for (int i = 0; i < n; i++) {
        ugly = minHeap.top();
        minHeap.pop();
        
        for (int prime : primes) {
            long next = ugly * prime;
            if (seen.find(next) == seen.end()) {
                minHeap.push(next);
                seen[next] = true;
            }
        }
    }
    
    return (int)ugly;
}

// Helper function
void displayVector(const vector<int>& vec) {
    cout << "[ ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << "]";
}

int main() {
    cout << "=== Advanced Heap Problems ===" << endl << endl;
    
    // Test 1: Task Scheduler
    cout << "Test 1: Task Scheduler" << endl;
    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n = 2;
    cout << "Tasks: A A A B B B, cooldown: " << n << endl;
    cout << "Minimum time: " << leastInterval(tasks, n) << endl << endl;
    
    // Test 2: Connect Ropes
    cout << "Test 2: Minimum Cost to Connect Ropes" << endl;
    vector<int> ropes = {4, 3, 2, 6};
    cout << "Ropes: "; displayVector(ropes); cout << endl;
    cout << "Minimum cost: " << connectRopes(ropes) << endl << endl;
    
    // Test 3: K Smallest Pairs
    cout << "Test 3: K Pairs with Smallest Sums" << endl;
    vector<int> nums1 = {1, 7, 11};
    vector<int> nums2 = {2, 4, 6};
    int k3 = 3;
    auto pairs = kSmallestPairs(nums1, nums2, k3);
    cout << "nums1: "; displayVector(nums1); cout << endl;
    cout << "nums2: "; displayVector(nums2); cout << endl;
    cout << "K smallest pairs: ";
    for (auto& [a, b] : pairs) {
        cout << "[" << a << "," << b << "] ";
    }
    cout << endl << endl;
    
    // Test 4: Reorganize String
    cout << "Test 4: Reorganize String" << endl;
    string s = "aab";
    cout << "Input: " << s << endl;
    cout << "Reorganized: " << reorganizeString(s) << endl << endl;
    
    // Test 5: IPO
    cout << "Test 5: IPO - Maximize Capital" << endl;
    int k5 = 2, w = 0;
    vector<int> profits = {1, 2, 3};
    vector<int> capital = {0, 1, 1};
    cout << "k: " << k5 << ", initial capital: " << w << endl;
    cout << "Profits: "; displayVector(profits); cout << endl;
    cout << "Capital required: "; displayVector(capital); cout << endl;
    cout << "Maximum capital: " << findMaximizedCapital(k5, w, profits, capital) << endl << endl;
    
    // Test 6: Ugly Number II
    cout << "Test 6: Ugly Number II" << endl;
    int n6 = 10;
    cout << n6 << "th ugly number: " << nthUglyNumber(n6) << endl;
    
    return 0;
}
