#include <iostream>
#include <string>
#include <map>
#include <vector>

/**
 * Basic Suffix Tree Operations in C++
 * Implements construction and substring search.
 */

struct Node {
    std::map<char, Node*> children;
    int start, end;

    Node(int s, int e) : start(s), end(e) {}

    int length() { return end - start + 1; }
};

class SuffixTree {
private:
    std::string text;
    Node* root;

    void insertSuffix(int suffixStart) {
        Node* curr = root;
        int i = suffixStart;

        while (i < text.length()) {
            char first = text[i];
            if (curr->children.find(first) == curr->children.end()) {
                curr->children[first] = new Node(i, text.length() - 1);
                return;
            }

            Node* next = curr->children[first];
            int j = 0;
            int labelLen = next->length();

            while (j < labelLen && i < text.length() && text[next->start + j] == text[i]) {
                i++;
                j++;
            }

            if (j == labelLen) {
                curr = next;
            } else {
                // Split
                Node* split = new Node(next->start, next->start + j - 1);
                next->start += j;
                curr->children[text[split->start]] = split;
                split->children[text[next->start]] = next;
                split->children[text[i]] = new Node(i, text.length() - 1);
                return;
            }
        }
    }

public:
    SuffixTree(std::string t) : text(t + "$") {
        root = new Node(-1, -1);
        for (int i = 0; i < text.length(); ++i) {
            insertSuffix(i);
        }
    }

    bool contains(std::string pattern) {
        Node* curr = root;
        int i = 0;
        while (i < pattern.length()) {
            char first = pattern[i];
            if (curr->children.find(first) == curr->children.end()) return false;

            Node* next = curr->children[first];
            int j = 0;
            while (j < next->length() && i < pattern.length()) {
                if (text[next->start + j] != pattern[i]) return false;
                i++;
                j++;
            }
            curr = next;
        }
        return true;
    }
};

int main() {
    std::string text = "banana";
    SuffixTree st(text);

    std::cout << "Text: " << text << std::endl;
    std::cout << "Contains 'nan': " << (st.contains("nan") ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'ana': " << (st.contains("ana") ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'ban': " << (st.contains("ban") ? "Yes" : "No") << std::endl;
    std::cout << "Contains 'apple': " << (st.contains("apple") ? "Yes" : "No") << std::endl;

    return 0;
}
