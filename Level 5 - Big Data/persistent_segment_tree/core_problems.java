package persistent_segment_tree;

public class core_problems {
    /**
     * Problem: Range Quantile Query (Kth Smallest in Range).
     * The most famous application of Persistent Segment Trees.
     * By building a persistent segment tree over a frequency array (compressed),
     * we can find the Kth smallest element in [L, R] in O(log N) by querying
     * roots[R] - roots[L-1].
     */
}
