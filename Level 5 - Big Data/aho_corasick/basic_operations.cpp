#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

/**
 * Aho-Corasick multi-pattern matching
 */
struct Node {
    map<char, Node*> children;
    Node* fail = nullptr;
    vector<int> patterns;
};

class AhoCorasick {
    Node* root;

public:
    AhoCorasick(const vector<string>& patterns) {
        root = new Node();
        for (int i = 0; i < patterns.size(); i++) {
            Node* curr = root;
            for (char c : patterns[i]) {
                if (curr->children.find(c) == curr->children.end())
                    curr->children[c] = new Node();
                curr = curr->children[c];
            }
            curr->patterns.push_back(i);
        }
        buildLinks();
    }

    void buildLinks() {
        queue<Node*> q;
        for (auto const& [c, node] : root->children) {
            node->fail = root;
            q.push(node);
        }
        while (!q.empty()) {
            Node* u = q.front(); q.pop();
            for (auto const& [c, v] : u->children) {
                Node* f = u->fail;
                while (f != nullptr && f->children.find(c) == f->children.end())
                    f = f->fail;
                v->fail = (f == nullptr) ? root : f->children[c];
                v->patterns.insert(v->patterns.end(), v->fail->patterns.begin(), v->fail->patterns.end());
                q.push(v);
            }
        }
    }

    void search(string text, const vector<string>& originalPatterns) {
        Node* curr = root;
        for (int i = 0; i < text.size(); i++) {
            char c = text[i];
            while (curr != root && curr->children.find(c) == curr->children.end())
                curr = curr->fail;
            if (curr->children.find(c) != curr->children.end())
                curr = curr->children[c];
            for (int idx : curr->patterns) {
                cout << "Pattern " << originalPatterns[idx] << " at index " << i - originalPatterns[idx].size() + 1 << endl;
            }
        }
    }
};

int main() {
    vector<string> patterns = {"apple", "app", "ple"};
    AhoCorasick ac(patterns);
    ac.search("apple", patterns);
    return 0;
}
