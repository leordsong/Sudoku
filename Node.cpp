#include "Node.h"

using namespace std;

Node::Node(int newX, int newY, int newValues[9], int newLength)
{
    x = newX;
    y = newY;
    next = nullptr;
    length = newLength;
    values = new int[length];
    int j = 0;
    for (int i = 0; i < 9; i++)
    {
        if (newValues[i] > 0)
        {
            values[j] = newValues[i];
            j++;
        }
    }
};

Node::~Node()
{
    delete values;
};

int Node::getX()
{
    return x;
}

int Node::getY()
{
    return y;
}

int* Node::getValues()
{
    return values;
}

void Node::setNext(Node* newNext)
{
    next = newNext;
}

Node* Node::getNext()
{
    return next;
}

int Node::getSize()
{
    return length;
}

void Node::print()
{
    cout << '(' << x << ", " << y << ", [";
    int* next = values;
    for (int i = 0; i < length; i++) {
        if (next != values) cout << ", ";
        cout << *next;
        next = next + 1;
    }
    cout << "])";
}

NodeContainer::NodeContainer(Node* newHead): head(newHead) {};

NodeContainer::~NodeContainer()
{
    Node* next = head;
    while (next) {
        head = next->getNext();
        delete next;
        next = head;
    }
}

Node* NodeContainer::getHead()
{
    return head;
}

bool NodeContainer::isEmpty()
{
    return head == nullptr;
}

void NodeContainer::add(Node* newOne)
{
    if (!newOne) return;
    if (!head || newOne->getSize() <= head->getSize()) {
        newOne->setNext(head);
        head = newOne;
        return;
    }
    Node* parent = head;
    Node* next = parent->getNext();
    while (next != nullptr && next->getSize() < newOne->getSize()) {
        parent = next;
        next = next->getNext();
    }
    parent->setNext(newOne);
    newOne->setNext(next);
}

void NodeContainer::print()
{
    Node* next = head;
    while (next) {
        next->print();
        cout << "->";
        next = next->getNext();
    }
    cout << "NULL" << endl;
}

Node* NodeContainer::pop()
{
    Node* next = head;
    if (next) {
        head = next->getNext();
        next->setNext(nullptr);
    }
    return next;
}

Node* NodeContainer::popAt(int x, int y)
{
    Node* next = head;
    if (next && next->getX() == x && next->getY() == y)
    {
        head = next->getNext();
        next->setNext(nullptr);
        return next;
    }

    Node* prev = nullptr;
    while (next && (next->getX() != x || next->getY() != y))
    {
        prev = next;
        next = next->getNext();
    }

    if (prev && next)
    {
        prev->setNext(next->getNext());
        next->setNext(nullptr);
        return next;
    }
    return nullptr;
}


