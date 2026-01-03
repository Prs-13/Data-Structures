#include <iostream>
using namespace std;


struct node {
    int data;
    node* next;
};

class Stack {
private:
    node* top;

public:
    Stack() {
        top = nullptr;
    }

    void push(int value) {
        node* newNode = new node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top == nullptr) {
            cout << "Stack underflow\n";
            return;
        }
        node* temp = top;
        top = top->next;
        delete temp;
    }
};


