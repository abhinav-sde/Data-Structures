
import java.util.*;

/**
 * Basic Roaring Bitmap Operations in Java
 * Implements Chunk management and Array-to-Bitmap container switching.
 */
public class basic_operations {

    private static final int MAX_ARRAY_SIZE = 4096;
    private final Map<Integer, Container> chunks = new TreeMap<>();

    interface Container {
        boolean add(char value);

        boolean contains(char value);

        int size();
    }

    // Stores sorted values in a char array (16-bit)
    static class ArrayContainer implements Container {
        List<Character> content = new ArrayList<>();

        public boolean add(char value) {
            int pos = Collections.binarySearch(content, value);
            if (pos < 0) {
                content.add(-pos - 1, value);
                return true;
            }
            return false;
        }

        public boolean contains(char value) {
            return Collections.binarySearch(content, value) >= 0;
        }

        public int size() {
            return content.size();
        }
    }

    // Stores values in a bitset (65,536 bits)
    static class BitmapContainer implements Container {
        BitSet bitSet = new BitSet(65536);
        int cardinality = 0;

        public boolean add(char value) {
            if (!bitSet.get(value)) {
                bitSet.set(value);
                cardinality++;
                return true;
            }
            return false;
        }

        public boolean contains(char value) {
            return bitSet.get(value);
        }

        public int size() {
            return cardinality;
        }
    }

    public void add(int x) {
        int key = x >>> 16;
        char value = (char) (x & 0xFFFF);

        Container container = chunks.get(key);
        if (container == null) {
            container = new ArrayContainer();
            chunks.put(key, container);
        }

        container.add(value);

        // Convert Array to Bitmap if it grows too large
        if (container instanceof ArrayContainer && container.size() > MAX_ARRAY_SIZE) {
            BitmapContainer bc = new BitmapContainer();
            for (char c : ((ArrayContainer) container).content)
                bc.add(c);
            chunks.put(key, bc);
        }
    }

    public boolean contains(int x) {
        int key = x >>> 16;
        char value = (char) (x & 0xFFFF);
        Container container = chunks.get(key);
        return container != null && container.contains(value);
    }

    public static void main(String[] args) {
        basic_operations rb = new basic_operations();

        System.out.println("Adding sparse data: 10, 100000, 200000");
        rb.add(10);
        rb.add(100000);
        rb.add(200000);

        System.out.println("Contains 100000: " + rb.contains(100000));
        System.out.println("Contains 50: " + rb.contains(50));

        System.out.println("\nAdding 5000 values to a single chunk (Triggers Bitmap conversion)...");
        for (int i = 0; i < 5000; i++)
            rb.add(i);

        System.out.println("Contains 2500: " + rb.contains(2500));
        System.out.println("Chunk count: " + rb.chunks.size());
    }
}
