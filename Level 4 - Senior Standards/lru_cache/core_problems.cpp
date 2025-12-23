#include <iostream>
#include <mutex>
#include <unordered_map>
#include <list>

using namespace std;

/**
 * Thread-Safe LRU Cache using std::mutex
 */
template <typename K, typename V>
class ThreadSafeLRU {
    int capacity;
    list<pair<K, V>> cache;
    unordered_map<K, typename list<pair<K, V>>::iterator> map;
    mutex mtx;

public:
    ThreadSafeLRU(int cap) : capacity(cap) {}

    V get(K key) {
        lock_guard<mutex> lock(mtx);
        if (map.find(key) == map.end()) return V();
        cache.splice(cache.begin(), cache, map[key]);
        return map[key]->second;
    }

    void put(K key, V value) {
        lock_guard<mutex> lock(mtx);
        if (map.find(key) != map.end()) {
            cache.erase(map[key]);
        } else if (cache.size() == capacity) {
            map.erase(cache.back().first);
            cache.pop_back();
        }
        cache.push_front({key, value});
        map[key] = cache.begin();
    }
};

int main() {
    ThreadSafeLRU<int, string> lru(5);
    lru.put(1, "SDE2");
    cout << "Value: " << lru.get(1) << endl;
    return 0;
}
