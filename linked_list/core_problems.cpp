#include <iostream>
#include <unordered_set>
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
// UTILITY FUNCTION
// ========================================

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

// ========================================
// 1. FIND MIDDLE ELEMENT
// ========================================
// Concept: Slow and fast pointer (Floyd's algorithm)
// Usage: middle = findMiddle(head)
// Example: List: 1->2->3->4->5, returns 3
int findMiddle(Node* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return -1;
    }
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow->data;
}

// ========================================
// 2. DETECT CYCLE IN LINKED LIST
// ========================================
// Concept: Floyd's Cycle Detection (Tortoise and Hare)
// Usage: hasCycle = detectCycle(head)
// Example: Returns true if cycle exists
bool detectCycle(Node* head) {
    if (head == nullptr) return false;
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return true;
        }
    }
    
    return false;
}

// ========================================
// 3. REMOVE DUPLICATES FROM SORTED LIST
// ========================================
// Usage: head = removeDuplicatesSorted(head)
// Example: 1->1->2->3->3 becomes 1->2->3
Node* removeDuplicatesSorted(Node* head) {
    if (head == nullptr) return head;
    
    Node* current = head;
    
    while (current != nullptr && current->next != nullptr) {
        if (current->data == current->next->data) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
    
    cout << "Duplicates removed from sorted list." << endl;
    return head;
}

// ========================================
// 4. REMOVE DUPLICATES FROM UNSORTED LIST
// ========================================
// Concept: Hashing
// Usage: head = removeDuplicatesUnsorted(head)
// Example: 1->3->2->1->4->2 becomes 1->3->2->4
Node* removeDuplicatesUnsorted(Node* head) {
    if (head == nullptr) return head;
    
    unordered_set<int> seen;
    Node* current = head;
    Node* prev = nullptr;
    
    while (current != nullptr) {
        if (seen.find(current->data) != seen.end()) {
            prev->next = current->next;
            delete current;
            current = prev->next;
        } else {
            seen.insert(current->data);
            prev = current;
            current = current->next;
        }
    }
    
    cout << "Duplicates removed from unsorted list." << endl;
    return head;
}

// ========================================
// 5. FIND NTH NODE FROM END
// ========================================
// Concept: Two pointer technique
// Usage: value = nthFromEnd(head, n)
// Example: nthFromEnd(head, 2) returns 2nd node from end
int nthFromEnd(Node* head, int n) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return -1;
    }
    
    Node* first = head;
    Node* second = head;
    
    // Move first pointer n steps ahead
    for (int i = 0; i < n; i++) {
        if (first == nullptr) {
            cout << "List has fewer than " << n << " nodes." << endl;
            return -1;
        }
        first = first->next;
    }
    
    // Move both pointers until first reaches end
    while (first != nullptr) {
        first = first->next;
        second = second->next;
    }
    
    return second->data;
}

// ========================================
// 6. CHECK IF PALINDROME
// ========================================
// Concept: Reverse second half and compare
// Usage: isPalindrome = checkPalindrome(head)
// Example: 1->2->3->2->1 returns true
bool checkPalindrome(Node* head) {
    if (head == nullptr || head->next == nullptr) return true;
    
    // Find middle
    Node* slow = head;
    Node* fast = head;
    
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Reverse second half
    Node* prev = nullptr;
    Node* current = slow->next;
    Node* next = nullptr;
    
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    // Compare
    Node* firstHalf = head;
    Node* secondHalf = prev;
    
    while (secondHalf != nullptr) {
        if (firstHalf->data != secondHalf->data) {
            return false;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }
    
    return true;
}

// ========================================
// 7. MERGE TWO SORTED LISTS
// ========================================
// Usage: merged = mergeSorted(head1, head2)
// Example: Merges two sorted lists into one sorted list
Node* mergeSorted(Node* head1, Node* head2) {
    if (head1 == nullptr) return head2;
    if (head2 == nullptr) return head1;
    
    Node* result = nullptr;
    
    if (head1->data <= head2->data) {
        result = head1;
        result->next = mergeSorted(head1->next, head2);
    } else {
        result = head2;
        result->next = mergeSorted(head1, head2->next);
    }
    
    return result;
}

// ========================================
// 8. INTERSECTION POINT OF TWO LISTS
// ========================================
// Concept: Two pointer technique
// Usage: intersection = findIntersection(head1, head2)
// Example: Returns node where two lists intersect or nullptr
Node* findIntersection(Node* head1, Node* head2) {
    if (head1 == nullptr || head2 == nullptr) return nullptr;
    
    Node* ptr1 = head1;
    Node* ptr2 = head2;
    
    while (ptr1 != ptr2) {
        ptr1 = (ptr1 == nullptr) ? head2 : ptr1->next;
        ptr2 = (ptr2 == nullptr) ? head1 : ptr2->next;
    }
    
    return ptr1;
}

// ========================================
// 9. REVERSE IN GROUPS OF K
// ========================================
// Usage: head = reverseInGroups(head, k)
// Example: 1->2->3->4->5->6, k=2 becomes 2->1->4->3->6->5
Node* reverseInGroups(Node* head, int k) {
    if (head == nullptr) return nullptr;
    
    Node* current = head;
    Node* next = nullptr;
    Node* prev = nullptr;
    int count = 0;
    
    // Reverse first k nodes
    while (current != nullptr && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
    
    // Recursively reverse remaining list
    if (next != nullptr) {
        head->next = reverseInGroups(next, k);
    }
    
    return prev;
}

// ========================================
// 10. ROTATE LIST BY K POSITIONS
// ========================================
// Usage: head = rotateList(head, k)
// Example: 1->2->3->4->5, k=2 becomes 4->5->1->2->3
Node* rotateList(Node* head, int k) {
    if (head == nullptr || k == 0) return head;
    
    // Find length
    Node* temp = head;
    int length = 1;
    while (temp->next != nullptr) {
        temp = temp->next;
        length++;
    }
    
    // Make circular
    temp->next = head;
    
    // Find new head
    k = k % length;
    int stepsToNewHead = length - k;
    
    Node* newTail = head;
    for (int i = 1; i < stepsToNewHead; i++) {
        newTail = newTail->next;
    }
    
    Node* newHead = newTail->next;
    newTail->next = nullptr;
    
    cout << "List rotated by " << k << " positions." << endl;
    return newHead;
}

// ========================================
// 11. SEGREGATE EVEN AND ODD NODES
// ========================================
// Usage: head = segregateEvenOdd(head)
// Example: 1->2->3->4->5 becomes 2->4->1->3->5
Node* segregateEvenOdd(Node* head) {
    if (head == nullptr) return head;
    
    Node* evenStart = nullptr;
    Node* evenEnd = nullptr;
    Node* oddStart = nullptr;
    Node* oddEnd = nullptr;
    
    Node* current = head;
    
    while (current != nullptr) {
        int val = current->data;
        
        if (val % 2 == 0) {
            if (evenStart == nullptr) {
                evenStart = current;
                evenEnd = evenStart;
            } else {
                evenEnd->next = current;
                evenEnd = evenEnd->next;
            }
        } else {
            if (oddStart == nullptr) {
                oddStart = current;
                oddEnd = oddStart;
            } else {
                oddEnd->next = current;
                oddEnd = oddEnd->next;
            }
        }
        
        current = current->next;
    }
    
    if (evenStart == nullptr || oddStart == nullptr) {
        return head;
    }
    
    evenEnd->next = oddStart;
    oddEnd->next = nullptr;
    
    cout << "Even and odd nodes segregated." << endl;
    return evenStart;
}

// ========================================
// 12. ADD TWO NUMBERS REPRESENTED BY LISTS
// ========================================
// Usage: result = addTwoNumbers(head1, head2)
// Example: 2->4->3 + 5->6->4 = 7->0->8 (342 + 465 = 807)
Node* addTwoNumbers(Node* head1, Node* head2) {
    Node* result = nullptr;
    Node* tail = nullptr;
    int carry = 0;
    
    while (head1 != nullptr || head2 != nullptr || carry != 0) {
        int sum = carry;
        
        if (head1 != nullptr) {
            sum += head1->data;
            head1 = head1->next;
        }
        
        if (head2 != nullptr) {
            sum += head2->data;
            head2 = head2->next;
        }
        
        carry = sum / 10;
        Node* newNode = new Node(sum % 10);
        
        if (result == nullptr) {
            result = newNode;
            tail = result;
        } else {
            tail->next = newNode;
            tail = tail->next;
        }
    }
    
    return result;
}

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    Node* head = nullptr;
    
    cout << "=== Linked List Core Problems ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // Create a sample list: 1->2->3->4->5
    // head = new Node(1);
    // head->next = new Node(2);
    // head->next->next = new Node(3);
    // head->next->next->next = new Node(4);
    // head->next->next->next->next = new Node(5);
    // display(head);
    
    // 1. Find middle
    // int middle = findMiddle(head);
    // cout << "Middle element: " << middle << endl;
    
    // 2. Detect cycle
    // bool hasCycle = detectCycle(head);
    // cout << "Has cycle: " << (hasCycle ? "Yes" : "No") << endl;
    
    // 3. Remove duplicates from sorted list
    // head = removeDuplicatesSorted(head);
    // display(head);
    
    // 4. Remove duplicates from unsorted list
    // head = removeDuplicatesUnsorted(head);
    // display(head);
    
    // 5. Nth node from end
    // int value = nthFromEnd(head, 2);
    // cout << "2nd node from end: " << value << endl;
    
    // 6. Check palindrome
    // bool isPalin = checkPalindrome(head);
    // cout << "Is palindrome: " << (isPalin ? "Yes" : "No") << endl;
    
    // 7. Merge two sorted lists
    // Node* list2 = new Node(2);
    // list2->next = new Node(4);
    // list2->next->next = new Node(6);
    // Node* merged = mergeSorted(head, list2);
    // display(merged);
    
    // 8. Find intersection (requires creating intersecting lists)
    // Node* intersection = findIntersection(head1, head2);
    
    // 9. Reverse in groups
    // head = reverseInGroups(head, 2);
    // display(head);
    
    // 10. Rotate list
    // head = rotateList(head, 2);
    // display(head);
    
    // 11. Segregate even and odd
    // head = segregateEvenOdd(head);
    // display(head);
    
    // 12. Add two numbers
    // Node* num1 = new Node(2);
    // num1->next = new Node(4);
    // num1->next->next = new Node(3);
    // Node* num2 = new Node(5);
    // num2->next = new Node(6);
    // num2->next->next = new Node(4);
    // Node* sum = addTwoNumbers(num1, num2);
    // display(sum);
    
    return 0;
}
