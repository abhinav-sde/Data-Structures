import java.util.*;

/**
 * Core Merkle Tree Problems in Java
 * Focuses on Merkle Proof (Audit Path) generation and verification.
 */
public class core_problems {

    static class Node {
        String hash;
        Node left, right;

        Node(String h) {
            this.hash = h;
        }
    }

    private List<Node> leaves;
    private String rootHash;

    public core_problems(List<String> data) {
        this.leaves = new ArrayList<>();
        for (String d : data)
            leaves.add(new Node(basic_operations.sha256(d)));
        this.rootHash = build(leaves).get(0).hash;
    }

    private List<Node> build(List<Node> currentLevel) {
        if (currentLevel.size() <= 1)
            return currentLevel;
        List<Node> parents = new ArrayList<>();
        for (int i = 0; i < currentLevel.size(); i += 2) {
            Node left = currentLevel.get(i);
            Node right = (i + 1 < currentLevel.size()) ? currentLevel.get(i + 1) : left;
            Node parent = new Node(basic_operations.sha256(left.hash + right.hash));
            parent.left = left;
            parent.right = right;
            parents.add(parent);
        }
        return build(parents);
    }

    // A proof consists of (sibling_hash, is_left_sibling) pairs
    static class ProofStep {
        String hash;
        boolean isLeft;

        ProofStep(String h, boolean l) {
            hash = h;
            isLeft = l;
        }
    }

    public List<ProofStep> getProof(int index) {
        List<ProofStep> proof = new ArrayList<>();
        int currIdx = index;
        List<Node> level = leaves;

        while (level.size() > 1) {
            int siblingIdx = (currIdx % 2 == 0) ? currIdx + 1 : currIdx - 1;
            if (siblingIdx < level.size()) {
                proof.add(new ProofStep(level.get(siblingIdx).hash, currIdx % 2 != 0));
            } else {
                // Odd length, sibling is self
                proof.add(new ProofStep(level.get(currIdx).hash, currIdx % 2 != 0));
            }
            currIdx /= 2;
            List<Node> nextLevel = new ArrayList<>();
            for (int i = 0; i < level.size(); i += 2) {
                Node left = level.get(i);
                Node right = (i + 1 < level.size()) ? level.get(i + 1) : left;
                nextLevel.add(new Node(basic_operations.sha256(left.hash + right.hash)));
            }
            level = nextLevel;
        }
        return proof;
    }

    public static boolean verify(String block, List<ProofStep> proof, String rootHash) {
        String currentHash = basic_operations.sha256(block);
        for (ProofStep step : proof) {
            if (step.isLeft) {
                currentHash = basic_operations.sha256(step.hash + currentHash);
            } else {
                currentHash = basic_operations.sha256(currentHash + step.hash);
            }
        }
        return currentHash.equals(rootHash);
    }

    public static void main(String[] args) {
        List<String> data = Arrays.asList("Tx1", "Tx2", "Tx3", "Tx4", "Tx5");
        core_problems mt = new core_problems(data);
        String root = mt.rootHash;

        System.out.println("Generating proof for 'Tx3' (index 2)...");
        List<ProofStep> proof = mt.getProof(2);

        System.out.println("Verifying Tx3: " + verify("Tx3", proof, root));
        System.out.println("Verifying Tx3 (Tampered): " + verify("Tx3_MOD", proof, root));
    }
}
