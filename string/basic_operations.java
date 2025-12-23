/**
 * String Basic Operations in Java
 * Contains standard string manipulation functions
 */

import java.util.*;

public class basic_operations {
    
    // ========================================
    // UTILITY FUNCTION
    // ========================================
    static void display(String str) {
        System.out.println("String: \"" + str + "\"");
    }
    
    // ========================================
    // 1. STRING LENGTH
    // ========================================
    static int getLength(String str) {
        return str.length();
    }
    
    // ========================================
    // 2. CONCATENATE TWO STRINGS
    // ========================================
    static String concatenate(String str1, String str2) {
        return str1 + str2;
    }
    
    // ========================================
    // 3. SUBSTRING
    // ========================================
    static String getSubstring(String str, int start, int length) {
        if (start < 0 || start >= str.length()) {
            System.out.println("Invalid start position.");
            return "";
        }
        // Java substring(beginIndex, endIndex) where endIndex is exclusive
        // Ensure we don't go out of bounds
        int end = Math.min(start + length, str.length());
        return str.substring(start, end);
    }
    
    // ========================================
    // 4. INSERT CHARACTER AT POSITION
    // ========================================
    static String insertChar(String str, int pos, char ch) {
        if (pos < 0 || pos > str.length()) {
            System.out.println("Invalid position.");
            return str;
        }
        StringBuilder sb = new StringBuilder(str);
        sb.insert(pos, ch);
        System.out.println("Character '" + ch + "' inserted at position " + pos);
        return sb.toString();
    }
    
    // ========================================
    // 5. DELETE CHARACTER AT POSITION
    // ========================================
    static String deleteChar(String str, int pos) {
        if (pos < 0 || pos >= str.length()) {
            System.out.println("Invalid position.");
            return str;
        }
        char deleted = str.charAt(pos);
        StringBuilder sb = new StringBuilder(str);
        sb.deleteCharAt(pos);
        System.out.println("Character '" + deleted + "' deleted from position " + pos);
        return sb.toString();
    }
    
    // ========================================
    // 6. REPLACE CHARACTER
    // ========================================
    static String replaceChar(String str, char oldChar, char newChar) {
        String result = str.replace(oldChar, newChar);
        System.out.println("All '" + oldChar + "' replaced with '" + newChar + "'");
        return result;
    }
    
    // ========================================
    // 7. CONVERT TO UPPERCASE
    // ========================================
    static String toUpperCase(String str) {
        String result = str.toUpperCase();
        System.out.println("Converted to uppercase.");
        return result;
    }
    
    // ========================================
    // 8. CONVERT TO LOWERCASE
    // ========================================
    static String toLowerCase(String str) {
        String result = str.toLowerCase();
        System.out.println("Converted to lowercase.");
        return result;
    }
    
    // ========================================
    // 9. REVERSE STRING
    // ========================================
    static String reverseString(String str) {
        StringBuilder sb = new StringBuilder(str);
        String result = sb.reverse().toString();
        System.out.println("String reversed.");
        return result;
    }
    
    // ========================================
    // 10. COMPARE TWO STRINGS
    // ========================================
    static int compareStrings(String str1, String str2) {
        return str1.compareTo(str2);
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
        
        // Get length
        // System.out.println("Length: " + getLength(str));
        
        // Concatenate
        // String result = concatenate(str, " World");
        // display(result);
        
        // Get substring
        // String sub = getSubstring(str, 0, 3);
        // display(sub);
        
        // Insert character
        // str = insertChar(str, 2, 'X');
        // display(str);
        
        // Delete character
        // str = deleteChar(str, 1);
        // display(str);
        
        // Replace char
        // str = replaceChar(str, 'l', 'x');
        // display(str);
        
        // To uppercase
        // str = toUpperCase(str);
        // display(str);
        
        // To lowercase
        // str = toLowerCase(str);
        // display(str);
        
        // Reverse string
        // str = reverseString(str);
        // display(str);
        
        // Compare strings
        // String str2 = "hello";
        // int cmp = compareStrings(str, str2);
        // if (cmp == 0) System.out.println("Strings are equal");
        // else if (cmp < 0) System.out.println("First string is smaller");
        // else System.out.println("First string is larger");
        
        scanner.close();
    }
}
