/**
 * Basic H3-style Hexagonal Grid Implementation (Simplified Educational Version)
 * 
 * Demonstrates core H3 concepts: coordinate conversion, indexing, and basic operations.
 * This is a simplified version for learning - use official H3 library for production.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// Hex coordinate using axial coordinates (q, r)
struct HexCoord {
    int q, r;  // Axial coordinates
    
    HexCoord(int q = 0, int r = 0) : q(q), r(r) {}
    
    int s() const { return -q - r; }  // Cube coordinate s
    
    bool operator==(const HexCoord& other) const {
        return q == other.q && r == other.r;
    }
};

// Geographic coordinate
struct GeoCoord {
    double lat, lng;
    
    GeoCoord(double lat = 0, double lng = 0) : lat(lat), lng(lng) {}
};

// Simplified H3 Index (educational - not actual H3 format)
struct H3Index {
    int resolution;
    HexCoord coord;
    
    H3Index(int res = 0, HexCoord c = HexCoord()) 
        : resolution(res), coord(c) {}
    
    // Convert to string representation
    string toString() const {
        stringstream ss;
        ss << "R" << resolution << "_Q" << coord.q << "_R" << coord.r;
        return ss.str();
    }
};

// Basic H3-style operations
class BasicH3 {
private:
    static constexpr double HEX_SIZE_BASE = 100.0;  // km at resolution 0
    static constinit double SQRT3 = 1.732050808;
    
    // Get hexagon size for resolution (simplified)
    static double getHexSize(int resolution) {
        return HEX_SIZE_BASE / pow(7, resolution * 0.5);
    }
    
    // Convert lat/lng to hexagon (simplified flat projection)
    static HexCoord geoToHex(double lat, double lng, int resolution) {
        double hexSize = getHexSize(resolution);
        
        // Simplified conversion (not actual H3 icosahedral projection)
        double x = lng;
        double y = lat;
        
        // Convert to hex axial coordinates
        double q = (SQRT3/3.0 * x - 1.0/3.0 * y) / hexSize;
        double r = (2.0/3.0 * y) / hexSize;
        
        // Round to nearest hex
        return hexRound(q, r);
    }
    
    // Round fractional hex coordinates to nearest hex
    static HexCoord hexRound(double q, double r) {
        double s = -q - r;
        
        int rq = round(q);
        int rr = round(r);
        int rs = round(s);
        
        double q_diff = abs(rq - q);
        double r_diff = abs(rr - r);
        double s_diff = abs(rs - s);
        
        if (q_diff > r_diff && q_diff > s_diff) {
            rq = -rr - rs;
        } else if (r_diff > s_diff) {
            rr = -rq - rs;
        }
        
        return HexCoord(rq, rr);
    }
    
public:
    // Convert geographic coordinate to H3 index
    static H3Index geoToH3(double lat, double lng, int resolution) {
        HexCoord hex = geoToHex(lat, lng, resolution);
        return H3Index(resolution, hex);
    }
    
    // Convert H3 index to geographic coordinate (center)
    static GeoCoord h3ToGeo(const H3Index& h3) {
        double hexSize = getHexSize(h3.resolution);
        
        // Convert hex coordinates to lat/lng
        double x = hexSize * (SQRT3 * h3.coord.q + SQRT3/2.0 * h3.coord.r);
        double y = hexSize * (3.0/2.0 * h3.coord.r);
        
        return GeoCoord(y, x);
    }
    
    // Get the 6 neighbors of a hexagon
    static vector<H3Index> getNeighbors(const H3Index& h3) {
        vector<H3Index> neighbors;
        
        // 6 directions in axial coordinates
        vector<pair<int, int>> directions = {
            {1, 0}, {1, -1}, {0, -1},
            {-1, 0}, {-1, 1}, {0, 1}
        };
        
        for (const auto& dir : directions) {
            HexCoord neighbor(h3.coord.q + dir.first, 
                            h3.coord.r + dir.second);
            neighbors.push_back(H3Index(h3.resolution, neighbor));
        }
        
        return neighbors;
    }
    
    // Get all hexagons within k steps (k-ring)
    static vector<H3Index> kRing(const H3Index& h3, int k) {
        vector<H3Index> results;
        
        for (int dq = -k; dq <= k; dq++) {
            for (int dr = max(-k, -dq - k); dr <= min(k, -dq + k); dr++) {
                HexCoord hex(h3.coord.q + dq, h3.coord.r + dr);
                results.push_back(H3Index(h3.resolution, hex));
            }
        }
        
        return results;
    }
    
    // Get hollow ring at distance k
    static vector<H3Index> hexRing(const H3Index& h3, int k) {
        if (k == 0) {
            return {h3};
        }
        
        vector<H3Index> results;
        
        // Start at kstep from hex in direction 4
        HexCoord current(h3.coord.q - k, h3.coord.r + k);
        
        // 6 directions for the ring
        vector<pair<int, int>> directions = {
            {1, 0}, {1, -1}, {0, -1},
            {-1, 0}, {-1, 1}, {0, 1}
        };
        
        // Walk around the ring
        for (const auto& dir : directions) {
            for (int i = 0; i < k; i++) {
                results.push_back(H3Index(h3.resolution, current));
                current.q += dir.first;
                current.r += dir.second;
            }
        }
        
        return results;
    }
    
    // Calculate grid distance between two hexagons
    static int gridDistance(const H3Index& a, const H3Index& b) {
        if (a.resolution != b.resolution) {
            cerr << "Cannot calculate distance between different resolutions" << endl;
            return -1;
        }
        
        int dq = abs(a.coord.q - b.coord.q);
        int dr = abs(a.coord.r - b.coord.r);
        int ds = abs(a.coord.s() - b.coord.s());
        
        return max({dq, dr, ds});
    }
    
    // Get area of hexagon at resolution (km²)
    static double hexArea(int resolution) {
        double hexSize = getHexSize(resolution);
        return 2.598 * hexSize * hexSize;  // Area = (3√3/2) * side²
    }
};

// Example usage
int main() {
    cout << "=== Basic H3-Style Hexagonal Grid Demo ===" << endl << endl;
    cout << "Note: This is a simplified educational implementation." << endl;
    cout << "For production use, please use official H3 library." << endl << endl;
    
    // Example 1: Convert coordinates to H3
    cout << "1. Geographic to H3 Index:" << endl;
    double lat = 37.7749, lng = -122.4194;  // San Francisco
    int resolution = 8;
    
    H3Index h3 = BasicH3::geoToH3(lat, lng, resolution);
    cout << "  Coords: (" << lat << ", " << lng << ")" << endl;
    cout << "  H3 Index: " << h3.toString() << endl;
    cout << "  Resolution: " << h3.resolution << endl;
    
    // Example 2: Convert H3 back to coordinates
    cout << "\n2. H3 Index to Geographic:" << endl;
    GeoCoord center = BasicH3::h3ToGeo(h3);
    cout << "  H3 Index: " << h3.toString() << endl;
    cout << "  Center: (" << center.lat << ", " << center.lng << ")" << endl;
    
    // Example 3: Get neighbors
    cout << "\n3. Get 6 Neighbors:" << endl;
    vector<H3Index> neighbors = BasicH3::getNeighbors(h3);
    cout << "  Neighbors of " << h3.toString() << ":" << endl;
    for (const auto& neighbor : neighbors) {
        cout << "    " << neighbor.toString() << endl;
    }
    
    // Example 4: k-Ring
    cout << "\n4. k-Ring (k=1):" << endl;
    vector<H3Index> kring1 = BasicH3::kRing(h3, 1);
    cout << "  k-Ring contains " << kring1.size() << " hexagons" << endl;
    cout << "  (1 center + 6 neighbors = 7 total)" << endl;
    
    cout << "\n5. k-Ring (k=2):" << endl;
    vector<H3Index> kring2 = BasicH3::kRing(h3, 2);
    cout << "  k-Ring contains " << kring2.size() << " hexagons" << endl;
    cout << "  (1 center + 6 + 12 = 19 total)" << endl;
    
    // Example 5: Hex Ring (hollow)
    cout << "\n6. Hollow Ring (k=2):" << endl;
    vector<H3Index> ring2 = BasicH3::hexRing(h3, 2);
    cout << "  Hollow ring contains " << ring2.size() << " hexagons" << endl;
    
    // Example 6: Grid distance
    cout << "\n7. Grid Distance:" << endl;
    H3Index h3_2 = BasicH3::geoToH3(37.8, -122.4, resolution);
    int dist = BasicH3::gridDistance(h3, h3_2);
    cout << "  Distance between " << h3.toString() 
         << " and " << h3_2.toString() << ": " << dist << " steps" << endl;
    
    // Example 7: Hex area
    cout << "\n8. Hexagon Area at Resolution " << resolution << ":" << endl;
    double area = BasicH3::hexArea(resolution);
    cout << "  Area: " << area << " km²" << endl;
    
    cout << "\n=== Demo Complete ===" << endl;
    cout << "Key Concepts Demonstrated:" << endl;
    cout << "  ✓ Coordinate conversion (geo ↔ H3)" << endl;
    cout << "  ✓ Neighbor finding (6 adjacent hexagons)" << endl;
    cout << "  ✓ k-Ring generation (all hexagons within k steps)" << endl;
    cout << "  ✓ Grid distance calculation" << endl;
    cout << "  ✓ Hexagon area calculation" << endl;
    
    return 0;
}
