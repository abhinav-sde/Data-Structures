#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int value;
    Node** forward;
    int level;
    
    Node(int val, int lvl) : value(val), level(lvl) {
        forward = new Node*[lvl + 1];
        for (int i = 0; i <= lvl; i++) {
            forward[i] = nullptr;
        }
    }
};

class SkipList {
private:
    static const int MAX_LEVEL = 16;
    Node* header;
    int level;
    
    int randomLevel() {
        int lvl = 0;
        while (lvl < MAX_LEVEL && (rand() % 2)) {
            lvl++;
        }
        return lvl;
    }
    
public:
    SkipList() {
        srand(time(0));
        header = new Node(INT32_MIN, MAX_LEVEL);
        level = 0;
    }
    
    bool search(int target) {
        Node* current = header;
        
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < target) {
                current = current->forward[i];
            }
        }
        
        current = current->forward[0];
        return current && current->value == target;
    }
    
    void insert(int value) {
        Node* update[MAX_LEVEL + 1];
        Node* current = header;
        
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        current = current->forward[0];
        
        if (!current || current->value != value) {
            int newLevel = randomLevel();
            
            if (newLevel > level) {
                for (int i = level + 1; i <= newLevel; i++) {
                    update[i] = header;
                }
                level = newLevel;
            }
            
            Node* newNode = new Node(value, newLevel);
            
            for (int i = 0; i <= newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }
};

int main() {
    SkipList sl;
    sl.insert(3);
    sl.insert(6);
    sl.insert(7);
    
    cout << "Search 6: " << (sl.search(6) ? "true" : "false") << endl;
    cout << "Search 5: " << (sl.search(5) ? "true" : "false") << endl;
    
    return 0;
}
