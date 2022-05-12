#pragma
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include "stack.h"

struct Cell** genMaze(int height, int width, int SEED, char WALL_SYMBOL);

int removeTop(struct Cell* cell, struct Cell** cellMatrix);

int removeRight(struct Cell* cell, int width, struct Cell** cellMatrix);

int removeBottom(struct Cell* cell, int height, struct Cell** cellMatrix);

int removeLeft(struct Cell* cell, struct Cell** cellMatrix);

void printCell(int x,int y, struct Cell** cellMatrix, int height, int width);

void reinterpritMaze(char sym, int height, int width, struct Cell** cellMatrix);
