import java.util.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * Basic Merkle Tree Operations in Java
 * Implements building a Merkle tree from data blocks and root hash generation.
 */
public class basic_operations {

    static class Node {
        String hash;
        Node left, right;

        Node(String hash) {
            this.hash = hash;
        }
    }

    private Node root;
    private List<String> dataBlocks;

    public basic_operations(List<String> dataBlocks) {
        this.dataBlocks = new ArrayList<>(dataBlocks);
        this.root = buildTree();
    }

    public String getRootHash() {
        return root != null ? root.hash : null;
    }

    private Node buildTree() {
        List<Node> nodes = new ArrayList<>();
        for (String data : dataBlocks) {
            nodes.add(new Node(sha256(data)));
        }

        while (nodes.size() > 1) {
            List<Node> parentNodes = new ArrayList<>();
            for (int i = 0; i < nodes.size(); i += 2) {
                Node left = nodes.get(i);
                Node right = (i + 1 < nodes.size()) ? nodes.get(i + 1) : left; // Duplicate last if odd

                Node parent = new Node(sha256(left.hash + right.hash));
                parent.left = left;
                parent.right = right;
                parentNodes.add(parent);
            }
            nodes = parentNodes;
        }
        return nodes.isEmpty() ? null : nodes.get(0);
    }

    public static String sha256(String input) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hash = digest.digest(input.getBytes());
            StringBuilder hexString = new StringBuilder();
            for (byte b : hash) {
                String hex = Integer.toHexString(0xff & b);
                if (hex.length() == 1)
                    hexString.append('0');
                hexString.append(hex);
            }
            return hexString.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        List<String> data = Arrays.asList("Block_1", "Block_2", "Block_3", "Block_4");
        basic_operations mt = new basic_operations(data);

        System.out.println("Data: " + data);
        System.out.println("Merkle Root Hash: " + mt.getRootHash());

        // Test integrity
        List<String> tamperedData = Arrays.asList("Block_1_TAMPERED", "Block_2", "Block_3", "Block_4");
        basic_operations mtTampered = new basic_operations(tamperedData);
        System.out.println("Tampered Root Hash: " + mtTampered.getRootHash());

        System.out.println("Integrity Match: " + mt.getRootHash().equals(mtTampered.getRootHash()));
    }
}
