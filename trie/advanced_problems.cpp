#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * Advanced Trie Problems in C++
 */

class TrieNode {
public:
    unordered_map<char, shared_ptr<TrieNode>> children;
    bool isEndOfWord = false;
    string word;
};

// Problem 1: Word Search II
void dfs(vector<vector<char>>& board, int i, int j, shared_ptr<TrieNode> node, unordered_set<string>& result) {
    if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) return;
    
    char ch = board[i][j];
    if (ch == '#' || node->children.find(ch) == node->children.end()) return;
    
    auto next = node->children[ch];
    if (next->isEndOfWord) {
        result.insert(next->word);
    }
    
    board[i][j] = '#';
    dfs(board, i + 1, j, next, result);
    dfs(board, i - 1, j, next, result);
    dfs(board, i, j + 1, next, result);
    dfs(board, i, j - 1, next, result);
    board[i][j] = ch;
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    auto root = make_shared<TrieNode>();
    
    for (const string& word : words) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = make_shared<TrieNode>();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
        current->word = word;
    }
    
    unordered_set<string> result;
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            dfs(board, i, j, root, result);
        }
    }
    
    return vector<string>(result.begin(), result.end());
}

// Problem 2: Replace Words
string replaceWords(vector<string>& dictionary, string sentence) {
    auto root = make_shared<TrieNode>();
    
    for (const string& word : dictionary) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = make_shared<TrieNode>();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }
    
    string result;
    istringstream iss(sentence);
    string word;
    
    while (iss >> word) {
        if (!result.empty()) result += " ";
        
        auto current = root;
        string prefix;
        
        for (char ch : word) {
            if (current->isEndOfWord) break;
            if (current->children.find(ch) == current->children.end()) {
                prefix = word;
                break;
            }
            prefix += ch;
            current = current->children[ch];
        }
        
        result += prefix.empty() ? word : prefix;
    }
    
    return result;
}

// Problem 3: Palindrome check helper
bool isPalindrome(const string& s) {
    int left = 0, right = s.length() - 1;
    while (left < right) {
        if (s[left++] != s[right--]) return false;
    }
    return true;
}

int main() {
    cout << "=== Advanced Trie Problems ===" << endl << endl;
    
    // Test 1: Word Search II
    cout << "Test 1: Word Search II" << endl;
    vector<vector<char>> board = {
        {'o', 'a', 'a', 'n'},
        {'e', 't', 'a', 'e'},
        {'i', 'h', 'k', 'r'},
        {'i', 'f', 'l', 'v'}
    };
    vector<string> words = {"oath", "pea", "eat", "rain"};
    vector<string> found = findWords(board, words);
    cout << "Found words: [ ";
    for (const string& w : found) cout << w << " ";
    cout << "]" << endl << endl;
    
    // Test 2: Replace Words
    cout << "Test 2: Replace Words" << endl;
    vector<string> dictionary = {"cat", "bat", "rat"};
    string sentence = "the cattle was rattled by the battery";
    cout << "Original: " << sentence << endl;
    cout << "Replaced: " << replaceWords(dictionary, sentence) << endl;
    
    return 0;
}
