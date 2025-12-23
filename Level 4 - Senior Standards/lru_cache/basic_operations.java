
import java.util.*;

/**
 * Basic LRU Cache Implementation
 * Uses HashMap for O(1) access and Doubly Linked List for O(1) eviction
 */
public class basic_operations {

    static class LRUCache {
        class Node {
            int key, value;
            Node prev, next;

            Node(int k, int v) {
                key = k;
                value = v;
            }
        }

        private Map<Integer, Node> map;
        private Node head, tail;
        private int capacity;

        public LRUCache(int capacity) {
            this.capacity = capacity;
            this.map = new HashMap<>();
            head = new Node(0, 0);
            tail = new Node(0, 0);
            head.next = tail;
            tail.prev = head;
        }

        public int get(int key) {
            if (!map.containsKey(key))
                return -1;
            Node node = map.get(key);
            remove(node);
            insertAtHead(node);
            return node.value;
        }

        public void put(int key, int value) {
            if (map.containsKey(key)) {
                remove(map.get(key));
            }
            if (map.size() == capacity) {
                remove(tail.prev);
            }
            insertAtHead(new Node(key, value));
        }

        private void remove(Node node) {
            map.remove(node.key);
            node.prev.next = node.next;
            node.next.prev = node.prev;
        }

        private void insertAtHead(Node node) {
            map.put(node.key, node);
            node.next = head.next;
            node.next.prev = node;
            head.next = node;
            node.prev = head;
        }

        public void display() {
            Node curr = head.next;
            System.out.print("Cache (Mru -> Lru): ");
            while (curr != tail) {
                System.out.print("[" + curr.key + ":" + curr.value + "] ");
                curr = curr.next;
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        LRUCache cache = new LRUCache(2);
        cache.put(1, 1);
        cache.put(2, 2);
        cache.display();
        System.out.println("Get 1: " + cache.get(1));
        cache.put(3, 3); // evicts 2
        cache.display();
    }
}
