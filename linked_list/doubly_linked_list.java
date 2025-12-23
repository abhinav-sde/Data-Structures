/**
 * Doubly Linked List Operations in Java
 * Contains doubly linked list algorithms
 */

import java.util.*;

public class doubly_linked_list {
    
    // ========================================
    // DOUBLY LINKED LIST NODE STRUCTURE
    // ========================================
    static class DoublyNode {
        int data;
        DoublyNode prev;
        DoublyNode next;
        
        DoublyNode(int val) {
            data = val;
            prev = null;
            next = null;
        }
    }
    
    // ========================================
    // UTILITY FUNCTIONS
    // ========================================
    
    // Display forward
    static void displayForward(DoublyNode head) {
        if (head == null) {
            System.out.println("List is empty.");
            return;
        }
        
        System.out.print("Forward: NULL <-> ");
        DoublyNode temp = head;
        while (temp != null) {
            System.out.print(temp.data + " <-> ");
            temp = temp.next;
        }
        System.out.println("NULL");
    }
    
    // Display backward
    static void displayBackward(DoublyNode head) {
        if (head == null) {
            System.out.println("List is empty.");
            return;
        }
        
        // Go to last node
        DoublyNode temp = head;
        while (temp.next != null) {
            temp = temp.next;
        }
        
        System.out.print("Backward: NULL <-> ");
        while (temp != null) {
            System.out.print(temp.data + " <-> ");
            temp = temp.prev;
        }
        System.out.println("NULL");
    }
    
    // Get length
    static int getLength(DoublyNode head) {
        int count = 0;
        DoublyNode temp = head;
        while (temp != null) {
            count++;
            temp = temp.next;
        }
        return count;
    }
    
    // ========================================
    // 1. INSERT AT BEGINNING
    // ========================================
    static DoublyNode insertAtBeginning(DoublyNode head, int value) {
        DoublyNode newNode = new DoublyNode(value);
        
        if (head != null) {
            newNode.next = head;
            head.prev = newNode;
        }
        
        System.out.println("Inserted " + value + " at beginning.");
        return newNode;
    }
    
    // ========================================
    // 2. INSERT AT END
    // ========================================
    static DoublyNode insertAtEnd(DoublyNode head, int value) {
        DoublyNode newNode = new DoublyNode(value);
        
        if (head == null) {
            System.out.println("Inserted " + value + " at end (first node).");
            return newNode;
        }
        
        DoublyNode temp = head;
        while (temp.next != null) {
            temp = temp.next;
        }
        
        temp.next = newNode;
        newNode.prev = temp;
        
        System.out.println("Inserted " + value + " at end.");
        return head;
    }
    
    // ========================================
    // 3. INSERT AT POSITION
    // ========================================
    static DoublyNode insertAtPosition(DoublyNode head, int value, int position) {
        if (position < 1) {
            System.out.println("Invalid position.");
            return head;
        }
        
        DoublyNode newNode = new DoublyNode(value);
        
        if (position == 1) {
            if (head != null) {
                newNode.next = head;
                head.prev = newNode;
            }
            System.out.println("Inserted " + value + " at position 1.");
            return newNode;
        }
        
        DoublyNode temp = head;
        for (int i = 1; i < position - 1 && temp != null; i++) {
            temp = temp.next;
        }
        
        if (temp == null) {
            System.out.println("Position out of bounds.");
            return head;
        }
        
        newNode.next = temp.next;
        newNode.prev = temp;
        
        if (temp.next != null) {
            temp.next.prev = newNode;
        }
        temp.next = newNode;
        
        System.out.println("Inserted " + value + " at position " + position + ".");
        return head;
    }
    
    // ========================================
    // 4. DELETE FROM BEGINNING
    // ========================================
    static DoublyNode deleteFromBeginning(DoublyNode head) {
        if (head == null) {
            System.out.println("List is empty. Cannot delete.");
            return head;
        }
        
        DoublyNode temp = head;
        head = head.next;
        
        if (head != null) {
            head.prev = null;
        }
        
        System.out.println("Deleted " + temp.data + " from beginning.");
        return head;
    }
    
    // ========================================
    // 5. DELETE FROM END
    // ========================================
    static DoublyNode deleteFromEnd(DoublyNode head) {
        if (head == null) {
            System.out.println("List is empty. Cannot delete.");
            return head;
        }
        
        if (head.next == null) {
            System.out.println("Deleted " + head.data + " from end.");
            return null;
        }
        
        DoublyNode temp = head;
        while (temp.next != null) {
            temp = temp.next;
        }
        
        temp.prev.next = null;
        System.out.println("Deleted " + temp.data + " from end.");
        return head;
    }
    
    // ========================================
    // 6. DELETE AT POSITION
    // ========================================
    static DoublyNode deleteAtPosition(DoublyNode head, int position) {
        if (head == null) {
            System.out.println("List is empty. Cannot delete.");
            return head;
        }
        
        if (position < 1) {
            System.out.println("Invalid position.");
            return head;
        }
        
        if (position == 1) {
            DoublyNode temp = head;
            head = head.next;
            if (head != null) {
                head.prev = null;
            }
            System.out.println("Deleted " + temp.data + " from position 1.");
            return head;
        }
        
        DoublyNode temp = head;
        for (int i = 1; i < position && temp != null; i++) {
            temp = temp.next;
        }
        
        if (temp == null) {
            System.out.println("Position out of bounds.");
            return head;
        }
        
        if (temp.prev != null) {
            temp.prev.next = temp.next;
        }
        if (temp.next != null) {
            temp.next.prev = temp.prev;
        }
        
        System.out.println("Deleted " + temp.data + " from position " + position + ".");
        return head;
    }
    
    // ========================================
    // 7. REVERSE DOUBLY LINKED LIST
    // ========================================
    static DoublyNode reverse(DoublyNode head) {
        if (head == null) return head;
        
        DoublyNode temp = null;
        DoublyNode current = head;
        
        while (current != null) {
            temp = current.prev;
            current.prev = current.next;
            current.next = temp;
            current = current.prev;
        }
        
        if (temp != null) {
            head = temp.prev;
        }
        
        System.out.println("List reversed.");
        return head;
    }
    
    // ========================================
    // 8. FIND PAIRS WITH GIVEN SUM
    // ========================================
    static void findPairsWithSum(DoublyNode head, int sum) {
        if (head == null) return;
        
        DoublyNode left = head;
        DoublyNode right = head;
        while (right.next != null) {
            right = right.next;
        }
        
        System.out.print("Pairs with sum " + sum + ": ");
        boolean found = false;
        
        while (left != right && left.prev != right) { // left != right ensures pointers don't cross for odd length, left.prev != right ensures for even length
            // NOTE: In Java, standard object reference comparison works.
            // However, a safer check for crossing pointers in DLL is tricky without indices.
            // But since 'left' moves forward and 'right' moves backward, they will meet or cross.
             
            // Proper condition for sorted list two pointer approach
            // We need to ensure left is "before" right.
            // A simple way is to check data if strict increase, but better to just loop while their values fit.
            if (left == right) break; // Met at same node
             
             // Check if crossed (right moved past left) - harder to do directly without index or full traversal.
             // But usually for this problem, standard loop is: while (left != right && right.next != left)
             // The original C++ condition `left != right && left->prev != right` covers it.
            
            int currentSum = left.data + right.data;
            
            if (currentSum == sum) {
                System.out.print("(" + left.data + ", " + right.data + ") ");
                found = true;
                left = left.next;
                right = right.prev;
            } else if (currentSum < sum) {
                left = left.next;
            } else {
                right = right.prev;
            }
        }
        
        if (!found) {
            System.out.print("None");
        }
        System.out.println();
    }
    
    // ========================================
    // 9. REMOVE DUPLICATES FROM SORTED DLL
    // ========================================
    static DoublyNode removeDuplicates(DoublyNode head) {
        if (head == null) return head;
        
        DoublyNode current = head;
        
        while (current != null && current.next != null) {
            if (current.data == current.next.data) {
                DoublyNode temp = current.next;
                current.next = temp.next;
                if (temp.next != null) {
                    temp.next.prev = current;
                }
            } else {
                current = current.next;
            }
        }
        
        System.out.println("Duplicates removed.");
        return head;
    }
    
    // ========================================
    // 10. ROTATE DLL BY N NODES
    // ========================================
    static DoublyNode rotate(DoublyNode head, int n) {
        if (head == null || n == 0) return head;
        
        DoublyNode current = head;
        int count = 1;
        
        while (count < n && current != null) {
            current = current.next;
            count++;
        }
        
        if (current == null) return head;
        
        DoublyNode nthNode = current;
        
        while (current.next != null) {
            current = current.next;
        }
        
        current.next = head;
        head.prev = current;
        
        head = nthNode.next;
        if (head != null) head.prev = null;
        
        nthNode.next = null;
        
        System.out.println("List rotated by " + n + " nodes.");
        return head;
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Doubly Linked List Operations ===");
        
        // Example usage - uncomment to use
        
        // DoublyNode head = null;
        // head = insertAtEnd(head, 10);
        // head = insertAtEnd(head, 20);
        // head = insertAtEnd(head, 30);
        // displayForward(head);
        
        // head = insertAtBeginning(head, 5);
        // displayForward(head);
        
        // head = deleteFromEnd(head);
        // displayForward(head);
    }
}
