#include "Node.h"
#include "utilities.h"

using namespace std;

void updateTree(int puzzle[N][N], NodeContainer* container) {
    NodeContainer* newContainer = new NodeContainer(nullptr);
    Node* node = nullptr;
    int length = 0;
    int solutions[N] = {};
    while (!container->isEmpty()) newContainer->add(container->pop());
    while (!newContainer->isEmpty())
    {
        node = newContainer->pop();
        length = getSolutions(puzzle, node->getX(), node->getY(), solutions);
        container->add(new Node(node->getX(), node->getY(), solutions, length));
        delete node;
    }
}

int isHiddenSingle(Node* node, NodeContainer* container) {
    for (int i = 0; i < node->getSize(); i++)
    {
        int value = node->getValues()[i];
        // if in row, return i
        bool success = true;
        for (int j = 0; j < N && success; j++)
        {
            Node* temp = container->popAt(node->getX(), j);
            if (temp)
            {
                for (int k = 0; k < temp->getSize() && success; k++)
                {
                    if (temp->getValues()[k] == value) success = false;
                }
                container->add(temp);
            }
        }
        if (success)
            return i;
        // if in column, return i
        success = true;
        for (int j = 0; j < N && success; j++)
        {
            Node* temp = container->popAt(j, node->getY());
            if (temp)
            {
                for (int k = 0; k < temp->getSize() && success; k++)
                {
                    if (temp->getValues()[k] == value) success = false;
                }
                container->add(temp);
            }
        }
        if (success)
            return i;
        // if in area, return i
        success = true;
        int row = node->getX() / 3;
        row = row * 3;
        int column = node->getY() / 3;
        column = column * 3;
        for (int j = 0; j < 3 && success; j++)
        {
            for (int k = 0; k < 3 && success; k++)
            {
                Node* temp = container->popAt(row + j, column + k);
                if (temp)
                {
                    for (int k = 0; k < temp->getSize() && success; k++)
                    {
                        if (temp->getValues()[k] == value) success = false;
                    }
                    container->add(temp);
                }
            }
        }
        if (success)
            return i;
    }
    return -1;
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
    for (int x = 0, y = 0; x < 9; next(&x, &y))
    {
        if (puzzle[x][y] == 0)
        {
            length = getSolutions(puzzle, x, y, solutions);
            container->add(new Node(x, y, solutions, length));
        }
    }
    
    // solve
    Node* node = nullptr;
    bool success = false;
    while (!container->isEmpty())
    {
        // naked single
        if (container->getHead()->getSize() == 1)
        {
            node = container->pop();
            puzzle[node->getX()][node->getY()] = node->getValues()[0];
            delete node;
            updateTree(puzzle, container);
            continue;
        }
        // hidden single
        success = false;
        for(int i = 0; i < N && !success; i++)
        {
            for (int j = 0; j < N && !success; j++)
            {
                if (puzzle[i][j] == 0)
                {
                    node = container->popAt(i, j);
                    int index = isHiddenSingle(node, container);
                    if (index > -1)
                    {
                        puzzle[node->getX()][node->getY()] = node->getValues()[index];
                        delete node;
                        updateTree(puzzle, container);
                        success = true;
                    }
                    else
                    {
                        container->add(node);
                    }
                }
            }
        }
        if (success) continue;
        else break;

    }

    // print solution
    if (container->isEmpty()) {
        cout << "Success!" << endl;
    } else {
        cout << "Fail." << endl;
        container->print();
    }
    printPuzzle(puzzle);

    delete container;
    return 0;
}
