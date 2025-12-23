#include <iostream>
#include <string>
#include <map>
#include <vector>

/**
 * Basic Radix Tree (Compressed Trie) Operations in C++
 * Implements insertion and search with path compression.
 */

struct Node;

struct Edge {
    std::string label;
    Node* target;

    Edge(std::string l, Node* t) : label(l), target(t) {}
};

struct Node {
    std::map<char, Edge*> children;
    bool isEndOfWord;

    Node() : isEndOfWord(false) {}
};

class RadixTree {
private:
    Node* root;

    void insert(Node* node, std::string word) {
        if (word.empty()) {
            node->isEndOfWord = true;
            return;
        }

        char firstChar = word[0];
        if (node->children.find(firstChar) == node->children.end()) {
            Node* newNode = new Node();
            newNode->isEndOfWord = true;
            node->children[firstChar] = new Edge(word, newNode);
            return;
        }

        Edge* edge = node->children[firstChar];
        int commonLen = 0;
        int maxLen = std::min((int)word.length(), (int)edge->label.length());
        while (commonLen < maxLen && word[commonLen] == edge->label[commonLen]) {
            commonLen++;
        }

        if (commonLen < (int)edge->label.length()) {
            // Split
            std::string commonPart = edge->label.substr(0, commonLen);
            std::string remainingEdgePart = edge->label.substr(commonLen);

            Node* splitNode = new Node();
            splitNode->children[remainingEdgePart[0]] = new Edge(remainingEdgePart, edge->target);
            
            edge->label = commonPart;
            edge->target = splitNode;
        }

        if (commonLen < (int)word.length()) {
            insert(edge->target, word.substr(commonLen));
        } else {
            edge->target->isEndOfWord = true;
        }
    }

    bool search(Node* node, std::string word) {
        if (word.empty()) return node->isEndOfWord;

        char firstChar = word[0];
        if (node->children.find(firstChar) == node->children.end()) return false;

        Edge* edge = node->children[firstChar];
        if (word.length() >= edge->label.length() && word.substr(0, edge->label.length()) == edge->label) {
            return search(edge->target, word.substr(edge->label.length()));
        }
        return false;
    }

public:
    RadixTree() : root(new Node()) {}

    void insert(std::string word) { insert(root, word); }
    bool search(std::string word) { return search(root, word); }
};

int main() {
    RadixTree radix;
    std::vector<std::string> words = {"apple", "app", "apricot", "banana", "band"};

    std::cout << "Inserting: apple, app, apricot, banana, band" << std::endl;
    for (const auto& w : words) radix.insert(w);

    std::cout << "Search 'apple': " << (radix.search("apple") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'app': " << (radix.search("app") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'apri': " << (radix.search("apri") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'apricot': " << (radix.search("apricot") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'band': " << (radix.search("band") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'balloon': " << (radix.search("balloon") ? "Found" : "Not Found") << std::endl;

    return 0;
}
