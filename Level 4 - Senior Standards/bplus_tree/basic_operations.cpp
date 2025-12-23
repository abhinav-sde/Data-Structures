#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BPlusNode {
public:
    bool isLeaf;
    vector<int> keys;
    vector<BPlusNode*> children;
    BPlusNode* next;

    BPlusNode(bool leaf) : isLeaf(leaf), next(nullptr) {}
};

class BPlusTree {
    int degree;
    BPlusNode* root;

    void split(BPlusNode* parent, int i, BPlusNode* child) {
        int mid = (degree - 1) / 2;
        BPlusNode* newNode = new BPlusNode(child->isLeaf);
        
        if (child->isLeaf) {
            for (int j = mid; j < child->keys.size(); j++) 
                newNode->keys.push_back(child->keys[j]);
            child->keys.erase(child->keys.begin() + mid, child->keys.end());
            parent->keys.insert(parent->keys.begin() + i, newNode->keys[0]);
            newNode->next = child->next;
            child->next = newNode;
        } else {
            for (int j = mid + 1; j < child->keys.size(); j++) 
                newNode->keys.push_back(child->keys[j]);
            for (int j = mid + 1; j < child->children.size(); j++) 
                newNode->children.push_back(child->children[j]);
            
            parent->keys.insert(parent->keys.begin() + i, child->keys[mid]);
            child->keys.erase(child->keys.begin() + mid, child->keys.end());
            child->children.erase(child->children.begin() + mid + 1, child->children.end());
        }
        parent->children.insert(parent->children.begin() + i + 1, newNode);
    }

    void insertNonFull(BPlusNode* node, int key) {
        int i = node->keys.size() - 1;
        if (node->isLeaf) {
            while (i >= 0 && key < node->keys[i]) i--;
            node->keys.insert(node->keys.begin() + i + 1, key);
        } else {
            while (i >= 0 && key < node->keys[i]) i--;
            i++;
            if (node->children[i]->keys.size() == degree - 1) {
                split(node, i, node->children[i]);
                if (key > node->keys[i]) i++;
            }
            insertNonFull(node->children[i], key);
        }
    }

public:
    BPlusTree(int d) : degree(d) {
        root = new BPlusNode(true);
    }

    void insert(int key) {
        if (root->keys.size() == degree - 1) {
            BPlusNode* s = new BPlusNode(false);
            s->children.push_back(root);
            split(s, 0, root);
            root = s;
        }
        insertNonFull(root, key);
    }

    void display() {
        BPlusNode* curr = root;
        while (!curr->isLeaf) curr = curr->children[0];
        while (curr) {
            cout << "[";
            for (int k : curr->keys) cout << k << " ";
            cout << "] -> ";
            curr = curr->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    BPlusTree tree(4);
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.display();
    return 0;
}
