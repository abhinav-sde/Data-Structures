#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <iomanip>
#include <sstream>

/**
 * Basic Merkle Tree Operations in C++
 * Note: Uses a simple string hash for demonstration. In production, use SHA-256.
 */

struct Node {
    std::string hash;
    Node *left, *right;
    Node(std::string h) : hash(h), left(nullptr), right(nullptr) {}
};

class MerkleTree {
private:
    Node* root;

    std::string sha256(const std::string& input) {
        // Mock SHA-256 for standard C++ (no built-in crypto)
        std::hash<std::string> hasher;
        size_t h = hasher(input);
        std::stringstream ss;
        ss << std::hex << std::setw(16) << std::setfill('0') << h;
        return ss.str();
    }

public:
    MerkleTree(const std::vector<std::string>& data) {
        std::vector<Node*> nodes;
        for (const auto& d : data) nodes.push_back(new Node(sha256(d)));

        while (nodes.size() > 1) {
            std::vector<Node*> parents;
            for (size_t i = 0; i < nodes.size(); i += 2) {
                Node* left = nodes[i];
                Node* right = (i + 1 < nodes.size()) ? nodes[i+1] : left;
                Node* parent = new Node(sha256(left->hash + right->hash));
                parent->left = left;
                parent->right = right;
                parents.push_back(parent);
            }
            nodes = parents;
        }
        root = nodes.empty() ? nullptr : nodes[0];
    }

    std::string getRootHash() { return root ? root->hash : ""; }
};

int main() {
    std::vector<std::string> data = {"Block_1", "Block_2", "Block_3", "Block_4"};
    MerkleTree mt(data);

    std::cout << "Data: Block_1, Block_2, Block_3, Block_4" << std::endl;
    std::cout << "Merkle Root Hash: " << mt.getRootHash() << std::endl;

    std::vector<std::string> tampered = {"Block_1_ALT", "Block_2", "Block_3", "Block_4"};
    MerkleTree mtT(tampered);
    std::cout << "Tampered Root Hash: " << mtT.getRootHash() << std::endl;

    return 0;
}
