/**
 * Advanced Linked List Problems in Java
 * Contains complex linked list algorithms
 */

import java.util.*;

public class advanced_problems {
    
    // ========================================
    // NODE STRUCTURES
    // ========================================
    static class Node {
        int data;
        Node next;
        Node(int val) { data = val; next = null; }
    }
    
    static class RandomNode {
        int data;
        RandomNode next;
        RandomNode random;
        RandomNode(int val) { data = val; next = null; random = null; }
    }
    
    static class DoublyNode {
        int data;
        DoublyNode prev, next;
        DoublyNode child; // Added for flattening problem
        DoublyNode(int val) { data = val; prev = null; next = null; child = null; }
    }
    
    // ========================================
    // UTILITY FUNCTION
    // ========================================
    static void display(Node head) {
        if (head == null) {
            System.out.println("List is empty.");
            return;
        }
        System.out.print("List: ");
        Node temp = head;
        while (temp != null) {
            System.out.print(temp.data + " -> ");
            temp = temp.next;
        }
        System.out.println("NULL");
    }
    
    // ========================================
    // 1. CLONE LINKED LIST WITH RANDOM POINTER
    // ========================================
    static RandomNode cloneRandomList(RandomNode head) {
        if (head == null) return null;
        
        Map<RandomNode, RandomNode> map = new HashMap<>();
        
        // First pass: create all nodes
        RandomNode current = head;
        while (current != null) {
            map.put(current, new RandomNode(current.data));
            current = current.next;
        }
        
        // Second pass: assign next and random pointers
        current = head;
        while (current != null) {
            map.get(current).next = map.get(current.next);
            map.get(current).random = map.get(current.random);
            current = current.next;
        }
        return map.get(head);
    }
    
    // ========================================
    // 2. MERGE TWO SORTED LISTS (Helper for Merge Sort)
    // ========================================
    static Node mergeTwoLists(Node a, Node b) {
        if (a == null) return b;
        if (b == null) return a;
        
        Node result;
        if (a.data < b.data) {
            result = a;
            result.next = mergeTwoLists(a.next, b);
        } else {
            result = b;
            result.next = mergeTwoLists(a, b.next);
        }
        return result;
    }
    
    // ========================================
    // 3. SORT LINKED LIST (MERGE SORT)
    // ========================================
    static Node findMiddle(Node head) {
        Node slow = head;
        Node fast = head.next;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }
    
    static Node mergeSort(Node head) {
        if (head == null || head.next == null) return head;
        
        Node middle = findMiddle(head);
        Node nextOfMiddle = middle.next;
        middle.next = null;
        
        Node left = mergeSort(head);
        Node right = mergeSort(nextOfMiddle);
        
        return mergeTwoLists(left, right);
    }
    
    // ========================================
    // 4. FIND LOOP START NODE
    // ========================================
    static Node findLoopStart(Node head) {
        if (head == null) return null;
        
        Node slow = head;
        Node fast = head;
        
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            
            if (slow == fast) {
                slow = head;
                while (slow != fast) {
                    slow = slow.next;
                    fast = fast.next;
                }
                return slow;
            }
        }
        return null;
    }
    
    // ========================================
    // 5. REMOVE LOOP FROM LINKED LIST
    // ========================================
    static void removeLoop(Node head) {
        if (head == null) return;
        
        Node slow = head;
        Node fast = head;
        
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            
            if (slow == fast) {
                slow = head;
                if (slow == fast) { // Loop at head
                    while (fast.next != slow) fast = fast.next;
                } else {
                    while (slow.next != fast.next) {
                        slow = slow.next;
                        fast = fast.next;
                    }
                }
                fast.next = null;
                System.out.println("Loop removed.");
                return;
            }
        }
        System.out.println("No loop found.");
    }
    
    // ========================================
    // 6. PARTITION LIST AROUND VALUE X
    // ========================================
    static Node partition(Node head, int x) {
        Node beforeHead = new Node(0);
        Node before = beforeHead;
        Node afterHead = new Node(0);
        Node after = afterHead;
        
        while (head != null) {
            if (head.data < x) {
                before.next = head;
                before = before.next;
            } else {
                after.next = head;
                after = after.next;
            }
            head = head.next;
        }
        
        after.next = null;
        before.next = afterHead.next;
        return beforeHead.next;
    }
    
    // ========================================
    // 7. REORDER LIST
    // ========================================
    static void reorderList(Node head) {
        if (head == null || head.next == null) return;
        
        Node slow = head, fast = head;
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        
        Node prev = null, current = slow.next;
        slow.next = null;
        
        while (current != null) {
            Node next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }
        
        Node first = head, second = prev;
        while (second != null) {
            Node temp1 = first.next;
            Node temp2 = second.next;
            
            first.next = second;
            second.next = temp1;
            
            first = temp1;
            second = temp2;
        }
        System.out.println("List reordered.");
    }
    
    // ========================================
    // 8. SWAP NODES IN PAIRS
    // ========================================
    static Node swapPairs(Node head) {
        if (head == null || head.next == null) return head;
        
        Node dummy = new Node(0);
        dummy.next = head;
        Node prev = dummy;
        
        while (prev.next != null && prev.next.next != null) {
            Node first = prev.next;
            Node second = prev.next.next;
            
            first.next = second.next;
            second.next = first;
            prev.next = second;
            
            prev = first;
        }
        return dummy.next;
    }
    
    // ========================================
    // 9. DELETE N NODES AFTER M NODES
    // ========================================
    static void deleteNAfterM(Node head, int m, int n) {
        Node current = head;
        while (current != null) {
            for (int i = 1; i < m && current != null; i++) current = current.next;
            if (current == null) return;
            
            Node temp = current.next;
            for (int i = 0; i < n && temp != null; i++) temp = temp.next;
            
            current.next = temp;
            current = temp;
        }
        System.out.println("Deleted " + n + " nodes after every " + m + " nodes.");
    }
    
    // ========================================
    // 10. MERGE K SORTED LISTS
    // ========================================
    static Node mergeKLists(List<Node> lists) {
        if (lists == null || lists.isEmpty()) return null;
        
        while (lists.size() > 1) {
            List<Node> mergedLists = new ArrayList<>();
            for (int i = 0; i < lists.size(); i += 2) {
                Node l1 = lists.get(i);
                Node l2 = (i + 1 < lists.size()) ? lists.get(i + 1) : null;
                mergedLists.add(mergeTwoLists(l1, l2));
            }
            lists = mergedLists;
        }
        return lists.get(0);
    }
    
    // ========================================
    // 11. REVERSE ALTERNATE K NODES
    // ========================================
    static Node reverseAlternateK(Node head, int k) {
        if (head == null) return null;
        
        Node current = head;
        Node next = null;
        Node prev = null;
        int count = 0;
        
        while (current != null && count < k) {
            next = current.next;
            current.next = prev;
            prev = current;
            current = next;
            count++;
        }
        
        if (head != null) head.next = current;
        
        count = 0;
        while (count < k - 1 && current != null) {
            current = current.next;
            count++;
        }
        
        if (current != null) current.next = reverseAlternateK(current.next, k);
        
        return prev;
    }
    
    // ========================================
    // 12. FLATTEN DOUBLY LINKED LIST
    // ========================================
    static DoublyNode flattenDoublyList(DoublyNode head) {
        if (head == null) return head;
        
        DoublyNode current = head;
        while (current != null) {
            if (current.child != null) {
                DoublyNode next = current.next;
                DoublyNode child = current.child;
                
                current.next = child;
                child.prev = current;
                current.child = null; // Cleanup
                
                DoublyNode tail = child;
                while (tail.next != null) tail = tail.next;
                
                tail.next = next;
                if (next != null) next.prev = tail;
            }
            current = current.next;
        }
        return head;
    }
    
    // ========================================
    // 13. LRU CACHE
    // ========================================
    static class LRUCache {
        private int capacity;
        private Map<Integer, DoublyNode> cache;
        private DoublyNode head, tail;
        
        static class DoublyNode {
            int key, value; // Need key to remove from map
            DoublyNode prev, next;
            DoublyNode(int k, int v) { key = k; value = v; }
        }
        
        public LRUCache(int cap) {
            capacity = cap;
            cache = new HashMap<>();
            head = new DoublyNode(0, 0);
            tail = new DoublyNode(0, 0);
            head.next = tail;
            tail.prev = head;
        }
        
        private void addToFront(DoublyNode node) {
            node.next = head.next;
            node.prev = head;
            head.next.prev = node;
            head.next = node;
        }
        
        private void removeNode(DoublyNode node) {
            node.prev.next = node.next;
            node.next.prev = node.prev;
        }
        
        public int get(int key) {
            if (!cache.containsKey(key)) return -1;
            DoublyNode node = cache.get(key);
            removeNode(node);
            addToFront(node);
            return node.value;
        }
        
        public void put(int key, int value) {
            if (cache.containsKey(key)) {
                removeNode(cache.get(key));
            }
            DoublyNode newNode = new DoublyNode(key, value);
            cache.put(key, newNode);
            addToFront(newNode);
            
            if (cache.size() > capacity) {
                DoublyNode lru = tail.prev;
                removeNode(lru);
                cache.remove(lru.key);
            }
        }
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Linked List Advanced Problems ===");
        
        // Example usage - uncomment to test
        
        // LRUCache cache = new LRUCache(2);
        // cache.put(1, 1);
        // cache.put(2, 2);
        // System.out.println("Get 1: " + cache.get(1));
        // cache.put(3, 3);
        // System.out.println("Get 2: " + cache.get(2));
    }
}
