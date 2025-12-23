#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

/**
 * Core Merkle Tree Problems in C++
 * Focuses on Proof (Audit Path) generation and verification.
 */

struct Node {
    std::string hash;
    Node *left, *right;
    Node(std::string h) : hash(h), left(nullptr), right(nullptr) {}
};

class MerkleTree {
private:
    std::string sha256(const std::string& input) {
        std::hash<std::string> hasher;
        size_t h = hasher(input);
        std::stringstream ss;
        ss << std::hex << std::setw(16) << std::setfill('0') << h;
        return ss.str();
    }

public:
    struct ProofStep {
        std::string hash;
        bool isLeft;
    };

    std::string rootHash;
    std::vector<std::string> leafHashes;

    MerkleTree(const std::vector<std::string>& data) {
        for (const auto& d : data) leafHashes.push_back(sha256(d));
        
        std::vector<std::string> level = leafHashes;
        while (level.size() > 1) {
            std::vector<std::string> next;
            for (size_t i = 0; i < level.size(); i += 2) {
                std::string left = level[i];
                std::string right = (i + 1 < level.size()) ? level[i+1] : left;
                next.push_back(sha256(left + right));
            }
            level = next;
        }
        rootHash = level.empty() ? "" : level[0];
    }

    std::vector<ProofStep> getProof(int index) {
        std::vector<ProofStep> proof;
        int curr = index;
        std::vector<std::string> level = leafHashes;

        while (level.size() > 1) {
            int sibling = (curr % 2 == 0) ? curr + 1 : curr - 1;
            if (sibling < (int)level.size()) {
                proof.push_back({level[sibling], curr % 2 != 0});
            } else {
                proof.push_back({level[curr], curr % 2 != 0});
            }
            curr /= 2;
            std::vector<std::string> next;
            for (size_t i = 0; i < level.size(); i += 2) {
                std::string l = level[i];
                std::string r = (i + 1 < level.size()) ? level[i+1] : l;
                next.push_back(sha256(l + r));
            }
            level = next;
        }
        return proof;
    }

    bool verify(const std::string& block, const std::vector<ProofStep>& proof) {
        std::string current = sha256(block);
        for (const auto& step : proof) {
            if (step.isLeft) current = sha256(step.hash + current);
            else current = sha256(current + step.hash);
        }
        return current == rootHash;
    }
};

int main() {
    std::vector<std::string> data = {"Tx1", "Tx2", "Tx3", "Tx4", "Tx5"};
    MerkleTree mt(data);

    std::cout << "Root: " << mt.rootHash << std::endl;
    std::cout << "Proof for Tx3..." << std::endl;
    auto proof = mt.getProof(2);

    std::cout << "Verify Tx3: " << (mt.verify("Tx3", proof) ? "Success" : "Failed") << std::endl;
    std::cout << "Verify Tx3 (Bad): " << (mt.verify("Tx3_BAD", proof) ? "Success" : "Failed") << std::endl;

    return 0;
}
