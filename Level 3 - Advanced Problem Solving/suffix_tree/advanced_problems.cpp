#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <bitset>
#include <algorithm>

/**
 * Advanced Suffix Tree Problems in C++
 * Implements Longest Common Substring of two strings using a Generalized Suffix Tree.
 */

struct Node {
    std::map<char, Node*> children;
    int start, end, depth;
    std::bitset<2> sources;

    Node(int s, int e, int d) : start(s), end(e), depth(d) {
        sources.reset();
    }
    int length() { return end - start + 1; }
};

class GeneralizedSuffixTree {
private:
    std::string text;
    Node* root;
    std::string lcs;

    void updateSources(Node* node) {
        for (auto const& [key, child] : node->children) {
            updateSources(child);
            node->sources |= child->sources;
        }
    }

    Node* findAnyLeaf(Node* node) {
        if (node->children.empty()) return node;
        return findAnyLeaf(node->children.begin()->second);
    }

    void dfsLCS(Node* node, int pathLen) {
        if (node->sources.all()) {
            if (pathLen > (int)lcs.length()) {
                Node* leaf = findAnyLeaf(node);
                int start = leaf->end - leaf->depth + 1;
                std::string candidate = text.substr(start, pathLen);
                if (candidate.find('#') == std::string::npos && candidate.find('$') == std::string::npos) {
                    lcs = candidate;
                }
            }
        }
        for (auto const& [key, child] : node->children) {
            dfsLCS(child, pathLen + child->length());
        }
    }

public:
    GeneralizedSuffixTree(std::string s1, std::string s2) : text(s1 + "#" + s2 + "$"), root(new Node(-1, -1, 0)), lcs("") {
        int s1Len = s1.length();
        for (int i = 0; i < (int)text.length(); ++i) {
            Node* curr = root;
            int bit = (i <= s1Len) ? 0 : 1;
            curr->sources.set(bit);
            int wordIdx = i;
            while (wordIdx < (int)text.length()) {
                char first = text[wordIdx];
                if (curr->children.find(first) == curr->children.end()) {
                    Node* leaf = new Node(wordIdx, text.length() - 1, curr->depth + (text.length() - wordIdx));
                    leaf->sources.set(bit);
                    curr->children[first] = leaf;
                    break;
                }
                Node* next = curr->children[first];
                next->sources.set(bit);
                int j = 0, labelLen = next->length();
                while (j < labelLen && wordIdx < (int)text.length() && text[next->start + j] == text[wordIdx]) {
                    wordIdx++; j++;
                }
                if (j == labelLen) { curr = next; }
                else {
                    Node* split = new Node(next->start, next->start + j - 1, curr->depth + j);
                    next->start += j;
                    curr->children[text[split->start]] = split;
                    split->children[text[next->start]] = next;
                    Node* leaf = new Node(wordIdx, text.length() - 1, split->depth + (text.length() - wordIdx));
                    leaf->sources.set(bit);
                    split->children[text[wordIdx]] = leaf;
                    break;
                }
            }
        }
    }

    std::string findLCS() {
        lcs = "";
        updateSources(root);
        dfsLCS(root, 0);
        return lcs;
    }
};

int main() {
    std::string s1 = "geeksforgeeks";
    std::string s2 = "quizgeeks";
    GeneralizedSuffixTree gst(s1, s2);
    std::cout << "S1: " << s1 << ", S2: " << s2 << std::endl;
    std::cout << "Longest Common Substring: " << gst.findLCS() << std::endl;
    return 0;
}
