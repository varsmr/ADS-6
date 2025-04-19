// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

struct SYM {
    char ch;
    int prior;
};
template<typename T>
class TPQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* head;

public:
    TPQueue() : head(nullptr) {}

    ~TPQueue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void enqueue(T item) {
        Node* newNode = new Node(item);
        if (!head || head->data.prior < item.prior) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->data.prior >= item.prior) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    T dequeue() {
        if (!head) {
            throw std::runtime_error("Queue is empty");
        }
        T item = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return item;
    }
    bool isEmpty() const {
        return head == nullptr;
    }
};

#endif  // INCLUDE_TPQUEUE_H_

