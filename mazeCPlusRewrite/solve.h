
#include <stdlib.h>
#include <fstream>

void allocateMaze(char ** maze, int rows, int cols);

void allocateMazeCP(int** mazeCP, int rows, int cols);

int dfs(int row, int col, int** mazeCP);

void getData(char** maze, int** mazeCP, int* y, int* x);

