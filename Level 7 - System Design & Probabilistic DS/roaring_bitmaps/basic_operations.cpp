#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <bitset>

/**
 * Basic Roaring Bitmap Operations in C++
 * Implements Array and Bitmap containers.
 */

class Container {
public:
    virtual ~Container() {}
    virtual bool add(uint16_t val) = 0;
    virtual bool contains(uint16_t val) = 0;
    virtual int size() = 0;
};

class ArrayContainer : public Container {
public:
    std::vector<uint16_t> content;
    bool add(uint16_t val) override {
        auto it = std::lower_bound(content.begin(), content.end(), val);
        if (it != content.end() && *it == val) return false;
        content.insert(it, val);
        return true;
    }
    bool contains(uint16_t val) override {
        return std::binary_search(content.begin(), content.end(), val);
    }
    int size() override { return content.size(); }
};

class BitmapContainer : public Container {
public:
    std::bitset<65536> bits;
    int count = 0;
    bool add(uint16_t val) override {
        if (!bits.test(val)) {
            bits.set(val);
            count++;
            return true;
        }
        return false;
    }
    bool contains(uint16_t val) override { return bits.test(val); }
    int size() override { return count; }
};

class RoaringBitmap {
private:
    std::map<uint16_t, Container*> chunks;
    const int THRESHOLD = 4096;

public:
    void add(uint32_t x) {
        uint16_t key = x >> 16;
        uint16_t val = x & 0xFFFF;
        if (chunks.find(key) == chunks.end()) {
            chunks[key] = new ArrayContainer();
        }
        Container* c = chunks[key];
        c->add(val);
        if (c->size() > THRESHOLD && dynamic_cast<ArrayContainer*>(c)) {
            BitmapContainer* bc = new BitmapContainer();
            for (uint16_t v : dynamic_cast<ArrayContainer*>(c)->content) bc->add(v);
            delete c;
            chunks[key] = bc;
        }
    }

    bool contains(uint32_t x) {
        uint16_t key = x >> 16;
        uint16_t val = x & 0xFFFF;
        if (chunks.find(key) == chunks.end()) return false;
        return chunks[key]->contains(val);
    }
};

int main() {
    RoaringBitmap rb;
    rb.add(100);
    rb.add(1000000);

    std::cout << "Contains 100: " << (rb.contains(100) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 500: " << (rb.contains(500) ? "Yes" : "No") << std::endl;

    for (int i = 0; i < 5000; ++i) rb.add(i);
    std::cout << "After dense add, contains 2500: " << (rb.contains(2500) ? "Yes" : "No") << std::endl;

    return 0;
}
