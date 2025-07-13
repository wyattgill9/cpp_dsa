#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

struct BinaryTree {
private:
    Node* root;

    Node* insert_recursive(Node* node, int data) {
        if(node == nullptr) {
            return new Node(data);
        }

        if(data < node->data) {
            node->left = insert_recursive(node->left, data);
        } else {
            node->right = insert_recursive(node->right, data);
        }
        
        return node;
    }
    
    bool search_recursive(Node* node, int data) const {
        if(node == nullptr) {
            return false;
        }
        
        if(node->data == data) {
            return true;
        }
        
        if(data < node->data) {
            return search_recursive(node->left, data);
        } else {
            return search_recursive(node->right, data);
        }
    }
    
    void destroy(Node* node) {
        if(node == nullptr) {
            return;
        }
        
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public: 
    BinaryTree() : root(nullptr) {}
    
    ~BinaryTree() {
        destroy(root); 
    }

    void insert(int data) {
        root = insert_recursive(root, data); 
    }

    bool search(int data) const {
        return search_recursive(root, data); 
    }
};

auto main() -> int {
    BinaryTree tree;
    
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    
    if (tree.search(4)) {
        std::cout << "Found 4 in the tree\n";
    }
    
    if (!tree.search(10)) {
        std::cout << "10 not found in the tree\n";
    }
    
    return 0;
}
