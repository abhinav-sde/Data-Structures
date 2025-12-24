# Queue Data Structure

A Queue is a linear data structure that follows the **FIFO (First In, First Out)** principle. The first element added to the queue will be the first one to be removed.

## Key Features
- **FIFO**: First In First Out.
- **Two Ends**: Operations happen at two different ends - insertion at the *rear* and deletion from the *front*.

## Time Complexity

| Operation | Time Complexity |
| :--- | :--- |
| Enqueue (Insert) | O(1) |
| Dequeue (Remove) | O(1) |
| Peek/Front | O(1) |
| IsEmpty | O(1) |

## Common Operations
1.  **Enqueue**: Add an element to the end of the queue.
2.  **Dequeue**: Remove the element from the front of the queue.
3.  **Peek/Front**: Get the value of the front element without removing it.
4.  **IsEmpty**: Check if the queue is empty.
5.  **IsFull**: Check if the queue is full (for fixed-capacity queues).
