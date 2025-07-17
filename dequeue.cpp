#include <cstddef>
#include <new>
#include <type_traits>
#include <vector>
#include <stdexcept>
#include <iostream>

// static_vector C++26
template<class T, std::size_t N>
class static_vector
{
    std::aligned_storage_t<sizeof(T), alignof(T)> data[N];
    std::size_t m_size = 0;
    std::size_t start_idx = 0;
 
public:
    static_vector() = default;
    
    template<typename ...Args> 
    void emplace_back(Args&&... args) {
        if (m_size >= N) 
            throw std::bad_alloc{};
 
        std::size_t back_idx = (start_idx + m_size) % N;
        ::new(&data[back_idx]) T(std::forward<Args>(args)...);
        ++m_size;
    }
    
    template<typename ...Args> 
    void emplace_front(Args&&... args) {
        if (m_size >= N) 
            throw std::bad_alloc{};
        
        start_idx = (start_idx - 1 + N) % N;
        ::new(&data[start_idx]) T(std::forward<Args>(args)...);
        ++m_size;
    }
 
    const T& operator[](std::size_t pos) const {
        std::size_t actual_idx = (start_idx + pos) % N;
        return *std::launder(reinterpret_cast<const T*>(&data[actual_idx]));
    }
    
    T& operator[](std::size_t pos) {
        std::size_t actual_idx = (start_idx + pos) % N;
        return *std::launder(reinterpret_cast<T*>(&data[actual_idx]));
    }
    
    void pop_back() {
        if (m_size > 0) {
            --m_size;
            std::size_t back_idx = (start_idx + m_size) % N;
            std::destroy_at(std::launder(reinterpret_cast<T*>(&data[back_idx])));
        }
    }
    
    void pop_front() {
        if (m_size > 0) {
            std::destroy_at(std::launder(reinterpret_cast<T*>(&data[start_idx])));
            start_idx = (start_idx + 1) % N;
            --m_size;
        }
    }
    
    std::size_t size() const { 
        return m_size; 
    }
    
    bool empty() const { 
        return m_size == 0; 
    }
    
    ~static_vector() {
        for (std::size_t i = 0; i < m_size; ++i) {
            std::size_t actual_idx = (start_idx + i) % N;
            std::destroy_at(std::launder(reinterpret_cast<T*>(&data[actual_idx])));
        }
    }
};

// Dequeue impl
template <typename T>
class Dequeue {
private:
    static constexpr size_t BLOCK_SIZE = 512;
    
    std::vector<static_vector<T, BLOCK_SIZE>> blocks;
    
    size_t num_elements = 0;
     
public:
    Dequeue() = default; 
    
    ~Dequeue() = default;
    
    void push_back(T value) {
        if (blocks.empty() || blocks.back().size() == BLOCK_SIZE) {
            blocks.emplace_back();
        }
        blocks.back().emplace_back(std::move(value));
        ++num_elements;
    }
    
    void push_front(T value) {
        if (blocks.empty() || blocks.front().size() == BLOCK_SIZE) {
            blocks.emplace(blocks.begin());
        }
        blocks.front().emplace_front(std::move(value));
        ++num_elements;
    } 
    
    void pop_back() {
        if(empty()) return;
        
        blocks.back().pop_back();
        --num_elements;
        if (blocks.back().empty() && blocks.size() > 1) {
            blocks.pop_back();
        }
    }
    
    void pop_front() {
        if (empty()) return;
        
        blocks.front().pop_front();
        --num_elements;
        
        if (blocks.front().empty() && blocks.size() > 1) {
            blocks.erase(blocks.begin());
        }
    }
    
    T& front() {
        if(empty()) throw std::runtime_error("Deque is empty");
        return blocks.front()[0];
    }
    
    T& back() {
        if(empty()) throw std::runtime_error("Deque is empty");
        return blocks.back()[blocks.back().size() - 1];
    }
    
    T& at(size_t index) {
        if(index >= num_elements) throw std::runtime_error("Index out of range");
        
        size_t current_index = 0;
        for (auto& block : blocks) {
            if (current_index + block.size() > index) {
                return block[index - current_index];
            }
            current_index += block.size();
        }
        throw std::runtime_error("Index out of range");
    }
    
    bool empty() const {
        return num_elements == 0;
    }
    
    size_t size() const {
        return num_elements;
    }
    
    void clear() {
        blocks.clear();
        num_elements = 0;
    }
};

auto main() -> int {
    Dequeue<int> dq;

    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.push_back(4);
    dq.push_back(5);
    dq.push_back(6);
    dq.push_back(7);
    dq.push_back(8);
    dq.push_back(9);
    dq.push_back(10);
    
    std::cout << "Element at index 4: " << dq.at(4) << '\n';

    return 0;
}
