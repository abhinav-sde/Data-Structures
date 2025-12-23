# Geohash + Trie

## What Is Geohash?

**Geohash** is a geocoding system invented by Gustavo Niemeyer in 2008 that encodes geographic coordinates (latitude and longitude) into a short string of letters and digits. It uses a hierarchical spatial data structure that subdivides space into grid-shaped cells, where each additional character in the geohash string represents a finer subdivision.

The key innovation of Geohash is that **nearby locations share common prefixes**, making it excellent for proximity searches and spatial indexing. For example, locations with geohash `9q8yy` are all close to each other, and locations starting with `9q8` are in a broader nearby region.

## What Is a Trie?

A **Trie** (from re**trie**val) is a tree-like data structure used for storing strings where nodes represent common prefixes. In a Trie:
- Each path from root to leaf represents a string
- Common prefixes share nodes
- Efficient for prefix-based searches
- Space-efficient for sets with shared prefixes

## Why Combine Geohash with Trie?

Combining Geohash with Trie creates a powerful spatial indexing structure:

### 1. **Natural Fit**
- Geohashes are strings with hierarchical prefixes
- Tries efficiently store and query prefix hierarchies
- Shared prefixes = nearby locations
- Perfect structural alignment

### 2. **Efficient Proximity Search**
- Find all points with common prefix
- O(k) search where k is geohash length
- No distance calculations needed for prefix matches
- Natural clustering of nearby points

### 3. **Range Queries**
- Query by prefix to get all points in a region
- Variable precision (longer prefix = smaller area)
- No complex spatial calculations
- Simple string operations

### 4. **Memory Efficiency**
- Shared prefixes stored once
- Compact representation of clustering data
- Better than storing full coordinates repeatedly

### 5. **Fast Insertion and Lookup**
- O(k) insertion where k is string length
- O(k) exact lookup
- O(k + m) prefix search where m is results
- No tree rebalancing needed

## How Geohash Works

### Encoding Process

Geohash uses **interleaved binary encoding**:

1. Start with latitude and longitude ranges
   - Latitude: [-90, 90]
   - Longitude: [-180, 180]

2. For each dimension, repeatedly:
   - Divide range in half
   - If coordinate is in upper half: append binary 1
   - If coordinate is in lower half: append binary 0

3. Interleave longitude and latitude bits (lng, lat, lng, lat, ...)

4. Convert 5-bit groups to base-32 characters

### Example: Encoding (42.6, -5.6)

```
Longitude: -5.6
[-180, 180] → [-180, 0] → [-90, 0] → [-45, 0] → [-22.5, 0] → [-11.25, 0]
     0            0           0           0            1
Bits: 00001

Latitude: 42.6
[-90, 90] → [0, 90] → [0, 45] → [22.5, 45] → [33.75, 45] → [39.375, 45]
     1         0          1           1             1
Bits: 10111

Interleaved: 01001001101... (lng, lat, lng, lat, lng, lat...)
Base-32: e z s 4 2...
Geohash: "ezs42"
```

### Precision Levels

| Length | Cell Width | Cell Height | Use Case |
|--------|------------|-------------|-----------|
| 1 | ±2500 km | ±2500 km | Continental |
| 2 | ±630 km | ±630 km | Country |
| 3 | ±78 km | ±156 km | Region |
| 4 | ±20 km | ±20 km | City |
| 5 | ±2.4 km | ±4.9 km | **Neighborhood** |
| 6 | ±610 m | ±610 m | **Street** |
| 7 | ±76 m | ±153 m | Building |
| 8 | ±19 m | ±19 m | Precise location |
| 9 | ±2.4 m | ±4.8 m | Room-level |
| 10 | ±60 cm | ±60 cm | High precision |
| 11 | ±7.4 cm | ±15 cm | Survey grade |
| 12 | ±1.9 cm | ±1.9 cm | Centimeter |

**Common practice**: 6-7 characters for most location-based services

### Geohash Properties

**Advantages**:
- ✅ Nearby locations share prefixes
- ✅ Variable precision by string length
- ✅ Human-readable strings
- ✅ URL-friendly (no special characters)
- ✅ Hierarchical subdivision
- ✅ Fast to encode/decode

**Limitations**:
- ❌ Edge discontinuity (locations at edges may have different prefixes)
- ❌ Not uniform cell size (latitude compression)
- ❌ North/South neighbors harder to find than East/West

## How Trie Stores Geohashes

### Trie Structure for Geohashes

```
Root
├─ 9 (Western US/Mexico)
│  ├─ q (San Francisco area)
│  │  ├─ 8 (SF Bay Area)
│  │  │  ├─ y (Downtown SF)
│  │  │  │  ├─ y (Specific blocks)
│  │  │  │  │  ├─ n (Point 1) ●
│  │  │  │  │  └─ p (Point 2) ●
│  │  │  │  └─ x (Point 3) ●
│  │  │  └─ z (Oakland)
│  │  └─ 9 (Peninsula)
│  └─ r (Los Angeles area)
├─ d (New York area)
└─ u (Amsterdam area)
```

Each node:
- Represents one character in geohash
- Contains up to 32 children (base-32 alphabet)
- Leaf nodes store actual point data
- Intermediate nodes represent regions

### Query Operations

**1. Exact Lookup**: Find point with specific geohash
```
Search("9q8yyn") → Follow path → Return point
Time: O(k) where k = geohash length
```

**2. Prefix Search**: Find all points in a region
```
Search("9q8y") → Traverse subtree → Return all descendants
Time: O(k + m) where m = number of results
```

**3. Proximity Search**: Find nearby points
```
1. Encode query location to geohash
2. Search with incrementally shorter prefixes
3. Expand search until enough results found
```

**4. Range Query**: Find points in bounding box
```
1. Compute geohash grid covering box
2. Search Trie for each grid cell
3. Filter results by exact coordinates
```

## Types of Geohash-Trie Structures

### 1. Basic Geohash Trie

**Purpose**: Simple storage and retrieval of geohashed points.

**Structure**:
- Each node has up to 32 children (one per base-32 character)
- Leaf nodes store point data (coordinates, metadata)
- No special optimizations

**Key Features**:
- Straightforward implementation
- Direct mapping from geohash to tree path
- Simple insertion and lookup

**Use Cases**:
- Learning and prototypes
- Small to medium datasets
- Applications where simplicity matters
- Static or slowly-changing data

**Time Complexity**:
- Insert: O(k) where k = geohash length
- Search: O(k)
- Prefix query: O(k + m) where m = results
- Delete: O(k)

**Space Complexity**: O(n × k) where n = number of points

**Advantages**:
- Simple to implement and understand
- Predictable performance
- Easy to debug
- No rebalancing needed

**Disadvantages**:
- Memory overhead from sparse nodes
- No performance optimizations
- Can waste space with few points
- Not cache-friendly

### 2. Compressed Geohash Trie (Path Compression)

**Purpose**: Reduce memory usage by compressing linear chains.

**Structure**:
- Nodes with single child are compressed into edge labels
- Stores substrings instead of single characters
- Radix tree / Patricia trie structure

**Compression Example**:
```
Before:                      After:
  9 → q → 8 → y → y         9 → "q8yy"
                 ↓                  ↓
                 n                  n (data)
```

**Key Features**:
- Significantly reduced node count
- Edge labels can be variable length
- Better memory efficiency

**Use Cases**:
- Sparse geohash spaces
- Memory-constrained environments
- Large-scale deployments
- Prefix-heavy workloads

**Time Complexity**:
- Insert: O(k)
- Search: O(k) but with fewer nodes
- Memory: 50-90% reduction in sparse cases

**Advantages**:
- Much lower memory usage
- Faster traversal (fewer nodes)
- Better cache performance
- Scales to larger datasets

**Disadvantages**:
- More complex implementation
- Edge label string storage
- Slightly slower insertion (need to split edges)
- Complexity in edge splitting

### 3. Adaptive Geohash Trie

**Purpose**: Dynamically adjust geohash precision based on data density.

**Structure**:
- Variable depth cutoff based on local density
- Dense areas use longer geohashes
- Sparse areas use shorter geohashes
- Metadata tracks density at each node

**Adaptive Strategy**:
```
High Density Area:          Low Density Area:
  9q8yyn (6 chars)           9r3 (3 chars)
    ↓                          ↓
  Detailed grid              Coarse grid
```

**Key Features**:
- Automatic precision adjustment
- Balances accuracy vs. storage
- Adapts to data characteristics
- Can merge cells in sparse regions

**Use Cases**:
- Highly non-uniform data distributions
- Multi-scale applications
- Urban vs. rural data (cities dense, countryside sparse)
- Dynamic clustering applications

**Time Complexity**:
- Insert: O(k) + adaptation overhead
- Query: Variable based on local precision
- Adaptation: Periodic O(n) rebalancing

**Advantages**:
- Optimal precision per region
- Better storage efficiency
- Improved query performance
- Natural clustering behavior

**Disadvantages**:
- Complex adaptation logic
- Requires density tracking
- Rebalancing overhead
- Less predictable performance

### 4. Geohash Trie with Bounding Volumes

**Purpose**: Augment trie nodes with bounding boxes for optimized queries.

**Structure**:
- Each node stores min/max lat/lng of all descendants
- Enables early pruning during spatial queries
- Hybrid structure combining Trie and R-Tree concepts

**Node Enhancement**:
```
Node "9q8y":
  - Children: y, x, z, w, ...
  - BBox: (37.7, -122.5) to (37.8, -122.4)
  - Point count: 1,247
```

**Key Features**:
- Bounding box at each node
- Can reject subtrees in range queries
- Better for complex spatial queries
- Combines string matching with geometric pruning

**Use Cases**:
- Complex range queries
- Radius searches
- Polygon containment queries
- Applications needing both prefix and spatial filtering

**Time Complexity**:
- Insert: O(k) + bbox update O(log n)
- Range query: O(k + m) with pruning
- Spatial query: Much faster than basic trie

**Space Complexity**: O(n × k) + O(nodes × bbox)

**Advantages**:
- Much faster spatial queries
- Early pruning of irrelevant subtrees
- Handles edge cases better
- Good for geometric queries

**Disadvantages**:
- Higher memory usage (bboxes)
- More complex maintenance
- Bbox updates on insertion
- Implementation complexity

## Time Complexity

### Operation Complexity Table

| Operation | Basic Trie | Compressed | Adaptive | With BBox |
|-----------|-----------|------------|----------|-----------|
| Insert | O(k) | O(k) | O(k) + adapt | O(k) + bbox |
| Search (exact) | O(k) | O(k) | O(k) | O(k) |
| Prefix query | O(k + m) | O(k + m) | O(k + m) | O(k + m) |
| Nearest neighbor | O(k × n) | O(k × n) | O(k × n) | O(k + log n) |
| Range query | O(c × m) | O(c × m) | O(c × m) | O(c + m) |
| Space | O(n × k) | O(n + e) | O(n × k̄) | O(n × k + b) |

**Where:**
- k = geohash string length (typically 6-8)
- n = number of points
- m = number of results
- c = number of cells in query range
- e = number of edges in compressed trie
- k̄ = average geohash length (adaptive)
- b = number of bounding boxes

### Complexity Analysis Details

#### Insertion: O(k)
- Traverse trie depth = geohash length
- Each step: check child, create if needed
- No rebalancing required
- Append data at leaf

**Why it's fast**:
- Direct path from geohash
- No tree rotations
- No complex balancing
- Simple pointer updates

#### Search (Exact): O(k)
- Follow path matching geohash characters
- Early termination if path doesn't exist
- Direct access to leaf node

#### Prefix Query: O(k + m)
- O(k): Navigate to prefix node
- O(m): Traverse subtree collecting results
- DFS or BFS through descendants

**Optimization**: Iterator pattern to return results lazily

#### Nearest Neighbor: O(k × n) naive, O(k + log n) with optimizations
- **Naive**: Expand search radius until found
- **Optimized**: Use bounding boxes, priority queue
- Geohash limitation: edge discontinuities complicate search

#### Range Query: O(c × (k + m))
- c = number of geohash cells covering range
- For each cell: O(k) to navigate + O(m) to collect
- Can be many cells for large ranges

**Optimization**: Use geohash grid covering algorithm to minimize c

#### Space Complexity

**Basic Trie**: O(n × k)
- n points, each with k-character path
- Each character creates potential node
- Sharing of prefixes reduces actual space

**Compressed Trie**: O(n + edges)
- n leaf nodes for points
- Significantly fewer internal nodes
- Edge labels add string storage

**With Bounding Boxes**: Additional O(nodes × bbox_size)
- Each node stores 4 doubles (min/max lat/lng)
- Typically 32 bytes per node

### Practical Performance

**Typical Geohash Length**: 6-7 characters
- Means tree depth of 6-7
- Very shallow compared to binary trees
- Fast traversal even without optimization

**Memory**: 
- 1M points with 6-char geohashes
- Basic trie: ~6M nodes = ~150 MB
- Compressed: ~1M nodes = ~30 MB
- 80% reduction with compression

## Advantages and Disadvantages

### Advantages

✅ **Proximity Preserved**: Nearby locations share prefixes  
✅ **Simple Implementation**: Straightforward trie + string operations  
✅ **Variable Precision**: Adjust by string length  
✅ **Fast Prefix Queries**: O(k + m) for region searches  
✅ **Human Readable**: Geohashes are short, memorable strings  
✅ **No Rebalancing**: Trie structure naturally balanced by data  
✅ **Efficient Storage**: Shared prefixes reduce memory  
✅ **URL Friendly**: Can be used in URLs and APIs  
✅ **Language Agnostic**: Works in any language with string support  

### Disadvantages

❌ **Edge Discontinuity**: Nearby points may have different prefixes at borders  
❌ **Non-uniform Cells**: Latitude compression causes rectangular distortion  
❌ **Neighbor Finding**: Non-trivial to find all neighbors directly  
❌ **Not Optimal for NN**: Nearest neighbor requires multiple queries  
❌ **Grid Artifacts**: Artificial boundaries at each subdivision  
❌ **Memory Overhead**: Sparse tries can waste space  
❌ **Pole Problems**: Poor behavior near poles (latitude compression)  
❌ **Limited to 2D**: Not naturally extensible to 3D+  

## Comparison with Other Spatial Structures

| Feature | Geohash+Trie | H3 | R-Tree | K-D Tree | Quad Tree |
|---------|-------------|-----|--------|----------|-----------|
| Structure | Trie | Hexagon grid | Balanced tree | Binary tree | Quad tree |
| Cell Shape | Rectangle | Hexagon | Variable | Point | Square |
| Precision | Variable (string len) | 16 levels | Adaptive | Unlimited | Unlimited |
| Prefix Query | Excellent | Good | N/A | N/A | N/A |
| NN Search | Fair | Good | Excellent | Excellent | Good |
| Range Query | Good | Excellent | Excellent | Good | Good |
| Memory | Good | Excellent | Good | Excellent | Good |
| Implementation | Simple | Complex | Complex | Medium | Medium |
| Edge Cases | Discontinuities | 12 pentagons | None | None | None |
| Human Readable | Yes | No | No | No | No |

## Practical Considerations

### When to Use Geohash + Trie

✓ **Prefix-based queries** are common  
✓ **URL/API encoding** of locations  
✓ **Variable precision** needed  
✓ **Human-readable** identifiers desired  
✓ **Simple implementation** preferred  
✓ **Clustering by proximity** required  
✓ **Redis geospatial** features (uses geohash internally)  
✓ **Quick prototyping** of location features  

### When NOT to Use Geohash + Trie

✗ **High-precision** nearest neighbor search  
✗ **Uniform coverage** required (use H3)  
✗ **3D or high-dimensional** data  
✗ **Exact geometric** operations  
✗ **Edge-heavy data** (discontinuity problems)  
✗ **Global scale** with pole data  
✗ **Complex spatial** predicates (use PostGIS)  

### Choosing Geohash Length

| Application | Recommended Length | Cell Size |
|-------------|-------------------|-----------|
| Country-level aggregation | 2-3 | ~630-78 km |
| City discovery | 4-5 | ~20-2.4 km |
| **Neighborhood search** | **5-6** | **~2.4 km - 610 m** |
| **Street-level** | **6-7** | **~610 m - 76 m** |
| Building/venue | 7-8 | ~76-19 m |
| Precise location | 8-9 | ~19-2.4 m |
| High-precision tracking | 10+ | < 60 cm |

**Recommendation**: Start with 6-7 for most applications

## Optimization Techniques

### 1. Lazy Loading
**Problem**: Large subtrees consume memory  
**Solution**: Load nodes on demand  
**Benefit**: Reduced memory footprint

### 2. Geohash Grid Covering
**Problem**: Range query needs many geohashes  
**Solution**: Compute minimal covering set  
**Algorithm**: Use hierarchical grid to minimize cells  
**Benefit**: Fewer trie queries

### 3. Caching
**Problem**: Repeated queries for same regions  
**Solution**: Cache prefix query results  
**Implementation**: LRU cache keyed by prefix  
**Benefit**: 10-100x speedup for hot queries

### 4. Batch Operations
**Problem**: Individual insertions are slow  
**Solution**: Batch insert with bulk loading  
**Technique**: Sort by geohash, insert in order  
**Benefit**: Better locality, fewer allocations

### 5. Prefix Compression
**Problem**: Long common prefixes waste space  
**Solution**: Use radix/Patricia trie  
**Benefit**: 50-90% memory reduction

## Common Patterns

### Pattern 1: Nearby Search
```
1. Encode query location to geohash
2. Query with progressively shorter prefixes:
   - Try exact geohash
   - Try prefix (length - 1)
   - Try prefix (length - 2)
   - Until sufficient results
3. Sort results by actual distance
```

### Pattern 2: Bounding Box Query
```
1. Compute geohash grid covering bbox
2. For each grid cell:
   - Query trie with cell geohash
   - Collect results
3. Filter by exact bbox containment
4. Return filtered results
```

### Pattern 3: Clustering
```
1. Encode all points to geohashes (fixed length)
2. Insert into trie
3. Traverse trie to depth = cluster precision
4. Each subtree = one cluster
5. Aggregate points in each cluster
```

### Pattern 4: Progressive Refinement
```
1. Start with short geohash (coarse)
2. Show initial results
3. As user zooms, extend geohash
4. Query more precise results
5. Update display incrementally
```

## Edge Case Handling

### Discontinuity Problem

**Issue**: Nearby points can have different prefixes
```
Point A: 9q8zzzzz (edge of cell)
Point B: 9q9 00000 (just across border)
Common prefix: "9q" (only 2 chars!)
```

**Solutions**:

**1. Expand Search to Neighbors**
```
1. Compute 8 neighbor geohashes
2. Query all 9 cells (center + neighbors)
3. Merge results
4. Sort by distance
```

**2. Use Multiple Precision Levels**
```
1. Query at precision p
2. Also query at p-1, p-2
3. Deduplicate results
4. Provides overlapping coverage
```

**3. Hybrid Approach**
```
1. Use geohash for filtering
2. Verify with actual distance calculation
3. Return k nearest after sorting
```

### Pole Handling

**Issue**: Geohash cells become very wide near poles

**Solutions**:
- Limit searches to ±85° latitude
- Use special handling for polar regions
- Consider alternative encoding (S2) for pole data

## Integration with Databases

### PostgreSQL
```sql
CREATE INDEX idx_geohash ON locations USING btree(geohash);
SELECT * FROM locations WHERE geohash LIKE '9q8y%';
```

### MongoDB
```javascript
db.locations.createIndex({ geohash: 1 });
db.locations.find({ geohash: /^9q8y/ });
```

### Redis
```
GEOADD locations 13.361389 38.115556 "Palermo"
GEORADIUS locations 15 37 200 km WITHDIST
// Internally uses geohash + sorted set
```

### Elasticsearch
```json
{
  "mappings": {
    "properties": {
      "location": { "type": "geo_point" }
    }
  }
}
// Uses geohash internally for geo queries
```

## Conclusion

Geohash combined with Trie creates an elegant and practical spatial indexing solution. The natural prefix hierarchy of geohashes maps perfectly to the trie structure, enabling fast proximity searches and efficient storage of spatial data.

**Key Strengths**:
- Simple to implement and understand
- Fast prefix-based queries
- Human-readable spatial codes
- Works well with existing string-based systems

**Best For**:
- Location-based services
- Proximity search at city/neighborhood scale
- URL encoding of locations
- Quick prototyping
- Integration with string-indexed databases

**Not Ideal For**:
- High-precision nearest neighbor (consider R-Trees, K-D Trees)
- Uniform global coverage (consider H3)
- Complex geometric queries (consider PostGIS)

**Recommended Usage**:
1. Use 6-7 character geohashes for most apps
2. Implement compressed trie for production
3. Handle edge discontinuities with neighbor expansion
4. Cache frequent prefix queries
5. Combine with actual distance checking for NN searches

Geohash+Trie remains a popular choice for spatial indexing due to its simplicity, URL-friendliness, and good-enough performance for many real-world applications. It's particularly well-suited for web services and APIs where human-readable location codes are valuable.

## Implementation Files

For practical implementations of Geohash+Trie variants, see:
- `BasicGeohashTrie.cpp` / `BasicGeohashTrie.java` - Simple geohash trie
- `CompressedGeohashTrie.cpp` / `CompressedGeohashTrie.java` - Path-compressed radix trie
- `AdaptiveGeohashTrie.cpp` / `AdaptiveGeohashTrie.java` - Density-adaptive precision
- `BoundedGeohashTrie.cpp` / `BoundedGeohashTrie.java` - With bounding volume hierarchy
