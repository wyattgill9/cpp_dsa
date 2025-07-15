class Queue {
private:
    struct Node {
        int data;
        Node* next;
        Node(int data) : data(data), next(nullptr) {} 
    };

    Node* head;
    Node* tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}

    ~Queue() {
        while(!isEmpty()) dequeue();
    }

    void enqueue(int value) {
        Node* new_node = new Node(value);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    void dequeue() {
        if (isEmpty()) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    int peek() {
        if (isEmpty()) return -1;
        return head->data; 
    }

    bool isEmpty() {
        return head == nullptr;
    }
};

auto main() -> int {
    Queue q;
    
    q.enqueue(1);
    q.enqueue(2);

    return 0;
}
