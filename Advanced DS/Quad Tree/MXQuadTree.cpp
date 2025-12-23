/**
 * MX Quad Tree Implementation
 * 
 * Used for image representation and compression.
 * Each node represents a square region, subdividing until
 * all pixels in a region have the same color/value.
 */

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Color structure
struct Color {
    int r, g, b;
    
    Color(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {}
    
    bool operator==(const Color& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
    
    bool operator!=(const Color& other) const {
        return !(*this == other);
    }
    
    void print() const {
        cout << "RGB(" << r << "," << g << "," << b << ")";
    }
};

// Node class for MX Quad Tree
class MXQuadTreeNode {
public:
    int x, y, size;
    Color color;
    bool isLeaf;
    
    // Four children
    unique_ptr<MXQuadTreeNode> nw;
    unique_ptr<MXQuadTreeNode> ne;
    unique_ptr<MXQuadTreeNode> sw;
    unique_ptr<MXQuadTreeNode> se;
    
    MXQuadTreeNode(int x, int y, int size)
        : x(x), y(y), size(size), color(0, 0, 0), isLeaf(true),
          nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr) {}
};

// MX Quad Tree class
class MXQuadTree {
private:
    unique_ptr<MXQuadTreeNode> root;
    vector<vector<Color>> image;
    int size;
    
    // Build tree recursively from image
    unique_ptr<MXQuadTreeNode> buildTree(int x, int y, int size) {
        auto node = make_unique<MXQuadTreeNode>(x, y, size);
        
        // Check if region is uniform
        Color firstColor = image[y][x];
        bool isUniform = true;
        
        for (int i = y; i < y + size && isUniform; i++) {
            for (int j = x; j < x + size && isUniform; j++) {
                if (image[i][j] != firstColor) {
                    isUniform = false;
                }
            }
        }
        
        if (isUniform || size == 1) {
            // Leaf node - uniform region
            node->isLeaf = true;
            node->color = firstColor;
        } else {
            // Internal node - subdivide
            node->isLeaf = false;
            int half = size / 2;
            
            node->nw = buildTree(x, y + half, half);
            node->ne = buildTree(x + half, y + half, half);
            node->sw = buildTree(x, y, half);
            node->se = buildTree(x + half, y, half);
        }
        
        return node;
    }
    
    // Get color at specific pixel
    Color getPixelRecursive(MXQuadTreeNode* node, int x, int y) {
        if (!node) return Color(0, 0, 0);
        
        if (node->isLeaf) {
            return node->color;
        }
        
        int half = node->size / 2;
        int midX = node->x + half;
        int midY = node->y + half;
        
        if (x < midX) {
            if (y < midY) {
                return getPixelRecursive(node->sw.get(), x, y);
            } else {
                return getPixelRecursive(node->nw.get(), x, y);
            }
        } else {
            if (y < midY) {
                return getPixelRecursive(node->se.get(), x, y);
            } else {
                return getPixelRecursive(node->ne.get(), x, y);
            }
        }
    }
    
    // Count total nodes
    int countNodes(MXQuadTreeNode* node) {
        if (!node) return 0;
        
        if (node->isLeaf) {
            return 1;
        }
        
        return 1 + countNodes(node->nw.get()) + 
                   countNodes(node->ne.get()) +
                   countNodes(node->sw.get()) + 
                   countNodes(node->se.get());
    }
    
    // Reconstruct image from tree
    void reconstructRecursive(MXQuadTreeNode* node, 
                             vector<vector<Color>>& result) {
        if (!node) return;
        
        if (node->isLeaf) {
            // Fill region with color
            for (int i = node->y; i < node->y + node->size; i++) {
                for (int j = node->x; j < node->x + node->size; j++) {
                    result[i][j] = node->color;
                }
            }
        } else {
            // Recurse into children
            reconstructRecursive(node->nw.get(), result);
            reconstructRecursive(node->ne.get(), result);
            reconstructRecursive(node->sw.get(), result);
            reconstructRecursive(node->se.get(), result);
        }
    }
    
    // Print tree structure (for debugging)
    void printTreeRecursive(MXQuadTreeNode* node, int depth = 0) {
        if (!node) return;
        
        string indent(depth * 2, ' ');
        
        if (node->isLeaf) {
            cout << indent << "Leaf at (" << node->x << "," << node->y 
                 << ") size=" << node->size << " color=";
            node->color.print();
            cout << endl;
        } else {
            cout << indent << "Internal at (" << node->x << "," << node->y 
                 << ") size=" << node->size << endl;
            printTreeRecursive(node->nw.get(), depth + 1);
            printTreeRecursive(node->ne.get(), depth + 1);
            printTreeRecursive(node->sw.get(), depth + 1);
            printTreeRecursive(node->se.get(), depth + 1);
        }
    }
    
public:
    MXQuadTree(const vector<vector<Color>>& img) {
        image = img;
        size = img.size();
        root = buildTree(0, 0, size);
    }
    
    // Get color at specific pixel
    Color getPixel(int x, int y) {
        return getPixelRecursive(root.get(), x, y);
    }
    
    // Calculate compression statistics
    void compressionStats() {
        int nodes = countNodes(root.get());
        int totalPixels = size * size;
        double compressionRatio = (1.0 - (double)nodes / totalPixels) * 100.0;
        
        cout << "Nodes: " << nodes << endl;
        cout << "Total Pixels: " << totalPixels << endl;
        cout << "Compression: " << compressionRatio << "%" << endl;
    }
    
    // Reconstruct image from quad tree
    vector<vector<Color>> reconstructImage() {
        vector<vector<Color>> result(size, vector<Color>(size));
        reconstructRecursive(root.get(), result);
        return result;
    }
    
    // Print tree structure
    void printTree() {
        printTreeRecursive(root.get());
    }
};

// Helper function to print image
void printImage(const vector<vector<Color>>& img) {
    for (const auto& row : img) {
        for (const auto& pixel : row) {
            if (pixel == Color(255, 255, 255)) {
                cout << "W ";
            } else if (pixel == Color(0, 0, 0)) {
                cout << "B ";
            } else {
                cout << "? ";
            }
        }
        cout << endl;
    }
}

// Example usage
int main() {
    cout << "=== MX Quad Tree Demo ===" << endl << endl;
    
    // Create a simple 8x8 checkerboard image
    Color white(255, 255, 255);
    Color black(0, 0, 0);
    
    vector<vector<Color>> image = {
        {white, white, white, white, black, black, black, black},
        {white, white, white, white, black, black, black, black},
        {white, white, white, white, black, black, black, black},
        {white, white, white, white, black, black, black, black},
        {black, black, black, black, white, white, white, white},
        {black, black, black, black, white, white, white, white},
        {black, black, black, black, white, white, white, white},
        {black, black, black, black, white, white, white, white},
    };
    
    cout << "Original Image (W=White, B=Black):" << endl;
    printImage(image);
    
    // Build quad tree
    cout << "\nBuilding MX Quad Tree..." << endl;
    MXQuadTree qt(image);
    
    // Get compression stats
    cout << "\nCompression Statistics:" << endl;
    qt.compressionStats();
    
    // Verify reconstruction
    cout << "\nReconstructed Image:" << endl;
    vector<vector<Color>> reconstructed = qt.reconstructImage();
    printImage(reconstructed);
    
    // Verify pixel access
    cout << "\nPixel at (2, 2): ";
    qt.getPixel(2, 2).print();
    cout << endl;
    
    cout << "Pixel at (6, 6): ";
    qt.getPixel(6, 6).print();
    cout << endl;
    
    return 0;
}
