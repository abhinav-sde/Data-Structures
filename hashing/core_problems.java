import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class core_problems {

    // Problem 1: Two Sum
    public static int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (map.containsKey(complement)) {
                return new int[] { map.get(complement), i };
            }
            map.put(nums[i], i);
        }
        return new int[] {};
    }

    // Problem 2: First Repeated Character
    public static char firstRepeatedChar(String s) {
        Set<Character> seen = new HashSet<>();
        for (char c : s.toCharArray()) {
            if (seen.contains(c))
                return c;
            seen.add(c);
        }
        return '\0';
    }

    public static void main(String[] args) {
        // Test Two Sum
        int[] nums = { 2, 7, 11, 15 };
        int target = 9;
        int[] result = twoSum(nums, target);
        if (result.length == 2) {
            System.out.println("Two Sum Indices: " + result[0] + ", " + result[1]);
        } else {
            System.out.println("Two Sum not found");
        }

        // Test First Repeated
        String s = "abacaba";
        System.out.println("First Repeated: " + firstRepeatedChar(s));
    }
}
