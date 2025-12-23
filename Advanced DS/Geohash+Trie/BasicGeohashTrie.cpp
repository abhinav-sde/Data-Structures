/**
 * Basic Geohash + Trie Implementation
 * 
 * Demonstrates geohash encoding and trie-based spatial indexing.
 * Educational implementation showing core concepts.
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cmath>
#include <algorithm>
using namespace std;

// Geographic coordinate
struct GeoPoint {
    double lat, lng;
    string data;
    
    GeoPoint(double lat = 0, double lng = 0, const string& data = "")
        : lat(lat), lng(lng), data(data) {}
    
    double distanceTo(const GeoPoint& other) const {
        // Haversine formula
        double R = 6371; // Earth radius in km
        double dLat = (other.lat - lat) * M_PI / 180.0;
        double dLng = (other.lng - lng) * M_PI / 180.0;
        
        double a = sin(dLat/2) * sin(dLat/2) +
                   cos(lat * M_PI / 180.0) * cos(other.lat * M_PI / 180.0) *
                   sin(dLng/2) * sin(dLng/2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        
        return R * c;
    }
};

// Geohash encoder/decoder
class Geohash {
private:
    static constexpr const char* BASE32 = "0123456789bcdefghjkmnpqrstuvwxyz";
    
public:
    // Encode lat/lng to geohash string
    static string encode(double lat, double lng, int precision = 6) {
        string hash;
        double latRange[] = {-90.0, 90.0};
        double lngRange[] = {-180.0, 180.0};
        
        int bit = 0;
        int ch = 0;
        
        while (hash.length() < precision) {
            if (bit % 2 == 0) {
                // Longitude
                double mid = (lngRange[0] + lngRange[1]) / 2;
                if (lng > mid) {
                    ch |= (1 << (4 - bit/2));
                    lngRange[0] = mid;
                } else {
                    lngRange[1] = mid;
                }
            } else {
                // Latitude
                double mid = (latRange[0] + latRange[1]) / 2;
                if (lat > mid) {
                    ch |= (1 << (4 - bit/2));
                    latRange[0] = mid;
                } else {
                    latRange[1] = mid;
                }
            }
            
            bit++;
            
            if (bit == 10) {
                hash += BASE32[ch];
                bit = 0;
                ch = 0;
            }
        }
        
        return hash;
    }
    
    // Decode geohash to lat/lng (center of cell)
    static GeoPoint decode(const string& hash) {
        double latRange[] = {-90.0, 90.0};
        double lngRange[] = {-180.0, 180.0};
        
        bool isEven = true;
        
        for (char c : hash) {
            int idx = string(BASE32).find(c);
            if (idx == string::npos) continue;
            
            for (int mask = 16; mask > 0; mask >>= 1) {
                if (isEven) {
                    // Longitude
                    double mid = (lngRange[0] + lngRange[1]) / 2;
                    if (idx & mask) {
                        lngRange[0] = mid;
                    } else {
                        lngRange[1] = mid;
                    }
                } else {
                    // Latitude
                    double mid = (latRange[0] + latRange[1]) / 2;
                    if (idx & mask) {
                        latRange[0] = mid;
                    } else {
                        latRange[1] = mid;
                    }
                }
                isEven = !isEven;
            }
        }
        
        double lat = (latRange[0] + latRange[1]) / 2;
        double lng = (lngRange[0] + lngRange[1]) / 2;
        
        return GeoPoint(lat, lng);
    }
    
    // Get 8 neighboring geohashes
    static vector<string> neighbors(const string& hash) {
        vector<string> result;
        GeoPoint center = decode(hash);
        
        // Estimate cell size
        double latError = (90.0 / pow(2, hash.length() * 2.5));
        double lngError = (180.0 / pow(2, hash.length() * 2.5));
        
        // Generate 8 neighbors
        for (int dlat = -1; dlat <= 1; dlat++) {
            for (int dlng = -1; dlng <= 1; dlng++) {
                if (dlat == 0 && dlng == 0) continue;
                
                double lat = center.lat + (dlat * latError);
                double lng = center.lng + (dlng * lngError);
                
                result.push_back(encode(lat, lng, hash.length()));
            }
        }
        
        return result;
    }
};

// Trie node
class TrieNode {
public:
    unordered_map<char, unique_ptr<TrieNode>> children;
    vector<GeoPoint> points;  // Points at this node
    bool isEnd;
    
    TrieNode() : isEnd(false) {}
};

// Geohash Trie
class GeohashTrie {
private:
    unique_ptr<TrieNode> root;
    int precision;
    
    // Collect all points under a node
    void collectPoints(TrieNode* node, vector<GeoPoint>& results) {
        if (!node) return;
        
        // Add points at this node
        for (const auto& point : node->points) {
            results.push_back(point);
        }
        
        // Recursively collect from children
        for (auto& child : node->children) {
            collectPoints(child.second.get(), results);
        }
    }
    
public:
    GeohashTrie(int precision = 6) : precision(precision) {
        root = make_unique<TrieNode>();
    }
    
    // Insert a point
    void insert(const GeoPoint& point) {
        string hash = Geohash::encode(point.lat, point.lng, precision);
        
        TrieNode* current = root.get();
        
        for (char c : hash) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = make_unique<TrieNode>();
            }
            current = current->children[c].get();
        }
        
        current->isEnd = true;
        current->points.push_back(point);
    }
    
    // Search for exact geohash
    vector<GeoPoint> search(const string& hash) {
        TrieNode* current = root.get();
        
        for (char c : hash) {
            if (current->children.find(c) == current->children.end()) {
                return {};
            }
            current = current->children[c].get();
        }
        
        return current->points;
    }
    
    // Prefix search - find all points in a region
    vector<GeoPoint> prefixSearch(const string& prefix) {
        TrieNode* current = root.get();
        
        // Navigate to prefix node
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return {};
            }
            current = current->children[c].get();
        }
        
        // Collect all points under this prefix
        vector<GeoPoint> results;
        collectPoints(current, results);
        
        return results;
    }
    
    // Find nearby points (within k geohash cells)
    vector<GeoPoint> findNearby(double lat, double lng, int searchDepth = 1) {
        string centerHash = Geohash::encode(lat, lng, precision);
        vector<GeoPoint> results;
        
        // Search center cell
        auto centerPoints = search(centerHash);
        results.insert(results.end(), centerPoints.begin(), centerPoints.end());
        
        // Search neighbor cells
        if (searchDepth > 0) {
            vector<string> neighborHashes = Geohash::neighbors(centerHash);
            for (const string& hash : neighborHashes) {
                auto points = search(hash);
                results.insert(results.end(), points.begin(), points.end());
            }
        }
        
        return results;
    }
    
    // Find k nearest neighbors (simple version)
    vector<GeoPoint> kNearest(double lat, double lng, int k) {
        GeoPoint query(lat, lng);
        
        // Start with current precision, expand if needed
        for (int depth = 1; depth <= precision; depth++) {
            string prefix = Geohash::encode(lat, lng, depth);
            vector<GeoPoint> candidates = prefixSearch(prefix);
            
            if (candidates.size() >= k) {
                // Sort by distance
                sort(candidates.begin(), candidates.end(),
                     [&query](const GeoPoint& a, const GeoPoint& b) {
                         return query.distanceTo(a) < query.distanceTo(b);
                     });
                
                // Return top k
                candidates.resize(min((int)candidates.size(), k));
                return candidates;
            }
        }
        
        // If still not enough, search all
        vector<GeoPoint> all = prefixSearch("");
        sort(all.begin(), all.end(),
             [&query](const GeoPoint& a, const GeoPoint& b) {
                 return query.distanceTo(a) < query.distanceTo(b);
             });
        all.resize(min((int)all.size(), k));
        return all;
    }
    
    // Print trie statistics
    void printStats() {
        int nodeCount = 0;
        int pointCount = 0;
        
        function<void(TrieNode*)> count = [&](TrieNode* node) {
            if (!node) return;
            nodeCount++;
            pointCount += node->points.size();
            for (auto& child : node->children) {
                count(child.second.get());
            }
        };
        
        count(root.get());
        
        cout << "Trie nodes: " << nodeCount << endl;
        cout << "Total points: " << pointCount << endl;
        cout << "Precision: " << precision << " characters" << endl;
    }
};

// Example usage
int main() {
    cout << "=== Geohash + Trie Demo ===" << endl << endl;
    
    // Example 1: Geohash encoding
    cout << "1. Geohash Encoding:" << endl;
    double lat = 37.7749, lng = -122.4194;  // San Francisco
    string hash = Geohash::encode(lat, lng, 6);
    cout << "  Location: (" << lat << ", " << lng << ")" << endl;
    cout << "  Geohash: " << hash << endl;
    
    // Example 2: Geohash decoding
    cout << "\n2. Geohash Decoding:" << endl;
    GeoPoint decoded = Geohash::decode(hash);
    cout << "  Geohash: " << hash << endl;
    cout << "  Decoded: (" << decoded.lat << ", " << decoded.lng << ")" << endl;
    
    // Example 3: Build geohash trie
    cout << "\n3. Building Geohash Trie:" << endl;
    GeohashTrie trie(6);
    
    vector<GeoPoint> locations = {
        GeoPoint(37.7749, -122.4194, "San Francisco"),
        GeoPoint(37.7849, -122.4094, "Fisherman's Wharf"),
        GeoPoint(37.8044, -122.2712, "Oakland"),
        GeoPoint(37.3382, -121.8863, "San Jose"),
        GeoPoint(40.7128, -74.0060, "New York"),
        GeoPoint(34.0522, -118.2437, "Los Angeles")
    };
    
    for (const auto& loc : locations) {
        trie.insert(loc);
        cout << "  Inserted: " << loc.data 
             << " (" << Geohash::encode(loc.lat, loc.lng, 6) << ")" << endl;
    }
    
    // Example 4: Prefix search
    cout << "\n4. Prefix Search (9q8 = SF Bay Area):" << endl;
    vector<GeoPoint> sfArea = trie.prefixSearch("9q8");
    cout << "  Found " << sfArea.size() << " locations:" << endl;
    for (const auto& loc : sfArea) {
        cout << "    " << loc.data << endl;
    }
    
    // Example 5: Nearby search
    cout << "\n5. Nearby Search (around SF):" << endl;
    vector<GeoPoint> nearby = trie.findNearby(37.77, -122.42, 1);
    cout << "  Found " << nearby.size() << " nearby locations:" << endl;
    for (const auto& loc : nearby) {
        GeoPoint query(37.77, -122.42);
        cout << "    " << loc.data << " (" 
             << query.distanceTo(loc) << " km away)" << endl;
    }
    
    // Example 6: K-nearest neighbors
    cout << "\n6. 3-Nearest Neighbors (from SF):" << endl;
    vector<GeoPoint> knn = trie.kNearest(37.7749, -122.4194, 3);
    for (int i = 0; i < knn.size(); i++) {
        GeoPoint query(37.7749, -122.4194);
        cout << "  " << (i+1) << ". " << knn[i].data 
             << " (" << query.distanceTo(knn[i]) << " km)" << endl;
    }
    
    // Example 7: Geohash neighbors
    cout << "\n7. Neighboring Geohashes:" << endl;
    vector<string> neighbors = Geohash::neighbors("9q8yy");
    cout << "  Neighbors of 9q8yy:" << endl;
    for (const auto& n : neighbors) {
        cout << "    " << n << endl;
    }
    
    // Statistics
    cout << "\n8. Trie Statistics:" << endl;
    trie.printStats();
    
    cout << "\n=== Demo Complete ===" << endl;
    
    return 0;
}
