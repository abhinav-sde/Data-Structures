# Vector Clocks

A **Vector Clock** is a data structure used for determining the partial ordering of events in a distributed system and detecting causality violations.

## Why Vector Clocks?
In a distributed system, there is no global clock. Physical clocks on different servers eventually drift. 
- **Lamport Timestamps**: Provide a total order of events but cannot distinguish between "concurrent" events and "causally related" events.
- **Vector Clocks**: Fix this by providing a way to detect if two events are concurrent or if one happened-before the other.

## How it Works
Each node (process) keeps a vector (array/map) of integers: $VC = [c_1, c_2, ..., c_n]$, where $n$ is the number of nodes.
1.  **Local Event**: When a node $i$ performs an internal event, it increments its own counter: $VC_i[i] = VC_i[i] + 1$.
2.  **Send Message**: When node $i$ sends a message, it first increments its local counter and then attaches its entire vector $VC_i$ to the message.
3.  **Receive Message**: When node $j$ receives a message with vector $VC_{msg}$:
    - It updates its own vector: $VC_j[k] = max(VC_j[k], VC_{msg}[k])$ for all $k$.
    - It increments its own local counter: $VC_j[j] = VC_j[j] + 1$.

## Comparing Vector Clocks
Two vector clocks $X$ and $Y$ can be compared:
- **$X = Y$**: If all elements in $X$ are equal to corresponding elements in $Y$.
- **$X < Y$ (Happens-Before)**: If every element in $X$ is less than or equal to corresponding element in $Y$, and at least one element is strictly less. 
- **$X \parallel Y$ (Concurrent/Conflict)**: If neither $X < Y$ nor $Y < X$ is true. This indicates that the events happened independently (a conflict that needs resolution).

## Applications
- **Distributed Databases**: Amazon Dynamo and Riak use vector clocks for versioning and conflict detection (Slowing down the "last-write-wins" problem).
- **Communication Systems**: Ordering messages in distributed chat or state synchronization.

## Complexity
| Characteristic | Complexity |
|----------------|------------|
| Space          | O(N) where N is number of nodes |
| Increment      | O(1)       |
| Compare        | O(N)       |
| Merge          | O(N)       |
