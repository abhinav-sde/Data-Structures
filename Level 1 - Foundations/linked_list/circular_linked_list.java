/**
 * Circular Linked List Operations in Java
 * Contains circular linked list algorithms
 */

import java.util.*;

public class circular_linked_list {
    
    // ========================================
    // CIRCULAR LINKED LIST NODE STRUCTURE
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
    // UTILITY FUNCTIONS
    // ========================================
    
    // Display circular linked list
    static void display(Node head) {
        if (head == null) {
            System.out.println("List is empty.");
            return;
        }
        
        System.out.print("List: ");
        Node temp = head;
        do {
            System.out.print(temp.data + " -> ");
            temp = temp.next;
        } while (temp != head);
        System.out.println("(back to " + head.data + ")");
    }
    
    // Get length
    static int getLength(Node head) {
        if (head == null) return 0;
        
        int count = 0;
        Node temp = head;
        do {
            count++;
            temp = temp.next;
        } while (temp != head);
        
        return count;
    }
    
    // ========================================
    // 1. INSERT AT BEGINNING
    // ========================================
    static Node insertAtBeginning(Node head, int value) {
        Node newNode = new Node(value);
        
        if (head == null) {
            newNode.next = newNode; // Point to itself
            System.out.println("Inserted " + value + " as first node.");
            return newNode;
        }
        
        // Find last node
        Node temp = head;
        while (temp.next != head) {
            temp = temp.next;
        }
        
        newNode.next = head;
        temp.next = newNode;
        
        System.out.println("Inserted " + value + " at beginning.");
        return newNode;
    }
    
    // ========================================
    // 2. INSERT AT END
    // ========================================
    static Node insertAtEnd(Node head, int value) {
        Node newNode = new Node(value);
        
        if (head == null) {
            newNode.next = newNode; // Point to itself
            System.out.println("Inserted " + value + " as first node.");
            return newNode;
        }
        
        // Find last node
        Node temp = head;
        while (temp.next != head) {
            temp = temp.next;
        }
        
        temp.next = newNode;
        newNode.next = head;
        
        System.out.println("Inserted " + value + " at end.");
        return head;
    }
    
    // ========================================
    // 3. INSERT AT POSITION
    // ========================================
    static Node insertAtPosition(Node head, int value, int position) {
        if (position < 1) {
            System.out.println("Invalid position.");
            return head;
        }
        
        Node newNode = new Node(value);
        
        if (head == null) {
            newNode.next = newNode;
            System.out.println("Inserted " + value + " as first node.");
            return newNode;
        }
        
        if (position == 1) {
            return insertAtBeginning(head, value);
        }
        
        Node temp = head;
        for (int i = 1; i < position - 1; i++) {
            temp = temp.next;
            if (temp == head) {
                System.out.println("Position out of bounds.");
                return head;
            }
        }
        
        newNode.next = temp.next;
        temp.next = newNode;
        
        System.out.println("Inserted " + value + " at position " + position + ".");
        return head;
    }
    
    // ========================================
    // 4. DELETE FROM BEGINNING
    // ========================================
    static Node deleteFromBeginning(Node head) {
        if (head == null) {
            System.out.println("List is empty. Cannot delete.");
            return head;
        }
        
        if (head.next == head) {
            System.out.println("Deleted " + head.data + " (last node).");
            return null;
        }
        
        // Find last node
        Node temp = head;
        while (temp.next != head) {
            temp = temp.next;
        }
        
        Node toDelete = head;
        temp.next = head.next;
        head = head.next;
        
        System.out.println("Deleted " + toDelete.data + " from beginning.");
        return head;
    }
    
    // ========================================
    // 5. DELETE FROM END
    // ========================================
    static Node deleteFromEnd(Node head) {
        if (head == null) {
            System.out.println("List is empty. Cannot delete.");
            return head;
        }
        
        if (head.next == head) {
            System.out.println("Deleted " + head.data + " (last node).");
            return null;
        }
        
        // Find second last node
        Node temp = head;
        while (temp.next.next != head) {
            temp = temp.next;
        }
        
        Node toDelete = temp.next;
        temp.next = head;
        
        System.out.println("Deleted " + toDelete.data + " from end.");
        return head;
    }
    
    // ========================================
    // 6. DELETE AT POSITION
    // ========================================
    static Node deleteAtPosition(Node head, int position) {
        if (head == null) {
            System.out.println("List is empty. Cannot delete.");
            return head;
        }
        
        if (position < 1) {
            System.out.println("Invalid position.");
            return head;
        }
        
        if (position == 1) {
            return deleteFromBeginning(head);
        }
        
        Node temp = head;
        for (int i = 1; i < position - 1; i++) {
            temp = temp.next;
            if (temp == head) {
                System.out.println("Position out of bounds.");
                return head;
            }
        }
        
        if (temp.next == head) {
            System.out.println("Position out of bounds.");
            return head;
        }
        
        Node toDelete = temp.next;
        temp.next = toDelete.next;
        
        System.out.println("Deleted " + toDelete.data + " from position " + position + ".");
        return head;
    }
    
    // ========================================
    // 7. SPLIT INTO TWO HALVES
    // ========================================
    static Node[] splitList(Node head) {
        Node[] result = new Node[2]; // Index 0 for head1, Index 1 for head2
        
        if (head == null) return result;
        
        Node slow = head;
        Node fast = head;
        
        while (fast.next != head && fast.next.next != head) {
            slow = slow.next;
            fast = fast.next.next;
        }
        
        if (fast.next.next == head) {
            fast = fast.next;
        }
        
        result[0] = head;
        if (head.next != head) {
            result[1] = slow.next;
        }
        
        slow.next = head;
        fast.next = result[1];
        
        System.out.println("List split into two halves.");
        return result;
    }
    
    // ========================================
    // 8. CHECK IF CIRCULAR
    // ========================================
    static boolean checkCircular(Node head) {
        if (head == null) return false;
        
        Node temp = head.next;
        while (temp != null && temp != head) {
            temp = temp.next;
        }
        return (temp == head);
    }
    
    // ========================================
    // 9. JOSEPHUS PROBLEM
    // ========================================
    static int josephus(int n, int k) {
        Node head = new Node(1);
        Node prev = head;
        
        for (int i = 2; i <= n; i++) {
            prev.next = new Node(i);
            prev = prev.next;
        }
        prev.next = head;
        
        Node ptr1 = head;
        Node ptr2 = head;
        
        while (ptr1.next != ptr1) {
            int count = 1;
            while (count != k) {
                ptr2 = ptr1;
                ptr1 = ptr1.next;
                count++;
            }
            
            ptr2.next = ptr1.next;
            System.out.println("Eliminated: " + ptr1.data);
            ptr1 = ptr2.next;
        }
        
        return ptr1.data;
    }
    
    // ========================================
    // 10. SORTED INSERT IN CIRCULAR LIST
    // ========================================
    static Node sortedInsert(Node head, int value) {
        Node newNode = new Node(value);
        
        if (head == null) {
            newNode.next = newNode;
            System.out.println("Inserted " + value + " as first node.");
            return newNode;
        }
        
        Node current = head;
        
        // Case 1: Insert at beginning
        if (value <= head.data) {
            while (current.next != head) {
                current = current.next;
            }
            newNode.next = head;
            current.next = newNode;
            System.out.println("Inserted " + value + " at beginning.");
            return newNode;
        }
        
        // Case 2: Insert in middle or end
        while (current.next != head && current.next.data < value) {
            current = current.next;
        }
        
        newNode.next = current.next;
        current.next = newNode;
        
        System.out.println("Inserted " + value + " in sorted order.");
        return head;
    }
    
    // ========================================
    // 11. DELETE NODE WITH GIVEN VALUE
    // ========================================
    static Node deleteValue(Node head, int value) {
        if (head == null) {
            System.out.println("List is empty.");
            return head;
        }
        
        if (head.data == value) {
            if (head.next == head) {
                System.out.println("Deleted " + value + " (last node).");
                return null;
            }
            
            Node temp = head;
            while (temp.next != head) {
                temp = temp.next;
            }
            
            temp.next = head.next;
            head = head.next;
            System.out.println("Deleted " + value);
            return head;
        }
        
        Node current = head;
        while (current.next != head && current.next.data != value) {
            current = current.next;
        }
        
        if (current.next == head) {
            System.out.println("Value " + value + " not found.");
            return head;
        }
        
        Node toDelete = current.next;
        current.next = toDelete.next;
        System.out.println("Deleted " + value);
        
        return head;
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        System.out.println("=== Circular Linked List Operations ===");
        
        // Example usage - uncomment to test
        
        // Node head = null;
        // head = insertAtEnd(head, 10);
        // head = insertAtEnd(head, 20);
        // head = insertAtEnd(head, 30);
        // display(head);
        
        // head = insertAtBeginning(head, 5);
        // display(head);
        
        // head = deleteFromBeginning(head);
        // display(head);
    }
}
