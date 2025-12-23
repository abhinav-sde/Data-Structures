/**
 * String Advanced Problems in Java
 * Contains complex string algorithms
 */

import java.util.*;

public class advanced_problems {
    
    // ========================================
    // UTILITY FUNCTION
    // ========================================
    static void display(String str) {
        System.out.println("String: \"" + str + "\"");
    }
    
    // ========================================
    // 1. LONGEST PALINDROMIC SUBSTRING
    // ========================================
    static int lo, maxLen;

    static String longestPalindrome(String str) {
        int len = str.length();
        if (len < 2) return str;
        
        lo = 0;
        maxLen = 0;
        
        for (int i = 0; i < len - 1; i++) {
            extendPalindrome(str, i, i);     // assume odd length, try to extend Palindrome as much as possible
            extendPalindrome(str, i, i + 1); // assume even length.
        }
        return str.substring(lo, lo + maxLen);
    }
    
    static void extendPalindrome(String s, int j, int k) {
        while (j >= 0 && k < s.length() && s.charAt(j) == s.charAt(k)) {
            j--;
            k++;
        }
        if (maxLen < k - j - 1) {
            lo = j + 1;
            maxLen = k - j - 1;
        }
    }
    
    // ========================================
    // 2. LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS
    // ========================================
    static int longestUniqueSubstring(String str) {
        Map<Character, Integer> charIndex = new HashMap<>();
        int maxLen = 0;
        int start = 0;
        
        for (int end = 0; end < str.length(); end++) {
            char ch = str.charAt(end);
            if (charIndex.containsKey(ch)) {
                start = Math.max(start, charIndex.get(ch) + 1);
            }
            charIndex.put(ch, end);
            maxLen = Math.max(maxLen, end - start + 1);
        }
        
        return maxLen;
    }
    
    // ========================================
    // 3. VALID PARENTHESES
    // ========================================
    static boolean isValidParentheses(String str) {
        Stack<Character> st = new Stack<>();
        
        for (char ch : str.toCharArray()) {
            if (ch == '(' || ch == '{' || ch == '[') {
                st.push(ch);
            } else {
                if (st.isEmpty()) return false;
                
                char top = st.pop();
                if ((ch == ')' && top != '(') ||
                    (ch == '}' && top != '{') ||
                    (ch == ']' && top != '[')) {
                    return false;
                }
            }
        }
        
        return st.isEmpty();
    }
    
    // ========================================
    // 4. STRING TO INTEGER (ATOI)
    // ========================================
    static int stringToInt(String str) {
        if (str == null || str.isEmpty()) return 0;
        
        int i = 0, sign = 1;
        long result = 0;
        int n = str.length();
        
        // Skip whitespace
        while (i < n && str.charAt(i) == ' ') i++;
        if (i == n) return 0;
        
        // Check sign
        if (str.charAt(i) == '+' || str.charAt(i) == '-') {
            sign = (str.charAt(i) == '-') ? -1 : 1;
            i++;
        }
        
        // Convert digits
        while (i < n && Character.isDigit(str.charAt(i))) {
            result = result * 10 + (str.charAt(i) - '0');
            
            // Check overflow
            if (result * sign > Integer.MAX_VALUE) return Integer.MAX_VALUE;
            if (result * sign < Integer.MIN_VALUE) return Integer.MIN_VALUE;
            
            i++;
        }
        
        return (int) (result * sign);
    }
    
    // ========================================
    // 5. GROUP ANAGRAMS
    // ========================================
    static void groupAnagrams(String[] strs) {
        Map<String, List<String>> groups = new HashMap<>();
        
        for (String s : strs) {
            char[] ca = s.toCharArray();
            Arrays.sort(ca);
            String key = String.valueOf(ca);
            
            groups.putIfAbsent(key, new ArrayList<>());
            groups.get(key).add(s);
        }
        
        System.out.println("Anagram groups:");
        for (List<String> list : groups.values()) {
            System.out.println(list);
        }
    }
    
    // ========================================
    // 6. LONGEST COMMON PREFIX
    // ========================================
    static String longestCommonPrefix(String[] strs) {
        if (strs == null || strs.length == 0) return "";
        
        String prefix = strs[0];
        
        for (int i = 1; i < strs.length; i++) {
            while (strs[i].indexOf(prefix) != 0) {
                prefix = prefix.substring(0, prefix.length() - 1);
                if (prefix.isEmpty()) return "";
            }
        }
        
        return prefix;
    }
    
    // ========================================
    // 7. ZIGZAG CONVERSION
    // ========================================
    static String zigzagConvert(String str, int numRows) {
        if (numRows == 1 || numRows >= str.length()) return str;
        
        List<StringBuilder> rows = new ArrayList<>();
        for (int i = 0; i < numRows; i++) rows.add(new StringBuilder());
        
        int currentRow = 0;
        boolean goingDown = false;
        
        for (char ch : str.toCharArray()) {
            rows.get(currentRow).append(ch);
            if (currentRow == 0 || currentRow == numRows - 1) {
                goingDown = !goingDown;
            }
            currentRow += goingDown ? 1 : -1;
        }
        
        StringBuilder result = new StringBuilder();
        for (StringBuilder row : rows) {
            result.append(row);
        }
        
        return result.toString();
    }
    
    // ========================================
    // 8. MINIMUM WINDOW SUBSTRING
    // ========================================
    static String minWindowSubstring(String str, String pattern) {
        if (str.isEmpty() || pattern.isEmpty()) return "";
        
        Map<Character, Integer> patternCount = new HashMap<>();
        for (char ch : pattern.toCharArray()) {
            patternCount.put(ch, patternCount.getOrDefault(ch, 0) + 1);
        }
        
        int required = patternCount.size();
        int formed = 0;
        int left = 0, right = 0;
        int[] ans = {-1, 0, 0}; // length, left, right
        
        Map<Character, Integer> windowCount = new HashMap<>();
        
        while (right < str.length()) {
            char c = str.charAt(right);
            windowCount.put(c, windowCount.getOrDefault(c, 0) + 1);
            
            if (patternCount.containsKey(c) && 
                windowCount.get(c).intValue() == patternCount.get(c).intValue()) {
                formed++;
            }
            
            while (left <= right && formed == required) {
                c = str.charAt(left);
                
                if (ans[0] == -1 || right - left + 1 < ans[0]) {
                    ans[0] = right - left + 1;
                    ans[1] = left;
                    ans[2] = right;
                }
                
                windowCount.put(c, windowCount.get(c) - 1);
                if (patternCount.containsKey(c) && 
                    windowCount.get(c) < patternCount.get(c)) {
                    formed--;
                }
                left++;
            }
            right++;
        }
        
        return ans[0] == -1 ? "" : str.substring(ans[1], ans[2] + 1);
    }
    
    // ========================================
    // 9. RABIN-KARP PATTERN MATCHING
    // ========================================
    static void rabinKarp(String text, String pattern) {
        int d = 256;
        int q = 101;
        int m = pattern.length();
        int n = text.length();
        int p = 0;
        int t = 0;
        int h = 1;
        
        for (int i = 0; i < m - 1; i++) {
            h = (h * d) % q;
        }
        
        for (int i = 0; i < m; i++) {
            p = (d * p + pattern.charAt(i)) % q;
            t = (d * t + text.charAt(i)) % q;
        }
        
        System.out.print("Pattern occurrences at indices: ");
        boolean found = false;
        
        for (int i = 0; i <= n - m; i++) {
            if (p == t) {
                boolean match = true;
                for (int j = 0; j < m; j++) {
                    if (text.charAt(i + j) != pattern.charAt(j)) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    System.out.print(i + " ");
                    found = true;
                }
            }
            
            if (i < n - m) {
                t = (d * (t - text.charAt(i) * h) + text.charAt(i + m)) % q;
                if (t < 0) t += q;
            }
        }
        
        if (!found) System.out.print("None");
        System.out.println();
    }
    
    // ========================================
    // 10. LONGEST REPEATING CHARACTER REPLACEMENT
    // ========================================
    static int longestRepeatingReplacement(String str, int k) {
        int[] count = new int[26];
        int maxCount = 0;
        int maxLen = 0;
        int start = 0;
        
        for (int end = 0; end < str.length(); end++) {
            maxCount = Math.max(maxCount, ++count[str.charAt(end) - 'A']);
            
            while (end - start + 1 - maxCount > k) {
                count[str.charAt(start) - 'A']--;
                start++;
            }
            maxLen = Math.max(maxLen, end - start + 1);
        }
        
        return maxLen;
    }
    
    // ========================================
    // 11. EDIT DISTANCE
    // ========================================
    static int editDistance(String str1, String str2) {
        int m = str1.length();
        int n = str2.length();
        int[][] dp = new int[m + 1][n + 1];
        
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0) dp[i][j] = j;
                else if (j == 0) dp[i][j] = i;
                else if (str1.charAt(i - 1) == str2.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + Math.min(Math.min(
                        dp[i - 1][j],    // Delete
                        dp[i][j - 1]),   // Insert
                        dp[i - 1][j - 1] // Replace
                    );
                }
            }
        }
        
        return dp[m][n];
    }
    
    // ========================================
    // 12. WILDCARD PATTERN MATCHING
    // ========================================
    static boolean wildcardMatch(String str, String pattern) {
        int m = str.length();
        int n = pattern.length();
        boolean[][] dp = new boolean[m + 1][n + 1];
        
        dp[0][0] = true;
        
        for (int j = 1; j <= n; j++) {
            if (pattern.charAt(j - 1) == '*') {
                dp[0][j] = dp[0][j - 1];
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (pattern.charAt(j - 1) == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else if (pattern.charAt(j - 1) == '?' || str.charAt(i - 1) == pattern.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[m][n];
    }
    
    // ========================================
    // 13. ENCODE AND DECODE STRINGS
    // ========================================
    static String encode(String str) {
        if (str.isEmpty()) return "";
        
        StringBuilder result = new StringBuilder();
        int count = 1;
        
        for (int i = 1; i < str.length(); i++) {
            if (str.charAt(i) == str.charAt(i - 1)) {
                count++;
            } else {
                result.append(count).append(str.charAt(i - 1));
                count = 1;
            }
        }
        result.append(count).append(str.charAt(str.length() - 1));
        
        return result.toString();
    }
    
    static String decode(String str) {
        StringBuilder result = new StringBuilder();
        int i = 0;
        
        while (i < str.length()) {
            int count = 0;
            while (i < str.length() && Character.isDigit(str.charAt(i))) {
                count = count * 10 + (str.charAt(i) - '0');
                i++;
            }
            if (i < str.length()) {
                char ch = str.charAt(i);
                for (int c = 0; c < count; c++) result.append(ch);
                i++;
            }
        }
        
        return result.toString();
    }
    
    // ========================================
    // 14. WORD BREAK PROBLEM
    // ========================================
    static boolean wordBreak(String str, List<String> wordDict) {
        Set<String> wordSet = new HashSet<>(wordDict);
        int n = str.length();
        boolean[] dp = new boolean[n + 1];
        dp[0] = true;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && wordSet.contains(str.substring(j, i))) {
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
    static int minPalindromeCuts(String str) {
        int n = str.length();
        boolean[][] isPalin = new boolean[n][n];
        int[] cuts = new int[n];
        
        for (int i = 0; i < n; i++) isPalin[i][i] = true;
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i < n - len + 1; i++) {
                int j = i + len - 1;
                if (len == 2) {
                    isPalin[i][j] = (str.charAt(i) == str.charAt(j));
                } else {
                    isPalin[i][j] = (str.charAt(i) == str.charAt(j) && isPalin[i + 1][j - 1]);
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (isPalin[0][i]) {
                cuts[i] = 0;
            } else {
                cuts[i] = Integer.MAX_VALUE;
                for (int j = 0; j < i; j++) {
                    if (isPalin[j + 1][i]) {
                        cuts[i] = Math.min(cuts[i], cuts[j] + 1);
                    }
                }
            }
        }
        
        return cuts[n - 1];
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
        
        // 1. Longest Palindromic Substring
        // System.out.println("Longest palindrome: " + longestPalindrome(str));
        
        // 2. Longest Unique Substring
        // System.out.println("Longest unique substring len: " + longestUniqueSubstring(str));
        
        // 5. Group Anagrams
        // String[] strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
        // groupAnagrams(strs);
        
        // 8. Minimum Window Substring
        // System.out.println("Minimum window: " + minWindowSubstring(str, "ABC"));
        
        // 9. Rabin-Karp
        // rabinKarp(str, "ab");
        
        // 11. Edit Distance
        // System.out.println("Edit distance: " + editDistance(str, "ros"));
        
        // 13. Encode Decode
        // String encoded = encode(str);
        // System.out.println("Encoded: " + encoded);
        // System.out.println("Decoded: " + decode(encoded));
        
        scanner.close();
    }
}
