#include <iostream>
using namespace std;

// ========================================
// DOUBLY LINKED LIST NODE STRUCTURE
// ========================================

struct DoublyNode {
    int data;
    DoublyNode* prev;
    DoublyNode* next;
    
    DoublyNode(int val) {
        data = val;
        prev = nullptr;
        next = nullptr;
    }
};

// ========================================
// UTILITY FUNCTIONS
// ========================================

// Display forward
void displayForward(DoublyNode* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    
    cout << "Forward: NULL <-> ";
    DoublyNode* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " <-> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

// Display backward
void displayBackward(DoublyNode* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    
    // Go to last node
    DoublyNode* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    
    cout << "Backward: NULL <-> ";
    while (temp != nullptr) {
        cout << temp->data << " <-> ";
        temp = temp->prev;
    }
    cout << "NULL" << endl;
}

// Get length
int getLength(DoublyNode* head) {
    int count = 0;
    DoublyNode* temp = head;
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
DoublyNode* insertAtBeginning(DoublyNode* head, int value) {
    DoublyNode* newNode = new DoublyNode(value);
    
    if (head != nullptr) {
        newNode->next = head;
        head->prev = newNode;
    }
    
    cout << "Inserted " << value << " at beginning." << endl;
    return newNode;
}

// ========================================
// 2. INSERT AT END
// ========================================
// Usage: head = insertAtEnd(head, value)
// Example: head = insertAtEnd(head, 50)
DoublyNode* insertAtEnd(DoublyNode* head, int value) {
    DoublyNode* newNode = new DoublyNode(value);
    
    if (head == nullptr) {
        cout << "Inserted " << value << " at end (first node)." << endl;
        return newNode;
    }
    
    DoublyNode* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->prev = temp;
    
    cout << "Inserted " << value << " at end." << endl;
    return head;
}

// ========================================
// 3. INSERT AT POSITION
// ========================================
// Usage: head = insertAtPosition(head, value, position)
// Example: head = insertAtPosition(head, 25, 3)
DoublyNode* insertAtPosition(DoublyNode* head, int value, int position) {
    if (position < 1) {
        cout << "Invalid position." << endl;
        return head;
    }
    
    DoublyNode* newNode = new DoublyNode(value);
    
    if (position == 1) {
        if (head != nullptr) {
            newNode->next = head;
            head->prev = newNode;
        }
        cout << "Inserted " << value << " at position 1." << endl;
        return newNode;
    }
    
    DoublyNode* temp = head;
    for (int i = 1; i < position - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    
    if (temp == nullptr) {
        cout << "Position out of bounds." << endl;
        delete newNode;
        return head;
    }
    
    newNode->next = temp->next;
    newNode->prev = temp;
    
    if (temp->next != nullptr) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    
    cout << "Inserted " << value << " at position " << position << "." << endl;
    return head;
}

// ========================================
// 4. DELETE FROM BEGINNING
// ========================================
// Usage: head = deleteFromBeginning(head)
// Example: head = deleteFromBeginning(head)
DoublyNode* deleteFromBeginning(DoublyNode* head) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return head;
    }
    
    DoublyNode* temp = head;
    head = head->next;
    
    if (head != nullptr) {
        head->prev = nullptr;
    }
    
    cout << "Deleted " << temp->data << " from beginning." << endl;
    delete temp;
    return head;
}

// ========================================
// 5. DELETE FROM END
// ========================================
// Usage: head = deleteFromEnd(head)
// Example: head = deleteFromEnd(head)
DoublyNode* deleteFromEnd(DoublyNode* head) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return head;
    }
    
    if (head->next == nullptr) {
        cout << "Deleted " << head->data << " from end." << endl;
        delete head;
        return nullptr;
    }
    
    DoublyNode* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    
    temp->prev->next = nullptr;
    cout << "Deleted " << temp->data << " from end." << endl;
    delete temp;
    
    return head;
}

// ========================================
// 6. DELETE AT POSITION
// ========================================
// Usage: head = deleteAtPosition(head, position)
// Example: head = deleteAtPosition(head, 3)
DoublyNode* deleteAtPosition(DoublyNode* head, int position) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return head;
    }
    
    if (position < 1) {
        cout << "Invalid position." << endl;
        return head;
    }
    
    if (position == 1) {
        DoublyNode* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        cout << "Deleted " << temp->data << " from position 1." << endl;
        delete temp;
        return head;
    }
    
    DoublyNode* temp = head;
    for (int i = 1; i < position && temp != nullptr; i++) {
        temp = temp->next;
    }
    
    if (temp == nullptr) {
        cout << "Position out of bounds." << endl;
        return head;
    }
    
    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }
    
    cout << "Deleted " << temp->data << " from position " << position << "." << endl;
    delete temp;
    
    return head;
}

// ========================================
// 7. REVERSE DOUBLY LINKED LIST
// ========================================
// Usage: head = reverse(head)
// Example: head = reverse(head)
DoublyNode* reverse(DoublyNode* head) {
    if (head == nullptr) return head;
    
    DoublyNode* temp = nullptr;
    DoublyNode* current = head;
    
    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    if (temp != nullptr) {
        head = temp->prev;
    }
    
    cout << "List reversed." << endl;
    return head;
}

// ========================================
// 8. FIND PAIRS WITH GIVEN SUM
// ========================================
// Concept: Two pointer technique (works on sorted DLL)
// Usage: findPairsWithSum(head, sum)
// Example: findPairsWithSum(head, 10)
void findPairsWithSum(DoublyNode* head, int sum) {
    if (head == nullptr) return;
    
    // Find last node
    DoublyNode* left = head;
    DoublyNode* right = head;
    while (right->next != nullptr) {
        right = right->next;
    }
    
    cout << "Pairs with sum " << sum << ": ";
    bool found = false;
    
    while (left != right && left->prev != right) {
        int currentSum = left->data + right->data;
        
        if (currentSum == sum) {
            cout << "(" << left->data << ", " << right->data << ") ";
            found = true;
            left = left->next;
            right = right->prev;
        } else if (currentSum < sum) {
            left = left->next;
        } else {
            right = right->prev;
        }
    }
    
    if (!found) {
        cout << "None";
    }
    cout << endl;
}

// ========================================
// 9. REMOVE DUPLICATES FROM SORTED DLL
// ========================================
// Usage: head = removeDuplicates(head)
// Example: head = removeDuplicates(head)
DoublyNode* removeDuplicates(DoublyNode* head) {
    if (head == nullptr) return head;
    
    DoublyNode* current = head;
    
    while (current != nullptr && current->next != nullptr) {
        if (current->data == current->next->data) {
            DoublyNode* temp = current->next;
            current->next = temp->next;
            if (temp->next != nullptr) {
                temp->next->prev = current;
            }
            delete temp;
        } else {
            current = current->next;
        }
    }
    
    cout << "Duplicates removed." << endl;
    return head;
}

// ========================================
// 10. ROTATE DLL BY N NODES
// ========================================
// Usage: head = rotate(head, n)
// Example: head = rotate(head, 2)
DoublyNode* rotate(DoublyNode* head, int n) {
    if (head == nullptr || n == 0) return head;
    
    DoublyNode* current = head;
    int count = 1;
    
    while (count < n && current != nullptr) {
        current = current->next;
        count++;
    }
    
    if (current == nullptr) return head;
    
    DoublyNode* nthNode = current;
    
    // Go to last node
    while (current->next != nullptr) {
        current = current->next;
    }
    
    // Make it circular
    current->next = head;
    head->prev = current;
    
    // New head
    head = nthNode->next;
    head->prev = nullptr;
    
    // Break the circle
    nthNode->next = nullptr;
    
    cout << "List rotated by " << n << " nodes." << endl;
    return head;
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    DoublyNode* head = nullptr;
    
    cout << "=== Doubly Linked List Operations ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // Insert operations
    // head = insertAtEnd(head, 10);
    // head = insertAtEnd(head, 20);
    // head = insertAtEnd(head, 30);
    // head = insertAtEnd(head, 40);
    // head = insertAtEnd(head, 50);
    // displayForward(head);
    // displayBackward(head);
    
    // Insert at beginning
    // head = insertAtBeginning(head, 5);
    // displayForward(head);
    
    // Insert at position
    // head = insertAtPosition(head, 25, 4);
    // displayForward(head);
    
    // Get length
    // int length = getLength(head);
    // cout << "Length: " << length << endl;
    
    // Delete operations
    // head = deleteFromBeginning(head);
    // displayForward(head);
    
    // head = deleteFromEnd(head);
    // displayForward(head);
    
    // head = deleteAtPosition(head, 2);
    // displayForward(head);
    
    // Reverse
    // head = reverse(head);
    // displayForward(head);
    
    // Find pairs with sum (for sorted DLL)
    // findPairsWithSum(head, 50);
    
    // Remove duplicates
    // head = removeDuplicates(head);
    // displayForward(head);
    
    // Rotate
    // head = rotate(head, 2);
    // displayForward(head);
    
    return 0;
}
