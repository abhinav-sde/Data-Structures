# Consistent Hashing

**Consistent Hashing** is a special kind of hashing such that when a hash table is resized, only $K/n$ keys need to be remapped on average, where $K$ is the number of keys, and $n$ is the number of slots (nodes).

## The Problem with Traditional Hashing
In traditional hashing (`index = hash(key) % N`), if the number of nodes $N$ changes (due to a server crash or a new server being added), almost all keys are remapped to new locations. This causes a "cache miss storm" in distributed systems, where all cache entries become invalid at once.

## The Solution: Consistent Hashing
Instead of mapping keys to a linear array, we map both nodes and keys to a **Hash Ring** (a circular coordinate system from $0$ to $2^{32}-1$).

1.  **Node Mapping**: Each server node is hashed and placed at a point on the ring.
2.  **Key Mapping**: Each key is hashed and placed on the ring.
3.  **Assignment**: A key is assigned to the first node encountered while moving clockwise on the ring.

## Virtual Nodes
If nodes are sparse on the ring, load distribution can be uneven. **Virtual Nodes** solve this by mapping each physical node to multiple points (e.g., node-A-v1, node-A-v2, etc.) on the ring.
- **Benefit**: Improved uniformity of distribution.
- **Benefit**: Easier to handle heterogeneous servers (powerful nodes get more virtual nodes).

## Performance Characteristics
- **Lookup**: O(log N) where N is the number of (virtual) nodes (using a balanced BST or sorted map).
- **Add/Remove Node**: Only affecting a small fraction of keys ($1/N$).

## Applications
- **Distributed Caching**: Memcached, Redis Cluster.
- **NoSQL Databases**: Apache Cassandra, Amazon DynamoDB.
- **Load Balancing**: Distributing requests across a server pool.

## Complexity
| Operation | Average   |
|-----------|-----------|
| Get Node  | O(log N)  |
| Add Node  | O(log N)  |
| Remove Node| O(log N) |

*(N is the total number of virtual nodes)*
