#include <vector>
#include <algorithm>
#include <exception>

template <typename T>
class MinHeap {
private:
    std::vector<T> heap;
    
    size_t get_parent(size_t i) { // get parent index
        return (i - 1) / 2;
    }
    
    void heapify_down(size_t i) {
        size_t smallest = i; // inits smallest element as the current index
        size_t left = 2 * i + 1; // left child
        size_t right = 2 * i + 2; // right child
        
        // check if left child is smaller than smallest and that it exists
        if(left < heap.size() && heap[left] < heap[smallest]) {
            smallest = left;
        }
        
        if(right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }
        
        // if the smallest element is not the original node, we swap
        if(smallest != i) {
            std::swap(heap[i], heap[smallest]);

            // recursively heapify down as the element we 
            // just moved down might still violate the heap property 
            heapify_down(smallest);
        }
    }
    
    // inverse of heapify down 
    void heapify_up(size_t i) {
        while(i > 0 && heap[get_parent(i)] > heap[i]) {
            std::swap(heap[i], heap[get_parent(i)]); // move smaller element up a level in the tree
            i = get_parent(i);
        }
    }

public:
    MinHeap() = default;

    // constructor, create heap from vector
    MinHeap(const std::vector<T>& vec) {
        heap = vec;
        make_heap(heap);
    }

    // floyds algorithm 
    void make_heap(std::vector<T>& vec) {
        heap = vec;
        
        // start from the last non-leaf node and heapify down
        for(int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapify_down(i);
        }
    }

    void push(const T& val) {
        heap.push_back(val);
        heapify_up(heap.size() - 1);
    }

    T pop() {
        T val = heap[0];
        
        // move last element to root and remove last element
        heap[0] = heap.back(); 
        heap.pop_back();
        
        // restore heap property 
        if(!heap.empty()) {
            heapify_down(0);
        }
        
        return val;
    }

    const T& top() const {
        if(heap.empty()) {
            throw std::runtime_error("heap is empty");
        }
        return heap[0];
    }
    
    bool empty() {
        return heap.empty();
    }

    size_t size() {
        return heap.size();
    }

    const std::vector<T>& get_heap() const {
        return heap; 
    }
};

auto main() -> int {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    MinHeap<int> min_heap(vec);
    
    return 0;
}
