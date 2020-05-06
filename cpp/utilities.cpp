#include <fstream>
#include "utilities.h"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

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
