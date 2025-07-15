#include <iostream>
#include <memory>

template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left; 
        std::unique_ptr<Node> right;
        int height; 

        Node(T data) : data(data), height(0) {}
    };

    std::unique_ptr<Node<T>> root;

    int get_balance(const std::unique_ptr<Node<T>>& node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    int height(const std::unique_ptr<Node<T>>& node) {
        return node ? node->height : 0; 
    }

    void update_height(std::unique_ptr<Node<T>>& node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

public:
    AVLTree(T data) : root{std::make_unique<Node<T>>(data)} {};

    ~AVLTree();
    
    void insert(T data) {
        root = insert_recursive(root, data);
    }   
    
};

auto main() -> int {
    AVLTree<int> tree;
    
    tree.insert(5);

    return 0;
}

