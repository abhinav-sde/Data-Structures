#include <iostream>
using namespace std;

// ========================================
// CIRCULAR LINKED LIST NODE STRUCTURE
// ========================================

struct Node {
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

// ========================================
// UTILITY FUNCTIONS
// ========================================

// Display circular linked list
void display(Node* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    
    cout << "List: ";
    Node* temp = head;
    do {
        cout << temp->data << " -> ";
        temp = temp->next;
    } while (temp != head);
    cout << "(back to " << head->data << ")" << endl;
}

// Get length
int getLength(Node* head) {
    if (head == nullptr) return 0;
    
    int count = 0;
    Node* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);
    
    return count;
}

// ========================================
// 1. INSERT AT BEGINNING
// ========================================
// Usage: head = insertAtBeginning(head, value)
// Example: head = insertAtBeginning(head, 10)
Node* insertAtBeginning(Node* head, int value) {
    Node* newNode = new Node(value);
    
    if (head == nullptr) {
        newNode->next = newNode;  // Point to itself
        cout << "Inserted " << value << " as first node." << endl;
        return newNode;
    }
    
    // Find last node
    Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    
    newNode->next = head;
    temp->next = newNode;
    
    cout << "Inserted " << value << " at beginning." << endl;
    return newNode;
}

// ========================================
// 2. INSERT AT END
// ========================================
// Usage: head = insertAtEnd(head, value)
// Example: head = insertAtEnd(head, 50)
Node* insertAtEnd(Node* head, int value) {
    Node* newNode = new Node(value);
    
    if (head == nullptr) {
        newNode->next = newNode;  // Point to itself
        cout << "Inserted " << value << " as first node." << endl;
        return newNode;
    }
    
    // Find last node
    Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->next = head;
    
    cout << "Inserted " << value << " at end." << endl;
    return head;
}

// ========================================
// 3. INSERT AT POSITION
// ========================================
// Usage: head = insertAtPosition(head, value, position)
// Example: head = insertAtPosition(head, 25, 3)
Node* insertAtPosition(Node* head, int value, int position) {
    if (position < 1) {
        cout << "Invalid position." << endl;
        return head;
    }
    
    Node* newNode = new Node(value);
    
    if (head == nullptr) {
        newNode->next = newNode;
        cout << "Inserted " << value << " as first node." << endl;
        return newNode;
    }
    
    if (position == 1) {
        return insertAtBeginning(head, value);
    }
    
    Node* temp = head;
    for (int i = 1; i < position - 1; i++) {
        temp = temp->next;
        if (temp == head) {
            cout << "Position out of bounds." << endl;
            delete newNode;
            return head;
        }
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
    
    cout << "Inserted " << value << " at position " << position << "." << endl;
    return head;
}

// ========================================
// 4. DELETE FROM BEGINNING
// ========================================
// Usage: head = deleteFromBeginning(head)
// Example: head = deleteFromBeginning(head)
Node* deleteFromBeginning(Node* head) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return head;
    }
    
    if (head->next == head) {
        cout << "Deleted " << head->data << " (last node)." << endl;
        delete head;
        return nullptr;
    }
    
    // Find last node
    Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    
    Node* toDelete = head;
    temp->next = head->next;
    head = head->next;
    
    cout << "Deleted " << toDelete->data << " from beginning." << endl;
    delete toDelete;
    
    return head;
}

// ========================================
// 5. DELETE FROM END
// ========================================
// Usage: head = deleteFromEnd(head)
// Example: head = deleteFromEnd(head)
Node* deleteFromEnd(Node* head) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return head;
    }
    
    if (head->next == head) {
        cout << "Deleted " << head->data << " (last node)." << endl;
        delete head;
        return nullptr;
    }
    
    // Find second last node
    Node* temp = head;
    while (temp->next->next != head) {
        temp = temp->next;
    }
    
    Node* toDelete = temp->next;
    temp->next = head;
    
    cout << "Deleted " << toDelete->data << " from end." << endl;
    delete toDelete;
    
    return head;
}

// ========================================
// 6. DELETE AT POSITION
// ========================================
// Usage: head = deleteAtPosition(head, position)
// Example: head = deleteAtPosition(head, 3)
Node* deleteAtPosition(Node* head, int position) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return head;
    }
    
    if (position < 1) {
        cout << "Invalid position." << endl;
        return head;
    }
    
    if (position == 1) {
        return deleteFromBeginning(head);
    }
    
    Node* temp = head;
    for (int i = 1; i < position - 1; i++) {
        temp = temp->next;
        if (temp == head) {
            cout << "Position out of bounds." << endl;
            return head;
        }
    }
    
    if (temp->next == head) {
        cout << "Position out of bounds." << endl;
        return head;
    }
    
    Node* toDelete = temp->next;
    temp->next = toDelete->next;
    
    cout << "Deleted " << toDelete->data << " from position " << position << "." << endl;
    delete toDelete;
    
    return head;
}

// ========================================
// 7. SPLIT INTO TWO HALVES
// ========================================
// Usage: splitList(head, head1, head2)
// Example: Splits circular list into two circular lists
void splitList(Node* head, Node** head1, Node** head2) {
    if (head == nullptr) {
        *head1 = nullptr;
        *head2 = nullptr;
        return;
    }
    
    // Find middle using slow and fast pointers
    Node* slow = head;
    Node* fast = head;
    
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // If even number of nodes
    if (fast->next->next == head) {
        fast = fast->next;
    }
    
    // Set first half
    *head1 = head;
    
    // Set second half
    if (head->next != head) {
        *head2 = slow->next;
    }
    
    // Make first half circular
    slow->next = head;
    
    // Make second half circular
    fast->next = *head2;
    
    cout << "List split into two halves." << endl;
}

// ========================================
// 8. CHECK IF CIRCULAR
// ========================================
// Usage: isCircular = checkCircular(head)
// Example: checkCircular(head) returns true
bool checkCircular(Node* head) {
    if (head == nullptr) return false;
    
    Node* temp = head->next;
    while (temp != nullptr && temp != head) {
        temp = temp->next;
    }
    
    return (temp == head);
}

// ========================================
// 9. JOSEPHUS PROBLEM
// ========================================
// Concept: Circular elimination
// Usage: survivor = josephus(n, k)
// Example: josephus(7, 3) - n people, eliminate every kth
int josephus(int n, int k) {
    // Create circular list with n nodes
    Node* head = new Node(1);
    Node* prev = head;
    
    for (int i = 2; i <= n; i++) {
        prev->next = new Node(i);
        prev = prev->next;
    }
    prev->next = head;  // Make circular
    
    Node* ptr1 = head;
    Node* ptr2 = head;
    
    while (ptr1->next != ptr1) {
        // Find k-th node
        int count = 1;
        while (count != k) {
            ptr2 = ptr1;
            ptr1 = ptr1->next;
            count++;
        }
        
        // Remove k-th node
        ptr2->next = ptr1->next;
        cout << "Eliminated: " << ptr1->data << endl;
        delete ptr1;
        ptr1 = ptr2->next;
    }
    
    int survivor = ptr1->data;
    delete ptr1;
    
    return survivor;
}

// ========================================
// 10. SORTED INSERT IN CIRCULAR LIST
// ========================================
// Usage: head = sortedInsert(head, value)
// Example: head = sortedInsert(head, 25)
Node* sortedInsert(Node* head, int value) {
    Node* newNode = new Node(value);
    
    if (head == nullptr) {
        newNode->next = newNode;
        cout << "Inserted " << value << " as first node." << endl;
        return newNode;
    }
    
    Node* current = head;
    
    // Case 1: Insert at beginning
    if (value <= head->data) {
        while (current->next != head) {
            current = current->next;
        }
        newNode->next = head;
        current->next = newNode;
        cout << "Inserted " << value << " at beginning." << endl;
        return newNode;
    }
    
    // Case 2: Insert in middle or end
    while (current->next != head && current->next->data < value) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    
    cout << "Inserted " << value << " in sorted order." << endl;
    return head;
}

// ========================================
// 11. DELETE NODE WITH GIVEN VALUE
// ========================================
// Usage: head = deleteValue(head, value)
// Example: head = deleteValue(head, 30)
Node* deleteValue(Node* head, int value) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return head;
    }
    
    // If head node is to be deleted
    if (head->data == value) {
        if (head->next == head) {
            delete head;
            cout << "Deleted " << value << " (last node)." << endl;
            return nullptr;
        }
        
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        
        temp->next = head->next;
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
        cout << "Deleted " << value << endl;
        return head;
    }
    
    // Search for node
    Node* current = head;
    while (current->next != head && current->next->data != value) {
        current = current->next;
    }
    
    if (current->next == head) {
        cout << "Value " << value << " not found." << endl;
        return head;
    }
    
    Node* toDelete = current->next;
    current->next = toDelete->next;
    delete toDelete;
    cout << "Deleted " << value << endl;
    
    return head;
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    Node* head = nullptr;
    
    cout << "=== Circular Linked List Operations ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // Insert operations
    // head = insertAtEnd(head, 10);
    // head = insertAtEnd(head, 20);
    // head = insertAtEnd(head, 30);
    // head = insertAtEnd(head, 40);
    // head = insertAtEnd(head, 50);
    // display(head);
    
    // Insert at beginning
    // head = insertAtBeginning(head, 5);
    // display(head);
    
    // Insert at position
    // head = insertAtPosition(head, 25, 4);
    // display(head);
    
    // Get length
    // int length = getLength(head);
    // cout << "Length: " << length << endl;
    
    // Delete operations
    // head = deleteFromBeginning(head);
    // display(head);
    
    // head = deleteFromEnd(head);
    // display(head);
    
    // head = deleteAtPosition(head, 2);
    // display(head);
    
    // head = deleteValue(head, 30);
    // display(head);
    
    // Check if circular
    // bool isCirc = checkCircular(head);
    // cout << "Is circular: " << (isCirc ? "Yes" : "No") << endl;
    
    // Split into two halves
    // Node* head1 = nullptr;
    // Node* head2 = nullptr;
    // splitList(head, &head1, &head2);
    // cout << "First half: "; display(head1);
    // cout << "Second half: "; display(head2);
    
    // Josephus problem
    // int survivor = josephus(7, 3);
    // cout << "Survivor: " << survivor << endl;
    
    // Sorted insert
    // head = sortedInsert(head, 15);
    // display(head);
    
    return 0;
}
