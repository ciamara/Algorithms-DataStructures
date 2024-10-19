#pragma once

class StackC {
private:
    struct Node {
        char data;
        Node* next;
        Node(const char& data) : data(data), next(nullptr) {}
    };

    Node* topNode;

public:
    StackC() : topNode(nullptr) {}

    ~StackC() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const char& data);

    char pop();

    char top() const;

    bool isEmpty() const;
};

