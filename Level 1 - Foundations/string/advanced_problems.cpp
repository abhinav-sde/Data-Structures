#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stack>
using namespace std;

// ========================================
// UTILITY FUNCTION
// ========================================

void display(string str) {
    cout << "String: \"" << str << "\"" << endl;
}

// ========================================
// 1. LONGEST PALINDROMIC SUBSTRING
// ========================================
// Concept: Expand around center
// Usage: result = longestPalindrome(str)
// Example: longestPalindrome("babad") returns "bab" or "aba"
string longestPalindrome(string str) {
    if (str.length() < 1) return "";
    
    int start = 0, maxLen = 1;
    
    auto expandAroundCenter = [&](int left, int right) {
        while (left >= 0 && right < str.length() && str[left] == str[right]) {
            if (right - left + 1 > maxLen) {
                start = left;
                maxLen = right - left + 1;
            }
            left--;
            right++;
        }
    };
    
    for (int i = 0; i < str.length(); i++) {
        expandAroundCenter(i, i);      // Odd length palindromes
        expandAroundCenter(i, i + 1);  // Even length palindromes
    }
    
    return str.substr(start, maxLen);
}

// ========================================
// 2. LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS
// ========================================
// Concept: Sliding window + Hashing
// Usage: length = longestUniqueSubstring(str)
// Example: longestUniqueSubstring("abcabcbb") returns 3 ("abc")
int longestUniqueSubstring(string str) {
    unordered_map<char, int> charIndex;
    int maxLen = 0;
    int start = 0;
    
    for (int end = 0; end < str.length(); end++) {
        if (charIndex.find(str[end]) != charIndex.end()) {
            start = max(start, charIndex[str[end]] + 1);
        }
        charIndex[str[end]] = end;
        maxLen = max(maxLen, end - start + 1);
    }
    
    return maxLen;
}

// ========================================
// 3. VALID PARENTHESES
// ========================================
// Concept: Stack
// Usage: result = isValidParentheses(str)
// Example: isValidParentheses("()[]{}") returns true
bool isValidParentheses(string str) {
    stack<char> st;
    
    for (char ch : str) {
        if (ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
        } else {
            if (st.empty()) return false;
            
            char top = st.top();
            if ((ch == ')' && top == '(') ||
                (ch == '}' && top == '{') ||
                (ch == ']' && top == '[')) {
                st.pop();
            } else {
                return false;
            }
        }
    }
    
    return st.empty();
}

// ========================================
// 4. STRING TO INTEGER (ATOI)
// ========================================
// Concept: String parsing with edge cases
// Usage: num = stringToInt(str)
// Example: stringToInt("  -42") returns -42
int stringToInt(string str) {
    int i = 0, sign = 1;
    long result = 0;
    
    // Skip whitespace
    while (i < str.length() && str[i] == ' ') i++;
    
    // Check sign
    if (i < str.length() && (str[i] == '+' || str[i] == '-')) {
        sign = (str[i] == '-') ? -1 : 1;
        i++;
    }
    
    // Convert digits
    while (i < str.length() && isdigit(str[i])) {
        result = result * 10 + (str[i] - '0');
        
        // Check overflow
        if (result * sign > INT_MAX) return INT_MAX;
        if (result * sign < INT_MIN) return INT_MIN;
        
        i++;
    }
    
    return result * sign;
}

// ========================================
// 5. GROUP ANAGRAMS
// ========================================
// Concept: Hashing with sorted string as key
// Usage: groupAnagrams(strs, n)
// Example: {"eat", "tea", "tan", "ate", "nat", "bat"} groups into [["eat","tea","ate"],["tan","nat"],["bat"]]
void groupAnagrams(string strs[], int n) {
    unordered_map<string, vector<string>> groups;
    
    for (int i = 0; i < n; i++) {
        string key = strs[i];
        sort(key.begin(), key.end());
        groups[key].push_back(strs[i]);
    }
    
    cout << "Anagram groups:" << endl;
    for (auto& pair : groups) {
        cout << "[ ";
        for (string& str : pair.second) {
            cout << "\"" << str << "\" ";
        }
        cout << "]" << endl;
    }
}

// ========================================
// 6. LONGEST COMMON PREFIX
// ========================================
// Concept: Vertical scanning
// Usage: prefix = longestCommonPrefix(strs, n)
// Example: longestCommonPrefix({"flower", "flow", "flight"}) returns "fl"
string longestCommonPrefix(string strs[], int n) {
    if (n == 0) return "";
    
    string prefix = strs[0];
    
    for (int i = 1; i < n; i++) {
        int j = 0;
        while (j < prefix.length() && j < strs[i].length() && prefix[j] == strs[i][j]) {
            j++;
        }
        prefix = prefix.substr(0, j);
        if (prefix.empty()) return "";
    }
    
    return prefix;
}

// ========================================
// 7. ZIGZAG CONVERSION
// ========================================
// Concept: Pattern simulation
// Usage: result = zigzagConvert(str, numRows)
// Example: zigzagConvert("PAYPALISHIRING", 3) returns "PAHNAPLSIIGYIR"
string zigzagConvert(string str, int numRows) {
    if (numRows == 1 || numRows >= str.length()) return str;
    
    vector<string> rows(min(numRows, (int)str.length()));
    int currentRow = 0;
    bool goingDown = false;
    
    for (char ch : str) {
        rows[currentRow] += ch;
        if (currentRow == 0 || currentRow == numRows - 1) {
            goingDown = !goingDown;
        }
        currentRow += goingDown ? 1 : -1;
    }
    
    string result;
    for (string& row : rows) {
        result += row;
    }
    
    return result;
}

// ========================================
// 8. MINIMUM WINDOW SUBSTRING
// ========================================
// Concept: Sliding window
// Usage: result = minWindowSubstring(str, pattern)
// Example: minWindowSubstring("ADOBECODEBANC", "ABC") returns "BANC"
string minWindowSubstring(string str, string pattern) {
    if (str.empty() || pattern.empty()) return "";
    
    unordered_map<char, int> patternCount, windowCount;
    for (char ch : pattern) {
        patternCount[ch]++;
    }
    
    int required = patternCount.size();
    int formed = 0;
    int left = 0, right = 0;
    int minLen = INT_MAX, minLeft = 0;
    
    while (right < str.length()) {
        char ch = str[right];
        windowCount[ch]++;
        
        if (patternCount.find(ch) != patternCount.end() && 
            windowCount[ch] == patternCount[ch]) {
            formed++;
        }
        
        while (left <= right && formed == required) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minLeft = left;
            }
            
            char leftChar = str[left];
            windowCount[leftChar]--;
            if (patternCount.find(leftChar) != patternCount.end() && 
                windowCount[leftChar] < patternCount[leftChar]) {
                formed--;
            }
            left++;
        }
        
        right++;
    }
    
    return minLen == INT_MAX ? "" : str.substr(minLeft, minLen);
}

// ========================================
// 9. RABIN-KARP PATTERN MATCHING
// ========================================
// Concept: Rolling hash
// Usage: rabinKarp(text, pattern)
// Example: rabinKarp("AABAACAADAABAABA", "AABA") prints all occurrences
void rabinKarp(string text, string pattern) {
    int d = 256;  // Number of characters in alphabet
    int q = 101;  // A prime number
    int m = pattern.length();
    int n = text.length();
    int p = 0;    // Hash value for pattern
    int t = 0;    // Hash value for text
    int h = 1;
    
    // Calculate h = pow(d, m-1) % q
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }
    
    // Calculate initial hash values
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }
    
    cout << "Pattern occurrences at indices: ";
    bool found = false;
    
    // Slide the pattern over text
    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            // Check characters one by one
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << i << " ";
                found = true;
            }
        }
        
        // Calculate hash for next window
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) t += q;
        }
    }
    
    if (!found) cout << "None";
    cout << endl;
}

// ========================================
// 10. LONGEST REPEATING CHARACTER REPLACEMENT
// ========================================
// Concept: Sliding window
// Usage: length = longestRepeatingReplacement(str, k)
// Example: longestRepeatingReplacement("AABABBA", 1) returns 4
int longestRepeatingReplacement(string str, int k) {
    unordered_map<char, int> count;
    int maxCount = 0;
    int maxLen = 0;
    int start = 0;
    
    for (int end = 0; end < str.length(); end++) {
        count[str[end]]++;
        maxCount = max(maxCount, count[str[end]]);
        
        // If window size - max frequency > k, shrink window
        while (end - start + 1 - maxCount > k) {
            count[str[start]]--;
            start++;
        }
        
        maxLen = max(maxLen, end - start + 1);
    }
    
    return maxLen;
}

// ========================================
// 11. EDIT DISTANCE (LEVENSHTEIN DISTANCE)
// ========================================
// Concept: Dynamic Programming
// Usage: distance = editDistance(str1, str2)
// Example: editDistance("horse", "ros") returns 3
int editDistance(string str1, string str2) {
    int m = str1.length();
    int n = str2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j],      // Delete
                                     dp[i][j - 1],      // Insert
                                     dp[i - 1][j - 1]}); // Replace
            }
        }
    }
    
    return dp[m][n];
}

// ========================================
// 12. WILDCARD PATTERN MATCHING
// ========================================
// Concept: Dynamic Programming
// Usage: result = wildcardMatch(str, pattern)
// Example: wildcardMatch("adceb", "*a*b") returns true
bool wildcardMatch(string str, string pattern) {
    int m = str.length();
    int n = pattern.length();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    
    dp[0][0] = true;
    
    // Handle patterns like *, **, ***
    for (int j = 1; j <= n; j++) {
        if (pattern[j - 1] == '*') {
            dp[0][j] = dp[0][j - 1];
        }
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (pattern[j - 1] == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            } else if (pattern[j - 1] == '?' || str[i - 1] == pattern[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    
    return dp[m][n];
}

// ========================================
// 13. ENCODE AND DECODE STRINGS
// ========================================
// Concept: String manipulation
// Usage: encoded = encode(str), decoded = decode(encoded)
// Example: encode("aaabbcccc") returns "3a2b4c"
string encode(string str) {
    if (str.empty()) return "";
    
    string result = "";
    int count = 1;
    
    for (int i = 1; i < str.length(); i++) {
        if (str[i] == str[i - 1]) {
            count++;
        } else {
            result += to_string(count) + str[i - 1];
            count = 1;
        }
    }
    result += to_string(count) + str[str.length() - 1];
    
    return result;
}

string decode(string str) {
    string result = "";
    int i = 0;
    
    while (i < str.length()) {
        int count = 0;
        while (i < str.length() && isdigit(str[i])) {
            count = count * 10 + (str[i] - '0');
            i++;
        }
        if (i < str.length()) {
            result += string(count, str[i]);
            i++;
        }
    }
    
    return result;
}

// ========================================
// 14. WORD BREAK PROBLEM
// ========================================
// Concept: Dynamic Programming
// Usage: result = wordBreak(str, dict, dictSize)
// Example: wordBreak("leetcode", {"leet", "code"}) returns true
bool wordBreak(string str, string dict[], int dictSize) {
    unordered_set<string> wordDict(dict, dict + dictSize);
    int n = str.length();
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] && wordDict.find(str.substr(j, i - j)) != wordDict.end()) {
                dp[i] = true;
                break;
            }
        }
    }
    
    return dp[n];
}

// ========================================
// 15. PALINDROME PARTITIONING (Minimum Cuts)
// ========================================
// Concept: Dynamic Programming
// Usage: cuts = minPalindromeCuts(str)
// Example: minPalindromeCuts("aab") returns 1 (partition: "aa|b")
int minPalindromeCuts(string str) {
    int n = str.length();
    vector<vector<bool>> isPalin(n, vector<bool>(n, false));
    vector<int> cuts(n);
    
    // Every single character is a palindrome
    for (int i = 0; i < n; i++) {
        isPalin[i][i] = true;
    }
    
    // Build palindrome table
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
            if (len == 2) {
                isPalin[i][j] = (str[i] == str[j]);
            } else {
                isPalin[i][j] = (str[i] == str[j] && isPalin[i + 1][j - 1]);
            }
        }
    }
    
    // Calculate minimum cuts
    for (int i = 0; i < n; i++) {
        if (isPalin[0][i]) {
            cuts[i] = 0;
        } else {
            cuts[i] = INT_MAX;
            for (int j = 0; j < i; j++) {
                if (isPalin[j + 1][i]) {
                    cuts[i] = min(cuts[i], cuts[j] + 1);
                }
            }
        }
    }
    
    return cuts[n - 1];
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    string str;
    
    cout << "Enter a string: ";
    getline(cin, str);
    
    cout << "\n=== Initial String ===" << endl;
    display(str);
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // 1. Longest Palindromic Substring
    // string longest = longestPalindrome(str);
    // cout << "Longest palindrome: " << longest << endl;
    
    // 2. Longest Substring Without Repeating Characters
    // int len = longestUniqueSubstring(str);
    // cout << "Longest unique substring length: " << len << endl;
    
    // 3. Valid Parentheses
    // if (isValidParentheses(str)) {
    //     cout << "Valid parentheses." << endl;
    // } else {
    //     cout << "Invalid parentheses." << endl;
    // }
    
    // 4. String to Integer
    // int num = stringToInt(str);
    // cout << "Integer value: " << num << endl;
    
    // 5. Group Anagrams
    // string strs[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    // groupAnagrams(strs, 6);
    
    // 6. Longest Common Prefix
    // string strs[] = {"flower", "flow", "flight"};
    // string prefix = longestCommonPrefix(strs, 3);
    // cout << "Longest common prefix: " << prefix << endl;
    
    // 7. Zigzag Conversion
    // string zigzag = zigzagConvert(str, 3);
    // cout << "Zigzag: " << zigzag << endl;
    
    // 8. Minimum Window Substring
    // string window = minWindowSubstring(str, "ABC");
    // cout << "Minimum window: " << window << endl;
    
    // 9. Rabin-Karp Pattern Matching
    // rabinKarp(str, "ab");
    
    // 10. Longest Repeating Character Replacement
    // int len = longestRepeatingReplacement(str, 2);
    // cout << "Longest repeating replacement length: " << len << endl;
    
    // 11. Edit Distance
    // int dist = editDistance(str, "ros");
    // cout << "Edit distance: " << dist << endl;
    
    // 12. Wildcard Pattern Matching
    // if (wildcardMatch(str, "*a*b")) {
    //     cout << "Pattern matches." << endl;
    // } else {
    //     cout << "Pattern does not match." << endl;
    // }
    
    // 13. Encode and Decode
    // string encoded = encode(str);
    // cout << "Encoded: " << encoded << endl;
    // string decoded = decode(encoded);
    // cout << "Decoded: " << decoded << endl;
    
    // 14. Word Break
    // string dict[] = {"leet", "code"};
    // if (wordBreak(str, dict, 2)) {
    //     cout << "Can be segmented." << endl;
    // } else {
    //     cout << "Cannot be segmented." << endl;
    // }
    
    // 15. Minimum Palindrome Cuts
    // int cuts = minPalindromeCuts(str);
    // cout << "Minimum cuts: " << cuts << endl;
    
    return 0;
}
