import java.util.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * Basic Consistent Hashing Implementation in Java
 * Uses TreeMap to simulate the Hash Ring and MD5 for hashing.
 */
public class basic_operations {

    private final SortedMap<Long, String> circle = new TreeMap<>();
    private final int numberOfReplicas; // Number of virtual nodes per physical node

    public basic_operations(int numberOfReplicas) {
        this.numberOfReplicas = numberOfReplicas;
    }

    public void addNode(String node) {
        for (int i = 0; i < numberOfReplicas; i++) {
            circle.put(hash(node + ":" + i), node);
        }
    }

    public void removeNode(String node) {
        for (int i = 0; i < numberOfReplicas; i++) {
            circle.remove(hash(node + ":" + i));
        }
    }

    public String getNode(String key) {
        if (circle.isEmpty())
            return null;
        long h = hash(key);
        if (!circle.containsKey(h)) {
            SortedMap<Long, String> tailMap = circle.tailMap(h);
            h = tailMap.isEmpty() ? circle.firstKey() : tailMap.firstKey();
        }
        return circle.get(h);
    }

    /**
     * Simple hash function using MD5 and returning a long to fit on the ring.
     */
    private long hash(String key) {
        try {
            MessageDigest md = MessageDigest.getInstance("MD5");
            byte[] bytes = md.digest(key.getBytes());
            // Use first 8 bytes for a 64-bit hash
            long h = 0;
            for (int i = 0; i < 8; i++) {
                h <<= 8;
                h |= (bytes[i] & 0xFF);
            }
            return h;
        } catch (NoSuchAlgorithmException e) {
            return key.hashCode(); // Fallback
        }
    }

    public static void main(String[] args) {
        basic_operations ch = new basic_operations(100); // 100 virtual nodes

        ch.addNode("Server_A");
        ch.addNode("Server_B");
        ch.addNode("Server_C");

        System.out.println("Node for 'my_photo.jpg': " + ch.getNode("my_photo.jpg"));
        System.out.println("Node for 'user_1234.json': " + ch.getNode("user_1234.json"));
        System.out.println("Node for 'session_abc': " + ch.getNode("session_abc"));

        System.out.println("\nRemoving Server_B...");
        ch.removeNode("Server_B");
        System.out.println("Node for 'my_photo.jpg' now: " + ch.getNode("my_photo.jpg"));
    }
}
