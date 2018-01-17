#include "Node.h"
#include "utilities.h"

using namespace std;

bool isProper(int puzzle[N][N], Node* head, int x, int y, int value) {
    puzzle[x][y] = value;
    int solutions[N] = {};
    int length = 0;
    while (head) {
        length = getSolutions(puzzle, head->getX(), head->getY(), solutions);
        if (length == 0) {
            puzzle[x][y] = 0;
            return false;
        }
        head = head->getNext();
    }
    puzzle[x][y] = 0;
    return true;
}

int main() {
    int puzzle[N][N] = { };
	string fileName;

	// read
	cout << "Welcome to Sudoku!" << endl;
	cout << "Enter file name: ";
	getline (cin, fileName);
	fillNineNinePuzzle(fileName, puzzle);
	printPuzzle(puzzle);
	cout << endl;

    // traverse tree
    int length = 0;
    int solutions[N] = {};
    NodeContainer* container = new NodeContainer(nullptr);
    for (int x = 0, y = 0; x != 8 || y != 8; next(&x, &y)) {
        if (puzzle[x][y] == 0) {
            length = getSolutions(puzzle, x, y, solutions);
            container->add(new Node(x, y, solutions, length));
        }
    }

    // solve
    Node* node = nullptr;
    NodeContainer* old = nullptr;
    while (!container->isEmpty()) {
        node = container->pop();
        if (node->getSize() == 1) {
            puzzle[node->getX()][node->getY()] = node->getValues()[0];
        } else {
            bool success = false;
            for (int i = 0; i < node->getSize() && !success; i++) {
                if (isProper(puzzle, container->getHead(), node->getX(), node->getY(), node->getValues()[i])) {
                    success = true;
                    puzzle[node->getX()][node->getY()] = node->getValues()[i];
                }
            }
            if (!success) {
                old = new NodeContainer(nullptr);
                while (!success && !container->isEmpty())
                {
                    // TODO bad guess
                    old->add(node);
                    node = container->pop();
                    for (int i = 0; i < node->getSize() && !success; i++) {
                        if (isProper(puzzle, container->getHead(), node->getX(), node->getY(), node->getValues()[i]) &&
                            isProper(puzzle, old->getHead(), node->getX(), node->getY(), node->getValues()[i])) {
                            success = true;
                            puzzle[node->getX()][node->getY()] = node->getValues()[i];
                        }
                    }
                }
                
                while (!old->isEmpty())
                {
                    container->add(old->pop());
                }
                delete old;
                
                if (!success)
                    break;
            }
            
        }
        delete node;
        old = container;
        container = new NodeContainer(nullptr);
        while (!old->isEmpty()) {
            node = old->pop();
            length = getSolutions(puzzle, node->getX(), node->getY(), solutions);
            container->add(new Node(node->getX(), node->getY(), solutions, length));
            delete node;
        }
        delete old;
    }

    // print solution
    if (container->isEmpty()) {
        cout << "Success!" << endl;
    } else {
        cout << "Fail." << endl;
    }
    printPuzzle(puzzle);

    delete container;
    return 0;
}
