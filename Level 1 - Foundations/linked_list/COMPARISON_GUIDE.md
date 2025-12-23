# LINKED LIST TYPES - COMPARISON GUIDE
## Complete Interview Preparation Reference

---

## 📋 TABLE OF CONTENTS
1. [Overview](#overview)
2. [Singly Linked List](#singly-linked-list)
3. [Doubly Linked List](#doubly-linked-list)
4. [Circular Linked List](#circular-linked-list)
5. [Comparison Table](#comparison-table)
6. [When to Use What](#when-to-use-what)
7. [Interview Questions & Answers](#interview-questions--answers)
8. [Code Examples](#code-examples)

---

## 🎯 OVERVIEW

### What is a Linked List?
A **linked list** is a linear data structure where elements (nodes) are stored in non-contiguous memory locations. Each node contains:
- **Data**: The actual value
- **Pointer(s)**: Reference to next (and/or previous) node

### Why Use Linked Lists?
✅ **Dynamic size** - Grows/shrinks at runtime  
✅ **Efficient insertions/deletions** - O(1) at known positions  
✅ **No memory waste** - Allocates exactly what's needed  
❌ **No random access** - Must traverse from head  
❌ **Extra memory** - Pointers consume additional space  

---

## 1️⃣ SINGLY LINKED LIST

### Structure
```
[Data|Next] -> [Data|Next] -> [Data|Next] -> NULL
```

### Node Definition
```cpp
struct Node {
    int data;
    Node* next;
};
```

### Characteristics
- **One-way traversal** - Can only move forward
- **Memory**: 1 pointer per node
- **Operations**:
  - Insert at head: O(1)
  - Insert at tail: O(n) without tail pointer
  - Delete at head: O(1)
  - Delete at tail: O(n)
  - Search: O(n)

### Real-World Examples
1. **Browser History** (forward only navigation)
2. **Music Playlist** (next song only)
3. **Undo functionality** (single direction)
4. **Image Viewer** (next image)

### Advantages
✅ Simple implementation  
✅ Less memory per node  
✅ Fast insertion at beginning  

### Disadvantages
❌ Cannot traverse backward  
❌ Deleting a node requires previous node reference  
❌ No direct access to previous element  

### Interview Example
**Q: Reverse a singly linked list**
```cpp
Node* reverse(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;
    
    while (current != nullptr) {
        next = current->next;  // Save next
        current->next = prev;  // Reverse link
        prev = current;        // Move prev forward
        current = next;        // Move current forward
    }
    
    return prev;  // New head
}
```
**Time**: O(n), **Space**: O(1)

---

## 2️⃣ DOUBLY LINKED LIST

### Structure
```
NULL <-> [Prev|Data|Next] <-> [Prev|Data|Next] <-> NULL
```

### Node Definition
```cpp
struct DoublyNode {
    int data;
    DoublyNode* prev;
    DoublyNode* next;
};
```

### Characteristics
- **Bi-directional traversal** - Can move forward and backward
- **Memory**: 2 pointers per node
- **Operations**:
  - Insert at head: O(1)
  - Insert at tail: O(1) with tail pointer
  - Delete at head: O(1)
  - Delete at tail: O(1) with tail pointer
  - Delete given node: O(1) - no need to find previous!
  - Search: O(n)

### Real-World Examples
1. **Browser History** (back and forward buttons)
2. **Music Player** (previous and next)
3. **LRU Cache** (move elements to front/back)
4. **Text Editor** (undo/redo)
5. **Navigation Systems** (route backtracking)

### Advantages
✅ Bi-directional traversal  
✅ Delete node in O(1) if node pointer given  
✅ Insert before a node easily  
✅ Better for certain algorithms (LRU cache)  

### Disadvantages
❌ Extra memory for prev pointer  
❌ More complex implementation  
❌ More pointers to maintain during operations  

### Interview Example
**Q: Delete a node in O(1) time (given node pointer)**
```cpp
void deleteNode(DoublyNode* node) {
    // Cannot delete if it's the only node or null
    if (node == nullptr) return;
    
    // Update previous node's next
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    }
    
    // Update next node's prev
    if (node->next != nullptr) {
        node->next->prev = node->prev;
    }
    
    delete node;
}
```
**Time**: O(1), **Space**: O(1)

**Q: Find pairs with given sum in sorted DLL**
```cpp
void findPairs(DoublyNode* head, int sum) {
    DoublyNode* left = head;
    DoublyNode* right = head;
    
    // Find last node
    while (right->next != nullptr) {
        right = right->next;
    }
    
    // Two pointer approach
    while (left != right && left->prev != right) {
        int currentSum = left->data + right->data;
        
        if (currentSum == sum) {
            cout << left->data << " + " << right->data << endl;
            left = left->next;
            right = right->prev;
        } else if (currentSum < sum) {
            left = left->next;
        } else {
            right = right->prev;
        }
    }
}
```
**Time**: O(n), **Space**: O(1)

---

## 3️⃣ CIRCULAR LINKED LIST

### Structure (Circular Singly)
```
[Data|Next] -> [Data|Next] -> [Data|Next] -┐
   ↑                                        |
   └────────────────────────────────────────┘
```

### Node Definition
```cpp
struct Node {
    int data;
    Node* next;  // Last node points to head
};
```

### Characteristics
- **Circular traversal** - No NULL, last points to first
- **Memory**: Same as singly (1 pointer) or doubly (2 pointers)
- **Operations**:
  - Insert at head: O(1) if tail pointer maintained
  - Insert at tail: O(1) if tail pointer maintained
  - Delete: O(n) to find previous node
  - Traverse: Can start from any node

### Real-World Examples
1. **Round-Robin Scheduling** (CPU task scheduling)
2. **Multiplayer Games** (turn-based, cycling through players)
3. **Music Playlist** (repeat all mode)
4. **Circular Buffer** (network packet handling)
5. **Josephus Problem** (elimination game)

### Advantages
✅ Can traverse entire list from any node  
✅ No NULL checks needed  
✅ Useful for round-robin algorithms  
✅ Can reach beginning from end in O(1)  

### Disadvantages
❌ Infinite loop risk if not handled carefully  
❌ More complex termination conditions  
❌ Harder to detect end of list  

### Interview Example
**Q: Josephus Problem - n people in circle, eliminate every kth**
```cpp
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
    
    // Eliminate until one remains
    while (ptr1->next != ptr1) {
        // Count k nodes
        for (int count = 1; count < k; count++) {
            ptr2 = ptr1;
            ptr1 = ptr1->next;
        }
        
        // Remove kth node
        ptr2->next = ptr1->next;
        delete ptr1;
        ptr1 = ptr2->next;
    }
    
    return ptr1->data;  // Survivor
}
```
**Time**: O(n*k), **Space**: O(1)

**Q: Split circular list into two halves**
```cpp
void splitList(Node* head, Node** head1, Node** head2) {
    Node* slow = head;
    Node* fast = head;
    
    // Find middle
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Adjust for even nodes
    if (fast->next->next == head) {
        fast = fast->next;
    }
    
    *head1 = head;
    *head2 = slow->next;
    
    // Make both circular
    slow->next = head;
    fast->next = *head2;
}
```
**Time**: O(n), **Space**: O(1)

---

## 📊 COMPARISON TABLE

| Feature | Singly LL | Doubly LL | Circular LL |
|---------|-----------|-----------|-------------|
| **Traversal** | Forward only | Both directions | Circular (any start) |
| **Memory/Node** | 1 pointer | 2 pointers | 1 or 2 pointers |
| **Insert at Head** | O(1) | O(1) | O(1)* |
| **Insert at Tail** | O(n) | O(1)† | O(1)* |
| **Delete at Head** | O(1) | O(1) | O(1)* |
| **Delete at Tail** | O(n) | O(1)† | O(n) |
| **Delete Given Node** | O(n) | O(1) | O(n) |
| **Search** | O(n) | O(n) | O(n) |
| **Reverse Traversal** | ❌ | ✅ | ❌ (singly) |
| **End Detection** | NULL check | NULL check | Compare with head |
| **Implementation** | Simple | Complex | Moderate |
| **Use Case** | Simple lists | LRU, Navigation | Round-robin, Games |

*With tail pointer maintained  
†With tail pointer maintained

---

## 🎯 WHEN TO USE WHAT

### Use **Singly Linked List** when:
- ✅ Memory is constrained
- ✅ Only forward traversal needed
- ✅ Simple stack implementation
- ✅ Implementing hash table chaining
- **Example**: Function call stack, polynomial representation

### Use **Doubly Linked List** when:
- ✅ Need backward traversal
- ✅ Frequent deletions with node reference
- ✅ Implementing LRU cache
- ✅ Browser history (back/forward)
- ✅ Undo/Redo functionality
- **Example**: LRU Cache, Text editor, Music player

### Use **Circular Linked List** when:
- ✅ Round-robin scheduling needed
- ✅ Continuous cycling through elements
- ✅ No clear start/end point
- ✅ Josephus-type problems
- **Example**: CPU scheduling, Multiplayer games, Circular buffers

---

## 💡 INTERVIEW QUESTIONS & ANSWERS

### Q1: Why use linked list over array?
**Answer:**
- **Dynamic size**: Arrays have fixed size, linked lists grow/shrink dynamically
- **Efficient insertion/deletion**: O(1) at known position vs O(n) for arrays
- **No memory waste**: Allocates exactly what's needed
- **Trade-off**: No random access (O(n) vs O(1) for arrays)

### Q2: What are the disadvantages of linked lists?
**Answer:**
1. **No random access** - Must traverse from head
2. **Extra memory** - Pointers consume space
3. **Cache unfriendly** - Non-contiguous memory
4. **Reverse traversal** - Difficult in singly LL

### Q3: How to detect a loop in a linked list?
**Answer:** Floyd's Cycle Detection (Tortoise and Hare)
```cpp
bool detectLoop(Node* head) {
    Node* slow = head;
    Node* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) return true;
    }
    return false;
}
```

### Q4: How to find the middle of a linked list?
**Answer:** Slow and fast pointer
```cpp
Node* findMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
```

### Q5: Difference between array and linked list?
**Answer:**

| Feature | Array | Linked List |
|---------|-------|-------------|
| Size | Fixed | Dynamic |
| Memory | Contiguous | Non-contiguous |
| Access | O(1) random | O(n) sequential |
| Insert/Delete | O(n) | O(1) at known pos |
| Memory overhead | None | Pointers |
| Cache | Friendly | Unfriendly |

### Q6: When would you use a doubly linked list over singly?
**Answer:**
- Need **backward traversal** (browser history)
- **Delete node in O(1)** when node pointer is given
- Implementing **LRU cache** (move to front/back)
- **Navigation** in both directions
- **Undo/Redo** functionality

### Q7: Explain LRU Cache implementation
**Answer:**
- **Hash Map** + **Doubly Linked List**
- Hash map: O(1) lookup by key
- DLL: O(1) move to front (most recent)
- On access: Move node to front
- On capacity: Remove from tail (least recent)

```cpp
class LRUCache {
    unordered_map<int, DoublyNode*> cache;
    DoublyNode* head;
    DoublyNode* tail;
    int capacity;
    
    void moveToFront(DoublyNode* node) {
        removeNode(node);
        addToFront(node);
    }
};
```

### Q8: How to reverse a linked list?
**Answer:** Three approaches:
1. **Iterative** - O(n) time, O(1) space
2. **Recursive** - O(n) time, O(n) space
3. **Stack** - O(n) time, O(n) space

Best: Iterative (shown in Singly LL section)

### Q9: How to merge two sorted linked lists?
**Answer:**
```cpp
Node* merge(Node* l1, Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    
    if (l1->data < l2->data) {
        l1->next = merge(l1->next, l2);
        return l1;
    } else {
        l2->next = merge(l1, l2->next);
        return l2;
    }
}
```

### Q10: What is the Josephus problem?
**Answer:**
- **n** people in a circle
- Eliminate every **kth** person
- Find the **survivor**
- **Solution**: Circular linked list with elimination
- **Time**: O(n*k)

---

## 💻 CODE EXAMPLES

### Example 1: Detect and Remove Loop
```cpp
void removeLoop(Node* head) {
    Node* slow = head;
    Node* fast = head;
    
    // Detect loop
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    
    if (slow != fast) return;  // No loop
    
    // Find loop start
    slow = head;
    while (slow->next != fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    
    // Remove loop
    fast->next = nullptr;
}
```

### Example 2: Clone List with Random Pointer
```cpp
RandomNode* clone(RandomNode* head) {
    if (!head) return nullptr;
    
    // Step 1: Create copy nodes
    RandomNode* curr = head;
    while (curr) {
        RandomNode* copy = new RandomNode(curr->data);
        copy->next = curr->next;
        curr->next = copy;
        curr = copy->next;
    }
    
    // Step 2: Set random pointers
    curr = head;
    while (curr) {
        if (curr->random) {
            curr->next->random = curr->random->next;
        }
        curr = curr->next->next;
    }
    
    // Step 3: Separate lists
    RandomNode* original = head;
    RandomNode* copy = head->next;
    RandomNode* result = copy;
    
    while (original) {
        original->next = copy->next;
        original = original->next;
        if (original) {
            copy->next = original->next;
            copy = copy->next;
        }
    }
    
    return result;
}
```

### Example 3: Palindrome Check
```cpp
bool isPalindrome(Node* head) {
    // Find middle
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Reverse second half
    Node* prev = nullptr;
    while (slow) {
        Node* next = slow->next;
        slow->next = prev;
        prev = slow;
        slow = next;
    }
    
    // Compare
    while (prev) {
        if (head->data != prev->data) return false;
        head = head->next;
        prev = prev->next;
    }
    
    return true;
}
```

---

## 🎓 INTERVIEW TIPS

### 1. **Always Clarify**
- What type of linked list? (singly/doubly/circular)
- Are there duplicates?
- Is the list sorted?
- Can we use extra space?

### 2. **Common Patterns**
- **Two pointers** (slow/fast) - middle, cycle detection
- **Dummy node** - simplify edge cases
- **Recursion** - reverse, merge
- **Hash map** - clone, intersection

### 3. **Edge Cases to Consider**
- Empty list (head == nullptr)
- Single node
- Two nodes
- Circular reference
- Odd vs even length

### 4. **Time/Space Complexity**
- Always mention both
- Explain trade-offs
- Optimize if asked

### 5. **Draw Diagrams**
- Visualize pointer movements
- Show before/after states
- Helps interviewer follow logic

---

## 📚 PRACTICE PROBLEMS

### Easy
1. Reverse a linked list
2. Find middle element
3. Detect cycle
4. Remove duplicates from sorted list
5. Merge two sorted lists

### Medium
6. Remove nth node from end
7. Reorder list (L0→Ln→L1→Ln-1)
8. Add two numbers
9. Palindrome check
10. Intersection of two lists

### Hard
11. Merge k sorted lists
12. Clone list with random pointer
13. LRU Cache
14. Reverse nodes in k-group
15. Flatten multilevel doubly linked list

---

## ✅ SUMMARY

| Type | Best For | Key Advantage | Key Limitation |
|------|----------|---------------|----------------|
| **Singly** | Simple lists, Stacks | Memory efficient | No backward traversal |
| **Doubly** | LRU, Navigation | Bi-directional | Extra memory |
| **Circular** | Round-robin, Games | Continuous cycle | Loop risk |

**Remember**: Choose based on your use case, not just features!

---

*Good luck with your interviews! 🚀*
