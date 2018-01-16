#include <iostream>
#include <fstream>

#define N 9

void fillNineNinePuzzle(std::string fileName, int puzzle[N][N]);
void printPuzzle(int puzzle[N][N]);
void next(int* x, int* y);
int getSolutions(int puzzle[N][N], int x, int y, int solutions[N]);
