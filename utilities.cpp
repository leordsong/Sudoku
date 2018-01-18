#include "utilities.h"

using namespace std;

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
		*x = *x + 1;
	}
	else
	{
		*y = *y + 1;
	}
}

void cleanSolutions(int solutions[N])
{
    for (int i = 0; i < N; i++) {
        solutions[N] = 0;
    }
}

int getSolutions(int puzzle[N][N], int x, int y, int solutions[N])
{
    int length = N;

    for (int i = 0; i < N; i++) solutions[i] = i + 1;

    // row
	for (int i = 0; i < N; i++)
	{
		int value = puzzle[x][i];
		if (value != 0 && solutions[value - 1] != 0)
        {
            solutions[value - 1] = 0;
            length--;
		}
	}

	// column
	for (int j = 0; j < N; j++)
	{
		int value = puzzle[j][y];
		if (value != 0 && solutions[value - 1] != 0)
        {
            solutions[value - 1] = 0;
            length--;
		}
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
			if (value != 0 && solutions[value - 1] != 0)
            {
                solutions[value - 1] = 0;
                length--;
            }
		}
	}

    return length;
}


