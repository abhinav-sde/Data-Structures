
import java.util.*;

public class basic_operations {

    static class SuffixArray {
        private String text;
        private Integer[] suffixArray;

        public SuffixArray(String text) {
            this.text = text;
            buildSuffixArray();
        }

        private void buildSuffixArray() {
            int n = text.length();
            suffixArray = new Integer[n];

            for (int i = 0; i < n; i++) {
                suffixArray[i] = i;
            }

            Arrays.sort(suffixArray, (a, b) -> text.substring(a).compareTo(text.substring(b)));
        }

        public int[] getSuffixArray() {
            return Arrays.stream(suffixArray).mapToInt(Integer::intValue).toArray();
        }

        public boolean search(String pattern) {
            int left = 0, right = suffixArray.length - 1;

            while (left <= right) {
                int mid = left + (right - left) / 2;
                int cmp = text.substring(suffixArray[mid]).compareTo(pattern);

                if (cmp < 0 && text.substring(suffixArray[mid]).startsWith(pattern)) {
                    return true;
                } else if (cmp < 0) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            return false;
        }

        public void display() {
            System.out.println("Suffix Array:");
            for (int i = 0; i < suffixArray.length; i++) {
                System.out.println(i + ": " + text.substring(suffixArray[i]));
            }
        }
    }

    public static void main(String[] args) {
        String text = "banana";
        SuffixArray sa = new SuffixArray(text);

        sa.display();
        System.out.println("\nSuffix Array: " + Arrays.toString(sa.getSuffixArray()));
    }
}
