#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

// Simple Hash Table using Chaining
class HashTable {
private:
    int buckets;
    vector<list<pair<string, string>>> table;

    // Hash Function
    int hashFunction(string key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % buckets;
        }
        return hash;
    }

public:
    HashTable(int size) {
        buckets = size;
        table.resize(size);
    }

    void insert(string key, string value) {
        int index = hashFunction(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value; // Update if exists
                return;
            }
        }
        table[index].push_back({key, value});
    }

    string search(string key) {
        int index = hashFunction(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return "Not Found";
    }

    void remove(string key) {
        int index = hashFunction(key);
        table[index].remove_if([&](pair<string, string> const& pair) {
            return pair.first == key;
        });
    }

    void printTable() {
        for (int i = 0; i < buckets; i++) {
            cout << i << ": ";
            for (auto& pair : table[i]) {
                cout << "[" << pair.first << ":" << pair.second << "] -> ";
            }
            cout << "NULL" << endl;
        }
    }
};

int main() {
    HashTable ht(10);
    ht.insert("name", "Alice");
    ht.insert("age", "25");
    ht.insert("city", "New York");

    cout << "Search 'name': " << ht.search("name") << endl;
    
    ht.printTable();

    ht.remove("age");
    cout << "After removing 'age':" << endl;
    ht.printTable();

    return 0;
}
