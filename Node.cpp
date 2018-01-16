#include <iostream>

using namespace std;

struct Node
{
  int data;
};

int main() {
  int values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Node *node = new Node;
  node->data = 1;
  cout << node->data << endl;
}
