import java.util.*;

/**
 * Advanced Merkle Tree Problems in Java
 * Implements Anti-Entropy (Data Repair) simulation.
 * Efficiently finds differences between two data sets using Merkle Tree level
 * comparison.
 */
public class advanced_problems {

    static class MerkleNode {
        String hash;
        MerkleNode left, right;
        int level; // 0 for leaves
        int start, end; // range of data blocks

        MerkleNode(String h, int lvl, int s, int e) {
            hash = h;
            level = lvl;
            start = s;
            end = e;
        }
    }

    public static MerkleNode buildTree(List<String> data) {
        List<MerkleNode> nodes = new ArrayList<>();
        for (int i = 0; i < data.size(); i++) {
            nodes.add(new MerkleNode(basic_operations.sha256(data.get(i)), 0, i, i));
        }
        return buildRecursive(nodes);
    }

    private static MerkleNode buildRecursive(List<MerkleNode> level) {
        if (level.size() == 1)
            return level.get(0);
        List<MerkleNode> parents = new ArrayList<>();
        for (int i = 0; i < level.size(); i += 2) {
            MerkleNode left = level.get(i);
            MerkleNode right = (i + 1 < level.size()) ? level.get(i + 1) : left;
            MerkleNode parent = new MerkleNode(basic_operations.sha256(left.hash + right.hash),
                    left.level + 1, left.start, right.end);
            parent.left = left;
            parent.right = right;
            parents.add(parent);
        }
        return buildRecursive(parents);
    }

    // Identifies differing leaf indices between two trees
    public static void findDifferences(MerkleNode n1, MerkleNode n2, List<Integer> diffs) {
        if (n1.hash.equals(n2.hash))
            return;

        if (n1.level == 0) {
            diffs.add(n1.start);
            return;
        }

        findDifferences(n1.left, n2.left, diffs);
        // Special care for trees of different shapes or odd levels
        if (n1.right != null && n2.right != null) {
            findDifferences(n1.right, n2.right, diffs);
        }
    }

    public static void main(String[] args) {
        List<String> nodeAData = Arrays.asList("D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8");
        List<String> nodeBData = Arrays.asList("D1", "D2_ERR", "D3", "D4", "D5", "D6_ERR", "D7", "D8");

        MerkleNode rootA = buildTree(nodeAData);
        MerkleNode rootB = buildTree(nodeBData);

        List<Integer> diffIndices = new ArrayList<>();
        findDifferences(rootA, rootB, diffIndices);

        System.out.println("Node A: " + nodeAData);
        System.out.println("Node B: " + nodeBData);
        System.out.println("Differing indices found via Merkle Tree: " + diffIndices);
    }
}
