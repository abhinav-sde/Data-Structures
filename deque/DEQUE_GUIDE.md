# Deque (Double-Ended Queue) Guide

## What is a Deque?

A **Deque** (pronounced "deck") is a double-ended queue that allows insertion and deletion from both ends (front and rear).

```
Front  ← [3, 1, 4, 1, 5] → Rear

Operations possible:
- pushFront(x)  - Insert at front
- pushRear(x)   - Insert at rear
- popFront()    - Remove from front
- popRear()     - Remove from rear
```

## Time Complexity

| Operation | Time | Description |
|-----------|------|-------------|
| **pushFront/Rear** | O(1) | Insert at either end |
| **popFront/Rear** | O(1) | Remove from either end |
| **getFront/Rear** | O(1) | Access either end |

## When to Use Deque

### ✅ Use Deque When:
- Sliding window problems
- Need both stack and queue operations
- Palindrome checking
- Maintaining min/max in window

### ❌ Avoid Deque When:
- Only need one-end operations (use stack/queue)
- Need random access (use array)

## Common Patterns

### Pattern: Sliding Window Maximum
Use monotonic deque to maintain maximum in window

```java
for (int i = 0; i < nums.length; i++) {
    // Remove out of window
    while (!dq.isEmpty() && dq.peekFirst() < i - k + 1) {
        dq.pollFirst();
    }
    
    // Maintain decreasing order
    while (!dq.isEmpty() && nums[dq.peekLast()] < nums[i]) {
        dq.pollLast();
    }
    
    dq.offerLast(i);
}
```

## Practice Problems

1. Sliding window maximum
2. Implement stack/queue using deque
3. Palindrome check
4. Longest subarray with diff <= limit

---

## Summary

Deque extends queue with O(1) operations on both ends, useful for advanced sliding window and monotonic queue patterns.
