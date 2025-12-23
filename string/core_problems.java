/**
 * String Core Problems in Java
 * Contains standard string algorithms
 */

import java.util.*;

public class core_problems {
    
    // ========================================
    // UTILITY FUNCTION
    // ========================================
    static void display(String str) {
        System.out.println("String: \"" + str + "\"");
    }
    
    // ========================================
    // 1. CHECK PALINDROME
    // ========================================
    static boolean isPalindrome(String str) {
        int left = 0, right = str.length() - 1;
        while (left < right) {
            if (str.charAt(left) != str.charAt(right)) {
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
    static void countVowelsConsonants(String str) {
        int vowels = 0, consonants = 0;
        str = str.toLowerCase();
        for (char ch : str.toCharArray()) {
            if (ch >= 'a' && ch <= 'z') {
                if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                    vowels++;
                } else {
                    consonants++;
                }
            }
        }
        System.out.println("Vowels: " + vowels + ", Consonants: " + consonants);
    }
    
    // ========================================
    // 3. COUNT WORDS IN STRING
    // ========================================
    static int countWords(String str) {
        int count = 0;
        boolean inWord = false;
        
        for (char ch : str.toCharArray()) {
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
    static int charFrequency(String str, char ch) {
        int count = 0;
        for (char c : str.toCharArray()) {
            if (c == ch) {
                count++;
            }
        }
        return count;
    }
    
    // ========================================
    // 5. REMOVE DUPLICATES
    // ========================================
    static String removeDuplicates(String str) {
        Set<Character> seen = new HashSet<>();
        StringBuilder result = new StringBuilder();
        
        for (char ch : str.toCharArray()) {
            if (!seen.contains(ch)) {
                result.append(ch);
                seen.add(ch);
            }
        }
        System.out.println("Duplicates removed.");
        return result.toString();
    }
    
    // ========================================
    // 6. REMOVE SPACES
    // ========================================
    static String removeSpaces(String str) {
        StringBuilder result = new StringBuilder();
        for (char ch : str.toCharArray()) {
            if (ch != ' ') {
                result.append(ch);
            }
        }
        System.out.println("Spaces removed.");
        return result.toString();
    }
    
    // ========================================
    // 7. FIND FIRST NON-REPEATING CHARACTER
    // ========================================
    static char firstNonRepeating(String str) {
        Map<Character, Integer> freq = new HashMap<>();
        
        for (char ch : str.toCharArray()) {
            freq.put(ch, freq.getOrDefault(ch, 0) + 1);
        }
        
        for (char ch : str.toCharArray()) {
            if (freq.get(ch) == 1) {
                return ch;
            }
        }
        return '\0'; // No non-repeating character
    }
    
    // ========================================
    // 8. CHECK ANAGRAM
    // ========================================
    static boolean isAnagram(String str1, String str2) {
        if (str1.length() != str2.length()) {
            return false;
        }
        
        char[] arr1 = str1.toCharArray();
        char[] arr2 = str2.toCharArray();
        
        Arrays.sort(arr1);
        Arrays.sort(arr2);
        
        return Arrays.equals(arr1, arr2);
    }
    
    // ========================================
    // 9. REVERSE WORDS IN STRING
    // ========================================
    static String reverseWords(String str) {
        StringBuilder result = new StringBuilder();
        StringBuilder word = new StringBuilder();
        
        for (int i = str.length() - 1; i >= 0; i--) {
            if (str.charAt(i) == ' ') {
                if (word.length() > 0) {
                    result.append(word.reverse()).append(" ");
                    word.setLength(0);
                }
            } else {
                word.append(str.charAt(i));
            }
        }
        
        if (word.length() > 0) {
            result.append(word.reverse());
        }
        
        // Remove trailing space if any
        if (result.length() > 0 && result.charAt(result.length() - 1) == ' ') {
            result.setLength(result.length() - 1);
        }
        
        System.out.println("Words reversed.");
        return result.toString();
    }
    
    // ========================================
    // 10. FIND SUBSTRING OCCURRENCE
    // ========================================
    static int findSubstring(String str, String substr) {
        return str.indexOf(substr);
        // Returns index of first occurrence, or -1 if not found
    }
    
    // ========================================
    // 11. COUNT SUBSTRING OCCURRENCES
    // ========================================
    static int countSubstring(String str, String substr) {
        int count = 0;
        int pos = 0;
        
        while ((pos = str.indexOf(substr, pos)) != -1) {
            count++;
            pos += substr.length();
        }
        return count;
    }
    
    // ========================================
    // 12. TOGGLE CASE
    // ========================================
    static String toggleCase(String str) {
        StringBuilder result = new StringBuilder();
        for (char ch : str.toCharArray()) {
            if (Character.isUpperCase(ch)) {
                result.append(Character.toLowerCase(ch));
            } else if (Character.isLowerCase(ch)) {
                result.append(Character.toUpperCase(ch));
            } else {
                result.append(ch);
            }
        }
        System.out.println("Case toggled.");
        return result.toString();
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String str = "";
        
        System.out.print("Enter a string: ");
        if (scanner.hasNextLine()) {
            str = scanner.nextLine();
        }
        
        System.out.println("\n=== Initial String ===");
        display(str);
        
        // Example usage - uncomment to use
        
        // Check palindrome
        // if (isPalindrome(str)) {
        //     System.out.println("String is a palindrome.");
        // } else {
        //     System.out.println("String is NOT a palindrome.");
        // }
        
        // Count vowels and consonants
        // countVowelsConsonants(str);
        
        // Count words
        // int words = countWords(str);
        // System.out.println("Number of words: " + words);
        
        // Character frequency
        // int freq = charFrequency(str, 'l');
        // System.out.println("Frequency of 'l': " + freq);
        
        // Remove duplicates
        // str = removeDuplicates(str);
        // display(str);
        
        // Remove spaces
        // str = removeSpaces(str);
        // display(str);
        
        // First non-repeating character
        // char ch = firstNonRepeating(str);
        // if (ch != '\0') {
        //     System.out.println("First non-repeating character: " + ch);
        // } else {
        //     System.out.println("No non-repeating character found.");
        // }
        
        // Check anagram
        // String str2 = "silent";
        // if (isAnagram(str, str2)) {
        //     System.out.println("Strings are anagrams.");
        // } else {
        //     System.out.println("Strings are NOT anagrams.");
        // }
        
        // Reverse words
        // str = reverseWords(str);
        // display(str);
        
        // Find substring
        // int pos = findSubstring(str, "world");
        // if (pos != -1) {
        //     System.out.println("Substring found at index: " + pos);
        // } else {
        //     System.out.println("Substring not found.");
        // }
        
        // Count substring occurrences
        // int count = countSubstring(str, "ab");
        // System.out.println("Substring occurrences: " + count);
        
        // Toggle case
        // str = toggleCase(str);
        // display(str);
        
        scanner.close();
    }
}
