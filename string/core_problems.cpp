#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

// ========================================
// UTILITY FUNCTION
// ========================================

void display(string str) {
    cout << "String: \"" << str << "\"" << endl;
}

// ========================================
// 1. CHECK PALINDROME
// ========================================
// Usage: result = isPalindrome(str)
// Example: isPalindrome("racecar") returns true
bool isPalindrome(string str) {
    int left = 0, right = str.length() - 1;
    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// ========================================
// 2. COUNT VOWELS AND CONSONANTS
// ========================================
// Usage: countVowelsConsonants(str)
// Example: countVowelsConsonants("hello") prints "Vowels: 2, Consonants: 3"
void countVowelsConsonants(string str) {
    int vowels = 0, consonants = 0;
    for (char ch : str) {
        ch = tolower(ch);
        if (ch >= 'a' && ch <= 'z') {
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                vowels++;
            } else {
                consonants++;
            }
        }
    }
    cout << "Vowels: " << vowels << ", Consonants: " << consonants << endl;
}

// ========================================
// 3. COUNT WORDS IN STRING
// ========================================
// Usage: count = countWords(str)
// Example: countWords("Hello World") returns 2
int countWords(string str) {
    int count = 0;
    bool inWord = false;
    
    for (char ch : str) {
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            inWord = false;
        } else if (!inWord) {
            inWord = true;
            count++;
        }
    }
    return count;
}

// ========================================
// 4. FIND CHARACTER FREQUENCY
// ========================================
// Usage: freq = charFrequency(str, ch)
// Example: charFrequency("hello", 'l') returns 2
int charFrequency(string str, char ch) {
    int count = 0;
    for (char c : str) {
        if (c == ch) {
            count++;
        }
    }
    return count;
}

// ========================================
// 5. REMOVE DUPLICATES
// ========================================
// Usage: result = removeDuplicates(str)
// Example: removeDuplicates("hello") returns "helo"
string removeDuplicates(string str) {
    unordered_map<char, bool> seen;
    string result = "";
    
    for (char ch : str) {
        if (seen.find(ch) == seen.end()) {
            result += ch;
            seen[ch] = true;
        }
    }
    cout << "Duplicates removed." << endl;
    return result;
}

// ========================================
// 6. REMOVE SPACES
// ========================================
// Usage: result = removeSpaces(str)
// Example: removeSpaces("Hello World") returns "HelloWorld"
string removeSpaces(string str) {
    string result = "";
    for (char ch : str) {
        if (ch != ' ') {
            result += ch;
        }
    }
    cout << "Spaces removed." << endl;
    return result;
}

// ========================================
// 7. FIND FIRST NON-REPEATING CHARACTER
// ========================================
// Usage: ch = firstNonRepeating(str)
// Example: firstNonRepeating("swiss") returns 'w'
char firstNonRepeating(string str) {
    unordered_map<char, int> freq;
    
    for (char ch : str) {
        freq[ch]++;
    }
    
    for (char ch : str) {
        if (freq[ch] == 1) {
            return ch;
        }
    }
    return '\0';  // No non-repeating character
}

// ========================================
// 8. CHECK ANAGRAM
// ========================================
// Usage: result = isAnagram(str1, str2)
// Example: isAnagram("listen", "silent") returns true
bool isAnagram(string str1, string str2) {
    if (str1.length() != str2.length()) {
        return false;
    }
    
    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());
    
    return str1 == str2;
}

// ========================================
// 9. REVERSE WORDS IN STRING
// ========================================
// Usage: result = reverseWords(str)
// Example: reverseWords("Hello World") returns "World Hello"
string reverseWords(string str) {
    string result = "";
    string word = "";
    
    for (int i = str.length() - 1; i >= 0; i--) {
        if (str[i] == ' ') {
            if (!word.empty()) {
                reverse(word.begin(), word.end());
                result += word + " ";
                word = "";
            }
        } else {
            word += str[i];
        }
    }
    
    if (!word.empty()) {
        reverse(word.begin(), word.end());
        result += word;
    }
    
    // Remove trailing space if any
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    cout << "Words reversed." << endl;
    return result;
}

// ========================================
// 10. FIND SUBSTRING OCCURRENCE
// ========================================
// Usage: index = findSubstring(str, substr)
// Example: findSubstring("hello world", "world") returns 6
int findSubstring(string str, string substr) {
    return str.find(substr);
    // Returns index of first occurrence, or string::npos if not found
}

// ========================================
// 11. COUNT SUBSTRING OCCURRENCES
// ========================================
// Usage: count = countSubstring(str, substr)
// Example: countSubstring("ababab", "ab") returns 3
int countSubstring(string str, string substr) {
    int count = 0;
    size_t pos = 0;
    
    while ((pos = str.find(substr, pos)) != string::npos) {
        count++;
        pos += substr.length();
    }
    return count;
}

// ========================================
// 12. TOGGLE CASE
// ========================================
// Usage: result = toggleCase(str)
// Example: toggleCase("HeLLo") returns "hEllO"
string toggleCase(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (isupper(str[i])) {
            str[i] = tolower(str[i]);
        } else if (islower(str[i])) {
            str[i] = toupper(str[i]);
        }
    }
    cout << "Case toggled." << endl;
    return str;
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
    
    // Check palindrome
    // if (isPalindrome(str)) {
    //     cout << "String is a palindrome." << endl;
    // } else {
    //     cout << "String is NOT a palindrome." << endl;
    // }
    
    // Count vowels and consonants
    // countVowelsConsonants(str);
    
    // Count words
    // int words = countWords(str);
    // cout << "Number of words: " << words << endl;
    
    // Character frequency
    // int freq = charFrequency(str, 'l');
    // cout << "Frequency of 'l': " << freq << endl;
    
    // Remove duplicates
    // str = removeDuplicates(str);
    // display(str);
    
    // Remove spaces
    // str = removeSpaces(str);
    // display(str);
    
    // First non-repeating character
    // char ch = firstNonRepeating(str);
    // if (ch != '\0') {
    //     cout << "First non-repeating character: " << ch << endl;
    // } else {
    //     cout << "No non-repeating character found." << endl;
    // }
    
    // Check anagram
    // string str2 = "silent";
    // if (isAnagram(str, str2)) {
    //     cout << "Strings are anagrams." << endl;
    // } else {
    //     cout << "Strings are NOT anagrams." << endl;
    // }
    
    // Reverse words
    // str = reverseWords(str);
    // display(str);
    
    // Find substring
    // int pos = findSubstring(str, "world");
    // if (pos != string::npos) {
    //     cout << "Substring found at index: " << pos << endl;
    // } else {
    //     cout << "Substring not found." << endl;
    // }
    
    // Count substring occurrences
    // int count = countSubstring(str, "ab");
    // cout << "Substring occurrences: " << count << endl;
    
    // Toggle case
    // str = toggleCase(str);
    // display(str);
    
    return 0;
}
