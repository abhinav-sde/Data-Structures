#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ========================================
// TRIE NODE STRUCTURE
// ========================================

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;
    int wordCount;  // For counting word frequency
    
    TrieNode() {
        isEndOfWord = false;
        wordCount = 0;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

// ========================================
// TRIE CLASS
// ========================================

class Trie {
private:
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    // ========================================
    // 1. INSERT WORD
    // ========================================
    // Usage: insert(word)
    // Example: insert("apple")
    void insert(string word) {
        TrieNode* current = root;
        
        for (char ch : word) {
            int index = ch - 'a';
            
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }
            
            current = current->children[index];
        }
        
        current->isEndOfWord = true;
        current->wordCount++;
        cout << "Inserted: " << word << endl;
    }
    
    // ========================================
    // 2. SEARCH WORD
    // ========================================
    // Usage: found = search(word)
    // Example: search("apple") returns true/false
    bool search(string word) {
        TrieNode* current = root;
        
        for (char ch : word) {
            int index = ch - 'a';
            
            if (current->children[index] == nullptr) {
                return false;
            }
            
            current = current->children[index];
        }
        
        return current->isEndOfWord;
    }
    
    // ========================================
    // 3. STARTS WITH (PREFIX SEARCH)
    // ========================================
    // Usage: hasPrefix = startsWith(prefix)
    // Example: startsWith("app") returns true if any word starts with "app"
    bool startsWith(string prefix) {
        TrieNode* current = root;
        
        for (char ch : prefix) {
            int index = ch - 'a';
            
            if (current->children[index] == nullptr) {
                return false;
            }
            
            current = current->children[index];
        }
        
        return true;
    }
    
    // ========================================
    // 4. DELETE WORD
    // ========================================
    // Usage: deleteWord(word)
    // Example: deleteWord("apple")
    bool deleteWordHelper(TrieNode* current, string word, int index) {
        if (index == word.length()) {
            if (!current->isEndOfWord) {
                return false;
            }
            
            current->isEndOfWord = false;
            current->wordCount = 0;
            
            // Check if node has children
            for (int i = 0; i < 26; i++) {
                if (current->children[i] != nullptr) {
                    return false;
                }
            }
            
            return true;
        }
        
        int charIndex = word[index] - 'a';
        TrieNode* node = current->children[charIndex];
        
        if (node == nullptr) {
            return false;
        }
        
        bool shouldDeleteChild = deleteWordHelper(node, word, index + 1);
        
        if (shouldDeleteChild) {
            delete node;
            current->children[charIndex] = nullptr;
            
            // Check if current node can be deleted
            if (!current->isEndOfWord) {
                for (int i = 0; i < 26; i++) {
                    if (current->children[i] != nullptr) {
                        return false;
                    }
                }
                return true;
            }
        }
        
        return false;
    }
    
    void deleteWord(string word) {
        if (deleteWordHelper(root, word, 0)) {
            cout << "Deleted: " << word << endl;
        } else {
            cout << "Word not found: " << word << endl;
        }
    }
    
    // ========================================
    // 5. COUNT WORDS WITH PREFIX
    // ========================================
    // Usage: count = countWordsWithPrefix(prefix)
    // Example: countWordsWithPrefix("app") counts words starting with "app"
    int countWordsHelper(TrieNode* node) {
        if (node == nullptr) return 0;
        
        int count = node->isEndOfWord ? 1 : 0;
        
        for (int i = 0; i < 26; i++) {
            count += countWordsHelper(node->children[i]);
        }
        
        return count;
    }
    
    int countWordsWithPrefix(string prefix) {
        TrieNode* current = root;
        
        for (char ch : prefix) {
            int index = ch - 'a';
            
            if (current->children[index] == nullptr) {
                return 0;
            }
            
            current = current->children[index];
        }
        
        return countWordsHelper(current);
    }
    
    // ========================================
    // 6. GET ALL WORDS WITH PREFIX (AUTOCOMPLETE)
    // ========================================
    // Usage: words = autocomplete(prefix)
    // Example: autocomplete("app") returns {"apple", "application"}
    void getAllWordsHelper(TrieNode* node, string current, vector<string>& words) {
        if (node == nullptr) return;
        
        if (node->isEndOfWord) {
            words.push_back(current);
        }
        
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                getAllWordsHelper(node->children[i], current + char('a' + i), words);
            }
        }
    }
    
    vector<string> autocomplete(string prefix) {
        vector<string> words;
        TrieNode* current = root;
        
        for (char ch : prefix) {
            int index = ch - 'a';
            
            if (current->children[index] == nullptr) {
                return words;
            }
            
            current = current->children[index];
        }
        
        getAllWordsHelper(current, prefix, words);
        return words;
    }
    
    // ========================================
    // 7. LONGEST COMMON PREFIX
    // ========================================
    // Usage: lcp = longestCommonPrefix()
    // Example: Returns longest prefix common to all words
    string longestCommonPrefix() {
        string prefix = "";
        TrieNode* current = root;
        
        while (true) {
            int childCount = 0;
            int childIndex = -1;
            
            for (int i = 0; i < 26; i++) {
                if (current->children[i] != nullptr) {
                    childCount++;
                    childIndex = i;
                }
            }
            
            if (childCount != 1 || current->isEndOfWord) {
                break;
            }
            
            prefix += char('a' + childIndex);
            current = current->children[childIndex];
        }
        
        return prefix;
    }
    
    // ========================================
    // 8. PRINT ALL WORDS
    // ========================================
    // Usage: printAllWords()
    // Example: Prints all words in trie
    void printAllWordsHelper(TrieNode* node, string current) {
        if (node == nullptr) return;
        
        if (node->isEndOfWord) {
            cout << current << " ";
        }
        
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                printAllWordsHelper(node->children[i], current + char('a' + i));
            }
        }
    }
    
    void printAllWords() {
        cout << "All words: ";
        printAllWordsHelper(root, "");
        cout << endl;
    }
    
    // ========================================
    // 9. COUNT TOTAL WORDS
    // ========================================
    // Usage: count = countTotalWords()
    // Example: Returns total number of words in trie
    int countTotalWordsHelper(TrieNode* node) {
        if (node == nullptr) return 0;
        
        int count = node->isEndOfWord ? 1 : 0;
        
        for (int i = 0; i < 26; i++) {
            count += countTotalWordsHelper(node->children[i]);
        }
        
        return count;
    }
    
    int countTotalWords() {
        return countTotalWordsHelper(root);
    }
    
    // ========================================
    // 10. WORD FREQUENCY
    // ========================================
    // Usage: freq = getWordFrequency(word)
    // Example: getWordFrequency("apple") returns how many times inserted
    int getWordFrequency(string word) {
        TrieNode* current = root;
        
        for (char ch : word) {
            int index = ch - 'a';
            
            if (current->children[index] == nullptr) {
                return 0;
            }
            
            current = current->children[index];
        }
        
        return current->isEndOfWord ? current->wordCount : 0;
    }
};

// ========================================
// ADDITIONAL TRIE PROBLEMS
// ========================================

// Word Break Problem
bool wordBreakHelper(string s, int start, Trie& trie, vector<int>& memo) {
    if (start == s.length()) return true;
    
    if (memo[start] != -1) return memo[start];
    
    for (int end = start + 1; end <= s.length(); end++) {
        string word = s.substr(start, end - start);
        
        if (trie.search(word) && wordBreakHelper(s, end, trie, memo)) {
            memo[start] = 1;
            return true;
        }
    }
    
    memo[start] = 0;
    return false;
}

bool wordBreak(string s, vector<string>& wordDict) {
    Trie trie;
    for (string word : wordDict) {
        trie.insert(word);
    }
    
    vector<int> memo(s.length(), -1);
    return wordBreakHelper(s, 0, trie, memo);
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    Trie trie;
    
    cout << "=== Trie Operations ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // Insert words
    // trie.insert("apple");
    // trie.insert("app");
    // trie.insert("application");
    // trie.insert("apply");
    // trie.insert("banana");
    // trie.insert("band");
    
    // Search
    // cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not found") << endl;
    // cout << "Search 'appl': " << (trie.search("appl") ? "Found" : "Not found") << endl;
    
    // Starts with (prefix)
    // cout << "Starts with 'app': " << (trie.startsWith("app") ? "Yes" : "No") << endl;
    // cout << "Starts with 'ban': " << (trie.startsWith("ban") ? "Yes" : "No") << endl;
    
    // Count words with prefix
    // int count = trie.countWordsWithPrefix("app");
    // cout << "Words with prefix 'app': " << count << endl;
    
    // Autocomplete
    // vector<string> suggestions = trie.autocomplete("app");
    // cout << "Autocomplete 'app': ";
    // for (string word : suggestions) {
    //     cout << word << " ";
    // }
    // cout << endl;
    
    // Print all words
    // trie.printAllWords();
    
    // Count total words
    // cout << "Total words: " << trie.countTotalWords() << endl;
    
    // Longest common prefix
    // string lcp = trie.longestCommonPrefix();
    // cout << "Longest common prefix: " << lcp << endl;
    
    // Delete word
    // trie.deleteWord("app");
    // trie.printAllWords();
    
    // Word frequency
    // trie.insert("apple");  // Insert again
    // int freq = trie.getWordFrequency("apple");
    // cout << "Frequency of 'apple': " << freq << endl;
    
    return 0;
}
