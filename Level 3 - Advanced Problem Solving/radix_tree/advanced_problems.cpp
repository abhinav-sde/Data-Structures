#include <iostream>
#include <string>
#include <map>
#include <vector>

/**
 * Advanced Radix Tree Problems in C++
 * Implements an IP Routing Table (CIDR) using Longest Prefix Matching.
 */

struct Node;

struct Edge {
    std::string label;
    Node* target;
    Edge(std::string l, Node* t) : label(l), target(t) {}
};

struct Node {
    std::map<char, Edge*> children;
    std::string gateway;
    Node() : gateway("") {}
};

class RoutingTable {
private:
    Node* root;

    void insert(Node* node, std::string prefix, std::string gateway) {
        if (prefix.empty()) { node->gateway = gateway; return; }
        char first = prefix[0];
        if (node->children.find(first) == node->children.end()) {
            Node* target = new Node(); target->gateway = gateway;
            node->children[first] = new Edge(prefix, target);
            return;
        }
        Edge* edge = node->children[first];
        int common = 0;
        while (common < edge->label.length() && common < prefix.length() && edge->label[common] == prefix[common])
            common++;
        
        if (common < edge->label.length()) {
            Node* split = new Node();
            split->children[edge->label[common]] = new Edge(edge->label.substr(common), edge->target);
            edge->label = edge->label.substr(0, common);
            edge->target = split;
        }
        if (common < prefix.length()) insert(edge->target, prefix.substr(common), gateway);
        else edge->target->gateway = gateway;
    }

public:
    RoutingTable() : root(new Node()) {}

    void addRoute(std::string prefix, std::string gateway) { insert(root, prefix, gateway); }

    std::string findRoute(std::string ip) {
        Node* curr = root;
        std::string bestGateway = "";
        std::string temp = ip;

        while (!temp.empty()) {
            if (curr->gateway != "") bestGateway = curr->gateway;
            char first = temp[0];
            if (curr->children.find(first) == curr->children.end()) break;
            Edge* edge = curr->children[first];
            if (temp.length() >= edge->label.length() && temp.substr(0, edge->label.length()) == edge->label) {
                temp = temp.substr(edge->label.length());
                curr = edge->target;
            } else break;
        }
        if (curr->gateway != "") bestGateway = curr->gateway;
        return bestGateway != "" ? bestGateway : "Default Gateway";
    }
};

int main() {
    RoutingTable rt;
    rt.addRoute("192.168.", "GW_INTERNAL");
    rt.addRoute("192.168.1.", "GW_NET_1");
    rt.addRoute("10.0.", "GW_DMZ");
    rt.addRoute("10.0.0.1", "HOST_SECURE");

    std::cout << "Route for 192.168.1.50: " << rt.findRoute("192.168.1.50") << std::endl;
    std::cout << "Route for 192.168.2.10: " << rt.findRoute("192.168.2.10") << std::endl;
    std::cout << "Route for 10.0.0.1: " << rt.findRoute("10.0.0.1") << std::endl;
    std::cout << "Route for 8.8.8.8: " << rt.findRoute("8.8.8.8") << std::endl;

    return 0;
}
