/**
 * Queue Advanced Problems in Java
 * Contains complex Queue algorithms
 */

import java.util.*;

public class advanced_problems {
    
    // ========================================
    // 1. SLIDING WINDOW MAXIMUM (DEQUE APPROACH)
    // ========================================
    static void slidingWindowMax(int[] arr, int n, int k, List<Integer> result) {
        Deque<Integer> dq = new ArrayDeque<>();
        
        for (int i = 0; i < n; i++) {
            // Remove elements outside window
            if (!dq.isEmpty() && dq.peekFirst() == i - k) {
                dq.pollFirst();
            }
            
            // Remove smaller elements from rear
            while (!dq.isEmpty() && arr[dq.peekLast()] <= arr[i]) {
                dq.pollLast();
            }
            
            dq.offerLast(i);
            
            // Add to result after first window
            if (i >= k - 1) {
                result.add(arr[dq.peekFirst()]);
            }
        }
    }
    
    // ========================================
    // 2. LRU CACHE IMPLEMENTATION
    // ========================================
    static class LRUCache {
        private int capacity;
        // LinkedHashMap with accessOrder = true works as LRU
        private LinkedHashMap<Integer, Integer> cache;
        
        public LRUCache(int cap) {
            this.capacity = cap;
            // The third argument true enables access-order insertion for LRU
            this.cache = new LinkedHashMap<Integer, Integer>(cap, 0.75f, true) {
                @Override
                protected boolean removeEldestEntry(Map.Entry<Integer, Integer> eldest) {
                    return size() > capacity;
                }
            };
        }
        
        public int get(int key) {
            return cache.getOrDefault(key, -1);
        }
        
        public void put(int key, int value) {
            cache.put(key, value);
        }
    }
    
    // Alternative implementation mimicking C++ directly (HashMap + Doubly Linked List) isn't strictly needed 
    // unless educational purpose demands showing the internals. 
    // Given Java's LinkedHashMap makes it trivial, we can stick to that or implement manually if preferred. 
    // Let's implement manually to match the educational value of C++ code which likely shows internal structure.
    
    static class LRUCacheManual {
        static class Node {
            int key, value;
            Node prev, next;
            Node(int k, int v) { key = k; value = v; }
        }
        
        private int capacity;
        private HashMap<Integer, Node> map;
        private Node head, tail;
        
        public LRUCacheManual(int cap) {
            capacity = cap;
            map = new HashMap<>();
            head = new Node(0, 0);
            tail = new Node(0, 0);
            head.next = tail;
            tail.prev = head;
        }
        
        private void remove(Node node) {
            node.prev.next = node.next;
            node.next.prev = node.prev;
        }
        
        private void addToFront(Node node) {
            node.next = head.next;
            node.prev = head;
            head.next.prev = node;
            head.next = node;
        }
        
        public int get(int key) {
            if (!map.containsKey(key)) return -1;
            Node node = map.get(key);
            remove(node);
            addToFront(node);
            return node.value;
        }
        
        public void put(int key, int value) {
            if (map.containsKey(key)) {
                remove(map.get(key));
            }
            Node newNode = new Node(key, value);
            map.put(key, newNode);
            addToFront(newNode);
            
            if (map.size() > capacity) {
                Node lru = tail.prev;
                remove(lru);
                map.remove(lru.key);
            }
        }
    }
    
    // ========================================
    // 3. ROTTEN ORANGES (BFS)
    // ========================================
    static int rottenOranges(int[][] grid, int rows, int cols) {
        Queue<int[]> q = new LinkedList<>();
        int freshCount = 0;
        
        // Find all rotten oranges
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 2) {
                    q.add(new int[]{i, j});
                } else if (grid[i][j] == 1) {
                    freshCount++;
                }
            }
        }
        
        if (freshCount == 0) return 0;
        
        int time = 0;
        int[] dx = {-1, 1, 0, 0};
        int[] dy = {0, 0, -1, 1};
        
        while (!q.isEmpty()) {
            int size = q.size();
            boolean rotted = false;
            
            for (int i = 0; i < size; i++) {
                int[] cell = q.poll();
                int x = cell[0];
                int y = cell[1];
                
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    
                    if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 1) {
                        grid[nx][ny] = 2;
                        q.add(new int[]{nx, ny});
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
    // Using int[] for queue elements: {x, y, distance}
    static int shortestPath(int[][] maze, int rows, int cols, int[] start, int[] end) {
        if (maze[start[0]][start[1]] == 0 || maze[end[0]][end[1]] == 0) {
            return -1;
        }
        
        Queue<int[]> q = new LinkedList<>();
        boolean[][] visited = new boolean[rows][cols];
        
        q.add(new int[]{start[0], start[1], 0});
        visited[start[0]][start[1]] = true;
        
        int[] dx = {-1, 1, 0, 0};
        int[] dy = {0, 0, -1, 1};
        
        while (!q.isEmpty()) {
            int[] current = q.poll();
            int x = current[0];
            int y = current[1];
            int dist = current[2];
            
            if (x == end[0] && y == end[1]) {
                return dist;
            }
            
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && 
                    maze[nx][ny] == 1 && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    q.add(new int[]{nx, ny, dist + 1});
                }
            }
        }
        
        return -1;
    }
    
    // ========================================
    // 5. LEVEL ORDER TRAVERSAL (BINARY TREE)
    // ========================================
    static class TreeNode {
        int data;
        TreeNode left, right;
        TreeNode(int val) { data = val; left = null; right = null; }
    }
    
    static void levelOrder(TreeNode root) {
        if (root == null) return;
        
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        
        System.out.print("Level order: ");
        while (!q.isEmpty()) {
            TreeNode node = q.poll();
            System.out.print(node.data + " ");
            
            if (node.left != null) q.add(node.left);
            if (node.right != null) q.add(node.right);
        }
        System.out.println();
    }
    
    // ========================================
    // 6. ZIGZAG LEVEL ORDER TRAVERSAL
    // ========================================
    static void zigzagLevelOrder(TreeNode root) {
        if (root == null) return;
        
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);
        boolean leftToRight = true;
        
        System.out.print("Zigzag level order: ");
        while (!q.isEmpty()) {
            int size = q.size();
            List<Integer> level = new ArrayList<>();
            
            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                level.add(node.data);
                
                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
            
            if (!leftToRight) {
                Collections.reverse(level);
            }
            
            for (int val : level) {
                System.out.print(val + " ");
            }
            
            leftToRight = !leftToRight;
        }
        System.out.println();
    }
    
    // ========================================
    // 7. MINIMUM OPERATIONS TO REACH TARGET
    // ========================================
    static int minOperations(int start, int target) {
        if (start == target) return 0;
        
        Queue<int[]> q = new LinkedList<>(); // {value, steps}
        boolean[] visited = new boolean[2000]; // Assuming safe upper bound based on constraints
        
        q.add(new int[]{start, 0});
        if (start < visited.length) visited[start] = true;
        
        while (!q.isEmpty()) {
            int[] curr = q.poll();
            int val = curr[0];
            int steps = curr[1];
            
            int next1 = val * 2;
            int next2 = val - 1;
            
            if (next1 == target || next2 == target) return steps + 1;
            
            if (next1 < visited.length && !visited[next1]) {
                visited[next1] = true;
                q.add(new int[]{next1, steps + 1});
            }
            
            if (next2 > 0 && next2 < visited.length && !visited[next2]) {
                visited[next2] = true;
                q.add(new int[]{next2, steps + 1});
            }
        }
        
        return -1;
    }
    
    // ========================================
    // 8. TASK SCHEDULER
    // ========================================
    static int taskScheduler(char[] tasks, int n, int cooldown) {
        int[] freq = new int[26];
        for (char task : tasks) freq[task - 'A']++;
        
        PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());
        for (int f : freq) if (f > 0) pq.add(f);
        
        int time = 0;
        
        while (!pq.isEmpty()) {
            List<Integer> temp = new ArrayList<>();
            int cycle = cooldown + 1;
            
            for (int i = 0; i < cycle; i++) {
                if (!pq.isEmpty()) {
                    temp.add(pq.poll());
                }
            }
            
            for (int count : temp) {
                if (--count > 0) pq.add(count);
            }
            
            time += pq.isEmpty() ? temp.size() : cycle;
        }
        
        return time;
    }
    
    // ========================================
    // 9. FIND K CLOSEST ELEMENTS
    // ========================================
    static void findKClosest(int[] arr, int n, int k, int x, List<Integer> result) {
        // Max heap to store pairs of {diff, value}
        // Custom comparator: compares differences, then values
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> {
            if (b[0] != a[0]) return b[0] - a[0]; 
            return b[1] - a[1];
        });
        
        for (int val : arr) {
            pq.add(new int[]{Math.abs(val - x), val});
            if (pq.size() > k) pq.poll();
        }
        
        while (!pq.isEmpty()) {
            result.add(pq.poll()[1]);
        }
        Collections.sort(result);
    }
    
    // ========================================
    // 10. CONNECT ROPES WITH MINIMUM COST
    // ========================================
    static int connectRopes(int[] ropes, int n) {
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int rope : ropes) pq.add(rope);
        
        int totalCost = 0;
        
        while (pq.size() > 1) {
            int first = pq.poll();
            int second = pq.poll();
            
            int cost = first + second;
            totalCost += cost;
            pq.add(cost);
        }
        
        return totalCost;
    }
    
    // ========================================
    // 11. KTH LARGEST ELEMENT IN STREAM
    // ========================================
    static class KthLargest {
        private PriorityQueue<Integer> pq;
        private int k;
        
        public KthLargest(int k) {
            this.k = k;
            this.pq = new PriorityQueue<>();
        }
        
        public int add(int val) {
            pq.add(val);
            if (pq.size() > k) pq.poll();
            return pq.peek();
        }
    }
    
    // ========================================
    // 12. MEDIAN OF INTEGER STREAM
    // ========================================
    static class MedianFinder {
        private PriorityQueue<Integer> maxHeap; // Lower half
        private PriorityQueue<Integer> minHeap; // Upper half
        
        public MedianFinder() {
            maxHeap = new PriorityQueue<>(Collections.reverseOrder());
            minHeap = new PriorityQueue<>();
        }
        
        public void addNum(int num) {
            if (maxHeap.isEmpty() || num <= maxHeap.peek()) {
                maxHeap.add(num);
            } else {
                minHeap.add(num);
            }
            
            // Balance heaps
            if (maxHeap.size() > minHeap.size() + 1) {
                minHeap.add(maxHeap.poll());
            } else if (minHeap.size() > maxHeap.size()) {
                maxHeap.add(minHeap.poll());
            }
        }
        
        public double findMedian() {
            if (maxHeap.size() == minHeap.size()) {
                return (maxHeap.peek() + minHeap.peek()) / 2.0;
            }
            return maxHeap.peek();
        }
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Queue Advanced Problems ===");
        
        // Example usage - uncomment to use
        
        // 1. Sliding Window Maximum
        // int[] arr = {1, 3, -1, -3, 5, 3, 6, 7};
        // List<Integer> result = new ArrayList<>();
        // slidingWindowMax(arr, 8, 3, result);
        // System.out.println("Sliding window max: " + result);
        
        // 2. LRU Cache
        // LRUCacheManual cache = new LRUCacheManual(2);
        // cache.put(1, 1);
        // cache.put(2, 2);
        // System.out.println("Get 1: " + cache.get(1));
        // cache.put(3, 3);
        // System.out.println("Get 2: " + cache.get(2));
        
        // 5. Level Order Traversal
        // TreeNode root = new TreeNode(1);
        // root.left = new TreeNode(2);
        // root.right = new TreeNode(3);
        // root.left.left = new TreeNode(4);
        // root.left.right = new TreeNode(5);
        // levelOrder(root);
        
        // 10. Connect Ropes
        // int[] ropes = {4, 3, 2, 6};
        // System.out.println("Minimum cost: " + connectRopes(ropes, 4));
        
        // 12. Median Finder
        // MedianFinder mf = new MedianFinder();
        // mf.addNum(1);
        // mf.addNum(2);
        // System.out.println("Median: " + mf.findMedian());
        // mf.addNum(3);
        // System.out.println("Median: " + mf.findMedian());
    }
}
