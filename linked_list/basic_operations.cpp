#include <iostream>
using namespace std;

// ========================================
// NODE STRUCTURE
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

// Display linked list
void display(Node* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    
    cout << "List: ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

// Get length of linked list
int getLength(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// ========================================
// 1. INSERT AT BEGINNING
// ========================================
// Usage: head = insertAtBeginning(head, value)
// Example: head = insertAtBeginning(head, 10)
Node* insertAtBeginning(Node* head, int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
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
        cout << "Inserted " << value << " at end (first node)." << endl;
        return newNode;
    }
    
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
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
    
    if (position == 1) {
        newNode->next = head;
        cout << "Inserted " << value << " at position 1." << endl;
        return newNode;
    }
    
    Node* temp = head;
    for (int i = 1; i < position - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    
    if (temp == nullptr) {
        cout << "Position out of bounds." << endl;
        delete newNode;
        return head;
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
    
    Node* temp = head;
    head = head->next;
    cout << "Deleted " << temp->data << " from beginning." << endl;
    delete temp;
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
    
    if (head->next == nullptr) {
        cout << "Deleted " << head->data << " from end." << endl;
        delete head;
        return nullptr;
    }
    
    Node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    
    cout << "Deleted " << temp->next->data << " from end." << endl;
    delete temp->next;
    temp->next = nullptr;
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
        Node* temp = head;
        head = head->next;
        cout << "Deleted " << temp->data << " from position 1." << endl;
        delete temp;
        return head;
    }
    
    Node* temp = head;
    for (int i = 1; i < position - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    
    if (temp == nullptr || temp->next == nullptr) {
        cout << "Position out of bounds." << endl;
        return head;
    }
    
    Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    cout << "Deleted " << nodeToDelete->data << " from position " << position << "." << endl;
    delete nodeToDelete;
    return head;
}

// ========================================
// 7. DELETE BY VALUE
// ========================================
// Usage: head = deleteByValue(head, value)
// Example: head = deleteByValue(head, 30)
Node* deleteByValue(Node* head, int value) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return head;
    }
    
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        cout << "Deleted " << value << " from list." << endl;
        delete temp;
        return head;
    }
    
    Node* temp = head;
    while (temp->next != nullptr && temp->next->data != value) {
        temp = temp->next;
    }
    
    if (temp->next == nullptr) {
        cout << "Value " << value << " not found." << endl;
        return head;
    }
    
    Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    cout << "Deleted " << value << " from list." << endl;
    delete nodeToDelete;
    return head;
}

// ========================================
// 8. SEARCH FOR VALUE
// ========================================
// Usage: position = search(head, value)
// Example: position = search(head, 30) - returns position or -1
int search(Node* head, int value) {
    Node* temp = head;
    int position = 1;
    
    while (temp != nullptr) {
        if (temp->data == value) {
            return position;
        }
        temp = temp->next;
        position++;
    }
    
    return -1;
}

// ========================================
// 9. REVERSE LINKED LIST
// ========================================
// Usage: head = reverse(head)
// Example: head = reverse(head)
Node* reverse(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;
    
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    cout << "List reversed." << endl;
    return prev;
}

// ========================================
// 10. DELETE ENTIRE LIST
// ========================================
// Usage: head = deleteList(head)
// Example: head = deleteList(head)
Node* deleteList(Node* head) {
    Node* current = head;
    Node* next = nullptr;
    
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    
    cout << "Entire list deleted." << endl;
    return nullptr;
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    Node* head = nullptr;
    
    cout << "=== Linked List Basic Operations ===" << endl;
    
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
    // cout << "Length: " << length << endl;
    
    // Search for value
    // int pos = search(head, 25);
    // if (pos != -1) {
    //     cout << "Value 25 found at position: " << pos << endl;
    // } else {
    //     cout << "Value 25 not found." << endl;
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
    
    return 0;
}
