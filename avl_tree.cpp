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
        Node(Node&& other) = default;
    };

    std::unique_ptr<Node> root;

    int get_height(const std::unique_ptr<Node>& node) {
        return node ? node->height : 0;
    }

    int get_balance(const std::unique_ptr<Node>& node) {
        return node ? get_height(node->left) - get_height(node->right) : 0;
    }

    void update_height(std::unique_ptr<Node>& node) {
        if(node) {
            node->height = 1 + std::max(get_height(node->left), get_height(node->right));
        }
    }

    std::unique_ptr<Node> rotate_left(std::unique_ptr<Node> a) {
        std::unique_ptr<Node> b = std::move(a->right);
        a->right = std::move(b->left);
        b->left = std::move(a);

        update_height(a);
        update_height(b);

        return b;
    }

    std::unique_ptr<Node> rotate_right(std::unique_ptr<Node> a) {
        std::unique_ptr<Node> b = std::move(a->left);
        a->left = std::move(b->right);
        b->right = std::move(a);                

        update_height(b->right);
        update_height(b);

        return b;
    }

    std::unique_ptr<Node> insert(std::unique_ptr<Node>& node, T data) {
        if(node == nullptr) {
            return std::make_unique<Node>(data);
        }

        if(data < node->data) {
            node->left = insert(node->left, data);
        } else {
            node->right = insert(node->right, data);
        }

        update_height(node);
        int bal_factor = get_balance(node);

        // left-left
        if (bal_factor > 1 && data < node->left->data) return rotate_right(std::move(node));
        // right-right
        if (bal_factor < -1 && data > node->right->data) return rotate_left(std::move(node));

        // left-right
        if (bal_factor > 1 && data > node->left->data) {
            node->left = rotate_left(std::move(node->left));
            return rotate_right(std::move(node));
        }

        // right-left
        if (data < -1 && data < node->right->data) {
            node->right = rotate_right(std::move(node->right));
            return rotate_left(std::move(node));
        }    

        return std::move(node);
    }

    std::unique_ptr<Node> delete_node(std::unique_ptr<Node>&& node, T data) {
        if(!node) return nullptr;

        if(data < node->data) {
            node->left = delete_node(std::move(node->left), data);
            return node;
        } else if(data > node->data) {
            node->right = delete_node(std::move(node->right), data);
            return node;
        }
    
        // node found -> deletion cases
        if(!node->left) return std::move(node->right);
        if(!node->right) return std::move(node->left);
    
        // 2 children -> find rightmost in left subtree
        auto* pred = node->left.get();
        while(pred->right) pred = pred->right.get();
    
        // swap data && delete pred
        node->data = pred->data;
        node->left = delete_node(std::move(node->left), pred->data);
    
        return node;
    }

    bool search(std::unique_ptr<Node>& node, T data) {
        if(!node) {
            return false;
        }

        if(data < node->data) {
            return search(node->left, data);
        } else if(data > node-> data) {
            return search(node->right, data);
        } else {
            return true;
        }
    }

public:
    AVLTree() = default;
    AVLTree(T data) : root { std::make_unique<Node>(data) } {};

    ~AVLTree() = default;
    
    void insert(T key) { root = insert(root, key); }
    void remove(T key) { root = delete_node(std::move(root), key);}
    bool search(T key) { return search(root, key); }
};

auto main() -> int {
    AVLTree<int> tree;
    
    tree.insert(5);
    tree.insert(10);
    tree.insert(100);
    tree.remove(100);

    return 0;
}
