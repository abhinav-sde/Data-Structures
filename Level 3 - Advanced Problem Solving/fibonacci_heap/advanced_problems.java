import java.util.*;

/**
 * Advanced Fibonacci Heap Problems in Java
 * Optimized Dijkstra's Algorithm using Fibonacci Heap.
 * Performance: O(E + V log V)
 */
public class advanced_problems {

    static class FibonacciHeap {
        static class Node {
            int vertex;
            double dist;
            int degree;
            boolean mark;
            Node parent, child, left, right;

            Node(int v, double d) {
                this.vertex = v;
                this.dist = d;
                this.left = this.right = this;
            }
        }

        Node min;
        int n;

        void insert(Node node) {
            if (min == null)
                min = node;
            else {
                node.right = min.right;
                node.left = min;
                min.right.left = node;
                min.right = node;
                if (node.dist < min.dist)
                    min = node;
            }
            n++;
        }

        Node extractMin() {
            Node z = min;
            if (z != null) {
                if (z.child != null) {
                    Node start = z.child;
                    Node curr = start;
                    do {
                        Node next = curr.right;
                        curr.parent = null;
                        curr.right = min.right;
                        curr.left = min;
                        min.right.left = curr;
                        min.right = curr;
                        curr = next;
                    } while (curr != start);
                }
                z.left.right = z.right;
                z.right.left = z.left;
                if (z == z.right)
                    min = null;
                else {
                    min = z.right;
                    consolidate();
                }
                n--;
            }
            return z;
        }

        void decreaseDist(Node x, double d) {
            if (d > x.dist)
                return;
            x.dist = d;
            Node y = x.parent;
            if (y != null && x.dist < y.dist) {
                cut(x, y);
                cascadingCut(y);
            }
            if (x.dist < min.dist)
                min = x;
        }

        private void cut(Node x, Node y) {
            if (x.right == x)
                y.child = null;
            else {
                x.left.right = x.right;
                x.right.left = x.left;
                if (y.child == x)
                    y.child = x.right;
            }
            y.degree--;
            x.parent = null;
            x.mark = false;
            x.right = min.right;
            x.left = min;
            min.right.left = x;
            min.right = x;
        }

        private void cascadingCut(Node y) {
            Node z = y.parent;
            if (z != null) {
                if (!y.mark)
                    y.mark = true;
                else {
                    cut(y, z);
                    cascadingCut(z);
                }
            }
        }

        private void consolidate() {
            int maxDegree = (int) (Math.log(n + 1) / Math.log(1.618)) + 2;
            Node[] A = new Node[maxDegree];
            List<Node> roots = new ArrayList<>();
            Node curr = min;
            if (curr != null) {
                Node start = curr;
                do {
                    roots.add(curr);
                    curr = curr.right;
                } while (curr != start);
            }
            for (Node x : roots) {
                int d = x.degree;
                while (A[d] != null) {
                    Node y = A[d];
                    if (x.dist > y.dist) {
                        Node t = x;
                        x = y;
                        y = t;
                    }
                    link(y, x);
                    A[d] = null;
                    d++;
                }
                A[d] = x;
            }
            min = null;
            for (Node node : A) {
                if (node != null) {
                    if (min == null) {
                        min = node;
                        node.left = node.right = node;
                    } else {
                        node.right = min.right;
                        node.left = min;
                        min.right.left = node;
                        min.right = node;
                        if (node.dist < min.dist)
                            min = node;
                    }
                }
            }
        }

        private void link(Node y, Node x) {
            y.left.right = y.right;
            y.right.left = y.left;
            y.parent = x;
            if (x.child == null) {
                x.child = y;
                y.left = y.right = y;
            } else {
                y.right = x.child;
                y.left = x.child.left;
                x.child.left.right = y;
                x.child.left = y;
            }
            x.degree++;
            y.mark = false;
        }
    }

    static class Edge {
        int to;
        double weight;

        Edge(int to, double w) {
            this.to = to;
            this.weight = w;
        }
    }

    public static double[] dijkstra(List<List<Edge>> adj, int start) {
        int n = adj.size();
        double[] dist = new double[n];
        Arrays.fill(dist, Double.POSITIVE_INFINITY);
        FibonacciHeap.Node[] nodes = new FibonacciHeap.Node[n];
        FibonacciHeap heap = new FibonacciHeap();

        dist[start] = 0;
        for (int i = 0; i < n; i++) {
            nodes[i] = new FibonacciHeap.Node(i, dist[i]);
            heap.insert(nodes[i]);
        }

        while (heap.n > 0) {
            FibonacciHeap.Node uNode = heap.extractMin();
            int u = uNode.vertex;

            for (Edge edge : adj.get(u)) {
                if (dist[u] + edge.weight < dist[edge.to]) {
                    dist[edge.to] = dist[u] + edge.weight;
                    heap.decreaseDist(nodes[edge.to], dist[edge.to]);
                }
            }
        }
        return dist;
    }

    public static void main(String[] args) {
        int V = 5;
        List<List<Edge>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++)
            adj.add(new ArrayList<>());

        adj.get(0).add(new Edge(1, 10));
        adj.get(0).add(new Edge(4, 5));
        adj.get(1).add(new Edge(2, 1));
        adj.get(1).add(new Edge(4, 2));
        adj.get(2).add(new Edge(3, 4));
        adj.get(3).add(new Edge(0, 7));
        adj.get(3).add(new Edge(2, 6));
        adj.get(4).add(new Edge(1, 3));
        adj.get(4).get(0).weight = 3; // adjustment
        adj.get(4).add(new Edge(2, 9));
        adj.get(4).add(new Edge(3, 2));

        double[] distances = dijkstra(adj, 0);
        System.out.println("Dijkstra's Shortest Paths from source 0:");
        for (int i = 0; i < V; i++) {
            System.out.println("To " + i + ": " + distances[i]);
        }
    }
}
