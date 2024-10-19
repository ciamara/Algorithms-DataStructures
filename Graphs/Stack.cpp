#include "Stack.h"
#include <iostream>

void Stack::push(const int& data) {
    Node* newNode = new Node(data);
    newNode->next = topNode;
    topNode = newNode;
}

int Stack::pop() {
    if (!isEmpty()) {
        Node* temp = topNode;
        int poppedElement = topNode->data;
        topNode = topNode->next;
        delete temp;
        return poppedElement;
    } else {
        return 0;
    }
}

int Stack::top() const {
    if (!isEmpty()) {
        return topNode->data;
    } else {
        return 0;
    }
}

void Stack::print() const {
    Node* current = topNode;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
}

bool Stack::isEmpty() const {
    return topNode == nullptr;
}