#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iomanip>

/**
 * Core Cuckoo Filter Problems in C++
 * Focuses on False Positive Rate measurement.
 */

// We reuse the logic from basic_operations.cpp (assuming it's available or implemented similarly)
#include "basic_operations.cpp" // Simplified for the example, usually would be a header

int main() {
    int capacity = 1000;
    CuckooFilter cf(capacity);

    std::cout << "Inserting 500 items..." << std::endl;
    for (int i = 0; i < 500; ++i) {
        cf.insert("data_" + std::to_string(i));
    }

    int fp_count = 0;
    int trials = 10000;
    std::cout << "Testing 10,000 random items..." << std::endl;
    for (int i = 0; i < trials; ++i) {
        if (cf.lookup("test_" + std::to_string(i))) {
            fp_count++;
        }
    }

    double fpr = (double)fp_count / trials * 100;
    std::cout << "False Positives: " << fp_count << std::endl;
    std::cout << "Empirical FPR: " << std::fixed << std::setprecision(4) << fpr << "%" << std::endl;

    return 0;
}
