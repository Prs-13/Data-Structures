#include <iostream>
using namespace std;


struct node {
    int data;
    node* next;
};

class Queue {
private:
    node* first;
    node* last;

public:
    Queue() {
        first = nullptr;
        last = nullptr;
    }

    void push(int value) {
        node* newNode = new node();
        if (first == nullptr)
            first = newNode;
        newNode->data = value;
        newNode->next = nullptr;
        if (last == nullptr)
            first = last = newNode;
        else {
            last->next = newNode;
            last = newNode;        
        }
    }

    void pop() {
        if (first == nullptr) {
            cout << "queue underflow\n";
            return;
        }
        node* temp = first;
        first = first->next;
        delete temp;
        if (first == nullptr)
            last = first;
    }
};


