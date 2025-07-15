#include <iostream>

struct Node {
    int data;
    Node* next;
};

struct LinkedList {
    Node* head;
    Node* tail;

    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    ~LinkedList() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    void append(int value) {
        Node* new_node = new Node();
        new_node->data = value;
        new_node->next = nullptr;

        if (head == nullptr) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    
    void pop() {
        if (head == nullptr) {
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }
};

auto main() -> int {
    LinkedList list;
    
    list.append(1);
    list.append(2);
    list.append(3);
    list.pop();

    return 0;
}
