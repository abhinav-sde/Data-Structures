#include <iostream>
#include <vector>
#include <string>
#include <bitset>
using namespace std;

class BloomFilter {
private:
    static const int SIZE = 1000;
    bitset<SIZE> bits;
    int numHashFunctions;
    
    int hash(const string& item, int seed) {
        int h = 0;
        for (char c : item) {
            h = (h * seed + c) % SIZE;
        }
        return abs(h);
    }
    
public:
    BloomFilter(int numHash) : numHashFunctions(numHash) {}
    
    void add(const string& item) {
        for (int i = 0; i < numHashFunctions; i++) {
            int index = hash(item, i + 1);
            bits.set(index);
        }
    }
    
    bool mightContain(const string& item) {
        for (int i = 0; i < numHashFunctions; i++) {
            int index = hash(item, i + 1);
            if (!bits.test(index)) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    BloomFilter bf(3);
    
    bf.add("apple");
    bf.add("banana");
    
    cout << "Contains 'apple': " << (bf.mightContain("apple") ? "true" : "false") << endl;
    cout << "Contains 'grape': " << (bf.mightContain("grape") ? "true" : "false") << endl;
    
    return 0;
}
