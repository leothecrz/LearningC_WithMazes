
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

char** maze;
int** mazeCP;

int rows;
int cols;

int yStart;
int xStart;

int SIZE_INPUT_MAX_LENGTH;
char crumbSym;
char wallSym;

enum terrain {
	empty,
	wall,
	goal,
	crumb
};

int main(void){

	SIZE_INPUT_MAX_LENGTH = 4;
	crumbSym = '.';

	getMaze("map.txt");

	dfs(yStart, xStart);
	addCrumbs();

	printMaze();

	return 0;
}

void allocateMaze(){
	maze = malloc( rows * sizeof(char*));
	for(int i=0; i< rows; i++){
		maze[i]= malloc( cols * sizeof(char*));
	}
}

void allocateMazeCP(){
	mazeCP = malloc( rows * sizeof(int*));
	for(int i=0; i< rows; i++){
		mazeCP[i]= malloc( cols * sizeof(int*));
	}
}

void getMaze(char* mapfile){
	
	char c;

	char stringRows[SIZE_INPUT_MAX_LENGTH];
	char stringCols[SIZE_INPUT_MAX_LENGTH];
	int r_i = 0;
	int c_i = 0;

	FILE* file = fopen(mapfile, "r");
	if (file){
		
		int flag = 0;
		while( (c = getc(file)) != EOF) {
			if( c == '\n'){
				break;
			} else if ( c == ','){
				flag = 1;		
			} else if (!flag){
				stringRows[r_i] = c;
				r_i++;
			} else {
				stringCols[c_i] = c;
				c_i++;
			}
		}
	}
	rows = atoi(stringRows);
	cols = atoi(stringCols);

	allocateMaze();
	int gotWalls = 0;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			c = getc(file);
			
			if ( c == '\n' ){
				c = getc(file);
			} 
			if ( c == 's' || c == 'S'){
				yStart = i;
				xStart = j;
			} else if ( (!gotWalls) &&(c != ' ') && (c != 'g') ){
				gotWalls = 1;
				wallSym = c;
			}

			maze[i][j] = c;
		}
	}

	fclose(file);

	allocateMazeCP();

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
		
			char terrain = maze[i][j];
			if(terrain == wallSym){
				mazeCP[i][j] = wall;
			} else if (terrain == 'g'){
				mazeCP[i][j] = goal;
			} else {
				mazeCP[i][j] = empty;
			}
		}
	}
}

void printMaze(){
	
	printf("\nROWS: %d, COLS:%d \n",rows, cols);

	for(int i=0;i<rows;i++){
		for (int j=0;j<cols;j++){
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}

	printf(" X-START: %d, Y-START: %d\n", xStart, yStart); 
}

void printMazeCP(){
	
	printf("\n");
	for(int i=0;i<rows;i++){
		for (int j=0;j<cols;j++){
			if(mazeCP[i][j] == 1){
				printf("0 ");
			} else if (mazeCP[i][j] == 0){
				printf("1 ");
			} else {
				printf("%d ", mazeCP[i][j]);

			}
			//printf("%d ", mazeCP[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int dfs(int row, int col){

	int* current = &mazeCP[row][col];

	if(*current == goal)
		return 1;

	if(*current == empty) {
		*current = wall;


		if(dfs(row-1, col)){
			*current = crumb;
			return 1;
		}

		if(dfs(row, col+1)){
			*current = crumb;
			return 1;
		}

		if(dfs(row+1, col)){
			*current = crumb;
			return 1;
		}

		if(dfs(row, col-1)){
			*current = crumb;
			return 1;
		}
	}
	return 0;
}

void addCrumbs(){
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){

			if (maze[i][j] != 's'){
				if( mazeCP[i][j] == crumb ){
					maze[i][j] = crumbSym;
				}
			}
			
		}
	}
}
