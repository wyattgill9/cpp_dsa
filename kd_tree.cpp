#include <vector>
#include <iostream>

struct Point {
    std::vector<double> coords;

    bool operator==(const Point& other) {
        return coords == other.coords;
    }
};

struct Node {
    Point point;
    
    Node* left;
    Node* right;

    Node(Point point) : point(point), left(nullptr), right(nullptr) {}
};

struct KDTree {
    Node* root;
    int k; // dimensions
    
    KDTree(int dimensions) : root(nullptr), k(!dimensions ? 1 : dimensions) {}

    void insert(Point point) {
        root = insert_recursive(root, point, 0);
    }

    bool search(Point point) {
        return search_recursive(root, point, 0);
    }

private:
    Node* insert_recursive(Node* node, Point point, int depth) {
        if(node == nullptr) {
            return new Node(point);
        }
        
        // alternate between dimensions x, y as you go down 
        int curr_dim = depth % k;
        
        // if the new point coords in the cur dimension is less than the nodes go left
        // otherwise go right
        if(point.coords[curr_dim] < node->point.coords[curr_dim]) {
            node->left = insert_recursive(node->left, point, depth + 1);
        } else {
            node->right = insert_recursive(node->right, point, depth + 1);
        }

        return node;
    }
    
    // same as insert, just traverse the tree until we find the point
    bool search_recursive(Node* node, Point point, int depth) {
        if(node == nullptr) {
            return false;
        }
        
        if(node->point == point) {
            return true;
        }

        int cur_dim = depth % k;
        
        if(point.coords[cur_dim] < node->point.coords[cur_dim]) {
            return search_recursive(node->left, point, depth + 1);
        } else {
            return search_recursive(node->right, point, depth + 1);
        }
    }
};

auto main() -> int {
    KDTree tree(2);

    tree.insert({{1, 2}}); // 1, 2 becomes root
    tree.insert({{3, 4}}); // 3, 4 becomes right child
    tree.insert({{5, 6}}); // 5,6 becomes right child of 3,4
    
    Point query = {{5, 6}};
    std::cout << tree.search(query) << "\n";

    return 0;
}
