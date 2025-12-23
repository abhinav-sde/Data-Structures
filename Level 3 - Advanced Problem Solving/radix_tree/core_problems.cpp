#include <iostream>
#include <string>
#include <map>
#include <vector>

/**
 * Core Radix Tree Problems in C++
 * Focuses on deletion and prefix completion.
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

    void collect(Node* node, std::string current, std::vector<std::string>& results) {
        if (node->isEndOfWord) results.push_back(current);
        for (auto const& [key, edge] : node->children) {
            collect(edge->target, current + edge->label, results);
        }
    }

public:
    RadixTree() : root(new Node()) {}

    void insert(std::string word) {
        Node* curr = root;
        while (!word.empty()) {
            char first = word[0];
            if (curr->children.find(first) == curr->children.end()) {
                curr->children[first] = new Edge(word, new Node());
                curr->children[first]->target->isEndOfWord = true;
                return;
            }
            Edge* edge = curr->children[first];
            int common = 0;
            while (common < edge->label.length() && common < word.length() && edge->label[common] == word[common])
                common++;
            
            if (common < edge->label.length()) {
                Node* split = new Node();
                split->children[edge->label[common]] = new Edge(edge->label.substr(common), edge->target);
                edge->label = edge->label.substr(0, common);
                edge->target = split;
            }
            word = word.substr(common);
            curr = edge->target;
        }
        curr->isEndOfWord = true;
    }

    std::vector<std::string> getWithPrefix(std::string prefix) {
        std::vector<std::string> results;
        Node* curr = root;
        std::string match = "";
        std::string temp = prefix;

        while (!temp.empty()) {
            char first = temp[0];
            if (curr->children.find(first) == curr->children.end()) {
                if (temp.length() < 0) {} // just safety
                return results;
            }
            Edge* edge = curr->children[first];
            if (temp.length() < edge->label.length()) {
                if (edge->label.substr(0, temp.length()) == temp) {
                    match += edge->label;
                    curr = edge->target;
                    break;
                }
                return results;
            } else if (temp.substr(0, edge->label.length()) == edge->label) {
                match += edge->label;
                temp = temp.substr(edge->label.length());
                curr = edge->target;
            } else return results;
        }
        collect(curr, match, results);
        return results;
    }
};

int main() {
    RadixTree radix;
    radix.insert("romane"); radix.insert("romanus"); radix.insert("romulus"); radix.insert("rubens");

    auto results = radix.getWithPrefix("rom");
    std::cout << "Prefix 'rom': ";
    for (const auto& s : results) std::cout << s << " ";
    std::cout << std::endl;

    results = radix.getWithPrefix("ru");
    std::cout << "Prefix 'ru': ";
    for (const auto& s : results) std::cout << s << " ";
    std::cout << std::endl;

    return 0;
}
