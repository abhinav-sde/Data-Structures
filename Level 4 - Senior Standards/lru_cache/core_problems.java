
import java.util.*;

public class core_problems {
    /**
     * Problem: LRU Cache in a multi-threaded environment
     * Industry Standard approach: Use ConcurrentHashMap and synchronized DLL or
     * ReadWriteLock
     */
    static class ThreadSafeLRU<K, V> {
        private final int capacity;
        private final Map<K, Node<K, V>> map;
        private final Node<K, V> head, tail;

        static class Node<K, V> {
            K key;
            V value;
            Node<K, V> prev, next;

            Node(K k, V v) {
                this.key = k;
                this.value = v;
            }
        }

        public ThreadSafeLRU(int capacity) {
            this.capacity = capacity;
            this.map = new HashMap<>(); // Usually wrapped in synchronized blocks or using a lock
            head = new Node<>(null, null);
            tail = new Node<>(null, null);
            head.next = tail;
            tail.prev = head;
        }

        public synchronized V get(K key) {
            Node<K, V> node = map.get(key);
            if (node == null)
                return null;
            moveToHead(node);
            return node.value;
        }

        public synchronized void put(K key, V value) {
            Node<K, V> node = map.get(key);
            if (node != null) {
                node.value = value;
                moveToHead(node);
            } else {
                if (map.size() >= capacity) {
                    map.remove(tail.prev.key);
                    removeNode(tail.prev);
                }
                Node<Integer, Integer> newNode = new Node(key, value);
                map.put(key, (Node<K, V>) newNode);
                addNode((Node<K, V>) newNode);
            }
        }

        private void moveToHead(Node<K, V> node) {
            removeNode(node);
            addNode(node);
        }

        private void removeNode(Node<K, V> node) {
            node.prev.next = node.next;
            node.next.prev = node.prev;
        }

        private void addNode(Node<K, V> node) {
            node.next = head.next;
            node.next.prev = node;
            head.next = node;
            node.prev = head;
        }
    }

    public static void main(String[] args) {
        System.out.println("Core implementation focuses on the Thread-Safe LRU pattern.");
    }
}
