
public class core_problems {
    /**
     * Discussion: B-Tree vs B+ Tree in Databases.
     * B+ Tree is preferred for Databases (InnoDB, PostgreSQL) because:
     * 1. Data only in leaves = higher fanout (internal nodes fit more keys).
     * 2. Leaf links allow efficient Range Scans (index-only scans).
     * 3. Consistent path length to all records.
     */
}
