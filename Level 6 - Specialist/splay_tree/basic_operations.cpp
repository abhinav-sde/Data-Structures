#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class SplayTree {
private:
    Node* root;
    
    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }
    
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    
    Node* splay(Node* root, int key) {
        if (!root || root->key == key)
            return root;
        
        if (key < root->key) {
            if (!root->left) return root;
            
            if (key < root->left->key) {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            } else if (key > root->left->key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right)
                    root->left = leftRotate(root->left);
            }
            
            return root->left ? rightRotate(root) : root;
        } else {
            if (!root->right) return root;
            
            if (key > root->right->key) {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            } else if (key < root->right->key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left)
                    root->right = rightRotate(root->right);
            }
            
            return root->right ? leftRotate(root) : root;
        }
    }
    
public:
    SplayTree() : root(nullptr) {}
    
    void insert(int key) {
        if (!root) {
            root = new Node(key);
            return;
        }
        
        root = splay(root, key);
        
        if (root->key == key) return;
        
        Node* newNode = new Node(key);
        
        if (key < root->key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        } else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }
        
        root = newNode;
    }
    
    bool search(int key) {
        root = splay(root, key);
        return root && root->key == key;
    }
};

int main() {
    SplayTree st;
    st.insert(100);
    st.insert(50);
    st.insert(200);
    
    cout << "Search 50: " << (st.search(50) ? "true" : "false") << endl;
    return 0;
}
