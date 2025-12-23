#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

/**
 * Advanced Merkle Tree Problems in C++
 * Implements Anti-Entropy (Data Repair) simulation.
 */

struct Node {
    std::string hash;
    Node *left, *right;
    int start, end, level;

    Node(std::string h, int s, int e, int l) : hash(h), start(s), end(e), level(l), left(nullptr), right(nullptr) {}
};

std::string mock_sha256(const std::string& input) {
    std::hash<std::string> hasher;
    size_t h = hasher(input);
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << h;
    return ss.str();
}

Node* buildRecursive(std::vector<Node*> current) {
    if (current.size() == 1) return current[0];
    std::vector<Node*> parents;
    for (size_t i = 0; i < current.size(); i += 2) {
        Node* left = current[i];
        Node* right = (i + 1 < current.size()) ? current[i+1] : left;
        Node* p = new Node(mock_sha256(left->hash + right->hash), left->start, right->end, left->level + 1);
        p->left = left; p->right = right;
        parents.push_back(p);
    }
    return buildRecursive(parents);
}

void findDiffs(Node* n1, Node* n2, std::vector<int>& diffs) {
    if (!n1 || !n2 || n1->hash == n2->hash) return;
    if (n1->level == 0) {
        diffs.push_back(n1->start);
        return;
    }
    findDiffs(n1->left, n2->left, diffs);
    if (n1->right != n1->left) // Avoid double processing for odd duplicates
        findDiffs(n1->right, n2->right, diffs);
}

int main() {
    std::vector<std::string> dataA = {"D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8"};
    std::vector<std::string> dataB = {"D1", "D2_X", "D3", "D4", "D5", "D6_X", "D7", "D8"};

    std::vector<Node*> leavesA, leavesB;
    for (int i = 0; i < 8; ++i) {
        leavesA.push_back(new Node(mock_sha256(dataA[i]), i, i, 0));
        leavesB.push_back(new Node(mock_sha256(dataB[i]), i, i, 0));
    }

    Node* rootA = buildRecursive(leavesA);
    Node* rootB = buildRecursive(leavesB);

    std::vector<int> diffs;
    findDiffs(rootA, rootB, diffs);

    std::cout << "Differing indices: ";
    for (int d : diffs) std::cout << d << " ";
    std::cout << std::endl;

    return 0;
}
