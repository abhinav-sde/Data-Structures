#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// ========================================
// NODE STRUCTURES
// ========================================

struct Node {
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

struct RandomNode {
    int data;
    RandomNode* next;
    RandomNode* random;
    
    RandomNode(int val) {
        data = val;
        next = nullptr;
        random = nullptr;
    }
};

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
// 1. CLONE LINKED LIST WITH RANDOM POINTER
// ========================================
// Concept: Hash map or interweaving nodes
// Usage: cloned = cloneRandomList(head)
// Example: Deep copy of list with random pointers
RandomNode* cloneRandomList(RandomNode* head) {
    if (head == nullptr) return nullptr;
    
    unordered_map<RandomNode*, RandomNode*> map;
    
    // First pass: create all nodes
    RandomNode* current = head;
    while (current != nullptr) {
        map[current] = new RandomNode(current->data);
        current = current->next;
    }
    
    // Second pass: assign next and random pointers
    current = head;
    while (current != nullptr) {
        map[current]->next = map[current->next];
        map[current]->random = map[current->random];
        current = current->next;
    }
    
    return map[head];
}

// ========================================
// 2. FLATTEN A MULTILEVEL LINKED LIST
// ========================================
// Concept: DFS or merge sorted lists
// Usage: head = flattenList(head)
// Example: Flattens nested linked list structure
Node* mergeTwoLists(Node* a, Node* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    
    Node* result;
    if (a->data < b->data) {
        result = a;
        result->next = mergeTwoLists(a->next, b);
    } else {
        result = b;
        result->next = mergeTwoLists(a, b->next);
    }
    return result;
}

// ========================================
// 3. SORT LINKED LIST (MERGE SORT)
// ========================================
// Concept: Divide and conquer
// Usage: head = mergeSort(head)
// Example: Sorts linked list in O(n log n)
Node* findMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head->next;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

Node* mergeSort(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    Node* middle = findMiddle(head);
    Node* nextOfMiddle = middle->next;
    middle->next = nullptr;
    
    Node* left = mergeSort(head);
    Node* right = mergeSort(nextOfMiddle);
    
    return mergeTwoLists(left, right);
}

// ========================================
// 4. FIND LOOP START NODE
// ========================================
// Concept: Floyd's algorithm with meeting point
// Usage: loopStart = findLoopStart(head)
// Example: Returns node where loop begins or nullptr
Node* findLoopStart(Node* head) {
    if (head == nullptr) return nullptr;
    
    Node* slow = head;
    Node* fast = head;
    
    // Detect loop
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            // Loop detected, find start
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    
    return nullptr;
}

// ========================================
// 5. REMOVE LOOP FROM LINKED LIST
// ========================================
// Usage: removeLoop(head)
// Example: Removes cycle from linked list
void removeLoop(Node* head) {
    if (head == nullptr) return;
    
    Node* slow = head;
    Node* fast = head;
    
    // Detect loop
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            // Loop detected
            slow = head;
            
            // Special case: loop at head
            if (slow == fast) {
                while (fast->next != slow) {
                    fast = fast->next;
                }
            } else {
                while (slow->next != fast->next) {
                    slow = slow->next;
                    fast = fast->next;
                }
            }
            
            fast->next = nullptr;
            cout << "Loop removed." << endl;
            return;
        }
    }
    
    cout << "No loop found." << endl;
}

// ========================================
// 6. PARTITION LIST AROUND VALUE X
// ========================================
// Concept: Two pointer technique
// Usage: head = partition(head, x)
// Example: Nodes < x before nodes >= x
Node* partition(Node* head, int x) {
    Node* beforeHead = new Node(0);
    Node* before = beforeHead;
    Node* afterHead = new Node(0);
    Node* after = afterHead;
    
    while (head != nullptr) {
        if (head->data < x) {
            before->next = head;
            before = before->next;
        } else {
            after->next = head;
            after = after->next;
        }
        head = head->next;
    }
    
    after->next = nullptr;
    before->next = afterHead->next;
    
    Node* result = beforeHead->next;
    delete beforeHead;
    delete afterHead;
    
    cout << "List partitioned around " << x << endl;
    return result;
}

// ========================================
// 7. REORDER LIST (L0→Ln→L1→Ln-1→L2→Ln-2...)
// ========================================
// Concept: Find middle, reverse second half, merge
// Usage: reorderList(head)
// Example: 1->2->3->4 becomes 1->4->2->3
void reorderList(Node* head) {
    if (head == nullptr || head->next == nullptr) return;
    
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
    slow->next = nullptr;
    
    while (current != nullptr) {
        Node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    // Merge two halves
    Node* first = head;
    Node* second = prev;
    
    while (second != nullptr) {
        Node* temp1 = first->next;
        Node* temp2 = second->next;
        
        first->next = second;
        second->next = temp1;
        
        first = temp1;
        second = temp2;
    }
    
    cout << "List reordered." << endl;
}

// ========================================
// 8. SWAP NODES IN PAIRS
// ========================================
// Usage: head = swapPairs(head)
// Example: 1->2->3->4 becomes 2->1->4->3
Node* swapPairs(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    
    Node* dummy = new Node(0);
    dummy->next = head;
    Node* prev = dummy;
    
    while (prev->next != nullptr && prev->next->next != nullptr) {
        Node* first = prev->next;
        Node* second = prev->next->next;
        
        first->next = second->next;
        second->next = first;
        prev->next = second;
        
        prev = first;
    }
    
    Node* newHead = dummy->next;
    delete dummy;
    
    cout << "Nodes swapped in pairs." << endl;
    return newHead;
}

// ========================================
// 9. DELETE N NODES AFTER M NODES
// ========================================
// Usage: deleteNAfterM(head, m, n)
// Example: m=2, n=3 means keep 2, delete 3, repeat
void deleteNAfterM(Node* head, int m, int n) {
    Node* current = head;
    
    while (current != nullptr) {
        // Skip m nodes
        for (int i = 1; i < m && current != nullptr; i++) {
            current = current->next;
        }
        
        if (current == nullptr) return;
        
        // Delete n nodes
        Node* temp = current->next;
        for (int i = 0; i < n && temp != nullptr; i++) {
            Node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        
        current->next = temp;
        current = temp;
    }
    
    cout << "Deleted " << n << " nodes after every " << m << " nodes." << endl;
}

// ========================================
// 10. MERGE K SORTED LISTS
// ========================================
// Concept: Divide and conquer or min heap
// Usage: merged = mergeKLists(lists, k)
// Example: Merges k sorted linked lists
Node* mergeKLists(vector<Node*>& lists) {
    if (lists.empty()) return nullptr;
    
    while (lists.size() > 1) {
        vector<Node*> mergedLists;
        
        for (int i = 0; i < lists.size(); i += 2) {
            Node* l1 = lists[i];
            Node* l2 = (i + 1 < lists.size()) ? lists[i + 1] : nullptr;
            mergedLists.push_back(mergeTwoLists(l1, l2));
        }
        
        lists = mergedLists;
    }
    
    return lists[0];
}

// ========================================
// 11. REVERSE ALTERNATE K NODES
// ========================================
// Usage: head = reverseAlternateK(head, k)
// Example: k=2: 1->2->3->4->5->6 becomes 2->1->3->4->6->5
Node* reverseAlternateK(Node* head, int k) {
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
    
    if (head != nullptr) {
        head->next = current;
    }
    
    // Skip next k nodes
    count = 0;
    while (count < k - 1 && current != nullptr) {
        current = current->next;
        count++;
    }
    
    // Recursively reverse alternate k nodes
    if (current != nullptr) {
        current->next = reverseAlternateK(current->next, k);
    }
    
    return prev;
}

// ========================================
// 12. FLATTEN DOUBLY LINKED LIST WITH CHILD POINTERS
// ========================================
// Concept: DFS traversal
// Usage: head = flattenDoublyList(head)
// Example: Flattens multilevel doubly linked list
DoublyNode* flattenDoublyList(DoublyNode* head) {
    if (head == nullptr) return head;
    
    DoublyNode* current = head;
    
    while (current != nullptr) {
        if (current->next == nullptr) {
            // Reached end, traverse back
            while (current->prev != nullptr) {
                current = current->prev;
            }
            break;
        }
        current = current->next;
    }
    
    return head;
}

// ========================================
// 13. LRU CACHE USING DOUBLY LINKED LIST
// ========================================
// Concept: Hash map + Doubly linked list
class LRUCache {
private:
    int capacity;
    unordered_map<int, DoublyNode*> cache;
    DoublyNode* head;
    DoublyNode* tail;
    
    void addToFront(DoublyNode* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    
    void removeNode(DoublyNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

public:
    LRUCache(int cap) {
        capacity = cap;
        head = new DoublyNode(0);
        tail = new DoublyNode(0);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        
        DoublyNode* node = cache[key];
        removeNode(node);
        addToFront(node);
        return node->data;
    }
    
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            removeNode(cache[key]);
            delete cache[key];
        }
        
        DoublyNode* newNode = new DoublyNode(value);
        cache[key] = newNode;
        addToFront(newNode);
        
        if (cache.size() > capacity) {
            DoublyNode* lru = tail->prev;
            removeNode(lru);
            cache.erase(key);
            delete lru;
        }
    }
};

// ========================================
// MAIN FUNCTION
// ========================================

int main() {
    Node* head = nullptr;
    
    cout << "=== Linked List Advanced Problems ===" << endl;
    
    // ========================================
    // Example function calls - uncomment to use
    // ========================================
    
    // Create sample list
    // head = new Node(4);
    // head->next = new Node(2);
    // head->next->next = new Node(1);
    // head->next->next->next = new Node(3);
    // display(head);
    
    // 3. Merge sort
    // head = mergeSort(head);
    // display(head);
    
    // 4. Find loop start
    // Node* loopStart = findLoopStart(head);
    
    // 5. Remove loop
    // removeLoop(head);
    
    // 6. Partition around value
    // head = partition(head, 3);
    // display(head);
    
    // 7. Reorder list
    // reorderList(head);
    // display(head);
    
    // 8. Swap pairs
    // head = swapPairs(head);
    // display(head);
    
    // 9. Delete N after M
    // deleteNAfterM(head, 2, 2);
    // display(head);
    
    // 10. Merge K sorted lists
    // vector<Node*> lists;
    // lists.push_back(new Node(1));
    // lists[0]->next = new Node(4);
    // lists.push_back(new Node(2));
    // lists[1]->next = new Node(3);
    // Node* merged = mergeKLists(lists);
    // display(merged);
    
    // 11. Reverse alternate K nodes
    // head = reverseAlternateK(head, 2);
    // display(head);
    
    // 13. LRU Cache
    // LRUCache cache(2);
    // cache.put(1, 1);
    // cache.put(2, 2);
    // cout << "Get 1: " << cache.get(1) << endl;
    // cache.put(3, 3);
    // cout << "Get 2: " << cache.get(2) << endl;
    
    return 0;
}
