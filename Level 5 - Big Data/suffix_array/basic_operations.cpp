#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class SuffixArray {
private:
    string text;
    vector<int> suffixArray;
    
public:
    SuffixArray(string txt) : text(txt) {
        buildSuffixArray();
    }
    
    void buildSuffixArray() {
        int n = text.length();
        vector<pair<string, int>> suffixes;
        
        for (int i = 0; i < n; i++) {
            suffixes.push_back({text.substr(i), i});
        }
        
        sort(suffixes.begin(), suffixes.end());
        
        for (auto& p : suffixes) {
            suffixArray.push_back(p.second);
        }
    }
    
    void display() {
        cout << "Suffix Array:" << endl;
        for (int i = 0; i < suffixArray.size(); i++) {
            cout << i << ": " << text.substr(suffixArray[i]) << endl;
        }
    }
};

int main() {
    SuffixArray sa("banana");
    sa.display();
    return 0;
}
