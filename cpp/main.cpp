#include "solver.h"
#include "utilities.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
    int puzzle[N][N] = { };
	string fileName;

	// read
	cout << "Welcome to Sudoku solver!" << endl;
	cout << "Enter file name: ";
	getline (cin, fileName);
	fillNineNinePuzzle(fileName, puzzle);
	printPuzzle(puzzle);
	cout << endl;

    // print solution
    if (solve(puzzle)) {
        cout << "Success!" << endl;
    } else {
        cout << "Fail." << endl;
    }
    printPuzzle(puzzle);
    return 0;
}
