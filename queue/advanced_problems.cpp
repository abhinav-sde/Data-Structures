#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>
using namespace std;

// ========================================
// 1. SLIDING WINDOW MAXIMUM (DEQUE APPROACH)
// ========================================
// Concept: Monotonic deque
// Usage: slidingWindowMax(arr, n, k, result)
// Example: arr = {1,3,-1,-3,5,3,6,7}, k = 3 -> {3,3,5,5,6,7}
void slidingWindowMax(int arr[], int n, int k, vector<int>& result) {
    deque<int> dq;
    
    for (int i = 0; i < n; i++) {
        // Remove elements outside window
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }
        
        // Remove smaller elements from rear
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        // Add to result after first window
        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }
}

// ========================================
// 2. LRU CACHE IMPLEMENTATION
// ========================================
// Concept: Queue + HashMap
#include <unordered_map>

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache;  // {key, value}
    unordered_map<int, list<pair<int, int>>::iterator> map;

public:
    LRUCache(int cap) {
        capacity = cap;
    }
    
    int get(int key) {
        if (map.find(key) == map.end()) {
            return -1;
        }
        
        // Move to front
        cache.splice(cache.begin(), cache, map[key]);
        return map[key]->second;
    }
    
    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            // Update existing
            cache.splice(cache.begin(), cache, map[key]);
            map[key]->second = value;
            return;
        }
        
        if (cache.size() == capacity) {
            // Remove least recently used
            int lruKey = cache.back().first;
            cache.pop_back();
            map.erase(lruKey);
        }
        
        // Add new
        cache.push_front({key, value});
        map[key] = cache.begin();
    }
};

// ========================================
// 3. ROTTEN ORANGES (BFS)
// ========================================
// Concept: Multi-source BFS
// Usage: time = rottenOranges(grid, rows, cols)
// Example: Returns minimum time to rot all oranges or -1
int rottenOranges(int grid[][100], int rows, int cols) {
    queue<pair<int, int>> q;
    int freshCount = 0;
    
    // Find all rotten oranges
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 2) {
                q.push({i, j});
            } else if (grid[i][j] == 1) {
                freshCount++;
            }
        }
    }
    
    if (freshCount == 0) return 0;
    
    int time = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    while (!q.empty()) {
        int size = q.size();
        bool rotted = false;
        
        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();
            
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    q.push({nx, ny});
                    freshCount--;
                    rotted = true;
                }
            }
        }
        
        if (rotted) time++;
    }
    
    return freshCount == 0 ? time : -1;
}

// ========================================
// 4. SHORTEST PATH IN BINARY MAZE
// ========================================
// Concept: BFS
// Usage: distance = shortestPath(maze, rows, cols, start, end)
// Example: Returns shortest path length or -1
int shortestPath(int maze[][100], int rows, int cols, pair<int, int> start, pair<int, int> end) {
    if (maze[start.first][start.second] == 0 || maze[end.first][end.second] == 0) {
        return -1;
    }
    
    queue<pair<pair<int, int>, int>> q;  // {{x, y}, distance}
    bool visited[100][100] = {false};
    
    q.push({start, 0});
    visited[start.first][start.second] = true;
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    while (!q.empty()) {
        auto [pos, dist] = q.front();
        q.pop();
        auto [x, y] = pos;
        
        if (x == end.first && y == end.second) {
            return dist;
        }
        
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && 
                maze[nx][ny] == 1 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({{nx, ny}, dist + 1});
            }
        }
    }
    
    return -1;
}

// ========================================
// 5. LEVEL ORDER TRAVERSAL (BINARY TREE)
// ========================================
// Concept: BFS for trees
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

void levelOrder(TreeNode* root) {
    if (!root) return;
    
    queue<TreeNode*> q;
    q.push(root);
    
    cout << "Level order: ";
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        cout << node->data << " ";
        
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    cout << endl;
}

// ========================================
// 6. ZIGZAG LEVEL ORDER TRAVERSAL
// ========================================
// Concept: BFS with alternating direction
void zigzagLevelOrder(TreeNode* root) {
    if (!root) return;
    
    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;
    
    cout << "Zigzag level order: ";
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->data);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        if (!leftToRight) {
            reverse(level.begin(), level.end());
        }
        
        for (int val : level) {
            cout << val << " ";
        }
        
        leftToRight = !leftToRight;
    }
    cout << endl;
}

// ========================================
// 7. MINIMUM OPERATIONS TO REACH TARGET
// ========================================
// Concept: BFS for shortest path
// Usage: ops = minOperations(start, target)
// Example: Operations: *2, -1. From 3 to 10 takes 4 steps
int minOperations(int start, int target) {
    if (start == target) return 0;
    
    queue<pair<int, int>> q;  // {value, steps}
    bool visited[1000] = {false};
    
    q.push({start, 0});
    visited[start] = true;
    
    while (!q.empty()) {
        auto [val, steps] = q.front();
        q.pop();
        
        // Try operations: *2 and -1
        int next1 = val * 2;
        int next2 = val - 1;
        
        if (next1 == target || next2 == target) {
            return steps + 1;
        }
        
        if (next1 < 1000 && !visited[next1]) {
            visited[next1] = true;
            q.push({next1, steps + 1});
        }
        
        if (next2 > 0 && !visited[next2]) {
            visited[next2] = true;
            q.push({next2, steps + 1});
        }
    }
    
    return -1;
}

// ========================================
// 8. TASK SCHEDULER
// ========================================
// Concept: Priority queue + cooling period
// Usage: time = taskScheduler(tasks, n, cooldown)
// Example: tasks = {A,A,A,B,B,B}, cooldown = 2 returns 8
int taskScheduler(char tasks[], int n, int cooldown) {
    int freq[26] = {0};
    
    for (int i = 0; i < n; i++) {
        freq[tasks[i] - 'A']++;
    }
    
    priority_queue<int> pq;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            pq.push(freq[i]);
        }
    }
    
    int time = 0;
    
    while (!pq.empty()) {
        vector<int> temp;
        int cycle = cooldown + 1;
        
        for (int i = 0; i < cycle; i++) {
            if (!pq.empty()) {
                temp.push_back(pq.top());
                pq.pop();
            }
        }
        
        for (int count : temp) {
            if (--count > 0) {
                pq.push(count);
            }
        }
        
        time += pq.empty() ? temp.size() : cycle;
    }
    
    return time;
}

// ========================================
// 9. FIND K CLOSEST ELEMENTS
// ========================================
// Concept: Priority queue (max heap)
// Usage: findKClosest(arr, n, k, x, result)
// Example: arr = {1,2,3,4,5}, k = 4, x = 3 -> {1,2,3,4}
void findKClosest(int arr[], int n, int k, int x, vector<int>& result) {
    priority_queue<pair<int, int>> pq;  // {difference, value}
    
    for (int i = 0; i < n; i++) {
        pq.push({abs(arr[i] - x), arr[i]});
        
        if (pq.size() > k) {
            pq.pop();
        }
    }
    
    while (!pq.empty()) {
        result.push_back(pq.top().second);
        pq.pop();
    }
    
    sort(result.begin(), result.end());
}

// ========================================
// 10. CONNECT ROPES WITH MINIMUM COST
// ========================================
// Concept: Min heap (priority queue)
// Usage: cost = connectRopes(ropes, n)
// Example: ropes = {4,3,2,6} returns 29
int connectRopes(int ropes[], int n) {
    priority_queue<int, vector<int>, greater<int>> pq;
    
    for (int i = 0; i < n; i++) {
        pq.push(ropes[i]);
    }
    
    int totalCost = 0;
    
    while (pq.size() > 1) {
        int first = pq.top(); pq.pop();
        int second = pq.top(); pq.pop();
        
        int cost = first + second;
        totalCost += cost;
        pq.push(cost);
    }
    
    return totalCost;
}

// ========================================
// 11. KTH LARGEST ELEMENT IN STREAM
// ========================================
// Concept: Min heap of size k
class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> pq;
    int k;

public:
    KthLargest(int kVal) {
        k = kVal;
    }
    
    int add(int val) {
        pq.push(val);
        
        if (pq.size() > k) {
            pq.pop();
        }
        
        return pq.top();
    }
};

// ========================================
// 12. MEDIAN OF INTEGER STREAM
// ========================================
// Concept: Two heaps (max and min)
class MedianFinder {
private:
    priority_queue<int> maxHeap;  // Lower half
    priority_queue<int, vector<int>, greater<int>> minHeap;  // Upper half

public:
    void addNum(int num) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        
        // Balance heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
        return maxHeap.top();
    }
};

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    cout << "=== Queue Advanced Problems ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // 1. Sliding Window Maximum
    // int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
    // vector<int> result;
    // slidingWindowMax(arr, 8, 3, result);
    // cout << "Sliding window max: ";
    // for (int val : result) cout << val << " ";
    // cout << endl;
    
    // 2. LRU Cache
    // LRUCache cache(2);
    // cache.put(1, 1);
    // cache.put(2, 2);
    // cout << "Get 1: " << cache.get(1) << endl;
    // cache.put(3, 3);
    // cout << "Get 2: " << cache.get(2) << endl;
    
    // 3. Rotten Oranges
    // int grid[100][100] = {{2,1,1},{1,1,0},{0,1,1}};
    // int time = rottenOranges(grid, 3, 3);
    // cout << "Time to rot all: " << time << endl;
    
    // 4. Shortest Path in Maze
    // int maze[100][100] = {{1,1,1,1},{1,0,0,1},{1,1,1,1}};
    // int dist = shortestPath(maze, 3, 4, {0,0}, {2,3});
    // cout << "Shortest path: " << dist << endl;
    
    // 5. Level Order Traversal
    // TreeNode* root = new TreeNode(1);
    // root->left = new TreeNode(2);
    // root->right = new TreeNode(3);
    // root->left->left = new TreeNode(4);
    // root->left->right = new TreeNode(5);
    // levelOrder(root);
    
    // 6. Zigzag Level Order
    // zigzagLevelOrder(root);
    
    // 7. Minimum Operations
    // int ops = minOperations(3, 10);
    // cout << "Minimum operations: " << ops << endl;
    
    // 8. Task Scheduler
    // char tasks[] = {'A','A','A','B','B','B'};
    // int time = taskScheduler(tasks, 6, 2);
    // cout << "Total time: " << time << endl;
    
    // 9. K Closest Elements
    // int arr[] = {1, 2, 3, 4, 5};
    // vector<int> result;
    // findKClosest(arr, 5, 4, 3, result);
    // cout << "K closest: ";
    // for (int val : result) cout << val << " ";
    // cout << endl;
    
    // 10. Connect Ropes
    // int ropes[] = {4, 3, 2, 6};
    // int cost = connectRopes(ropes, 4);
    // cout << "Minimum cost: " << cost << endl;
    
    // 11. Kth Largest in Stream
    // KthLargest kthLargest(3);
    // cout << kthLargest.add(3) << endl;
    // cout << kthLargest.add(5) << endl;
    // cout << kthLargest.add(10) << endl;
    // cout << kthLargest.add(9) << endl;
    
    // 12. Median Finder
    // MedianFinder mf;
    // mf.addNum(1);
    // mf.addNum(2);
    // cout << "Median: " << mf.findMedian() << endl;
    // mf.addNum(3);
    // cout << "Median: " << mf.findMedian() << endl;
    
    return 0;
}
