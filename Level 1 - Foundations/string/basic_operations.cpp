#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// ========================================
// UTILITY FUNCTION
// ========================================

void display(string str) {
    cout << "String: \"" << str << "\"" << endl;
}

// ========================================
// 1. STRING LENGTH
// ========================================
// Usage: len = getLength(str)
// Example: getLength("hello") returns 5
int getLength(string str) {
    return str.length();
}

// ========================================
// 2. CONCATENATE TWO STRINGS
// ========================================
// Usage: result = concatenate(str1, str2)
// Example: concatenate("Hello", "World") returns "HelloWorld"
string concatenate(string str1, string str2) {
    return str1 + str2;
}

// ========================================
// 3. SUBSTRING
// ========================================
// Usage: result = getSubstring(str, start, length)
// Example: getSubstring("Hello", 1, 3) returns "ell"
string getSubstring(string str, int start, int length) {
    if (start < 0 || start >= str.length()) {
        cout << "Invalid start position." << endl;
        return "";
    }
    return str.substr(start, length);
}

// ========================================
// 4. INSERT CHARACTER AT POSITION
// ========================================
// Usage: result = insertChar(str, pos, ch)
// Example: insertChar("Helo", 3, 'l') returns "Hello"
string insertChar(string str, int pos, char ch) {
    if (pos < 0 || pos > str.length()) {
        cout << "Invalid position." << endl;
        return str;
    }
    str.insert(pos, 1, ch);
    cout << "Character '" << ch << "' inserted at position " << pos << endl;
    return str;
}

// ========================================
// 5. DELETE CHARACTER AT POSITION
// ========================================
// Usage: result = deleteChar(str, pos)
// Example: deleteChar("Hello", 1) returns "Hllo"
string deleteChar(string str, int pos) {
    if (pos < 0 || pos >= str.length()) {
        cout << "Invalid position." << endl;
        return str;
    }
    char deleted = str[pos];
    str.erase(pos, 1);
    cout << "Character '" << deleted << "' deleted from position " << pos << endl;
    return str;
}

// ========================================
// 6. REPLACE CHARACTER
// ========================================
// Usage: result = replaceChar(str, oldChar, newChar)
// Example: replaceChar("Hello", 'l', 'x') returns "Hexxo"
string replaceChar(string str, char oldChar, char newChar) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == oldChar) {
            str[i] = newChar;
        }
    }
    cout << "All '" << oldChar << "' replaced with '" << newChar << "'" << endl;
    return str;
}

// ========================================
// 7. CONVERT TO UPPERCASE
// ========================================
// Usage: result = toUpperCase(str)
// Example: toUpperCase("hello") returns "HELLO"
string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    cout << "Converted to uppercase." << endl;
    return str;
}

// ========================================
// 8. CONVERT TO LOWERCASE
// ========================================
// Usage: result = toLowerCase(str)
// Example: toLowerCase("HELLO") returns "hello"
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    cout << "Converted to lowercase." << endl;
    return str;
}

// ========================================
// 9. REVERSE STRING
// ========================================
// Usage: result = reverseString(str)
// Example: reverseString("hello") returns "olleh"
string reverseString(string str) {
    reverse(str.begin(), str.end());
    cout << "String reversed." << endl;
    return str;
}

// ========================================
// 10. COMPARE TWO STRINGS
// ========================================
// Usage: result = compareStrings(str1, str2)
// Example: compareStrings("abc", "abc") returns 0 (equal)
int compareStrings(string str1, string str2) {
    return str1.compare(str2);
    // Returns: 0 if equal, <0 if str1 < str2, >0 if str1 > str2
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
    
    // Get length
    // int len = getLength(str);
    // cout << "Length: " << len << endl;
    
    // Concatenate
    // string result = concatenate(str, " World");
    // display(result);
    
    // Get substring
    // string sub = getSubstring(str, 0, 3);
    // display(sub);
    
    // Insert character at position 2
    // str = insertChar(str, 2, 'X');
    // display(str);
    
    // Delete character at position 1
    // str = deleteChar(str, 1);
    // display(str);
    
    // Replace 'l' with 'x'
    // str = replaceChar(str, 'l', 'x');
    // display(str);
    
    // Convert to uppercase
    // str = toUpperCase(str);
    // display(str);
    
    // Convert to lowercase
    // str = toLowerCase(str);
    // display(str);
    
    // Reverse string
    // str = reverseString(str);
    // display(str);
    
    // Compare strings
    // string str2 = "hello";
    // int cmp = compareStrings(str, str2);
    // if (cmp == 0) cout << "Strings are equal" << endl;
    // else if (cmp < 0) cout << "First string is smaller" << endl;
    // else cout << "First string is larger" << endl;
    
    return 0;
}
