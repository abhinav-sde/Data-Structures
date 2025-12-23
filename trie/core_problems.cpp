#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * Core Trie Problems in C++
 */

class TrieNode {
public:
    unordered_map<char, shared_ptr<TrieNode>> children;
    bool isEndOfWord = false;
    string word;
};

// Problem 1: Implement Trie
class ImplementTrie {
private:
    shared_ptr<TrieNode> root;
    
public:
    ImplementTrie() {
        root = make_shared<TrieNode>();
    }
    
    void insert(string word) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = make_shared<TrieNode>();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }
    
    bool search(string word) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) return false;
            current = current->children[ch];
        }
        return current->isEndOfWord;
    }
    
    bool startsWith(string prefix) {
        auto current = root;
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) return false;
            current = current->children[ch];
        }
        return true;
    }
};

// Problem 2: Longest Common Prefix
string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    
    auto root = make_shared<TrieNode>();
    
    // Insert all strings
    for (const string& str : strs) {
        auto current = root;
        for (char ch : str) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = make_shared<TrieNode>();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }
    
    // Find LCP
    string prefix;
    auto current = root;
    
    while (current->children.size() == 1 && !current->isEndOfWord) {
        auto it = current->children.begin();
        prefix += it->first;
        current = it->second;
    }
    
    return prefix;
}

// Problem 3: Word Break
bool wordBreak(string s, vector<string>& wordDict) {
    auto root = make_shared<TrieNode>();
    
    // Build trie
    for (const string& word : wordDict) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = make_shared<TrieNode>();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }
    
    // DP
    vector<bool> dp(s.length() + 1, false);
    dp[0] = true;
    
    for (int i = 0; i < s.length(); i++) {
        if (!dp[i]) continue;
        
        auto current = root;
        for (int j = i; j < s.length(); j++) {
            char ch = s[j];
            if (current->children.find(ch) == current->children.end()) break;
            
            current = current->children[ch];
            if (current->isEndOfWord) {
                dp[j + 1] = true;
            }
        }
    }
    
    return dp[s.length()];
}

// Problem 4: Add and Search Word
class WordDictionary {
private:
    shared_ptr<TrieNode> root;
    
    bool searchHelper(const string& word, int index, shared_ptr<TrieNode> node) {
        if (index == word.length()) {
            return node->isEndOfWord;
        }
        
        char ch = word[index];
        
        if (ch == '.') {
            for (auto& [c, child] : node->children) {
                if (searchHelper(word, index + 1, child)) {
                    return true;
                }
            }
            return false;
        } else {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            return searchHelper(word, index + 1, node->children[ch]);
        }
    }
    
public:
    WordDictionary() {
        root = make_shared<TrieNode>();
    }
    
    void addWord(string word) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = make_shared<TrieNode>();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }
    
    bool search(string word) {
        return searchHelper(word, 0, root);
    }
};

// Problem 5: Maximum XOR
int findMaximumXOR(vector<int>& nums) {
    auto root = make_shared<TrieNode>();
    
    // Build trie
    for (int num : nums) {
        auto current = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            char ch = '0' + bit;
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = make_shared<TrieNode>();
            }
            current = current->children[ch];
        }
    }
    
    int maxXor = 0;
    
    for (int num : nums) {
        auto current = root;
        int currentXor = 0;
        
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            char complement = '0' + (1 - bit);
            
            if (current->children.find(complement) != current->children.end()) {
                currentXor |= (1 << i);
                current = current->children[complement];
            } else {
                current = current->children['0' + bit];
            }
        }
        
        maxXor = max(maxXor, currentXor);
    }
    
    return maxXor;
}

int main() {
    cout << "=== Core Trie Problems ===" << endl << endl;
    
    // Test 1
    cout << "Test 1: Implement Trie" << endl;
    ImplementTrie trie;
    trie.insert("apple");
    cout << "Search 'apple': " << (trie.search("apple") ? "true" : "false") << endl;
    cout << "Search 'app': " << (trie.search("app") ? "true" : "false") << endl;
    cout << "StartsWith 'app': " << (trie.startsWith("app") ? "true" : "false") << endl;
    trie.insert("app");
    cout << "Search 'app': " << (trie.search("app") ? "true" : "false") << endl << endl;
    
    // Test 2
    cout << "Test 2: Longest Common Prefix" << endl;
    vector<string> strs = {"flower", "flow", "flight"};
    cout << "LCP: " << longestCommonPrefix(strs) << endl << endl;
    
    // Test 3
    cout << "Test 3: Word Break" << endl;
    string s = "leetcode";
    vector<string> wordDict = {"leet", "code"};
    cout << "Can break: " << (wordBreak(s, wordDict) ? "true" : "false") << endl << endl;
    
    // Test 4
    cout << "Test 4: Add and Search Word" << endl;
    WordDictionary wd;
    wd.addWord("bad");
    wd.addWord("dad");
    wd.addWord("mad");
    cout << "Search 'pad': " << (wd.search("pad") ? "true" : "false") << endl;
    cout << "Search 'bad': " << (wd.search("bad") ? "true" : "false") << endl;
    cout << "Search '.ad': " << (wd.search(".ad") ? "true" : "false") << endl;
    cout << "Search 'b..': " << (wd.search("b..") ? "true" : "false") << endl << endl;
    
    // Test 5
    cout << "Test 5: Maximum XOR" << endl;
    vector<int> nums = {3, 10, 5, 25, 2, 8};
    cout << "Max XOR: " << findMaximumXOR(nums) << endl;
    
    return 0;
}
