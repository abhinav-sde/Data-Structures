#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

/**
 * LFU Cache using:
 * 1. Key Table: key -> {value, freq, iterator to list}
 * 2. Frequency Table: freq -> list of keys
 */
class LFUCache {
    int capacity;
    int minFreq;
    
    struct Node {
        int key, value, freq;
    };

    unordered_map<int, list<Node>::iterator> keyMap;
    unordered_map<int, list<Node>> freqMap;

public:
    LFUCache(int cap) : capacity(cap), minFreq(0) {}

    int get(int key) {
        if (keyMap.find(key) == keyMap.end()) return -1;
        update(keyMap[key]);
        return keyMap[key]->value;
    }

    void put(int key, int value) {
        if (capacity <= 0) return;
        if (get(key) != -1) {
            keyMap[key]->value = value;
            return;
        }
        if (keyMap.size() >= capacity) {
            keyMap.erase(freqMap[minFreq].back().key);
            freqMap[minFreq].pop_back();
        }
        minFreq = 1;
        freqMap[1].push_front({key, value, 1});
        keyMap[key] = freqMap[1].begin();
    }

    void update(list<Node>::iterator it) {
        int key = it->key, val = it->value, freq = it->freq;
        freqMap[freq].erase(it);
        if (freqMap[freq].empty() && freq == minFreq) minFreq++;
        freqMap[freq + 1].push_front({key, val, freq + 1});
        keyMap[key] = freqMap[freq + 1].begin();
    }

    void display() {
        cout << "LFU (minFreq " << minFreq << "): ";
        for (auto const& [key, it] : keyMap) cout << key << ":" << it->value << " ";
        cout << endl;
    }
};

int main() {
    LFUCache lfu(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    lfu.display();
    lfu.get(1);
    lru.put(3, 3); // Error: lfu.put(3, 3)
    lfu.put(3, 3);
    lfu.display();
    return 0;
}
