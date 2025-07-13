#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
    
    Node(T d) {
        data = d;
        next = prev = nullptr;
    }
};

template <typename T>
class DoubleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    
    int total_size;

public:
    DoubleLinkedList() {
        head = tail = nullptr;
        total_size = 0;
    }
    
    ~DoubleLinkedList() {
        Node<T>* curr = head;
        while (curr != nullptr) {
            Node<T>* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    DoubleLinkedList(const DoubleLinkedList&) = delete; 
    DoubleLinkedList& operator=(const DoubleLinkedList&) = delete; 


    void append(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        total_size++;
    }

    void prepend(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            head->prev = new_node;
            new_node->next = head;
            head = new_node;
        }            
        total_size++; 
    } 
    
    void pop_front() {
        if (head == nullptr) {
            return;
        }
        Node<T>* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        total_size--;
    }

    void pop_back() {
        if (tail == nullptr) {
            return;
        }
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        total_size--;
    }

    bool empty() const {
        return total_size == 0;
    }
    
    int size() const {
        return total_size;
    }

    void print() const {
        Node<T>* curr = head;
        while (curr != nullptr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << "\n";
    }
};

auto main() -> int {
    DoubleLinkedList<int> dll;
    
    dll.append(1);
    dll.append(2);
    dll.append(3);
    dll.append(4);
    dll.prepend(0);
    dll.pop_front();
    dll.pop_back();
    
    dll.print(); // 1 2 3
    return 0;
}
