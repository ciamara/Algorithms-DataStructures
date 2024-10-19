#include "stacki.h"
#include <iostream>

void StackI::push(const int& data) {
    Node* newNode = new Node(data);
    newNode->next = topNode;
    topNode = newNode;
}

int StackI::pop() {
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

int StackI::top() const {
    if (!isEmpty()) {
        return topNode->data;
    } else {
        return 0;
    }
}

void StackI::print() const {
    Node* current = topNode;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
}

bool StackI::isEmpty() const {
    return topNode == nullptr;
}