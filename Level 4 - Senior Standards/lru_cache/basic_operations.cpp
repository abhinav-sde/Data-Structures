#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

/**
 * LRU Cache using std::list (DLL) and std::unordered_map
 */
class LRUCache {
    int capacity;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> map;

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        if (map.find(key) == map.end()) return -1;
        // Move to front (list::splice)
        cache.splice(cache.begin(), cache, map[key]);
        return map[key]->second;
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            cache.erase(map[key]);
        } else if (cache.size() == capacity) {
            map.erase(cache.back().first);
            cache.pop_back();
        }
        cache.push_front({key, value});
        map[key] = cache.begin();
    }

    void display() {
        cout << "LRU State: ";
        for (auto it : cache) cout << "[" << it.first << ":" << it.second << "] ";
        cout << endl;
    }
};

int main() {
    LRUCache lru(2);
    lru.put(1, 1);
    lru.put(2, 2);
    lru.display();
    lru.get(1);
    lru.put(3, 3);
    lru.display();
    return 0;
}
