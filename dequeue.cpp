#include <iostream>

template <typename T>
class Dequeue {
private:
    static constexpr size_t BLOCK_SIZE = 512;
 
    struct Block {
        T data[BLOCK_SIZE];
    };

    Block* blocks; // pointer to a struct of type T
    size_t num_blocks;
    size_t capacity; 

    size_t num_elements;
   
public:
    Dequeue() : blocks(nullptr), num_blocks(0), capacity(0), num_elements(0) {
        blocks = new T[1];  
    }
    
    ~Dequeue() {
    }

    void push_back(T value) {
        if(num_elements == 0) {
            alloc_block(0);
            blocks[0][0] = value;
            num_elements++;
        } else {


            num_elements++;
        }
        
    }

    void push_front() {} 

    void pop_back() {}
    
    void pop_front() {}

    T& front() {}

    T& back() {}

    T& at(size_t index) {}

    bool empty() {}
    
    size_t size() {}
    
    void clear() {}

    void erase(size_t index) {}
};


auto main() -> int {
    return 0;
}
