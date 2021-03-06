#ifndef N
#define N 9
#endif

class Node {
    int x;
    int y;
    int* values;
    int length;
    Node* next;
public:
    Node(int newX, int newY, int newValues[N], int length);
    ~Node();
    int getX();
    int getY();
    int* getValues();
    void setNext(Node* newNext);
    Node* getNext();
    int getSize();
    void print();
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
    Node* popAt(int x, int y);
};
