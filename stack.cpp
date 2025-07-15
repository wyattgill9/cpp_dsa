#include <iostream>


class Stack {
private:
    struct Node {
        int data;
        Node* next;
    };
    
    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) pop(); 
    }

    void push(int value) {
        Node* new_node = new Node {value, top}; 
        top = new_node;
    }

    void pop() {
        if (isEmpty()) return;
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    int peek() {
        if (isEmpty()) return -1;
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

auto main() -> int {
    Stack s;
    
    s.push(1);
    s.push(2);

    return 0;
}
