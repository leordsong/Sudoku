#include <iostream>
#include <string>

class Node {
    int x;
    int y;
    int* values;
    int length;
    Node* next;
public:
    Node(int newX, int newY, int newValues[9], int length);
    ~Node();
    int getX();
    int getY();
    int* getValues();
    void setNext(Node* newNext);
    Node* getNext();
    int getSize();
    std::string toString();
};

class NodeContainer {
    Node* head;
public:
    NodeContainer(Node *newHead);
    ~NodeContainer();
    Node* getHead();
    void add(Node* newOne);
    bool isEmpty();
    void print();
    Node* pop();
};
