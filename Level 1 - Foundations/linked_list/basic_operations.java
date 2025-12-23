/**
 * Linked List Basic Operations in Java
 * Contains insertion, deletion, and traversal operations
 */

import java.util.*;

public class basic_operations {
    
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
    // UTILITY FUNCTIONS
    // ========================================
    
    // Display linked list
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
    
    // Get length of linked list
    static int getLength(Node head) {
        int count = 0;
        Node temp = head;
        while (temp != null) {
            count++;
            temp = temp.next;
        }
        return count;
    }
    
    // ========================================
    // 1. INSERT AT BEGINNING
    // ========================================
    static Node insertAtBeginning(Node head, int value) {
        Node newNode = new Node(value);
        newNode.next = head;
        System.out.println("Inserted " + value + " at beginning.");
        return newNode;
    }
    
    // ========================================
    // 2. INSERT AT END
    // ========================================
    static Node insertAtEnd(Node head, int value) {
        Node newNode = new Node(value);
        
        if (head == null) {
            System.out.println("Inserted " + value + " at end (first node).");
            return newNode;
        }
        
        Node temp = head;
        while (temp.next != null) {
            temp = temp.next;
        }
        temp.next = newNode;
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
        
        if (position == 1) {
            newNode.next = head;
            System.out.println("Inserted " + value + " at position 1.");
            return newNode;
        }
        
        Node temp = head;
        for (int i = 1; i < position - 1 && temp != null; i++) {
            temp = temp.next;
        }
        
        if (temp == null) {
            System.out.println("Position out of bounds.");
            return head;
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
        
        Node temp = head;
        head = head.next;
        System.out.println("Deleted " + temp.data + " from beginning.");
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
        
        if (head.next == null) {
            System.out.println("Deleted " + head.data + " from end.");
            return null;
        }
        
        Node temp = head;
        while (temp.next.next != null) {
            temp = temp.next;
        }
        
        System.out.println("Deleted " + temp.next.data + " from end.");
        temp.next = null;
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
            Node temp = head;
            head = head.next;
            System.out.println("Deleted " + temp.data + " from position 1.");
            return head;
        }
        
        Node temp = head;
        for (int i = 1; i < position - 1 && temp != null; i++) {
            temp = temp.next;
        }
        
        if (temp == null || temp.next == null) {
            System.out.println("Position out of bounds.");
            return head;
        }
        
        Node nodeToDelete = temp.next;
        temp.next = nodeToDelete.next;
        System.out.println("Deleted " + nodeToDelete.data + " from position " + position + ".");
        return head;
    }
    
    // ========================================
    // 7. DELETE BY VALUE
    // ========================================
    static Node deleteByValue(Node head, int value) {
        if (head == null) {
            System.out.println("List is empty. Cannot delete.");
            return head;
        }
        
        if (head.data == value) {
            Node temp = head;
            head = head.next;
            System.out.println("Deleted " + value + " from list.");
            return head;
        }
        
        Node temp = head;
        while (temp.next != null && temp.next.data != value) {
            temp = temp.next;
        }
        
        if (temp.next == null) {
            System.out.println("Value " + value + " not found.");
            return head;
        }
        
        Node nodeToDelete = temp.next;
        temp.next = nodeToDelete.next;
        System.out.println("Deleted " + value + " from list.");
        return head;
    }
    
    // ========================================
    // 8. SEARCH FOR VALUE
    // ========================================
    static int search(Node head, int value) {
        Node temp = head;
        int position = 1;
        
        while (temp != null) {
            if (temp.data == value) {
                return position;
            }
            temp = temp.next;
            position++;
        }
        return -1;
    }
    
    // ========================================
    // 9. REVERSE LINKED LIST
    // ========================================
    static Node reverse(Node head) {
        Node prev = null;
        Node current = head;
        Node next = null;
        
        while (current != null) {
            next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }
        
        System.out.println("List reversed.");
        return prev;
    }
    
    // ========================================
    // 10. DELETE ENTIRE LIST
    // ========================================
    static Node deleteList(Node head) {
        System.out.println("Entire list deleted (dereferenced in Java).");
        return null;
    }
    
    // ========================================
    // MAIN FUNCTION
    // ========================================
    public static void main(String[] args) {
        Node head = null;
        
        System.out.println("=== Linked List Basic Operations ===");
        
        // ========================================
        // Example function calls - uncomment to use
        // ========================================
        
        // Insert at beginning
        // head = insertAtBeginning(head, 10);
        // head = insertAtBeginning(head, 5);
        // display(head);
        
        // Insert at end
        // head = insertAtEnd(head, 20);
        // head = insertAtEnd(head, 30);
        // head = insertAtEnd(head, 40);
        // display(head);
        
        // Insert at position
        // head = insertAtPosition(head, 25, 4);
        // display(head);
        
        // Get length
        // int length = getLength(head);
        // System.out.println("Length: " + length);
        
        // Search for value
        // int pos = search(head, 25);
        // if (pos != -1) {
        //     System.out.println("Value 25 found at position: " + pos);
        // } else {
        //     System.out.println("Value 25 not found.");
        // }
        
        // Delete from beginning
        // head = deleteFromBeginning(head);
        // display(head);
        
        // Delete from end
        // head = deleteFromEnd(head);
        // display(head);
        
        // Delete at position
        // head = deleteAtPosition(head, 2);
        // display(head);
        
        // Delete by value
        // head = deleteByValue(head, 30);
        // display(head);
        
        // Reverse list
        // head = reverse(head);
        // display(head);
        
        // Delete entire list
        // head = deleteList(head);
        // display(head);
    }
}
