/**
 * Core Linked List Problems in Java
 * Contains standard linked list algorithms
 */

import java.util.*;

public class core_problems {
    
    // ========================================
    // NODE STRUCTURE
    // ========================================
    static class Node {
        int data;
        Node next;
        
        Node(int val) {
            data = val;
            next = null;
        }
    }
    
    // ========================================
    // UTILITY FUNCTION
    // ========================================
    static void display(Node head) {
        if (head == null) {
            System.out.println("List is empty.");
            return;
        }
        
        System.out.print("List: ");
        Node temp = head;
        while (temp != null) {
            System.out.print(temp.data + " -> ");
            temp = temp.next;
        }
        System.out.println("NULL");
    }
    
    // ========================================
    // 1. FIND MIDDLE ELEMENT
    // ========================================
    static int findMiddle(Node head) {
        if (head == null) {
            System.out.println("List is empty.");
            return -1;
        }
        
        Node slow = head;
        Node fast = head;
        
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow.data;
    }
    
    // ========================================
    // 2. DETECT CYCLE IN LINKED LIST
    // ========================================
    static boolean detectCycle(Node head) {
        if (head == null) return false;
        
        Node slow = head;
        Node fast = head;
        
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) return true;
        }
        return false;
    }
    
    // ========================================
    // 3. REMOVE DUPLICATES FROM SORTED LIST
    // ========================================
    static Node removeDuplicatesSorted(Node head) {
        if (head == null) return head;
        
        Node current = head;
        while (current != null && current.next != null) {
            if (current.data == current.next.data) {
                current.next = current.next.next;
            } else {
                current = current.next;
            }
        }
        System.out.println("Duplicates removed from sorted list.");
        return head;
    }
    
    // ========================================
    // 4. REMOVE DUPLICATES FROM UNSORTED LIST
    // ========================================
    static Node removeDuplicatesUnsorted(Node head) {
        if (head == null) return head;
        
        Set<Integer> seen = new HashSet<>();
        Node current = head;
        Node prev = null;
        
        while (current != null) {
            if (seen.contains(current.data)) {
                prev.next = current.next;
            } else {
                seen.add(current.data);
                prev = current;
            }
            current = current.next;
        }
        System.out.println("Duplicates removed from unsorted list.");
        return head;
    }
    
    // ========================================
    // 5. FIND NTH NODE FROM END
    // ========================================
    static int nthFromEnd(Node head, int n) {
        if (head == null) {
            System.out.println("List is empty.");
            return -1;
        }
        
        Node first = head;
        Node second = head;
        
        for (int i = 0; i < n; i++) {
            if (first == null) {
                System.out.println("List has fewer than " + n + " nodes.");
                return -1;
            }
            first = first.next;
        }
        
        while (first != null) {
            first = first.next;
            second = second.next;
        }
        return second.data;
    }
    
    // ========================================
    // 6. CHECK IF PALINDROME
    // ========================================
    static boolean checkPalindrome(Node head) {
        if (head == null || head.next == null) return true;
        
        Node slow = head;
        Node fast = head;
        
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        
        Node prev = null;
        Node current = slow.next;
        Node next = null;
        
        while (current != null) {
            next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }
        
        Node firstHalf = head;
        Node secondHalf = prev;
        
        while (secondHalf != null) {
            if (firstHalf.data != secondHalf.data) return false;
            firstHalf = firstHalf.next;
            secondHalf = secondHalf.next;
        }
        return true;
    }
    
    // ========================================
    // 7. MERGE TWO SORTED LISTS
    // ========================================
    static Node mergeSorted(Node head1, Node head2) {
        if (head1 == null) return head2;
        if (head2 == null) return head1;
        
        Node result;
        if (head1.data <= head2.data) {
            result = head1;
            result.next = mergeSorted(head1.next, head2);
        } else {
            result = head2;
            result.next = mergeSorted(head1, head2.next);
        }
        return result;
    }
    
    // ========================================
    // 8. INTERSECTION POINT OF TWO LISTS
    // ========================================
    static Node findIntersection(Node head1, Node head2) {
        if (head1 == null || head2 == null) return null;
        
        Node ptr1 = head1;
        Node ptr2 = head2;
        
        while (ptr1 != ptr2) {
            ptr1 = (ptr1 == null) ? head2 : ptr1.next;
            ptr2 = (ptr2 == null) ? head1 : ptr2.next;
        }
        return ptr1;
    }
    
    // ========================================
    // 9. REVERSE IN GROUPS OF K
    // ========================================
    static Node reverseInGroups(Node head, int k) {
        if (head == null) return null;
        
        Node current = head;
        Node next = null;
        Node prev = null;
        int count = 0;
        
        while (current != null && count < k) {
            next = current.next;
            current.next = prev;
            prev = current;
            current = next;
            count++;
        }
        
        if (next != null) {
            head.next = reverseInGroups(next, k);
        }
        return prev;
    }
    
    // ========================================
    // 10. ROTATE LIST BY K POSITIONS
    // ========================================
    static Node rotateList(Node head, int k) {
        if (head == null || k == 0) return head;
        
        Node temp = head;
        int length = 1;
        while (temp.next != null) {
            temp = temp.next;
            length++;
        }
        
        temp.next = head;
        k = k % length;
        int stepsToNewHead = length - k;
        
        Node newTail = head;
        for (int i = 1; i < stepsToNewHead; i++) {
            newTail = newTail.next;
        }
        
        Node newHead = newTail.next;
        newTail.next = null;
        System.out.println("List rotated by " + k + " positions.");
        return newHead;
    }
    
    // ========================================
    // 11. SEGREGATE EVEN AND ODD NODES
    // ========================================
    static Node segregateEvenOdd(Node head) {
        if (head == null) return head;
        
        Node evenStart = null, evenEnd = null;
        Node oddStart = null, oddEnd = null;
        Node current = head;
        
        while (current != null) {
            int val = current.data;
            if (val % 2 == 0) {
                if (evenStart == null) {
                    evenStart = current;
                    evenEnd = evenStart;
                } else {
                    evenEnd.next = current;
                    evenEnd = evenEnd.next;
                }
            } else {
                if (oddStart == null) {
                    oddStart = current;
                    oddEnd = oddStart;
                } else {
                    oddEnd.next = current;
                    oddEnd = oddEnd.next;
                }
            }
            current = current.next;
        }
        
        if (evenStart == null || oddStart == null) return head;
        
        evenEnd.next = oddStart;
        oddEnd.next = null;
        System.out.println("Even and odd nodes segregated.");
        return evenStart;
    }
    
    // ========================================
    // 12. ADD TWO NUMBERS REPRESENTED BY LISTS
    // ========================================
    static Node addTwoNumbers(Node head1, Node head2) {
        Node result = null;
        Node tail = null;
        int carry = 0;
        
        while (head1 != null || head2 != null || carry != 0) {
            int sum = carry;
            if (head1 != null) { sum += head1.data; head1 = head1.next; }
            if (head2 != null) { sum += head2.data; head2 = head2.next; }
            
            carry = sum / 10;
            Node newNode = new Node(sum % 10);
            
            if (result == null) {
                result = newNode;
                tail = result;
            } else {
                tail.next = newNode;
                tail = tail.next;
            }
        }
        return result;
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Linked List Core Problems ===");
        
        // Example usage - uncomment to test
        
        // Node head = new Node(1);
        // head.next = new Node(2);
        // head.next.next = new Node(3);
        // head.next.next.next = new Node(4);
        // head.next.next.next.next = new Node(5);
        // display(head);
        
        // int middle = findMiddle(head);
        // System.out.println("Middle element: " + middle);
    }
}
