import java.util.*;

/**
 * Advanced Radix Tree Problems in Java
 * Implements an IP Routing Table (CIDR) using a Radix Tree.
 * Each node optionally stores the Gateway/Next Hop for a specific subnet
 * prefix.
 */
public class advanced_problems {

    static class Node {
        Map<Character, Edge> children = new HashMap<>();
        String gateway = null;
    }

    static class Edge {
        String label;
        Node target;

        Edge(String l, Node t) {
            label = l;
            target = t;
        }
    }

    private Node root = new Node();

    // CIDR is typically bit-based, but here we model it with string prefixes for
    // simplicity
    public void addRoute(String prefix, String gateway) {
        insert(root, prefix, gateway);
    }

    private void insert(Node node, String prefix, String gateway) {
        if (prefix.isEmpty()) {
            node.gateway = gateway;
            return;
        }
        char first = prefix.charAt(0);
        Edge edge = node.children.get(first);
        if (edge == null) {
            node.children.put(first, new Edge(prefix, new Node() {
                {
                    this.gateway = gateway;
                }
            }));
            return;
        }
        int common = 0;
        while (common < Math.min(prefix.length(), edge.label.length()) &&
                prefix.charAt(common) == edge.label.charAt(common))
            common++;

        if (common < edge.label.length()) {
            String commonPart = edge.label.substring(0, common);
            Node split = new Node();
            split.children.put(edge.label.charAt(common), new Edge(edge.label.substring(common), edge.target));
            edge.label = commonPart;
            edge.target = split;
        }
        if (common < prefix.length())
            insert(edge.target, prefix.substring(common), gateway);
        else
            edge.target.gateway = gateway;
    }

    // Longest Prefix Matching
    public String findRoute(String ip) {
        Node curr = root;
        String bestGateway = null;
        String temp = ip;

        while (!temp.isEmpty()) {
            if (curr.gateway != null)
                bestGateway = curr.gateway;
            Edge edge = curr.children.get(temp.charAt(0));
            if (edge == null || !temp.startsWith(edge.label))
                break;
            temp = temp.substring(edge.label.length());
            curr = edge.target;
        }
        if (curr.gateway != null)
            bestGateway = curr.gateway;

        return bestGateway != null ? bestGateway : "Default Gateway";
    }

    public static void main(String[] args) {
        advanced_problems routingTable = new advanced_problems();

        // Modelling IP subnets as strings (e.g., bit strings would be better for real
        // IP)
        routingTable.addRoute("192.168.", "GW_INTERNAL");
        routingTable.addRoute("192.168.1.", "GW_NET_1");
        routingTable.addRoute("10.0.", "GW_DMZ");
        routingTable.addRoute("10.0.0.1", "HOST_SECURE");

        System.out.println("Route for 192.168.1.50: " + routingTable.findRoute("192.168.1.50"));
        System.out.println("Route for 192.168.2.10: " + routingTable.findRoute("192.168.2.10"));
        System.out.println("Route for 10.0.0.1: " + routingTable.findRoute("10.0.0.1"));
        System.out.println("Route for 8.8.8.8: " + routingTable.findRoute("8.8.8.8"));
    }
}
