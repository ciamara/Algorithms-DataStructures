#pragma once

class Stack {
private:
    struct Node {
        int data;
        Node* next;
        Node(const int& data) : data(data), next(nullptr) {}
    };

    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const int& data);

    int pop();

    int top() const;

    void print() const;

    bool isEmpty() const;
};