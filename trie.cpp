#include <array>
#include <string>

struct TrieNode {
    std::array<TrieNode*, 26> children;
    bool is_terminal = false;

    TrieNode(): children{} {}

    ~TrieNode() {
        for (TrieNode* child : children) {
            delete child;
        }
    }
};

struct Trie {
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }
    
    ~Trie() {
        delete root;
    }
    
    void insert(const std::string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
        node->is_terminal = true;
    }
     
    TrieNode* find_node(std::string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr) {
                return nullptr;
            }
            node = node->children[idx];
        }
        return node;
    } 
    
    bool is_prefix(const std::string& word) {
        TrieNode* node = root;
        for(char c : word) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr) {
                return false;
            }
            node = node->children[idx];
        }
        return true;
    }

    bool search(const std::string& word) {
        TrieNode* node = find_node(word);
        return node != nullptr && node->is_terminal;
    }
};

auto main() -> int {
    return 0;
}
