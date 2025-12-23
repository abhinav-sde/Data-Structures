package hyperloglog;

public class core_problems {
    /**
     * Problem: Merging Distributed HLLs.
     * SDE2-3 Concept: One of the greatest features of HLL is that it is
     * "Mergeable".
     * To merge two HLLs, you just take the element-wise maximum of their registers.
     * Rationale: Allows counting unique users across multiple regions/shards
     * without central coordination.
     */
}
