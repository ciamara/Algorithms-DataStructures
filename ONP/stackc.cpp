#include "stackc.h"

void StackC::push(const char& data) {
    Node* newNode = new Node(data);
    newNode->next = topNode;
    topNode = newNode;
}

char StackC::pop() {
    if (!isEmpty()) {
        Node* temp = topNode;
        char poppedElement = topNode->data;
        topNode = topNode->next;
        delete temp;
        return poppedElement;
    } else {
        return 0;
    }
}

char StackC::top() const {
    if (!isEmpty()) {
        return topNode->data;
    } else {
        return 0;
    }
}

bool StackC::isEmpty() const {
    return topNode == nullptr;
}