#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

/**
 * Advanced Cuckoo Filter Problems in C++
 * Focuses on Load Factor and Saturation.
 */

#include "basic_operations.cpp"

int main() {
    int capacity = 1000;
    CuckooFilter cf(capacity);

    std::cout << "Filling filter until it fails..." << std::endl;
    int count = 0;
    for (int i = 0; i < 2000; ++i) {
        if (!cf.insert("val_" + std::to_string(i))) {
            count = i;
            break;
        }
    }

    double lf = (double)count / capacity * 100;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "Inserted: " << count << std::endl;
    std::cout << "Load Factor: " << std::fixed << std::setprecision(2) << lf << "%" << std::endl;

    std::cout << "\nFreeing space by deleting 50 items..." << std::endl;
    for(int i=0; i<50; ++i) cf.remove("val_" + std::to_string(i));
    
    std::cout << "Insert after delete: " << (cf.insert("retry_1") ? "Success" : "Failed") << std::endl;

    return 0;
}
