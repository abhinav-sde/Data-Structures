/**
 * MX Quad Tree Implementation in Java
 * 
 * Used for image representation and compression.
 * Each node represents a square region, subdividing until
 * all pixels in a region have the same color/value.
 */

import java.util.*;

class Color {
    int r, g, b;
    
    public Color(int r, int g, int b) {
        this.r = r;
        this.g = g;
        this.b = b;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Color)) return false;
        Color other = (Color) obj;
        return r == other.r && g == other.g && b == other.b;
    }
    
    public void print() {
        System.out.printf("RGB(%d,%d,%d)", r, g, b);
    }
}

class MXQuadTreeNode {
    int x, y, size;
    Color color;
    boolean isLeaf;
    
    // Four children
    MXQuadTreeNode nw, ne, sw, se;
    
    public MXQuadTreeNode(int x, int y, int size) {
        this.x = x;
        this.y = y;
        this.size = size;
        this.isLeaf = true;
    }
}

public class MXQuadTree {
    private MXQuadTreeNode root;
    private Color[][] image;
    private int size;
    
    public MXQuadTree(Color[][] image) {
        this.image = image;
        this.size = image.length;
        this.root = buildTree(0, 0, size);
    }
    
    private MXQuadTreeNode buildTree(int x, int y, int size) {
        MXQuadTreeNode node = new MXQuadTreeNode(x, y, size);
        
        // Check if region is uniform
        Color firstColor = image[y][x];
        boolean isUniform = true;
        
        outerLoop:
        for (int i = y; i < y + size; i++) {
            for (int j = x; j < x + size; j++) {
                if (!image[i][j].equals(firstColor)) {
                    isUniform = false;
                    break outerLoop;
                }
            }
        }
        
        if (isUniform || size == 1) {
            // Leaf node - uniform region
            node.isLeaf = true;
            node.color = firstColor;
        } else {
            // Internal node - subdivide
            node.isLeaf = false;
            int half = size / 2;
            
            node.nw = buildTree(x, y + half, half);
            node.ne = buildTree(x + half, y + half, half);
            node.sw = buildTree(x, y, half);
            node.se = buildTree(x + half, y, half);
        }
        
        return node;
    }
    
    public Color getPixel(int x, int y) {
        return getPixelRecursive(root, x, y);
    }
    
    private Color getPixelRecursive(MXQuadTreeNode node, int x, int y) {
        if (node == null) return new Color(0, 0, 0);
        
        if (node.isLeaf) {
            return node.color;
        }
        
        int half = node.size / 2;
        int midX = node.x + half;
        int midY = node.y + half;
        
        if (x < midX) {
            if (y < midY) {
                return getPixelRecursive(node.sw, x, y);
            } else {
                return getPixelRecursive(node.nw, x, y);
            }
        } else {
            if (y < midY) {
                return getPixelRecursive(node.se, x, y);
            } else {
                return getPixelRecursive(node.ne, x, y);
            }
        }
    }
    
    private int countNodes(MXQuadTreeNode node) {
        if (node == null) return 0;
        
        if (node.isLeaf) {
            return 1;
        }
        
        return 1 + countNodes(node.nw) + countNodes(node.ne) +
                   countNodes(node.sw) + countNodes(node.se);
    }
    
    public void compressionStats() {
        int nodes = countNodes(root);
        int totalPixels = size * size;
        double compressionRatio = (1.0 - (double) nodes / totalPixels) * 100.0;
        
        System.out.println("Nodes: " + nodes);
        System.out.println("Total Pixels: " + totalPixels);
        System.out.printf("Compression: %.2f%%%n", compressionRatio);
    }
    
    public Color[][] reconstructImage() {
        Color[][] result = new Color[size][size];
        reconstructRecursive(root, result);
        return result;
    }
    
    private void reconstructRecursive(MXQuadTreeNode node, Color[][] result) {
        if (node == null) return;
        
        if (node.isLeaf) {
            // Fill region with color
            for (int i = node.y; i < node.y + node.size; i++) {
                for (int j = node.x; j < node.x + node.size; j++) {
                    result[i][j] = node.color;
                }
            }
        } else {
            // Recurse into children
            reconstructRecursive(node.nw, result);
            reconstructRecursive(node.ne, result);
            reconstructRecursive(node.sw, result);
            reconstructRecursive(node.se, result);
        }
    }
    
    private static void printImage(Color[][] img) {
        Color white = new Color(255, 255, 255);
        Color black = new Color(0, 0, 0);
        
        for (Color[] row : img) {
            for (Color pixel : row) {
                if (pixel.equals(white)) {
                    System.out.print("W ");
                } else if (pixel.equals(black)) {
                    System.out.print("B ");
                } else {
                    System.out.print("? ");
                }
            }
            System.out.println();
        }
    }
    
    // Example usage
    public static void main(String[] args) {
        System.out.println("=== MX Quad Tree Demo ===\n");
        
        // Create a simple 8x8 checkerboard image
        Color white = new Color(255, 255, 255);
        Color black = new Color(0, 0, 0);
        
        Color[][] image = {
            {white, white, white, white, black, black, black, black},
            {white, white, white, white, black, black, black, black},
            {white, white, white, white, black, black, black, black},
            {white, white, white, white, black, black, black, black},
            {black, black, black, black, white, white, white, white},
            {black, black, black, black, white, white, white, white},
            {black, black, black, black, white, white, white, white},
            {black, black, black, black, white, white, white, white},
        };
        
        System.out.println("Original Image (W=White, B=Black):");
        printImage(image);
        
        // Build quad tree
        System.out.println("\nBuilding MX Quad Tree...");
        MXQuadTree qt = new MXQuadTree(image);
        
        // Get compression stats
        System.out.println("\nCompression Statistics:");
        qt.compressionStats();
        
        // Verify reconstruction
        System.out.println("\nReconstructed Image:");
        Color[][] reconstructed = qt.reconstructImage();
        printImage(reconstructed);
        
        // Verify pixel access
        System.out.print("\nPixel at (2, 2): ");
        qt.getPixel(2, 2).print();
        System.out.println();
        
        System.out.print("Pixel at (6, 6): ");
        qt.getPixel(6, 6).print();
        System.out.println();
    }
}
