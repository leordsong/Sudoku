#include <iostream>
#include <fstream>

using namespace std;

#define N 9

//====== Function Declaration ======//

void fillNineNinePuzzle(string fileName, int puzzle[N][N]);
void printPuzzle(int puzzle[N][N]);
void next(int *x, int *y);
bool getNext(int puzzle[N][N], int *x, int *y);
bool solve(int puzzle[N][N], const int x, const int y);

//====== Main ======//

int main()
{
	int puzzle[N][N] = { 0 };
	string fileName;

	// read
	cout << "Welcome to Sudoku!" << endl;
	cout << "Enter file name: ";
	getline (cin, fileName);
	fillNineNinePuzzle(fileName, puzzle);
	printPuzzle(puzzle);
	cout << endl;

	// solve
	int x = 0, y = 0, count = 0;
	while (getNext(puzzle, &x, &y) && (count++ < 1000))
	{
		if (!solve(puzzle, x, y)) next(&x, &y);
	}

	// end
	if (getNext(puzzle, &x, &y)) cout << "Fail!" << endl;
	else cout << "Success!" << endl;
	printPuzzle(puzzle);
	return 0;
}

//====== Function Body ======//

/**
 * Read sudouku from given file
 * @param fileName the name of file to open
 * @param puzzle a two dimentional array that reprensents a sudouku
 */
void fillNineNinePuzzle(string fileName, int puzzle[N][N])
{
	ifstream infile(fileName + ".txt");
	int i = 0;
	while (infile
		>> puzzle[i][0] >> puzzle[i][1] >> puzzle[i][2]
		>> puzzle[i][3] >> puzzle[i][4] >> puzzle[i][5]
		>> puzzle[i][6] >> puzzle[i][7] >> puzzle[i][8]
		&& ++i < N) ;
}

void printPuzzle(int puzzle[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << puzzle[i][j] << " ";
		}
		cout << endl;
	}
}

void next(int *x, int *y)
{
	if (*y == N - 1)
	{
		*y = 0;
		*x = (*x == N - 1) ? 0 : *x + 1;
	}
	else
	{
		*y = *y + 1;
	}
}

bool getNext(int puzzle[N][N], int *x, int *y)
{
	int init_x = *x, init_y = *y;
	while (puzzle[*x][*y] != 0)
	{
		next(x, y);
		if (init_x == *x && init_y == *y) return false;
	}
	return true;
}

bool solve(int puzzle[N][N], const int x, const int y) {
	if (puzzle[x][y] != 0) return true;

	int result[N] = { 0 };
	for (int i = 0; i < N; i++) result[i] = i + 1;

	// row
	for (int i = 0; i < N; i++)
	{
		int value = puzzle[x][i];
		if (value != 0) result[value - 1] = 0;
	}

	// column
	for (int j = 0; j < N; j++)
	{
		int value = puzzle[j][y];
		if (value != 0) result[value - 1] = 0;
	}
	
	// area
	int row = x / 3;
	row = row * 3;
	int column = y / 3;
	column = column * 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int value = puzzle[row + i][column + j];
			if (value != 0) result[value - 1] = 0;
		}
	}

	int count = 0;
	for (int i = 0; i < N; i++)
	{
		if (result[i] != 0) count++;
		if (count > 1) return false;
	}

	for (int i = 0; i < N; i++)
	{
		int value = result[i];
		if (value != 0)
		{
			puzzle[x][y] = value;
			return true;
		}
	}
	return false;
}
