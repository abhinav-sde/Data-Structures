#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
using namespace std;

/**
 * Basic Trie (Prefix Tree) Operations in C++
 * Also known as Digital Tree or Prefix Tree
 */

class TrieNode {
public:
    unordered_map<char, shared_ptr<TrieNode>> children;
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    shared_ptr<TrieNode> root;
    
    void collectWords(shared_ptr<TrieNode> node, string prefix, vector<string>& words) {
        if (node->isEndOfWord) {
            words.push_back(prefix);
        }
        
        for (auto& [ch, child] : node->children) {
            collectWords(child, prefix + ch, words);
        }
    }
    
    bool deleteHelper(shared_ptr<TrieNode> current, const string& word, int index) {
        if (index == word.length()) {
            if (!current->isEndOfWord) {
                return false;
            }
            current->isEndOfWord = false;
            return current->children.empty();
        }
        
        char ch = word[index];
        auto it = current->children.find(ch);
        
        if (it == current->children.end()) {
            return false;
        }
        
        bool shouldDeleteCurrentNode = deleteHelper(it->second, word, index + 1);
        
        if (shouldDeleteCurrentNode) {
            current->children.erase(ch);
            return current->children.empty() && !current->isEndOfWord;
        }
        
        return false;
    }
    
    int countWordsHelper(shared_ptr<TrieNode> node) {
        int count = node->isEndOfWord ? 1 : 0;
        
        for (auto& [ch, child] : node->children) {
            count += countWordsHelper(child);
        }
        
        return count;
    }
    
public:
    Trie() {
        root = make_shared<TrieNode>();
    }
    
    // Insert a word
    // Time Complexity: O(m)
    void insert(const string& word) {
        auto current = root;
        
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = make_shared<TrieNode>();
            }
            current = current->children[ch];
        }
        
        current->isEndOfWord = true;
        cout << "Inserted: " << word << endl;
    }
    
    // Search for a complete word
    // Time Complexity: O(m)
    bool search(const string& word) {
        auto current = root;
        
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        
        return current->isEndOfWord;
    }
    
    // Check if prefix exists
    // Time Complexity: O(m)
    bool startsWith(const string& prefix) {
        auto current = root;
        
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        
        return true;
    }
    
    // Delete a word
    bool deleteWord(const string& word) {
        return deleteHelper(root, word, 0);
    }
    
    // Get all words in trie
    vector<string> getAllWords() {
        vector<string> words;
        collectWords(root, "", words);
        return words;
    }
    
    // Autocomplete - get words with prefix
    vector<string> getWordsWithPrefix(const string& prefix) {
        vector<string> words;
        auto current = root;
        
        // Navigate to prefix
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return words; // No words with this prefix
            }
            current = current->children[ch];
        }
        
        // Collect all words from this point
        collectWords(current, prefix, words);
        return words;
    }
    
    // Count total words
    int countWords() {
        return countWordsHelper(root);
    }
    
    // Find longest common prefix
    string longestCommonPrefix() {
        string prefix;
        auto current = root;
        
        while (current->children.size() == 1 && !current->isEndOfWord) {
            auto it = current->children.begin();
            prefix += it->first;
            current = it->second;
        }
        
        return prefix;
    }
};

int main() {
    cout << "=== Trie Basic Operations Demo ===" << endl << endl;
    
    Trie trie;
    
    // Insert words
    cout << "--- Inserting Words ---" << endl;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("apply");
    trie.insert("bat");
    trie.insert("batch");
    trie.insert("batman");
    cout << endl;
    
    // Search for words
    cout << "--- Searching Words ---" << endl;
    cout << "Search 'apple': " << (trie.search("apple") ? "true" : "false") << endl;
    cout << "Search 'app': " << (trie.search("app") ? "true" : "false") << endl;
    cout << "Search 'appl': " << (trie.search("appl") ? "true" : "false") << endl;
    cout << "Search 'bat': " << (trie.search("bat") ? "true" : "false") << endl;
    cout << "Search 'ball': " << (trie.search("ball") ? "true" : "false") << endl;
    cout << endl;
    
    // Check prefixes
    cout << "--- Checking Prefixes ---" << endl;
    cout << "Starts with 'app': " << (trie.startsWith("app") ? "true" : "false") << endl;
    cout << "Starts with 'appl': " << (trie.startsWith("appl") ? "true" : "false") << endl;
    cout << "Starts with 'bat': " << (trie.startsWith("bat") ? "true" : "false") << endl;
    cout << "Starts with 'ball': " << (trie.startsWith("ball") ? "true" : "false") << endl;
    cout << endl;
    
    // Autocomplete
    cout << "--- Autocomplete (words with prefix 'app') ---" << endl;
    vector<string> suggestions = trie.getWordsWithPrefix("app");
    cout << "[ ";
    for (const string& word : suggestions) {
        cout << word << " ";
    }
    cout << "]" << endl << endl;
    
    cout << "--- Autocomplete (words with prefix 'bat') ---" << endl;
    suggestions = trie.getWordsWithPrefix("bat");
    cout << "[ ";
    for (const string& word : suggestions) {
        cout << word << " ";
    }
    cout << "]" << endl << endl;
    
    // Get all words
    cout << "--- All Words in Trie ---" << endl;
    vector<string> allWords = trie.getAllWords();
    cout << "[ ";
    for (const string& word : allWords) {
        cout << word << " ";
    }
    cout << "]" << endl << endl;
    
    // Count words
    cout << "--- Count Words ---" << endl;
    cout << "Total words: " << trie.countWords() << endl << endl;
    
    // Delete word
    cout << "--- Deleting 'app' ---" << endl;
    trie.deleteWord("app");
    cout << "Search 'app' after delete: " << (trie.search("app") ? "true" : "false") << endl;
    cout << "Search 'apple' after delete: " << (trie.search("apple") ? "true" : "false") << endl;
    
    allWords = trie.getAllWords();
    cout << "All words: [ ";
    for (const string& word : allWords) {
        cout << word << " ";
    }
    cout << "]" << endl;
    
    return 0;
}
