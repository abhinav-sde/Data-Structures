#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

/**
 * Core Suffix Tree Problems in C++
 * Focuses on Longest Repeated Substring and Pattern Counting.
 */

struct Node {
    std::map<char, Node*> children;
    int start, end, depth;

    Node(int s, int e, int d) : start(s), end(e), depth(d) {}
    int length() { return end - start + 1; }
};

class SuffixTree {
private:
    std::string text;
    Node* root;
    std::string max_repeated;

    Node* findAnyLeaf(Node* node) {
        if (node->children.empty()) return node;
        return findAnyLeaf(node->children.begin()->second);
    }

    void dfs(Node* node, int pathLen) {
        if (node->children.size() >= 2) {
            if (pathLen > (int)max_repeated.length()) {
                Node* leaf = findAnyLeaf(node);
                int start = leaf->end - leaf->depth + 1;
                std::string candidate = text.substr(start, pathLen);
                if (candidate.find('$') == std::string::npos) max_repeated = candidate;
            }
        }
        for (auto const& [key, child] : node->children) {
            dfs(child, pathLen + child->length());
        }
    }

    int countLeaves(Node* node) {
        if (node->children.empty()) return 1;
        int count = 0;
        for (auto const& [key, child] : node->children) count += countLeaves(child);
        return count;
    }

public:
    SuffixTree(std::string t) : text(t + "$"), root(new Node(-1, -1, 0)), max_repeated("") {
        for (int i = 0; i < (int)text.length(); ++i) {
            Node* curr = root;
            int wordIdx = i;
            while (wordIdx < (int)text.length()) {
                char first = text[wordIdx];
                if (curr->children.find(first) == curr->children.end()) {
                    curr->children[first] = new Node(wordIdx, text.length() - 1, curr->depth + (text.length() - wordIdx));
                    break;
                }
                Node* next = curr->children[first];
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
                    split->children[text[wordIdx]] = new Node(wordIdx, text.length() - 1, split->depth + (text.length() - wordIdx));
                    break;
                }
            }
        }
    }

    std::string findLongestRepeatedSubstring() {
        max_repeated = "";
        dfs(root, 0);
        return max_repeated;
    }

    int countOccurrences(std::string pattern) {
        Node* curr = root;
        int i = 0;
        while (i < (int)pattern.length()) {
            char first = pattern[i];
            if (curr->children.find(first) == curr->children.end()) return 0;
            Node* next = curr->children[first];
            int j = 0;
            while (j < next->length() && i < (int)pattern.length()) {
                if (text[next->start + j] != pattern[i]) return 0;
                i++; j++;
            }
            curr = next;
        }
        return countLeaves(curr);
    }
};

int main() {
    std::string text = "banana";
    SuffixTree st(text);
    std::cout << "Longest Repeated Substring in 'banana': " << st.findLongestRepeatedSubstring() << std::endl;
    std::cout << "Occurrences of 'ana': " << st.countOccurrences("ana") << std::endl;
    return 0;
}
